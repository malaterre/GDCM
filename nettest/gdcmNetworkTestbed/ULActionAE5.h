/*
This header defines the payload and class for Action AE-5, the fifth action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Issue Transport connection response primitive, start ARTIM timer

Next state:
eSta2Open

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE5Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE5 {
    public:
      void PerformAction();

    }
  }
}