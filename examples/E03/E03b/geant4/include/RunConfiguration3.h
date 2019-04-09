#ifndef RUN_CONFIGURATION3_H
#define RUN_CONFIGURATION3_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03a/geant4/include/RunConfiguration3.h
/// \brief Definition of the RunConfiguration3 class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4RunConfiguration.h"

namespace VMC
{
namespace E03
{

/// \ingroup E03
/// \brief User Geant4 VMC run configuration
///
/// This class demonstrates how to add to Geant4 VMC geometry construction
/// user defined regions
///
/// \author I. Hrivnacova; IPN, Orsay

class RunConfiguration3 : public ::TG4RunConfiguration
{
  public:
    RunConfiguration3(const TString& userGeometry,
                          const TString& physicsList = "FTFP_BERT",
                          const TString& specialProcess = "stepLimiter");
    virtual ~RunConfiguration3();

    // methods
    virtual TG4VUserRegionConstruction*  CreateUserRegionConstruction();
};

}
}

#endif //RUN_CONFIGURATION3_H

