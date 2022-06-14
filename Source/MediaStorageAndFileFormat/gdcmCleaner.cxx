/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmCleaner.h"
#include "gdcmAnonymizeEvent.h"
#include "gdcmAttribute.h"
#include "gdcmCSAHeader.h"
#include "gdcmDataSetHelper.h"
#include "gdcmDicts.h"
#include "gdcmEvent.h"
#include "gdcmGlobal.h"

#include "gdcmcsa/csa.h"

namespace gdcm {

typedef std::set<DataElement> DataElementSet;
typedef DataElementSet::const_iterator ConstIterator;

struct Cleaner::impl {
  std::set<DPath> preserve_dpaths;
  std::set<DPath> empty_dpaths;
  std::set<DPath> remove_dpaths;
  std::set<DPath> wipe_dpaths;
  std::set<Tag> empty_tags;
  std::set<PrivateTag> empty_privatetags;
  std::set<Tag> remove_tags;
  std::set<PrivateTag> remove_privatetags;
  std::set<Tag> wipe_tags;
  std::set<PrivateTag> wipe_privatetags;
  std::set<VR> empty_vrs;
  std::set<VR> remove_vrs;
  bool AllMissingPrivateCreator;
  bool AllGroupLength;
  bool AllIllegal;
  impl()
      : AllMissingPrivateCreator(true),
        AllGroupLength(true),
        AllIllegal(true) {}

  enum ACTION { NONE, EMPTY, REMOVE, WIPE };
  enum ACTION ComputeAction(File const &file, DataSet &ds,
                            const DataElement &de, VR const &ref_dict_vr,
                            const std::string &tag_path);

  bool Clean(File const &file, DataSet &ds, const DataElement &de,
             VR const &ref_dict_vr, const std::string &tag_path);

  bool ProcessDataSet(File &file, DataSet &ds, const std::string &tag_path);

  template <typename T>
  bool CheckVRBeforeInsert(T const &t, std::set<T> &set) {
    if (empty_vrs.empty()) {
      set.insert(t);
      return true;
    } else {
      // Let's check if VR of tag is already contained in VR
      static const Global &g = GlobalInstance;
      static const Dicts &dicts = g.GetDicts();
      const DictEntry &entry = dicts.GetDictEntry(t);
      const VR &refvr = entry.GetVR();
      if (empty_vrs.find(refvr) != empty_vrs.end()) {
        gdcmWarningMacro(
            "Tag: " << t << " is also cleanup with VR cleaning. skipping");
      } else {
        set.insert(t);
      }
      return true;
    }
  }
  bool Empty(Tag const &t) {
    if (t.IsPublic() && !t.IsGroupLength()) {
      return CheckVRBeforeInsert(t, empty_tags);
    }
    return false;
  }
  bool Empty(PrivateTag const &pt) {
    const char *owner = pt.GetOwner();
    if (pt.IsPrivate() && *owner) {
      return CheckVRBeforeInsert(pt, empty_privatetags);
    }
    return false;
  }
  bool Empty(DPath const &dpath) {
    empty_dpaths.insert(dpath);
    return true;
  }
  bool Empty(VR const &vr) {
    if (vr == VR::PN) {
      empty_vrs.insert(vr);
      return true;
    }
    return false;
  }

  bool Remove(Tag const &t) {
    if (t.IsPublic() && !t.IsGroupLength()) {
      return CheckVRBeforeInsert(t, remove_tags);
    }
    return false;
  }
  bool Remove(PrivateTag const &pt) {
    const char *owner = pt.GetOwner();
    if (pt.IsPrivate() && *owner) {
      return CheckVRBeforeInsert(pt, remove_privatetags);
    }
    return false;
  }
  bool Remove(DPath const &dpath) {
    remove_dpaths.insert(dpath);
    return true;
  }
  bool Remove(VR const &vr) {
    if (vr == VR::PN) {
      remove_vrs.insert(vr);
      return true;
    }
    return false;
  }

  bool Wipe(Tag const &t) { return false; }
  bool Wipe(PrivateTag const &pt) {
    static const PrivateTag &csa1 = CSAHeader::GetCSAImageHeaderInfoTag();
    static const PrivateTag &csa2 = CSAHeader::GetCSASeriesHeaderInfoTag();
    if (pt == csa1 || pt == csa2) {
      wipe_privatetags.insert(pt);
      return true;
    }
    return false;
  }
  bool Wipe(DPath const &dpath) {
    wipe_dpaths.insert(dpath);
    return true;
  }

  bool Wipe(VR const &vr) { return false; }

  bool Preserve(DPath const &dpath) {
    preserve_dpaths.insert(dpath);
    return true;
  }

  void RemoveAllMissingPrivateCreator(bool remove) {
    AllMissingPrivateCreator = remove;
  }
  bool RemoveMissingPrivateCreator(Tag const &t) { return false; }
  void RemoveAllGroupLength(bool remove) { AllGroupLength = remove; }
  void RemoveAllIllegal(bool remove) { AllIllegal = remove; }
};

static VR ComputeDictVR(File &file, DataSet &ds, DataElement const &de) {
  VR dict_vr = de.GetVR();
  const Tag &tag = de.GetTag();
  bool compute_dict_vr = true;
  if (tag.IsPublic() || tag.IsGroupLength() || tag.IsPrivateCreator()) {
  } else {
    const PrivateTag pt = ds.GetPrivateTag(tag);
    const char *owner = pt.GetOwner();
    assert(owner);
    compute_dict_vr = *owner != 0;
  }
  if (compute_dict_vr) dict_vr = DataSetHelper::ComputeVR(file, ds, tag);

  if (de.GetVR() == VR::SQ) {
    assert(dict_vr != VR::UN);
    if (!dict_vr.Compatible(de.GetVR())) {
      gdcmErrorMacro("Impossible. Dict states VR is: "
                     << dict_vr << " which is impossible for SQ");
      dict_vr = VR::SQ;
    }
  }
  if (dict_vr != VR::SQ) {
    if (de.GetVL().IsUndefined()) {
      Tag pixelData(0x7fe0, 0x0010);
      assert(dict_vr == VR::OB);
      if (tag != pixelData) {
        gdcmErrorMacro("Impossible happen: " << de);
        return VR::SQ;
      }
    }
  }
  return dict_vr;
}

static inline std::string tostring(uint16_t const val, int const width = 4) {
  std::ostringstream oss;
  oss.setf(std::ios::right);
  oss << std::hex << std::setw(width) << std::setfill('0') << val;
  return oss.str();
}

static std::vector<std::string> tag2strings(DataSet const &ds, Tag const &tag) {
  std::vector<std::string> ret;
  if (tag.IsPublic() || tag.IsPrivateCreator() || tag.IsGroupLength()) {
    ret.push_back(tostring(tag.GetGroup()));
    ret.push_back(tostring(tag.GetElement()));
  } else {
    const PrivateTag pt = ds.GetPrivateTag(tag);
    ret.push_back(tostring(pt.GetGroup()));
    ret.push_back(tostring(pt.GetElement(), 2));
    ret.push_back(pt.GetOwner());
  }
  return ret;
}

template <typename T>
static void print_contents(std::ostream &oss, const std::vector<T> &v,
                           const char *const separator = ",") {
  if (!v.empty()) {
    std::copy(v.begin(), --v.end(), std::ostream_iterator<T>(oss, separator));
    oss << v.back();
  }
}

static bool isAllZero(const char *buffer, size_t len) {
  while (len-- > 0) {
    if (buffer[len] != 0) return false;
  }
  return true;
}

static bool CleanCSA(DataSet &ds, const DataElement &de) {
  const ByteValue *bv = de.GetByteValue();
  // fast path:
  if (!bv) return true;
  static const char vs01[] = "VS01";
  // bogus big-endian conversion
  if (bv->GetLength() >= 4 && memcmp(bv->GetPointer(), vs01, 4) == 0) {
    return true;
  }
  static const char pds_com[] = "<pds><com>";
  // PET_REPLAY_PARAM case:
  if (bv->GetLength() >= 10 && memcmp(bv->GetPointer(), pds_com, 10) == 0) {
    return true;
  }
  static const char end[] = "END!      ";
  if (bv->GetLength() >= 10 &&
      memcmp(bv->GetPointer() + bv->GetLength() - 10, end, 10) == 0) {
    return true;
  }
  const bool zero = isAllZero(bv->GetPointer(), bv->GetLength());
  if (zero) return true;

  DataElement clean(de.GetTag());
  clean.SetVR(de.GetVR());
  std::vector<char> v;
  v.resize(bv->GetLength());
  if (csa_memcpy(&v[0], bv->GetPointer(), bv->GetLength())) {
    clean.SetByteValue(&v[0], v.size());
    ds.Replace(clean);
    return true;
  }
  gdcmErrorMacro("Failure to call CleanCSA");
  return false;
}

static DPath ConstructDPath(std::string const &tag_path, const DataSet &ds,
                            const Tag &tag) {
  DPath dpath;
  std::ostringstream oss;
  oss << tag_path;
  const std::vector<std::string> tag_strings = tag2strings(ds, tag);
  print_contents(oss, tag_strings);
  dpath.ConstructFromString(oss.str().c_str());
  return dpath;
}

static bool IsDPathInSet(std::set<DPath> const &aset, DPath const dpath) {
  bool found = false;
  for (std::set<DPath>::const_iterator it = aset.begin();
       found == false && it != aset.end(); ++it) {
    found = it->Match(dpath);
  }

  return found;
}

Cleaner::impl::ACTION Cleaner::impl::ComputeAction(
    File const &file, DataSet &ds, const DataElement &de, VR const &ref_dict_vr,
    const std::string &tag_path) {
  const Tag &tag = de.GetTag();
  if (tag.IsGroupLength()) {
    if (AllGroupLength) return Cleaner::impl::REMOVE;
  } else if (tag.IsIllegal()) {
    if (AllIllegal) return Cleaner::impl::REMOVE;
  }

  if (tag.IsPublic()) {
    const DPath dpath = ConstructDPath(tag_path, ds, tag);
    // Preserve
    if (IsDPathInSet(preserve_dpaths, dpath)) return Cleaner::impl::NONE;
    // Wipe
    if (wipe_tags.find(tag) != wipe_tags.end() ||
        IsDPathInSet(wipe_dpaths, dpath)) {
      return Cleaner::impl::WIPE;
    }
    // Empty
    if (empty_tags.find(tag) != empty_tags.end() ||
        IsDPathInSet(empty_dpaths, dpath)) {
      assert(!tag.IsGroupLength());
      assert(!tag.IsPrivateCreator());
      assert(ds.FindDataElement(tag));
      return Cleaner::impl::EMPTY;
    }
    // Remove
    if (remove_tags.find(tag) != remove_tags.end() ||
        IsDPathInSet(remove_dpaths, dpath)) {
      return Cleaner::impl::REMOVE;
    }
  }

  if (tag.IsPrivate() && !tag.IsPrivateCreator() && !tag.IsGroupLength()) {
    const PrivateTag pt = ds.GetPrivateTag(tag);
    const char *owner = pt.GetOwner();
    assert(owner);
    if (*owner == 0 && AllMissingPrivateCreator) {
      return Cleaner::impl::REMOVE;
    }
    // At this point we have a private creator, it makes sense to check for
    // preserve: Preserve
    const DPath dpath = ConstructDPath(tag_path, ds, tag);
    if (IsDPathInSet(preserve_dpaths, dpath)) return Cleaner::impl::NONE;
    // Wipe
    if (wipe_privatetags.find(pt) != wipe_privatetags.end() ||
        IsDPathInSet(wipe_dpaths, dpath)) {
      return Cleaner::impl::WIPE;
    }
    // Empty
    if (empty_privatetags.find(pt) != empty_privatetags.end() ||
        IsDPathInSet(empty_dpaths, dpath)) {
      return Cleaner::impl::EMPTY;
    }
    // Remove
    if (remove_privatetags.find(pt) != remove_privatetags.end() ||
        IsDPathInSet(remove_dpaths, dpath)) {
      return Cleaner::impl::REMOVE;
    }
  }

  // VR cleanup
  if (!empty_vrs.empty() || !remove_vrs.empty()) {
    VR vr = de.GetVR();
    // we want to clean VR==PN; but this is a problem for implicit transfer
    // syntax, so let's be nice to the user and prefer dict_vr. however for
    // explicit, do not assume value in dict can take over the read VR
    assert(ref_dict_vr != VR::INVALID);
    if (vr == VR::INVALID) {
      vr = ref_dict_vr;
    }
    if (vr == VR::UN && ref_dict_vr != VR::UN) {
      vr = ref_dict_vr;
    }
    // Empty
    if (empty_vrs.find(vr) != empty_vrs.end()) {
      return Cleaner::impl::EMPTY;
    }
    // Remove
    if (remove_vrs.find(vr) != remove_vrs.end()) {
      return Cleaner::impl::REMOVE;
    }
  }

  // default action:
  return Cleaner::impl::NONE;
}

bool Cleaner::impl::Clean(File const &file, DataSet &ds, const DataElement &de,
                          VR const &ref_dict_vr, const std::string &tag_path) {
  const Tag tag = de.GetTag();  // important make a copy
  if (tag.IsGroupLength()) {
    if (AllGroupLength) ds.Remove(tag);
    return true;
  } else if (tag.IsIllegal()) {
    if (AllIllegal) ds.Remove(tag);
    return true;
  }

  if (tag.IsPublic()) {
    const DPath dpath = ConstructDPath(tag_path, ds, tag);
    // Preserve
    if (IsDPathInSet(preserve_dpaths, dpath)) return true;
    // Wipe
    if (wipe_tags.find(tag) != wipe_tags.end() ||
        IsDPathInSet(wipe_dpaths, dpath)) {
      gdcmErrorMacro("Not Implemented");
      return false;
    }
    // Empty
    if (empty_tags.find(tag) != empty_tags.end() ||
        IsDPathInSet(empty_dpaths, dpath)) {
      assert(!tag.IsGroupLength());
      assert(!tag.IsPrivateCreator());
      assert(ds.FindDataElement(tag));
      DataElement clean(de.GetTag());
      clean.SetVR(de.GetVR());
      ds.Replace(clean);
    }
    // Remove
    if (remove_tags.find(tag) != remove_tags.end() ||
        IsDPathInSet(remove_dpaths, dpath)) {
      ds.Remove(tag);
    }
  }

  if (tag.IsPrivate() && !tag.IsPrivateCreator()) {
    const PrivateTag pt = ds.GetPrivateTag(tag);
    const char *owner = pt.GetOwner();
    assert(owner);
    if (*owner == 0 && AllMissingPrivateCreator) {
      ds.Remove(tag);
    }
    // At this point we have a private creator, it makes sense to check for
    // preserve: Preserve
    const DPath dpath = ConstructDPath(tag_path, ds, tag);
    if (IsDPathInSet(preserve_dpaths, dpath)) return true;
    // Wipe
    if (wipe_privatetags.find(pt) != wipe_privatetags.end() ||
        IsDPathInSet(wipe_dpaths, dpath)) {
      static const PrivateTag &csa1 = CSAHeader::GetCSAImageHeaderInfoTag();
      static const PrivateTag &csa2 = CSAHeader::GetCSASeriesHeaderInfoTag();

      if (pt == csa1) {
        const bool ret = CleanCSA(ds, de);
        if (!ret) return false;
      } else if (pt == csa2) {
        const bool ret = CleanCSA(ds, de);
        if (!ret) return false;
      } else {
        gdcmErrorMacro(" not implemented");
        return false;
      }
    }
    // Empty
    if (empty_privatetags.find(pt) != empty_privatetags.end() ||
        IsDPathInSet(empty_dpaths, dpath)) {
      DataElement clean(de.GetTag());
      clean.SetVR(de.GetVR());
      ds.Replace(clean);
    }
    // Remove
    if (remove_privatetags.find(pt) != remove_privatetags.end() ||
        IsDPathInSet(remove_dpaths, dpath)) {
      ds.Remove(tag);
    }
  }

  // VR cleanup
  if (!empty_vrs.empty() || !remove_vrs.empty()) {
    VR vr = de.GetVR();
    // we want to clean VR==PN; but this is a problem for implicit transfer
    // syntax, so let's be nice to the user and prefer dict_vr. however for
    // explicit, do not assume value in dict can take over the read VR
    assert(ref_dict_vr != VR::INVALID);
    if (vr == VR::INVALID) {
      vr = ref_dict_vr;
    }
    if (vr == VR::UN && ref_dict_vr != VR::UN) {
      vr = ref_dict_vr;
    }
    // Empty
    if (empty_vrs.find(vr) != empty_vrs.end()) {
      DataElement clean(de.GetTag());
      clean.SetVR(vr);
      ds.Replace(clean);
    }
    // Remove
    if (remove_vrs.find(vr) != remove_vrs.end()) {
      ds.Remove(tag);
    }
  }

  return true;
}

bool Cleaner::impl::ProcessDataSet(File &file, DataSet &ds,
                                   const std::string &tag_path) {
  ConstIterator it = ds.GetDES().begin();

  for (; it != ds.GetDES().end(); /*++it*/) {
    const DataElement &de = *it;
    ++it;  // 'Remove/Empty' may invalidate iterator
    const Tag &tag = de.GetTag();
    VR dict_vr = ComputeDictVR(file, ds, de);
    Cleaner::impl::ACTION action =
        Cleaner::impl::ComputeAction(file, ds, de, dict_vr, tag_path);

    if (action == Cleaner::impl::NONE) {
      // nothing to do, but recurse in nested-dataset:
      if (dict_vr == VR::SQ) {
        SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();
        if (sqi) {
          SequenceOfItems::SizeType s = sqi->GetNumberOfItems();
          for (SequenceOfItems::SizeType i = 1; i <= s; ++i) {
            Item &item = sqi->GetItem(i);

            DataSet &nestedds = item.GetNestedDataSet();
            const std::vector<std::string> tag_strings = tag2strings(ds, tag);

            std::ostringstream os;
            os << tag_path;  // already padded with trailing '/'
            print_contents(os, tag_strings);
            os << '/';
            os << '*';  // no need for item numbering
            os << '/';

            if (!ProcessDataSet(file, nestedds, os.str())) {
              gdcmErrorMacro("Error processing Item #" << i);
              return false;
            }
          }
          // Simple mechanism to avoid recomputation of Sequence Length: make
          // them undefined length
          DataElement dup(de.GetTag());
          dup.SetVR(VR::SQ);
          dup.SetValue(*sqi);
          dup.SetVLToUndefined();
          ds.Replace(dup);
        } else {
          // SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();
          assert(de.GetVL() == 0);
          if (!de.IsEmpty()) {
            gdcmErrorMacro("Impossible happen" << de);
            return false;
          }
        }
      }
    } else if (action == Cleaner::impl::EMPTY) {
      DataElement clean(de.GetTag());
      clean.SetVR(de.GetVR());
      ds.Replace(clean);

    } else if (action == Cleaner::impl::REMOVE) {
      ds.Remove(tag);
    } else if (action == Cleaner::impl::WIPE) {
      const PrivateTag pt = ds.GetPrivateTag(tag);

      static const PrivateTag &csa1 = CSAHeader::GetCSAImageHeaderInfoTag();
      static const PrivateTag &csa2 = CSAHeader::GetCSASeriesHeaderInfoTag();

      if (pt == csa1) {
        const bool ret = CleanCSA(ds, de);
        if (!ret) return false;
      } else if (pt == csa2) {
        const bool ret = CleanCSA(ds, de);
        if (!ret) return false;
      } else {
        gdcmErrorMacro(" not implemented");
        return false;
      }
    }
  }
  return true;
}

Cleaner::Cleaner() : pimpl(new impl) {}

Cleaner::~Cleaner() { delete pimpl; }

bool Cleaner::Empty(Tag const &t) { return pimpl->Empty(t); }
bool Cleaner::Empty(PrivateTag const &pt) { return pimpl->Empty(pt); }
bool Cleaner::Empty(DPath const &dpath) { return pimpl->Empty(dpath); }
bool Cleaner::Empty(VR const &vr) { return pimpl->Empty(vr); }

bool Cleaner::Remove(Tag const &t) { return pimpl->Remove(t); }
bool Cleaner::Remove(PrivateTag const &pt) { return pimpl->Remove(pt); }
bool Cleaner::Remove(DPath const &dpath) { return pimpl->Remove(dpath); }
bool Cleaner::Remove(VR const &vr) { return pimpl->Remove(vr); }

bool Cleaner::Wipe(Tag const &t) { return pimpl->Wipe(t); }
bool Cleaner::Wipe(PrivateTag const &pt) { return pimpl->Wipe(pt); }
bool Cleaner::Wipe(DPath const &dpath) { return pimpl->Wipe(dpath); }
bool Cleaner::Wipe(VR const &vr) { return pimpl->Wipe(vr); }

bool Cleaner::Preserve(DPath const &dpath) { return pimpl->Preserve(dpath); }

void Cleaner::RemoveAllMissingPrivateCreator(bool remove) {
  pimpl->RemoveAllMissingPrivateCreator(remove);
}
bool Cleaner::RemoveMissingPrivateCreator(Tag const &t) {
  return pimpl->RemoveMissingPrivateCreator(t);
}
void Cleaner::RemoveAllGroupLength(bool remove) {
  pimpl->RemoveAllGroupLength(remove);
}
void Cleaner::RemoveAllIllegal(bool remove) { pimpl->RemoveAllIllegal(remove); }

bool Cleaner::Clean() {
  DataSet &ds = F->GetDataSet();
  return pimpl->ProcessDataSet(*F, ds, "/");
}

}  // end namespace gdcm
