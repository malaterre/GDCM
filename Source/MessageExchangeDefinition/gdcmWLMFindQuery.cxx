/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmWLMFindQuery.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{
WLMFindQuery::WLMFindQuery()
{
  mRootType = ePatientRootType;
  mHelpDescription = "Modality Worklist query";
}

void WLMFindQuery::InitializeDataSet(const EQueryLevel& inQueryLevel)
{
  // no level so no tags to add
}

  std::vector<Tag> 
WLMFindQuery::GetTagListByLevel(const EQueryLevel& inQueryLevel)
{
  // no level so no tags
  std::vector<Tag> tags ;
  return tags;
}

bool 
WLMFindQuery::ValidateQuery(bool inStrict) const
{
  //if it's empty, it's not useful
  const DataSet &ds = GetQueryDataSet();
  if (ds.Size() == 0) return false;

  // in Query somme tags are required other are optional
  // lets check that we have required one's

  bool theReturn = true ;
  DataSet validDs = GetValidDataSet();
  theReturn &= ValidDataSet( ds, validDs );

  return theReturn ;
}

bool
WLMFindQuery::ValidDataSet( const DataSet & dataSetToValid, const DataSet & dataSetReference ) const
{
  bool theReturn = true ;
  DataSet::ConstIterator itor;
  for (itor = dataSetReference.Begin(); itor != dataSetReference.End(); itor++)
    {
    if ( dataSetToValid.FindDataElement( itor->GetTag() ) )
      {
      SmartPointer<SequenceOfItems> pSqi = dataSetToValid.GetDataElement( itor->GetTag() ).GetValueAsSQ();
      SmartPointer<SequenceOfItems> pSqiRef = pSqi ? itor->GetValueAsSQ() : NULL ;
      if ( pSqi && pSqiRef )
        {
        if( pSqi->GetNumberOfItems() < pSqiRef->GetNumberOfItems() )
          {
          gdcmErrorMacro( "DataSet to valid has less Items " << pSqi->GetNumberOfItems() << " for sequence : " << itor->GetTag() << " than valid one " << pSqiRef->GetNumberOfItems() );
          theReturn = false ;
          break ;
          }
        SequenceOfItems::SizeType indexOfItem ;
        for ( indexOfItem = 1 ; indexOfItem <= pSqiRef->GetNumberOfItems(); indexOfItem++ )
          {
          const Item & currentReferenceItem = pSqiRef->GetItem( indexOfItem );
          const Item & currentItemToValid = pSqi->GetItem( indexOfItem );
          // now valid subDataSet
          theReturn &= ValidDataSet( currentItemToValid.GetNestedDataSet(), currentReferenceItem.GetNestedDataSet() );
          if ( !theReturn )
            break ;
          }
        }
      else // tag is found its not a sequence so it's ok
        theReturn &= true ;
      }
    else
      {
      gdcmErrorMacro( "You must have this tag : " << itor->GetTag() << " in your query dataset. ");
      theReturn = false ;
      break ;
      }
    }
  return theReturn ;
}

UIDs::TSName WLMFindQuery::GetAbstractSyntaxUID() const
{
  return UIDs::ModalityWorklistInformationModelFIND;
}

DataSet WLMFindQuery::GetValidDataSet() const
{
  DataSet validDataSet ;
  Attribute<0x10,0x10> PatientName;
  validDataSet.Insert( PatientName.GetAsDataElement() );
  Attribute<0x10,0x20> PatientId;
  validDataSet.Insert( PatientId.GetAsDataElement() );

  gdcm::SmartPointer<gdcm::SequenceOfItems> sqItemList = new gdcm::SequenceOfItems();
  gdcm::DataElement scheduledProcedureStepSequence;
  scheduledProcedureStepSequence.SetTag( Tag(0x40,0x0100) );
  scheduledProcedureStepSequence.SetVR( gdcm::VR::SQ );
  scheduledProcedureStepSequence.SetValue( *sqItemList );
  scheduledProcedureStepSequence.SetVLToUndefined();
  validDataSet.Insert( scheduledProcedureStepSequence );


  // Item Separator
  gdcm::Item item; //( Tag(0xfffe,0xe000) );
  item.SetVLToUndefined();

  Attribute<0x8,0x60> Modality ;
  item.GetNestedDataSet().Insert( Modality.GetAsDataElement() );
  Attribute<0x40,0x1, VR::AE, VM::VM1> ScheduledStationAETitle ;
  item.GetNestedDataSet().Insert( ScheduledStationAETitle.GetAsDataElement() );
  Attribute<0x40,0x2> ScheduledProcedureStepStartDate;
  item.GetNestedDataSet().Insert( ScheduledProcedureStepStartDate.GetAsDataElement() );
  Attribute<0x40,0x3> ScheduledProcedureStepStartTime ;
  item.GetNestedDataSet().Insert( ScheduledProcedureStepStartTime.GetAsDataElement() );
  Attribute<0x40,0x3> ScheduledPerformingPhysiciansName ;
  item.GetNestedDataSet().Insert( ScheduledPerformingPhysiciansName.GetAsDataElement() );
  sqItemList->AddItem( item );
  return validDataSet;
}

} // end namespace gdcm
