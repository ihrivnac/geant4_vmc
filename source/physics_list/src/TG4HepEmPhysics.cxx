//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4HepEmPhysics.cxx
/// \brief Implementation of the TG4HepEmPhysics class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4HepEmPhysics.h"

// include the G4HepEmProcess from the G4HepEm lib.
#include "G4HepEmProcess.h"

#include "G4EmBuilder.hh"
#include "G4hMultipleScattering.hh"
#include "G4NuclearStopping.hh"
#include "G4ionIonisation.hh"
#include "G4EmModelActivator.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"
#include "G4EmParameters.hh"
#include "G4BuilderType.hh"
#include "G4SystemOfUnits.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4GenericIon.hh"

//_____________________________________________________________________________
TG4HepEmPhysics::TG4HepEmPhysics(const G4String& name)
: G4VPhysicsConstructor(name) 
{
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetDefaults();

  param->SetMscRangeFactor(0.04);

  SetPhysicsType(bElectromagnetic);
}


//_____________________________________________________________________________
TG4HepEmPhysics::~TG4HepEmPhysics() 
{}


//_____________________________________________________________________________
void TG4HepEmPhysics::ConstructProcess() 
{
  // Prepare G4 bulder
  // (From G4EmStandardPhysics)

  if(verboseLevel > 1) {
    G4cout << "### " << GetPhysicsName() << " Construct Processes " << G4endl;
  }
  G4EmBuilder::PrepareEMPhysics();

  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  G4EmParameters* param = G4EmParameters::Instance();

  // processes used by several particles
  G4hMultipleScattering* hmsc = new G4hMultipleScattering("ionmsc");

  // nuclear stopping is enabled if th eenergy limit above zero
  G4double nielEnergyLimit = param->MaxNIELEnergy();
  G4NuclearStopping* pnuc = nullptr;
  if(nielEnergyLimit > 0.0) {
    pnuc = new G4NuclearStopping();
    pnuc->SetMaxKinEnergy(nielEnergyLimit);
  }

  // high energy limit for e+- scattering models and bremsstrahlung
  G4double highEnergyLimit = param->MscEnergyLimit();

  // G4HepEm - gamma, e+, e-
  //

  // creae the only one G4HepEm process that will be assigned to e-/e+ and gamma
  G4HepEmProcess* hepEmProcess = new G4HepEmProcess();
  hepEmProcess->SetVerboseLevel(verboseLevel);

  // Add gamma EM Processes
  G4ParticleDefinition* particle = G4Gamma::Gamma();
  particle->GetProcessManager()->AddProcess(hepEmProcess, -1, -1, 1);

  // e-
  particle = G4Electron::Electron();
  particle->GetProcessManager()->AddProcess(hepEmProcess, -1, -1, 1);

  // e+
  particle = G4Positron::Positron();
  particle->GetProcessManager()->AddProcess(hepEmProcess, -1, -1, 1);

  // Other particles
  // (From G4EmStandardPhysics)

  // generic ion
  particle = G4GenericIon::GenericIon();
  G4ionIonisation* ionIoni = new G4ionIonisation();
  ph->RegisterProcess(hmsc, particle);
  ph->RegisterProcess(ionIoni, particle);
  if(nullptr != pnuc) { ph->RegisterProcess(pnuc, particle); }

  // muons, hadrons ions
  G4EmBuilder::ConstructCharged(hmsc, pnuc);

  // extra configuration
  G4EmModelActivator mact(GetPhysicsName());

  if (G4Threading::IsMasterThread() && verboseLevel > 0) {
    G4EmParameters::Instance()->Dump();
  }
}
