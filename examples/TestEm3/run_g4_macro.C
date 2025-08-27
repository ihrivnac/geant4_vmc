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
/// \brief Macro for running TestEm3 with Geant4.

#include "TVirtualMC.h"

void run_g4_macro(const TString& macroName = "macros/tileCal")
{
/// Macro function for running TestEm3 with Geant4 with the
/// original Geant4 macro splitted in two macros:
/// - macro_init.mac: run during initialization
/// - macro.mac     : run during event processing
///   
/// The Geant4 '/run/beamOn nevent' is replaced with
/// '/mcRun/runBeamOn nevent'.
/// As the VMC frameworks does not support processing more than one run
/// per application run, the additional /run/beamOn calls, if present,
/// were disabled.

  // MC application
  MCApplication* appl
    =  new MCApplication("TestEm3", "The TestEm3 VMC application");

  appl->InitMC("g4Config.C", macroName + TString("_init.mac"));

  // Define application setup
  ((TGeant4*)gMC)->ProcessGeantMacro(macroName + TString(".mac"));

  appl->FinishRun();

  delete appl;
}
