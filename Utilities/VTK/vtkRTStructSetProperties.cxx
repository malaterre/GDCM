/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkRTStructSetProperties.h"
#include "vtkObjectFactory.h"

#include "gdcmDirectory.h"
#include "gdcmScanner.h"
#include "gdcmDataSet.h"
#include "gdcmReader.h"

#include <string>
#include <map>
#include <vector>
#include <set>
#include <time.h> // for strftime
#include <ctype.h> // for isdigit
#include <assert.h>

//----------------------------------------------------------------------------
vtkCxxRevisionMacro(vtkRTStructSetProperties, "1.21")
vtkStandardNewMacro(vtkRTStructSetProperties)



struct StructureSetROI
{
  int ROINumber;
  std::string RefFrameRefUID;
  std::string ROIName;
  std::string ROIGenerationAlgorithm;

  // (3006,0080) SQ (Sequence with undefine)# u/l, 1 RTROIObservationsSequence
  // (3006,0082) IS [0]                     #   2, 1 ObservationNumber
  // (3006,0084) IS [0]                     #   2, 1 ReferencedROINumber
  // (3006,00a4) CS [ORGAN]                 #   6, 1 RTROIInterpretedType
  // (3006,00a6) PN (no value available)    #   0, 0 ROIInterpreter
  int ObservationNumber;
  // RefROI is AFAIK simply ROINumber
  std::string RTROIInterpretedType;
  std::string ROIInterpreter;
};

//----------------------------------------------------------------------------
class vtkRTStructSetPropertiesInternals
{
public:
  void Print(ostream &os, vtkIndent indent)
    {
    }
  void DeepCopy(vtkRTStructSetPropertiesInternals *p)
    {
    ReferencedFrameOfReferences = p->ReferencedFrameOfReferences;
    }
  vtkIdType GetNumberOfContourReferencedFrameOfReferences()
    {
    return ContourReferencedFrameOfReferences.size();
    }
  vtkIdType GetNumberOfContourReferencedFrameOfReferences(vtkIdType pdnum)
    {
    return ContourReferencedFrameOfReferences[pdnum].size();
    }
  const char *GetContourReferencedFrameOfReferenceClassUID( vtkIdType pdnum, vtkIdType id )
    {
    return ContourReferencedFrameOfReferences[pdnum][ id ].first.c_str();
    }
  const char *GetContourReferencedFrameOfReferenceInstanceUID( vtkIdType pdnum, vtkIdType id )
    {
    return ContourReferencedFrameOfReferences[pdnum][ id ].second.c_str();
    }
  vtkIdType GetNumberOfReferencedFrameOfReferences()
    {
    return ReferencedFrameOfReferences.size();
    }
  const char *GetReferencedFrameOfReferenceClassUID( vtkIdType id )
    {
    return ReferencedFrameOfReferences[ id ].first.c_str();
    }
  const char *GetReferencedFrameOfReferenceInstanceUID(vtkIdType id )
    {
    return ReferencedFrameOfReferences[ id ].second.c_str();
    }
  void AddContourReferencedFrameOfReference( vtkIdType pdnum, const char *classuid , const char * instanceuid )
    {
    ContourReferencedFrameOfReferences.resize(pdnum+1);
    ContourReferencedFrameOfReferences[pdnum].push_back(
      std::make_pair( classuid, instanceuid ) );
    }
  std::vector< std::vector < std::pair< std::string, std::string > > > ContourReferencedFrameOfReferences;
  void AddReferencedFrameOfReference( const char *classuid , const char * instanceuid )
    {
    ReferencedFrameOfReferences.push_back(
      std::make_pair( classuid, instanceuid ) );
    }
  std::vector < std::pair< std::string, std::string > > ReferencedFrameOfReferences;
  void AddStructureSetROIObservation( int refnumber,
    int observationnumber,
    const char *rtroiinterpretedtype,
    const char *roiinterpreter
  )
    {
    std::vector<StructureSetROI>::iterator it = StructureSetROIs.begin();
    bool found = false;
    for( ; it != StructureSetROIs.end(); ++it )
      {
      if( it->ROINumber == refnumber )
        {
        found = true;
        it->ObservationNumber = observationnumber;
        it->RTROIInterpretedType = rtroiinterpretedtype;
        it->ROIInterpreter = roiinterpreter;
        }
      }
    // postcond
    assert( found );
    }

  void AddStructureSetROI( int roinumber,
    const char* refframerefuid,
    const char* roiname,
    const char* roigenerationalgorithm
  )
    {
    StructureSetROI structuresetroi;
    structuresetroi.ROIName = roiname;
    structuresetroi.ROINumber = roinumber;
    structuresetroi.RefFrameRefUID = refframerefuid;
    structuresetroi.ROIGenerationAlgorithm = roigenerationalgorithm;
    StructureSetROIs.push_back( structuresetroi );
    }
  vtkIdType GetNumberOfStructureSetROIs()
    {
    return StructureSetROIs.size();
    }
  int GetStructureSetObservationNumber(vtkIdType id)
    {
    return StructureSetROIs[id].ObservationNumber;
    }
  int GetStructureSetROINumber(vtkIdType id)
    {
    return StructureSetROIs[id].ROINumber;
    }
  const char *GetStructureSetRTROIInterpretedType(vtkIdType id)
    {
    return StructureSetROIs[id].RTROIInterpretedType.c_str();
    }
  const char *GetStructureSetROIRefFrameRefUID(vtkIdType id)
    {
    return StructureSetROIs[id].RefFrameRefUID.c_str();
    }
  const char *GetStructureSetROIName(vtkIdType id)
    {
    return StructureSetROIs[id].ROIName.c_str();
    }
  const char *GetStructureSetROIGenerationAlgorithm(vtkIdType id)
    {
    return StructureSetROIs[id].ROIGenerationAlgorithm.c_str();
    }

  std::vector<StructureSetROI> StructureSetROIs;
};

//----------------------------------------------------------------------------
vtkRTStructSetProperties::vtkRTStructSetProperties()
{
  this->Internals = new vtkRTStructSetPropertiesInternals;

  this->StructureSetLabel             = NULL;
  this->StructureSetName              = NULL;
  this->StructureSetDate              = NULL;
  this->StructureSetTime              = NULL;

  this->SOPInstanceUID= NULL;
  this->StudyInstanceUID = NULL;
  this->SeriesInstanceUID = NULL;
  this->ReferenceSeriesInstanceUID = NULL;
  this->ReferenceFrameOfReferenceUID = NULL;
}

//----------------------------------------------------------------------------
vtkRTStructSetProperties::~vtkRTStructSetProperties()
{
  delete this->Internals;
  this->Clear();
}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::AddContourReferencedFrameOfReference(vtkIdType pdnum, const char *classuid , const char * instanceuid )
{
  this->Internals->AddContourReferencedFrameOfReference(pdnum, classuid, instanceuid );
}
const char *vtkRTStructSetProperties::GetContourReferencedFrameOfReferenceClassUID( vtkIdType pdnum, vtkIdType id )
{
  return this->Internals->GetContourReferencedFrameOfReferenceClassUID(pdnum, id );
}

const char *vtkRTStructSetProperties::GetContourReferencedFrameOfReferenceInstanceUID( vtkIdType pdnum, vtkIdType id )
{
  return this->Internals->GetContourReferencedFrameOfReferenceInstanceUID(pdnum ,id );
}

vtkIdType vtkRTStructSetProperties::GetNumberOfContourReferencedFrameOfReferences()
{
  return this->Internals->GetNumberOfContourReferencedFrameOfReferences();
}

vtkIdType vtkRTStructSetProperties::GetNumberOfContourReferencedFrameOfReferences(vtkIdType pdnum)
{
  return this->Internals->GetNumberOfContourReferencedFrameOfReferences(pdnum);
}

void vtkRTStructSetProperties::AddReferencedFrameOfReference( const char *classuid , const char * instanceuid )
{
  this->Internals->AddReferencedFrameOfReference( classuid, instanceuid );
}

const char *vtkRTStructSetProperties::GetReferencedFrameOfReferenceClassUID( vtkIdType id )
{
  return this->Internals->GetReferencedFrameOfReferenceClassUID(id );
}

const char *vtkRTStructSetProperties::GetReferencedFrameOfReferenceInstanceUID( vtkIdType id )
{
  return this->Internals->GetReferencedFrameOfReferenceInstanceUID(id );
}

vtkIdType vtkRTStructSetProperties::GetNumberOfReferencedFrameOfReferences()
{
  return this->Internals->GetNumberOfReferencedFrameOfReferences();
}
void vtkRTStructSetProperties::AddStructureSetROIObservation( int refnumber,
    int observationnumber,
    const char *rtroiinterpretedtype,
    const char *roiinterpreter)
{
  this->Internals->AddStructureSetROIObservation( refnumber, observationnumber, rtroiinterpretedtype, roiinterpreter );
}

void vtkRTStructSetProperties::AddStructureSetROI( int roinumber,
    const char* refframerefuid,
    const char* roiname,
    const char* roigenerationalgorithm
  )
{
  this->Internals->AddStructureSetROI( roinumber, refframerefuid, roiname, roigenerationalgorithm );
}

vtkIdType vtkRTStructSetProperties::GetNumberOfStructureSetROIs()
{
  return this->Internals->GetNumberOfStructureSetROIs();
}
int vtkRTStructSetProperties::GetStructureSetObservationNumber(vtkIdType id)
{
  return this->Internals->GetStructureSetObservationNumber(id);
}
int vtkRTStructSetProperties::GetStructureSetROINumber(vtkIdType id)
{
  return this->Internals->GetStructureSetROINumber(id);
}
const char *vtkRTStructSetProperties::GetStructureSetRTROIInterpretedType(vtkIdType id)
{
  return this->Internals->GetStructureSetRTROIInterpretedType(id);
}

const char *vtkRTStructSetProperties::GetStructureSetROIRefFrameRefUID(vtkIdType id)
{
  return this->Internals->GetStructureSetROIRefFrameRefUID(id);
}
const char *vtkRTStructSetProperties::GetStructureSetROIName(vtkIdType id)
{
  return this->Internals->GetStructureSetROIName(id);
}
const char *vtkRTStructSetProperties::GetStructureSetROIGenerationAlgorithm(vtkIdType id)
{
  return this->Internals->GetStructureSetROIGenerationAlgorithm(id);
}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::Clear()
{
  this->SetStructureSetLabel(NULL);
  this->SetStructureSetName(NULL);
  this->SetStructureSetDate(NULL);
  this->SetStructureSetTime(NULL);

  this->SetSOPInstanceUID( NULL );
  this->SetStudyInstanceUID ( NULL );
  this->SetSeriesInstanceUID ( NULL );
  this->SetReferenceSeriesInstanceUID ( NULL );
  this->SetReferenceFrameOfReferenceUID ( NULL );

}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::DeepCopy(vtkRTStructSetProperties *p)
{
  if (p == NULL)
    {
    return;
    }

  this->Clear();

  this->SetStructureSetDate(p->GetStructureSetDate());
  this->SetStructureSetTime(p->GetStructureSetTime());

  this->Internals->DeepCopy( p->Internals );
}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << "\n" << indent << "StructureSetDate: ";
  if (this->StructureSetDate)
    {
    os << this->StructureSetDate;
    }
  os << "\n" << indent << "StructureSetTime: ";
  if (this->StructureSetTime)
    {
    os << this->StructureSetTime;
    }

  this->Internals->Print(os << "\n", indent.GetNextIndent() );
}
