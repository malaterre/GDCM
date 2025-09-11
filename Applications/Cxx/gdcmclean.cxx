/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 */
#include "gdcmCSAHeader.h"
#include "gdcmCleaner.h"
#include "gdcmDPath.h"
#include "gdcmDefs.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmDirectory.h"
#include "gdcmGlobal.h"
#include "gdcmReader.h"
#include "gdcmSystem.h"
#include "gdcmVR.h"
#include "gdcmVersion.h"
#include "gdcmWriter.h"

#include <getopt.h>
#include <memory>

static void PrintVersion() {
  std::cout << "gdcmclean: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

static bool CleanOneFile(gdcm::Cleaner &cleaner, const char *filename,
                         const char *outfilename, bool skipmeta,
                         bool continuemode = false) {
  gdcm::Reader reader;
  reader.SetFileName(filename);
  if (!reader.Read()) {
    std::cerr << "Could not read : " << filename << std::endl;
    if (continuemode) {
      std::cerr << "Skipping from cleaning process (continue mode)."
                << std::endl;
      return true;
    } else {
      std::cerr << "Check [--continue] option for skipping files." << std::endl;
      return false;
    }
  }
  gdcm::File &file = reader.GetFile();
  cleaner.SetFile(file);
  if (!cleaner.Clean()) {
    std::cerr << "Could not clean: " << filename << std::endl;
    if (continuemode) {
      std::cerr << "Skipping from cleaning process (continue mode)."
                << std::endl;
      return true;
    } else {
      std::cerr << "Check [--continue] option for skipping files." << std::endl;
      return false;
    }
  }

  gdcm::Writer writer;
  writer.SetFileName(outfilename);
  writer.SetCheckFileMetaInformation(!skipmeta);
  writer.SetFile(file);
  if (!writer.Write()) {
    std::cerr << "Could not Write : " << outfilename << std::endl;
    if (strcmp(filename, outfilename) != 0) {
      gdcm::System::RemoveFile(outfilename);
    } else {
      std::cerr << "gdcmclean just corrupted: " << filename
                << " for you (data lost)." << std::endl;
    }
    return false;
  }
  return true;
}

static inline bool isValidPublicKeyword(const char *keyword, gdcm::Tag &tag) {
  static const gdcm::Global &g = gdcm::Global::GetInstance();
  static const gdcm::Dicts &dicts = g.GetDicts();
  static const gdcm::Dict &pubdict = dicts.GetPublicDict();

  pubdict.GetDictEntryByKeyword(keyword, tag);
  if (tag != gdcm::Tag(0xffff, 0xffff)) return true;
  return false;
}

static void PrintHelp() {
  PrintVersion();
  std::cout << "Usage: gdcmclean [OPTION]... FILE..." << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -i --input                  DICOM filename / directory"
            << std::endl;
  std::cout << "  -o --output                 DICOM filename / directory"
            << std::endl;
  std::cout
      << "  -r --recursive              recursively process (sub-)directories."
      << std::endl;
  std::cout << "     --continue               Do not stop when file found is "
               "not DICOM."
            << std::endl;
  std::cout << "Edition options:" << std::endl;
  std::cout << "     --empty    %d,%d         DICOM tag(s) to empty"
            << std::endl;
  std::cout << "                %d,%d,%s      DICOM private tag(s) to empty"
            << std::endl;
  std::cout << "                %s            DICOM keyword/path(s) to empty"
            << std::endl;
  std::cout << "     --remove   %d,%d         DICOM tag(s) to remove"
            << std::endl;
  std::cout << "                %d,%d,%s      DICOM private tag(s) to remove"
            << std::endl;
  std::cout << "                %s            DICOM keyword/path(s) to remove"
            << std::endl;
  std::cout << "     --scrub    %d,%d         DICOM tag(s) to scrub"
            << std::endl;
  std::cout << "                %d,%d,%s      DICOM private tag(s) to scrub"
            << std::endl;
  std::cout << "                %s            DICOM keyword/path(s) to scrub"
            << std::endl;
  std::cout << "     --code_meaning %s,%s,%s  DICOM code meaning(s) to alter"
            << std::endl;
  std::cout << "     --preserve %s            DICOM path(s) to preserve"
            << std::endl;
  std::cout << "     --preserve-missing-private-creator             Whether or "
               "not preserve private attributes with missing private creator."
            << std::endl;
  std::cout << "     --preserve-group-length                        Whether or "
               "not preserve deprecated group length attributes (will not be "
               "re-computed)."
            << std::endl;
  std::cout << "     --preserve-illegal                             Whether or "
               "not preserve illegal attributes (eg. group 0003...)."
            << std::endl;
  std::cout
      << "     --empty-when-scrub-fails                       Fallback to "
         "emptying any attribute for which scrub operation failed."
      << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose                more verbose (warning+error)."
            << std::endl;
  std::cout << "  -W --warning                print warning info." << std::endl;
  std::cout << "  -D --debug                  print debug info." << std::endl;
  std::cout << "  -E --error                  print error info." << std::endl;
  std::cout << "  -h --help                   print help." << std::endl;
  std::cout << "  -v --version                print version." << std::endl;
}

namespace {
std::vector<std::string> split(const std::string &str, const char delimiter = ',') {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string item;
  while (std::getline(ss, item, delimiter)) {
    tokens.push_back(item);
  }
  return tokens;
}
template <std::size_t I, std::size_t TupleSize, typename Tuple>
struct print_tuple_helper {
  static void print(const Tuple& t) {
    if (I > 0) std::cerr << ", ";
    std::cerr << std::get<I>(t);
    print_tuple_helper<I + 1, TupleSize, Tuple>::print(t);
  }
};

template <std::size_t TupleSize, typename Tuple>
struct print_tuple_helper<TupleSize, TupleSize, Tuple> {
  static void print(const Tuple&) {}
};

template <typename... Ts>
void print_tuple(const std::tuple<Ts...>& t) {
  print_tuple_helper<0, sizeof...(Ts), std::tuple<Ts...>>::print(t);
}
}  // namespace

int main(int argc, char *argv[]) {
  int c;

  std::string filename;
  gdcm::Directory::FilenamesType filenames;
  std::string outfilename;
  gdcm::Directory::FilenamesType outfilenames;
  int skipmeta = 0;
  int continuemode = 0;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  int recursive = 0;
  int empty_tag = 0;
  int remove_tag = 0;
  int scrub_tag = 0;
  int code_meaning = 0;
  int preserve_tag = 0;
  int preserveAllMissingPrivateCreator = 0;
  int preserveAllGroupLength = 0;
  int preserveAllIllegal = 0;
  int emptyWhenScrubFails = 0;
  std::vector<gdcm::DPath> empty_dpaths;
  std::vector<gdcm::DPath> remove_dpaths;
  std::vector<gdcm::DPath> scrub_dpaths;
  std::vector<gdcm::Cleaner::CodedEntryData> coded_entry_datas;
  std::vector<gdcm::DPath> preserve_dpaths;
  std::vector<gdcm::VR> empty_vrs;
  std::vector<gdcm::Tag> empty_tags;
  std::vector<gdcm::PrivateTag> empty_privatetags;
  std::vector<gdcm::VR> remove_vrs;
  std::vector<gdcm::Tag> remove_tags;
  std::vector<gdcm::PrivateTag> remove_privatetags;
  std::vector<gdcm::Tag> scrub_tags;                // clean-digital-trash
  std::vector<gdcm::PrivateTag> scrub_privatetags;  // clean-digital-trash
  gdcm::Tag tag;
  gdcm::PrivateTag privatetag;
  gdcm::DPath dpath;

  while (true) {
    // int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", required_argument, nullptr, 'i'},   // i
        {"output", required_argument, nullptr, 'o'},  // o
        {"recursive", no_argument, nullptr, 'r'},
        {"empty", required_argument, &empty_tag, 1},        // 3
        {"remove", required_argument, &remove_tag, 1},      // 4
        {"scrub", required_argument, &scrub_tag, 1},        // 5
        {"code_meaning", required_argument, &code_meaning, 1},  // 6
        {"preserve", required_argument, &preserve_tag, 1},  // 7
        {"continue", no_argument, nullptr, 'c'},
        {"skip-meta", 0, &skipmeta, 1},  // should I document this one ?
        {"preserve-missing-private-creator", 0,
         &preserveAllMissingPrivateCreator, 1},                    //
        {"preserve-group-length", 0, &preserveAllGroupLength, 1},  //
        {"preserve-illegal", 0, &preserveAllIllegal, 1},           //
        {"empty-when-scrub-fails", 0, &emptyWhenScrubFails, 1},    //

        {"verbose", no_argument, nullptr, 'V'},
        {"warning", no_argument, nullptr, 'W'},
        {"debug", no_argument, nullptr, 'D'},
        {"error", no_argument, nullptr, 'E'},
        {"help", no_argument, nullptr, 'h'},
        {"version", no_argument, nullptr, 'v'},

        {nullptr, 0, nullptr, 0}};

    c = getopt_long(argc, argv, "i:o:rcVWDEhv", long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
      case 0: {
        const char *s = long_options[option_index].name;
        (void)s;
        if (optarg) {
          if (option_index == 3) /* empty */
          {
            gdcm_assert(strcmp(s, "empty") == 0);
            if (gdcm::VR::IsValid(optarg))
              empty_vrs.push_back(gdcm::VR::GetVRTypeFromFile(optarg));
            else if (privatetag.ReadFromCommaSeparatedString(optarg))
              empty_privatetags.push_back(privatetag);
            else if (tag.ReadFromCommaSeparatedString(optarg))
              empty_tags.push_back(tag);
            else if (isValidPublicKeyword(optarg, tag))
              empty_tags.push_back(tag);
            else if (dpath.ConstructFromString(optarg))
              empty_dpaths.push_back(dpath);
            else {
              std::cerr << "Could not read Tag/PrivateTag/DPath: " << optarg
                        << std::endl;
              return 1;
            }

          } else if (option_index == 4) /* remove */
          {
            if (gdcm::VR::IsValid(optarg))
              remove_vrs.push_back(gdcm::VR::GetVRTypeFromFile(optarg));
            if (privatetag.ReadFromCommaSeparatedString(optarg))
              remove_privatetags.push_back(privatetag);
            else if (tag.ReadFromCommaSeparatedString(optarg))
              remove_tags.push_back(tag);
            else if (isValidPublicKeyword(optarg, tag))
              remove_tags.push_back(tag);
            else if (dpath.ConstructFromString(optarg))
              remove_dpaths.push_back(dpath);
            else {
              std::cerr << "Could not read Tag/PrivateTag/DPath: " << optarg
                        << std::endl;
              return 1;
            }

          } else if (option_index == 5) /* scrub */
          {
            if (privatetag.ReadFromCommaSeparatedString(optarg))
              scrub_privatetags.push_back(privatetag);
            else if (tag.ReadFromCommaSeparatedString(optarg))
              scrub_tags.push_back(tag);
            else if (isValidPublicKeyword(optarg, tag))
              scrub_tags.push_back(tag);
            else {
              std::cerr << "Could not read Tag/PrivateTag/DPath: " << optarg
                        << std::endl;
              return 1;
            }
          } else if (option_index == 6) /* code_meaning */
          {
            gdcm::Cleaner::CodedEntryData coded_entry_data;
            auto entries = split(optarg);
            auto s = entries.size();
            if ( s == 1 )
              coded_entry_data = std::make_tuple(entries[0], "", "");
            else if (s == 2)
              coded_entry_data = std::make_tuple(entries[0], entries[1], "");
            else if (s == 3)
              coded_entry_data =
                  std::make_tuple(entries[0], entries[1], entries[2]);
            else {
              std::cerr << "Could not read CodedDataEntry: " << optarg
                        << std::endl;
              return 1;
            }
            coded_entry_datas.push_back(coded_entry_data);
          } else if (option_index == 7) /* preserve */
          {
            if (dpath.ConstructFromString(optarg))
              preserve_dpaths.push_back(dpath);
            else {
              std::cerr << "Could not read DPath: " << optarg << std::endl;
              return 1;
            }
          } else {
            gdcm_assert(0);
          }
        }
      } break;

      case 'i':
        gdcm_assert(filename.empty());
        filename = optarg;
        break;

      case 'o':
        gdcm_assert(outfilename.empty());
        outfilename = optarg;
        break;

      case 'c':
        continuemode = 1;
        break;

      case 'r':
        recursive = 1;
        break;

      case 'V':
        verbose = 1;
        break;

      case 'W':
        warning = 1;
        break;

      case 'D':
        debug = 1;
        break;

      case 'E':
        error = 1;
        break;

      case 'h':
        help = 1;
        break;

      case 'v':
        version = 1;
        break;

      case '?':
        break;

      default:
        printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) {
    std::vector<std::string> files;
    while (optind < argc) {
      files.push_back(argv[optind++]);
    }
    if (files.size() == 2 && filename.empty() && outfilename.empty()) {
      filename = files[0];
      outfilename = files[1];
    } else {
      PrintHelp();
      return 1;
    }
  }

  if (version) {
    PrintVersion();
    return 0;
  }

  if (help) {
    PrintHelp();
    return 0;
  }

  if (filename.empty()) {
    PrintHelp();
    return 1;
  }

  if (!gdcm::System::FileExists(filename.c_str())) {
    std::cerr << "Could not find file: " << filename << std::endl;
    return 1;
  }

  // Are we in single file or directory mode:
  unsigned int nfiles = 1;
  gdcm::Directory dir;
  if (gdcm::System::FileIsDirectory(filename.c_str())) {
    if (!gdcm::System::FileIsDirectory(outfilename.c_str())) {
      if (gdcm::System::FileExists(outfilename.c_str())) {
        std::cerr << "Could not create directory since " << outfilename
                  << " is already a file" << std::endl;
        return 1;
      }
    }
    // For now avoid user mistake
    if (filename == outfilename) {
      std::cerr << "Input directory should be different from output directory"
                << std::endl;
      return 1;
    }
    if (*outfilename.rbegin() != '/') outfilename += '/';
    nfiles = dir.Load(filename, (recursive > 0 ? true : false));
    filenames = dir.GetFilenames();
    gdcm::Directory::FilenamesType::const_iterator it = filenames.begin();
    // Prepare outfilenames
    for (; it != filenames.end(); ++it) {
      std::string dup = *it;  // make a copy
      std::string &out = dup.replace(0, filename.size(), outfilename);
      outfilenames.push_back(out);
    }
    // Prepare outdirectory
    gdcm::Directory::FilenamesType const &dirs = dir.GetDirectories();
    gdcm::Directory::FilenamesType::const_iterator itdir = dirs.begin();
    for (; itdir != dirs.end(); ++itdir) {
      std::string dirdup = *itdir;  // make a copy
      std::string &dirout = dirdup.replace(0, filename.size(), outfilename);
      if (!gdcm::System::MakeDirectory(dirout.c_str())) {
        std::cerr << "Could not create directory: " << dirout << std::endl;
        return 1;
      }
    }
  } else {
    filenames.push_back(filename);
    outfilenames.push_back(outfilename);
  }

  if (filenames.size() != outfilenames.size()) {
    std::cerr << "Something went really wrong" << std::endl;
    return 1;
  }

  // Debug is a little too verbose
  gdcm::Trace::SetDebug((debug > 0 ? true : false));
  gdcm::Trace::SetWarning((warning > 0 ? true : false));
  gdcm::Trace::SetError((error > 0 ? true : false));
  // when verbose is true, make sure warning+error are turned on:
  if (verbose) {
    gdcm::Trace::SetWarning((verbose > 0 ? true : false));
    gdcm::Trace::SetError((verbose > 0 ? true : false));
  }

  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle("gdcmclean");

  // Setup gdcm::Cleaner
  gdcm::Cleaner cleaner;
  cleaner.RemoveAllMissingPrivateCreator(!preserveAllMissingPrivateCreator);
  cleaner.RemoveAllGroupLength(!preserveAllGroupLength);
  cleaner.RemoveAllIllegal(!preserveAllIllegal);
  cleaner.EmptyWhenScrubFails(!!emptyWhenScrubFails);
  // Preserve
  for (std::vector<gdcm::DPath>::const_iterator it = preserve_dpaths.begin();
       it != preserve_dpaths.end(); ++it) {
    if (!cleaner.Preserve(*it)) {
      std::cerr << "Impossible to Preserve: " << *it << std::endl;
      return 1;
    }
  }
  // VR
  for (std::vector<gdcm::VR>::const_iterator it = empty_vrs.begin();
       it != empty_vrs.end(); ++it) {
    if (!cleaner.Empty(*it)) {
      std::cerr << "Impossible to Empty: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::VR>::const_iterator it = remove_vrs.begin();
       it != remove_vrs.end(); ++it) {
    if (!cleaner.Remove(*it)) {
      std::cerr << "Impossible to Remove: " << *it << std::endl;
      return 1;
    }
  }
  // Empty
  for (std::vector<gdcm::Tag>::const_iterator it = empty_tags.begin();
       it != empty_tags.end(); ++it) {
    if (!cleaner.Empty(*it)) {
      std::cerr << "Impossible to Empty: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::PrivateTag>::const_iterator it =
           empty_privatetags.begin();
       it != empty_privatetags.end(); ++it) {
    if (!cleaner.Empty(*it)) {
      std::cerr << "Impossible to Empty: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::DPath>::const_iterator it = empty_dpaths.begin();
       it != empty_dpaths.end(); ++it) {
    if (!cleaner.Empty(*it)) {
      std::cerr << "Impossible to Empty: " << *it << std::endl;
      return 1;
    }
  }
  // Remove
  for (std::vector<gdcm::Tag>::const_iterator it = remove_tags.begin();
       it != remove_tags.end(); ++it) {
    if (!cleaner.Remove(*it)) {
      std::cerr << "Impossible to Remove: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::PrivateTag>::const_iterator it =
           remove_privatetags.begin();
       it != remove_privatetags.end(); ++it) {
    if (!cleaner.Remove(*it)) {
      std::cerr << "Impossible to Remove: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::DPath>::const_iterator it = remove_dpaths.begin();
       it != remove_dpaths.end(); ++it) {
    if (!cleaner.Remove(*it)) {
      std::cerr << "Impossible to Remove: " << *it << std::endl;
      return 1;
    }
  }
  // Scrub
  for (std::vector<gdcm::Tag>::const_iterator it = scrub_tags.begin();
       it != scrub_tags.end(); ++it) {
    if (!cleaner.Scrub(*it)) {
      std::cerr << "Impossible to Scrub: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::PrivateTag>::const_iterator it =
           scrub_privatetags.begin();
       it != scrub_privatetags.end(); ++it) {
    if (!cleaner.Scrub(*it)) {
      std::cerr << "Impossible to Scrub: " << *it << std::endl;
      return 1;
    }
  }
  for (std::vector<gdcm::DPath>::const_iterator it = scrub_dpaths.begin();
       it != scrub_dpaths.end(); ++it) {
    if (!cleaner.Scrub(*it)) {
      std::cerr << "Impossible to Scrub: " << *it << std::endl;
      return 1;
    }
  }
  // Coded Data Entry (empty "code meaning")
  for (std::vector<gdcm::Cleaner::CodedEntryData>::const_iterator it = coded_entry_datas.begin();
       it != coded_entry_datas.end(); ++it) {
    if (!cleaner.ReplaceCodeMeaning(*it)) {
      std::cerr << "Impossible to CodedEntryData: ";
      print_tuple(*it);
      std::cerr << std::endl;
      return 1;
    }
  }
  {
    for (unsigned int i = 0; i < nfiles; ++i) {
      const char *in = filenames[i].c_str();
      const char *out = outfilenames[i].c_str();
      if (!CleanOneFile(cleaner, in, out, skipmeta > 0 ? true : false,
                        continuemode > 0 ? true : false)) {
        return 1;
      }
    }
  }

  return 0;
}
