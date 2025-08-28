//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4RunMessenger.cxx
/// \brief Implementation of the TG4RunMessenger class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4RunMessenger.h"
#include "TG4Globals.h"
#include "TG4RunManager.h"
#include "TG4UICmdWithAComplexString.h"

#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIdirectory.hh>

//_____________________________________________________________________________
TG4RunMessenger::TG4RunMessenger(TG4RunManager* runManager)
  : G4UImessenger(),
    fRunManager(runManager),
    fControlDirectory(nullptr),
    fRunDirectory(nullptr),
    fRootCmd(nullptr),
    fRootMacroCmd(nullptr),
    fRootCommandCmd(nullptr),
    fUseRootRandomCmd(nullptr),
    fG3DefaultsCmd(nullptr)
{
  /// Standard constructor

  fControlDirectory = new G4UIdirectory("/mcControl/");
  fControlDirectory->SetGuidance("TGeant4 control commands.");

  fRunDirectory = new G4UIdirectory("/mcRun/");
  fRunDirectory->SetGuidance("TGeant4 run commands.");

  fRootCmd = new G4UIcmdWithoutParameter("/mcControl/root", this);
  fRootCmd->SetGuidance("Switch to Root interactive shell.");
  fRootCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle,
    G4State_GeomClosed, G4State_EventProc);

  fRootMacroCmd = new G4UIcmdWithAString("/mcControl/rootMacro", this);
  fRootMacroCmd->SetGuidance(
    "Process Root macro with given name (from file name.C)");
  fRootMacroCmd->SetParameterName("macroName", true);
  fRootMacroCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle,
    G4State_GeomClosed, G4State_EventProc);

  fRootCommandCmd = new TG4UICmdWithAComplexString("/mcControl/rootCmd", this);
  fRootCommandCmd->SetGuidance("Process Root command");
  fRootCommandCmd->SetParameterName("command", false);
  fRootCommandCmd->SetDefaultValue(" ");
  fRootCommandCmd->AvailableForStates(G4State_PreInit, G4State_Init,
    G4State_Idle, G4State_GeomClosed, G4State_EventProc);

  fUseRootRandomCmd = new G4UIcmdWithABool("/mcControl/useRootRandom", this);
  fUseRootRandomCmd->SetGuidance(
    "(In)Activate passing the random number seed from Root to Geant4");
  fUseRootRandomCmd->SetParameterName("UseRootRandom", true);
  fUseRootRandomCmd->AvailableForStates(G4State_PreInit);

  fG3DefaultsCmd = new G4UIcmdWithoutParameter("/mcControl/g3Defaults", this);
  fG3DefaultsCmd->SetGuidance("Set G3 default parameters (cut values,");
  fG3DefaultsCmd->SetGuidance("tracking media max step values, ...)");
  fG3DefaultsCmd->AvailableForStates(G4State_PreInit);

  fBeamOnCmd = new G4UIcmdWithAnInteger("/mcRun/beamOn", this);
  fBeamOnCmd->SetGuidance(
    "Process run with the given number of events");
  fBeamOnCmd->SetParameterName("nevent", false);
  fBeamOnCmd->AvailableForStates(G4State_Idle);
  fBeamOnCmd->SetToBeBroadcasted(false);
}

//_____________________________________________________________________________
TG4RunMessenger::~TG4RunMessenger()
{
  /// Destructor

  delete fControlDirectory;
  delete fRunDirectory;
  delete fRootCmd;
  delete fRootMacroCmd;
  delete fRootCommandCmd;
  delete fUseRootRandomCmd;
  delete fG3DefaultsCmd;
  delete fBeamOnCmd;
}

//
// public methods
//

//_____________________________________________________________________________
void TG4RunMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  /// Apply command to the associated object.

  if (command == fRootCmd) {
    fRunManager->StartRootUI();
    return;
  }

  if (command == fRootMacroCmd) {
    fRunManager->ProcessRootMacro(newValue);
    return;
  }

  if (command == fRootCommandCmd) {
    fRunManager->ProcessRootCommand(newValue);
    return;
  }

  if (command == fUseRootRandomCmd) {
    fRunManager->UseRootRandom(fUseRootRandomCmd->GetNewBoolValue(newValue));
    return;
  }

  if (command == fG3DefaultsCmd) {
    fRunManager->UseG3Defaults();
    return;
  }

  if (command == fBeamOnCmd) {
    fRunManager->ProcessRun(fBeamOnCmd->GetNewIntValue(newValue));
    return;
  }
}
