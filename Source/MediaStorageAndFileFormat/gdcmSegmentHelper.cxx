#include "gdcmSegmentHelper.h"

namespace gdcm
{

namespace SegmentHelper
{

bool BasicCodedEntry::IsEmpty(const bool checkOptionalAttributes/* = false*/) const
{
  bool res = false;

  if (!CV.empty() && !CSD.empty() && !CM.empty())
  {
    if (checkOptionalAttributes)
    {
      if (!CSV.empty())
      {
        res =true;
      }
    }
    else
    {
      res = true;
    }
  }

  return res;
}

} // end of SegmentHelper namespace

} // end of gdcm namespace
