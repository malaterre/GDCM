/*
file name: gdcmQueryFactory.h
contains: a class to produce a query based off of user-entered information
name and date: 18 oct 2010 mmr

Essentially, this class is used to construct a query based off of user input (typically
from the command line; if in code directly, the query itself could just be instantiated)

In theory, could also be used as the interface to validate incoming datasets as belonging
to a particular query style
*/

#include "gdcmBaseRootQuery.h"

namespace gdcm{
  namespace network{
    class GDCM_EXPORT QueryFactory {
    public:
      static BaseRootQuery* ProduceQuery(const ERootType &inRootType);
    };
  }
}