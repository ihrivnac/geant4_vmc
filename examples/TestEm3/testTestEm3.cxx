//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file testTestEm3.cxx
/// \brief The Geant4 VMC example TestEm3 test application
///
/// The Geant4 VMC test application with explicitly instantiated 
/// TGeant4 and linked with all libraries.
/// Note: g4Config.C is not used.
///
/// <pre>
/// Usage:
/// testTestEm3
///   [-g4pl, --g4-physics-list]:    Geant4 physics list selection
///   [-g4sp, --g4-special-physics]: Geant4 special physics selection
///   [-g4cm, --g4-config-macro]:    Geant4 configuration macro
///   [-g4m,  --g4-macro]:           Geant4 run macro
///   [-v,    --verbose]:            verbose option (yes,no)
///
/// \date 27/08/2025
/// \author I. Hrivnacova; IJCLab Orsay

#include "MCApplication.h"
#include "RunConfiguration.h"

#include "TGeant4.h"

#include "TROOT.h"

#include <iostream>
#include <string>

namespace
{

/// Prints usage on error output stream
void PrintUsage(std::string programName)
{
  // clang-format off
  std::cerr << " Usage: " << std::endl;
  std::cerr << " " << programName << std::endl;
  std::cerr << "   [-g4pl, --g4-physics-list]:    Geant4 physics list selection"    << std::endl;
  std::cerr << "   [-g4sp, --g4-special-physics]: Geant4 special physics selection" << std::endl;
  std::cerr << "   [-g4cm, --g4-config-macro]:    Geant4 configuration macro"       << std::endl;
  std::cerr << "   [-g4m,  --g4-macro]:           Geant4 macro"                     << std::endl;
  std::cerr << "   [-v,    --verbose]:            verbose option (yes,no)"          << std::endl;
  // clang-format on
}

#ifdef USE_GEANT4
/// Prints selected configuration on output stream (Geant4)
void PrintG4Configuration(const std::string& programName,
  const std::string& g4PhysicsList, const std::string& g4SpecialPhysics, 
  const std::string& g4ConfigMacro,  const std::string& g4Macro)
{
  std::cout << " Running " << programName << " with options:" << std::endl;
  std::cout << "   --g4-physics-list:    " << g4PhysicsList << std::endl;
  if (g4SpecialPhysics.size()) {
    std::cout << "   --g4-special-physics: " << g4SpecialPhysics << std::endl;
  }
  if (g4ConfigMacro.size()) {
    std::cout << "   --g4-config-macro:    " << g4Macro << std::endl;
  }
  if (g4Macro.size()) {
    std::cout << "   --g4-macro:           " << g4Macro << std::endl;
  }
}
#endif

} // namespace

/// Application main program
int main(int argc, char** argv)
{
  // Initialize Root threading.
  // (Multi-threading is triggered automatically if Geant4 was built
  //  in MT mode.)
#ifdef G4MULTITHREADED
  ROOT::EnableThreadSafety();
#endif

  // Process arguments
  // Local physics list
  std::string g4PhysicsList = "local";
  std::string g4SpecialPhysics = "";
  // Can be changes with G4 physics lists
  // std::string g4PhysicsList = "FTFP_BERT";
  // std::string g4SpecialPhysics = "stepLimiter";
  std::string g4ConfigMacro = "g4config.in";
  std::string g4Macro = "";
  std::string verbose = "yes";

  for (Int_t i = 1; i < argc; i = i + 2) {
    std::cout << "processing " << argv[i] << " with " << argv[i + 1]
              << std::endl;
    if (std::string(argv[i]) == "--g4-physics-list" ||
             std::string(argv[i]) == "-g4pl")
      g4PhysicsList = argv[i + 1];
    else if (std::string(argv[i]) == "--g4-special-physics" ||
             std::string(argv[i]) == "-g4sp")
      g4SpecialPhysics = argv[i + 1];
    else if (std::string(argv[i]) == "--g4-config-macro" ||
             std::string(argv[i]) == "-g4cm")
      g4ConfigMacro = argv[i + 1];
    else if (std::string(argv[i]) == "--g4-macro" ||
             std::string(argv[i]) == "-g4m")
      g4Macro = argv[i + 1];
    else if (std::string(argv[i]) == "--verbose" ||
             std::string(argv[i]) == "-v")
      verbose = argv[i + 1];
    else {
      PrintUsage("testTestEm3");
      return 1;
    }
  }

  if (verbose == "yes") {
    PrintG4Configuration("testTestEm3", g4PhysicsList, g4SpecialPhysics,
      g4ConfigMacro, g4Macro);
  }
  //
  // end of code to process arguments

  // Create MC application (thread local)
  MCApplication* appl =
    new MCApplication("TestEm3", "The TestEm3 VMC application");

  G4bool isLocalPhysics = true;
  if (g4PhysicsList != "local") {
    isLocalPhysics = false;
  }

  // RunConfiguration for Geant4
  RunConfiguration* runConfiguration
    = new RunConfiguration(g4PhysicsList, g4SpecialPhysics);
  
  // TGeant4
  TGeant4* geant4 = new TGeant4(
    "TGeant4", "The Geant4 Monte Carlo", runConfiguration, argc, argv);
  
  if (g4ConfigMacro.size()) {
    // geant4-vmc configuration
    geant4->ProcessGeantMacro(g4ConfigMacro.c_str());
  }

  if (g4Macro.size()) {
    //  g4 application configuration
    std::string initMacroName = g4Macro + "_init.mac";
    geant4->ProcessGeantMacro(initMacroName.c_str());
    // run initialization
    appl->InitMC("");
    // process run macro
    std::string macroName = g4Macro + ".mac";
    ((TGeant4*)gMC)->ProcessGeantMacro(macroName.c_str());
    // terminate application run
    appl->FinishRun();
  }

  else {
    // Customise Geant4 setting
    // (verbose level, global range cut, ..)
    appl->InitMC("");
    appl->RunMC(5);
  }

  delete appl;
}
