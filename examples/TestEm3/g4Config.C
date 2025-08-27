//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup TestEm3
/// \file TestEm3/g4Config.C
/// \brief Configuration macro for Geant4 VirtualMC for TestEm3
///
/// For geometry defined with Geant4 and Geant4 native navigation

void Config(const TString& macroName)
{
/// The configuration function for Geant4 VMC for TestEm3
/// called during MC application initialization.
/// For geometry defined with Root and selected Geant4 native navigation

  cout << "processing Config() starts" << endl;

  // Run configuration
  RunConfiguration* runConfiguration = new RunConfiguration("local");

  // Run configuration with Geant4 physics list and special cuts activated
  // RunConfiguration* runConfiguration
  //   = new RunConfiguration("FTFP_BERT", "specialCuts");

  // TGeant4
  TGeant4* geant4
    = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration);

  cout << "Geant4 has been created." << endl;

  // Customise Geant4 VMC setting
  // (verbose level, global range cut, ..)
  geant4->ProcessGeantMacro("g4config.in");

  // Customise Geant4 setting
  // (verbose level, global range cut, ..)
  if (macroName.Length() > 0) {
    geant4->ProcessGeantMacro(macroName);
    cout << "Processing " << macroName << " done." << endl;
  }

  // Switch off photo nuclear process
  // geant4->SetProcess("PFIS", 0);

  cout << "Processing Config(" << macroName << ")  done." << endl;
}
