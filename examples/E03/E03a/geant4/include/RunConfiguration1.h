#ifndef RUN_CONFIGURATION1_H
#define RUN_CONFIGURATION1_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03a/geant4/include/RunConfiguration1.h
/// \brief Definition of the RunConfiguration1 class
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
/// This class overrides setting of the default Geant4 VMC geometry
/// construction with Geant4 detector construction
///
/// \author I. Hrivnacova; IPN, Orsay

class RunConfiguration1 : public ::TG4RunConfiguration
{
  public:
    RunConfiguration1(const TString& physicsList = "FTFP_BERT",
                          const TString& specialProcess = "stepLimiter");
    virtual ~RunConfiguration1();

    // methods
    virtual G4VUserDetectorConstruction*  CreateDetectorConstruction();
};

}
}

#endif //RUN_CONFIGURATION1_H

