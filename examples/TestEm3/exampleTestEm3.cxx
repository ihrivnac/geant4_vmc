//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file exampleTestEm3.cxx
/// \brief The Geant4 VMC example TestEm3 application executable
///
/// The Geant4 VMC test application with explicitly instantiated 
/// TGeant4 and linked with all libraries.
/// Note: g4Config.C is not used.
///
/// \date 27/08/2025
/// \author I. Hrivnacova; IJCLab Orsay

#include "MCApplication.h"

#include "RunConfiguration.h"
#include "TGeant4.h"

#include "TROOT.h"

/// Application main program
int main(int argc, char** argv)
{
  // Initialize Root threading.
  // (Multi-threading is triggered automatically if Geant4 was built
  //  in MT mode.)
#ifdef G4MULTITHREADED
  ROOT::EnableThreadSafety();
#endif

  // Create MC application (thread local)
  MCApplication* appl =
    new MCApplication("TestEm3", "The TestEm3 VMC application");

  // RunConfiguration for Geant4
  RunConfiguration* runConfiguration = new RunConfiguration("local");

  // TGeant4
  TGeant4* geant4 = new TGeant4(
    "TGeant4", "The Geant4 Monte Carlo", runConfiguration, argc, argv);

  // Customise Geant4 setting
  // (verbose level, global range cut, ..)
  geant4->ProcessGeantMacro("g4config.in");

  // Run example
  appl->InitMC("");

  // Setting Geant4 visualization
  geant4->ProcessGeantMacro("macros/vis.mac");

  appl->RunMC(5);

  delete appl;
}
