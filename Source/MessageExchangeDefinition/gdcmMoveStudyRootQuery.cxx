/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmMoveStudyRootQuery.h"

#include "gdcmAttribute.h"
#include "gdcmDataSet.h"

namespace gdcm
{

MoveStudyRootQuery::MoveStudyRootQuery()
{
  mRootType = eStudyRootType;
  mHelpDescription = "Study-level root query";
}

void MoveStudyRootQuery::InitializeDataSet(const EQueryLevel& inQueryLevel)
{
  switch (inQueryLevel)
    {
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
      Attribute<0x20, 0xd> Studylevel = { "" };// make it blank
      mDataSet.Insert( Studylevel.GetAsDataElement() );
      }
  default:
    break;
  case eImageOrFrame:
      {
      Attribute<0x8,0x52> at1 = { "IMAGE " };
      mDataSet.Insert( at1.GetAsDataElement() );

      Attribute<0x20, 0xd> Studylevel = { "" };// make it blank
      mDataSet.Insert( Studylevel.GetAsDataElement() );

      Attribute<0x20, 0xe> SeriesLevel = { "" };// make it blank
      mDataSet.Insert( SeriesLevel.GetAsDataElement() );
      }
    break;
  }
}

std::vector<Tag> MoveStudyRootQuery::GetTagListByLevel(const EQueryLevel& inQueryLevel)
{
  switch (inQueryLevel)
    {
  case ePatient:
    return mPatient.GetUniqueTags(eStudyRootType);
  case eStudy:
    return mStudy.GetUniqueTags(eStudyRootType);
  case eSeries:
//  default:
    return mSeries.GetUniqueTags(eStudyRootType);
  case eImageOrFrame:
    return mImage.GetUniqueTags(eStudyRootType);
  default: //have to return _something_ if a query level isn't given
	  assert(0);
	  {
		  std::vector<Tag> empty;
		  return empty;
	  }
    }
}

bool MoveStudyRootQuery::ValidateQuery(bool inStrict) const
{
  //if it's empty, it's not useful
  DataSet ds = GetQueryDataSet();
  if (ds.Size() == 0)
    {
    if (inStrict)
      gdcmWarningMacro( "Empty DataSet in ValidateQuery" );
    return false;
    }

  //search for 0x8,0x52
  Attribute<0x0008, 0x0052> level;
  level.SetFromDataElement( ds.GetDataElement( level.GetTag() ) );
  std::string theVal = level.GetValue();

  if (strcmp(theVal.c_str(), "PATIENT ") == 0)
    {
    gdcmWarningMacro( "Invalid Level" );
    return false;
    }

  bool theReturn = true;

  std::vector<Tag> tags;
  if (inStrict)
    {
    QueryBase* qb = NULL;
    if (strcmp(theVal.c_str(), "STUDY ") == 0)
      {
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      qb = new QueryStudy();
      }
    if (strcmp(theVal.c_str(), "SERIES") == 0)
      {
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      qb = new QuerySeries();
      }
    if (strcmp(theVal.c_str(), "IMAGE ") == 0 || strcmp(theVal.c_str(), "FRAME ") == 0)
      {
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      qb = new QueryImage();
      }
    if (qb == NULL)
      {
      gdcmWarningMacro( "Invalid Level" );
      return false;
      }
    tags = qb->GetUniqueTags(eStudyRootType);
    delete qb;
    }
  else //include all previous levels (ie, series gets study, image gets series and study)
  {
    QueryBase* qb = NULL;

    if (strcmp(theVal.c_str(), "STUDY ") == 0)
      {
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      std::vector<Tag> tagGroup;
      qb = new QueryStudy();
      tagGroup = qb->GetUniqueTags(eStudyRootType);
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      }
    if (strcmp(theVal.c_str(), "SERIES") == 0)
      {
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      std::vector<Tag> tagGroup;
      qb = new QueryStudy();
      tagGroup = qb->GetUniqueTags(eStudyRootType);
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      qb = new QuerySeries();
      tagGroup = qb->GetUniqueTags(eStudyRootType);
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      }
    if (strcmp(theVal.c_str(), "IMAGE ") == 0 || strcmp(theVal.c_str(), "FRAME ") == 0)
      {
      //make sure remaining tags are somewhere in the list of required, unique, or optional tags
      std::vector<Tag> tagGroup;
      qb = new QueryStudy();
      tagGroup = qb->GetUniqueTags(eStudyRootType);
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      qb = new QuerySeries();
      tagGroup = qb->GetUniqueTags(eStudyRootType);
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      qb = new QueryImage();
      tagGroup = qb->GetUniqueTags(eStudyRootType);
      tags.insert(tags.end(), tagGroup.begin(), tagGroup.end());
      delete qb;
      }
    if (tags.empty())
      {
      gdcmWarningMacro( "Invalid Level" );
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
  int thePresentTagCount = 1;
  DataSet::ConstIterator itor;
  Attribute<0x0008, 0x0005> language;
  if( inStrict )
    {
    thePresentTagCount = 0;
    for (itor = ds.Begin(); itor != ds.End(); itor++)
      {
      Tag t = itor->GetTag();
      if (t == level.GetTag()) continue;
      if (t == language.GetTag()) continue;
      if (std::find(tags.begin(), tags.end(), t) == tags.end())
        {
        //check to see if it's a language tag, 8,5, and if it is, ignore if it's one
        //of the possible language tag values
        //well, for now, just allow it if it's present.
        gdcmWarningMacro( "You have an extra tag: " << t );
        theReturn = false;
        break;
        }
      else
        {
        thePresentTagCount++;
        }
      }
    }
  return theReturn && (thePresentTagCount > 0);
}

UIDs::TSName MoveStudyRootQuery::GetAbstractSyntaxUID() const
{
  return UIDs::StudyRootQueryRetrieveInformationModelMOVE;
}

} // end namespace gdcm
