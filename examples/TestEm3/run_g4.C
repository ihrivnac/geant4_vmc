//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup TestEm3
/// \file TestEm3/run_g4.C
/// \brief Macro for running TestEm3 with Geant4 with visualization.

#include "TVirtualMC.h"

void run_g4(const TString& configMacro = "g4Config.C")
{
/// Macro function for running TestEm3 with Geant4 from
/// Root interactive session
/// Note that since Root 6 the libraries have to be loaded first
/// via load_g4.C.
/// \param configMacro configuration macro name, default \ref E03/g4Config.C

  // MC application
  MCApplication* appl
    =  new MCApplication("TestEm3", "The TestEm3 VMC application");

  appl->InitMC(configMacro);

  // // Visualization setting
  ((TGeant4*)gMC)->ProcessGeantMacro("macros/vis.mac");

  // Enter in Geant4 interactive session
  // ((TGeant4*)gMC)->StartGeantUI();

  appl->RunMC(5);

  delete appl;
}
