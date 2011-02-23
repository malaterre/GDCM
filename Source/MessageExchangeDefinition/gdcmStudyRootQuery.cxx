/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
/*
file name: gdcmStudyRootQuery.cxx
contains: the class which will produce a dataset for c-find and c-move with study root
name and date: 18 oct 2010 mmr

placeholder file to get the compiler/linker to play nice with this file
*/


#include "gdcmStudyRootQuery.h"

#include "gdcmAttribute.h"
#include "gdcmDataSet.h"

namespace gdcm{

StudyRootQuery::StudyRootQuery() {
  SetParameters();
}

StudyRootQuery::~StudyRootQuery(){}


void StudyRootQuery::SetParameters(){
  mRootType = eStudyRootType;
  mHelpDescription = "Study-level root query";
}


std::vector<Tag> StudyRootQuery::GetTagListByLevel(const EQueryLevel& inQueryLevel, bool forFind){
  if (forFind){
    switch (inQueryLevel){
      case ePatient:
        return mPatient.GetAllTags(eStudyRootType);
      case eStudy:
        return mStudy.GetAllTags(eStudyRootType);
      case eSeries:
      default:
        return mSeries.GetAllTags(eStudyRootType);
      case eImageOrFrame:
        return mImage.GetAllTags(eStudyRootType);
    }
  }
  else {//for move
    switch (inQueryLevel){
      case ePatient:
        return mPatient.GetUniqueTags(eStudyRootType);
      case eStudy:
        return mStudy.GetUniqueTags(eStudyRootType);
      case eSeries:
      default:
        return mSeries.GetUniqueTags(eStudyRootType);
      case eImageOrFrame:
        return mImage.GetUniqueTags(eStudyRootType);
    }
  }
}
///have to be able to ensure that
///0x8,0x52 is set
///that the level is appropriate (ie, not setting PATIENT for a study query
///that the tags in the query match the right level (either required, unique, optional)
bool StudyRootQuery::ValidateQuery(bool forFind, bool inStrict) const{
  //if it's empty, it's not useful
  DataSet ds = GetQueryDataSet();
  if (ds.Size() == 0) return false;

  //search for 0x8,0x52
  Attribute<0x0008, 0x0052> level;
  level.SetFromDataElement( ds.GetDataElement( level.GetTag() ) );
  std::string theVal = level.GetValue();

  if (strcmp(theVal.c_str(), "PATIENT ") == 0) return false;

  bool theReturn = true;

  std::vector<Tag> tags;
  if (inStrict)
  {
    QueryBase* qb = NULL;

    if (strcmp(theVal.c_str(), "STUDY ") == 0){
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      qb = new QueryStudy();
    }
    if (strcmp(theVal.c_str(), "SERIES") == 0){
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      qb = new QuerySeries();
    }
    if (strcmp(theVal.c_str(), "IMAGE ") == 0 || strcmp(theVal.c_str(), "FRAME ") == 0){
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      qb = new QueryImage();
    }
    if (qb == NULL){
      return false;
    }
    if (forFind){
      tags = qb->GetAllTags(eStudyRootType);
    } else{
      tags = qb->GetUniqueTags(eStudyRootType);
    }
    delete qb;
  }
  else //include all previous levels (ie, series gets study, image gets series and study)
  {
    QueryBase* qb = NULL;

    if (strcmp(theVal.c_str(), "STUDY ") == 0){
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      std::vector<Tag> tagGroup;
      qb = new QueryStudy();
      if (forFind){
        tagGroup = qb->GetAllTags(eStudyRootType);
      } else{
        tagGroup = qb->GetUniqueTags(eStudyRootType);
      }
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
    }
    if (strcmp(theVal.c_str(), "SERIES") == 0){
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      std::vector<Tag> tagGroup;
      qb = new QueryStudy();
      if (forFind){
        tagGroup = qb->GetAllTags(eStudyRootType);
      } else{
        tagGroup = qb->GetUniqueTags(eStudyRootType);
      }
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      qb = new QuerySeries();
      if (forFind){
        tagGroup = qb->GetAllTags(eStudyRootType);
      } else{
        tagGroup = qb->GetUniqueTags(eStudyRootType);
      }
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
    }
    if (strcmp(theVal.c_str(), "IMAGE ") == 0 || strcmp(theVal.c_str(), "FRAME ") == 0){
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      std::vector<Tag> tagGroup;
      qb = new QueryStudy();
      if (forFind){
        tagGroup = qb->GetAllTags(eStudyRootType);
      } else{
        tagGroup = qb->GetUniqueTags(eStudyRootType);
      }
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      qb = new QuerySeries();
      if (forFind){
        tagGroup = qb->GetAllTags(eStudyRootType);
      } else{
        tagGroup = qb->GetUniqueTags(eStudyRootType);
      }
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      qb = new QueryImage();
      if (forFind){
        tagGroup = qb->GetAllTags(eStudyRootType);
      } else{
        tagGroup = qb->GetUniqueTags(eStudyRootType);
      }
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
    }
    if (tags.empty()){
      return false;
    }
  }

  //all the tags in the dataset should be in that tag list
  //otherwise, it's not valid
  //also, while the level tag must be present, and the language tag can be
  //present (but does not have to be), some other tag must show up as well
  //so, have two counts: 1 for tags that are found, 1 for tags that are not
  //if there are no found tags, then the query is invalid
  //if there is one improper tag found, then the query is invalid
  int thePresentTagCount = 0;
  DataSet::ConstIterator itor;
  Attribute<0x0008, 0x0005> language;
  for (itor = ds.Begin(); itor != ds.End(); itor++){
    Tag t = itor->GetTag();
    if (t == level.GetTag()) continue;
    if (t.GetGroup() == language.GetTag().GetGroup() &&
      t.GetElement() == language.GetTag().GetElement()) continue;
    if (std::find(tags.begin(), tags.end(), t) == tags.end()){
      //check to see if it's a language tag, 8,5, and if it is, ignore if it's one
      //of the possible language tag values
      //well, for now, just allow it if it's present.
      theReturn = false;
      break;
    } else {
      thePresentTagCount++;
    }
  }
  return theReturn && (thePresentTagCount > 0);
}
  void StudyRootQuery::InitializeDataSet(const EQueryLevel& inQueryLevel){
    switch (inQueryLevel){
      case eStudy:
      {
        Attribute<0x8,0x52> at1 = { "STUDY " };
        mDataSet.Insert( at1.GetAsDataElement() );
      }
        break;
      case eSeries:
      {
        Attribute<0x8,0x52> at1 = { "SERIES" };
        mDataSet.Insert( at1.GetAsDataElement() );
        Attribute<0x20, 0xd> Studylevel;// make it blank
        mDataSet.Insert( Studylevel.GetAsDataElement() );
      }
      default:
        break;
      case eImageOrFrame:
      {
        Attribute<0x8,0x52> at1 = { "IMAGE " };
        mDataSet.Insert( at1.GetAsDataElement() );
        
        Attribute<0x20, 0xd> Studylevel;// make it blank
        mDataSet.Insert( Studylevel.GetAsDataElement() );
        
        Attribute<0x20, 0xe> SeriesLevel;// make it blank
        mDataSet.Insert( SeriesLevel.GetAsDataElement() );
      }
        break;
    }
  }
  
}
