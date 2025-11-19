//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm1/src/StepMaxMessenger.cc
/// \brief Implementation of the StepMaxMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "StepMaxMessenger.hh"

#include "StepMax.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StepMaxMessenger::StepMaxMessenger(StepMax* stepM) : fStepMax(stepM)
{
  fStepMaxDir = new G4UIdirectory("/testem/stepMax/");
  fStepMaxDir->SetGuidance("stepmax control");

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/testem/stepMax", this);
  fStepMaxCmd->SetGuidance("Set max allowed step length");
  fStepMaxCmd->SetParameterName("mxStep", false);
  fStepMaxCmd->SetRange("mxStep>0.");
  fStepMaxCmd->SetUnitCategory("Length");

  fStepMaxAbsorberCmd = new G4UIcommand("/testem/stepMax/absorber",this);
  fStepMaxAbsorberCmd->SetGuidance("Set max allowed step length in absorber k");
  //
  G4UIparameter* k = new G4UIparameter("k",'i',false);
  k->SetGuidance("absorber number : from 1 to MaxHisto-1");
  k->SetParameterRange("k>0");
  fStepMaxAbsorberCmd->SetParameter(k);
  //
  G4UIparameter* sMax = new G4UIparameter("sMax",'d',false);
  sMax->SetGuidance("stepMax, expressed in choosen unit");
  sMax->SetParameterRange("sMax>0.");
  fStepMaxAbsorberCmd->SetParameter(sMax);
  //
  G4UIparameter* unit = new G4UIparameter("unit",'s',false);
  fStepMaxAbsorberCmd->SetParameter(unit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StepMaxMessenger::~StepMaxMessenger()
{
  delete fStepMaxCmd;
  delete fStepMaxAbsorberCmd;
  delete fStepMaxDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StepMaxMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fStepMaxCmd) {
    fStepMax->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
  }

  if (command == fStepMaxAbsorberCmd) {
     G4int k;
     G4double sMax;
     G4String unts;
     std::istringstream is(newValue);
     is >> k >> sMax >> unts;
     G4String unit = unts;
     G4double vUnit = G4UIcommand::ValueOf(unit);
     fStepMax->SetMaxStep(k, sMax*vUnit);
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
