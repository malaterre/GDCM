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
  std::set<Tag> empty_tags;
  std::set<PrivateTag> empty_privatetags;
  std::set<Tag> remove_tags;
  std::set<PrivateTag> remove_privatetags;
  std::set<Tag> wipe_tags;
  std::set<PrivateTag> wipe_privatetags;
  bool AllMissingPrivateCreator;
  bool AllGroupLength;
  std::set<VR> AllValueRepresentation;
  impl() : AllMissingPrivateCreator(false), AllGroupLength(true) {}

  bool Clean(File const &file, DataSet &ds, const DataElement &de,
             VR const &ref_dict_vr, const std::string &tag_path);

  bool ProcessDataSet(File &file, DataSet &ds, const std::string &tag_path);

  bool Empty(Tag const &t) {
    empty_tags.insert(t);
    return true;
  }
  bool Empty(PrivateTag const &pt) {
    empty_privatetags.insert(pt);
    return true;
  }
  bool Empty(const char *tag_path) { return false; }

  bool Remove(Tag const &t) {
    remove_tags.insert(t);
    return true;
  }
  bool Remove(PrivateTag const &pt) {
    remove_privatetags.insert(pt);
    return true;
  }
  bool Remove(const char *tag_path) { return false; }

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
  bool Wipe(const char *tag_path) { return false; }

  void RemoveAllMissingPrivateCreator(bool remove) {
    AllMissingPrivateCreator = remove;
  }
  bool RemoveMissingPrivateCreator(Tag const &t) { return false; }
  void RemoveAllGroupLength(bool remove) { AllGroupLength = remove; }
  bool RemoveAllValueRepresentation(VR const &vr) {
    if (vr == VR::PN) {
      AllValueRepresentation.insert(vr);
      return true;
    }
    return false;
  }
};

static VR ComputeDictVR(File &file, DataSet &ds, DataElement const &de) {
  VR dict_vr = de.GetVR();
  const Tag &tag = de.GetTag();
  bool compute_dict_vr = true;
  if (tag.IsPublic() || tag.IsGroupLength() || tag.IsPrivateCreator()) {
  } else {
    const PrivateTag pt = ds.GetPrivateTag(tag);
    compute_dict_vr = "" != pt.GetOwner();
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

static std::vector<std::string> tag2strings(
    DataSet const &ds, Tag const &tag, std::string const &fallback_creator) {
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
  return false;
}

bool Cleaner::impl::Clean(File const &file, DataSet &ds, const DataElement &de,
                          VR const &ref_dict_vr, const std::string &tag_path) {
  const Tag &tag = de.GetTag();
  if (tag.IsGroupLength()) {
    if (AllGroupLength) ds.Remove(tag);
    return true;
  }

  if (tag.IsPublic()) {
    const bool is_in = empty_tags.find(tag) != empty_tags.end();
    // Empty
    if (is_in) {
      assert(!tag.IsGroupLength());
      assert(!tag.IsPrivateCreator());
      assert(ds.FindDataElement(tag));
      // fast path
      const ByteValue *bv = de.GetByteValue();
      if (!bv) return true;
      DataElement clean(de.GetTag());
      clean.SetVR(de.GetVR());
      ds.Replace(clean);
    }
    // Remove
    if (remove_tags.find(tag) != remove_tags.end()) {
      ds.Remove(tag);
    }
    // Wipe
    if (wipe_tags.find(tag) != wipe_tags.end()) {
      assert(0);
    }
  }

  if (tag.IsPrivate()) {
    const PrivateTag pt = ds.GetPrivateTag(tag);
    // Empty
    if (empty_privatetags.find(pt) != empty_privatetags.end()) {
      // fast path
      const ByteValue *bv = de.GetByteValue();
      if (!bv) return true;
      DataElement clean(de.GetTag());
      clean.SetVR(de.GetVR());
      ds.Replace(clean);
    }
    // Remove
    if (remove_privatetags.find(pt) != remove_privatetags.end()) {
      ds.Remove(tag);
    }
    // Wipe
    if (wipe_privatetags.find(pt) != wipe_privatetags.end()) {
      static const PrivateTag &csa1 = CSAHeader::GetCSAImageHeaderInfoTag();
      static const PrivateTag &csa2 = CSAHeader::GetCSASeriesHeaderInfoTag();

      if (pt == csa1) {
        const bool ret = CleanCSA(ds, de);
        if (!ret) return false;
      } else if (pt == csa2) {
        const bool ret = CleanCSA(ds, de);
        if (!ret) return false;
      } else {
        assert(0);
      }
    }
  }

  return true;
}

bool Cleaner::impl::ProcessDataSet(File &file, DataSet &ds,
                                   const std::string &tag_path) {
  ConstIterator it = ds.GetDES().begin();

  for (; it != ds.GetDES().end(); /*++it*/) {
    const DataElement &de = *it;
    ++it;
    const Tag &tag = de.GetTag();
    VR dict_vr = ComputeDictVR(file, ds, de);
    if (dict_vr != VR::SQ) {
      Clean(file, ds, de, dict_vr, tag_path);
    } else if (dict_vr == VR::SQ) {
      SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();
      if (sqi) {
        SequenceOfItems::SizeType s = sqi->GetNumberOfItems();
        for (SequenceOfItems::SizeType i = 1; i <= s; ++i) {
          Item &item = sqi->GetItem(i);

          DataSet &nestedds = item.GetNestedDataSet();
          const std::vector<std::string> tag_strings = tag2strings(ds, tag, "");

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
  }
  return true;
}

Cleaner::Cleaner() : pimpl(new impl) {}

Cleaner::~Cleaner() { delete pimpl; }

bool Cleaner::Empty(Tag const &t) { return pimpl->Empty(t); }
bool Cleaner::Empty(PrivateTag const &pt) { return pimpl->Empty(pt); }

bool Cleaner::Remove(Tag const &t) { return pimpl->Remove(t); }
bool Cleaner::Remove(PrivateTag const &pt) { return pimpl->Remove(pt); }

bool Cleaner::Wipe(Tag const &t) { return pimpl->Wipe(t); }
bool Cleaner::Wipe(PrivateTag const &pt) { return pimpl->Wipe(pt); }

bool Cleaner::RemoveAllValueRepresentation(VR const &vr) {
  return pimpl->RemoveAllValueRepresentation(vr);
}

bool Cleaner::Clean() {
  DataSet &ds = F->GetDataSet();
  return pimpl->ProcessDataSet(*F, ds, "/");
}

}  // end namespace gdcm
