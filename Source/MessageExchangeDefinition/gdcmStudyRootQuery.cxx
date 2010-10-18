/* 
file name: gdcmStudyRootQuery.cxx
contains: the class which will produce a dataset for c-find and c-move with study root
name and date: 18 oct 2010 mmr

placeholder file to get the compiler/linker to play nice with this file
*/


#include "gdcmStudyRootQuery.h"

namespace gdcm{
namespace network { 

StudyRootQuery::StudyRootQuery() {
  mRootType = eStudyRootType;
  mHelpDescription = "Study-level root query";
}

StudyRootQuery::~StudyRootQuery(){};

}
}
