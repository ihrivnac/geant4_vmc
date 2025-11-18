//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4EmTrackingPhysics.cxx
/// \brief Implementation of the TG4EmTrackingPhysics class
///
/// \author I. Hrivnacova; IPN, Orsay

#ifdef USE_G4HEPEM

#include "TG4EmTrackingPhysics.h"

#include "G4EmTrackingManager.hh"
#include "G4EmParameters.hh"

#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4Positron.hh"

//_____________________________________________________________________________
TG4EmTrackingPhysics::TG4EmTrackingPhysics(const G4String& name)
  : G4VPhysicsConstructor(name)
{
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetDefaults();

  param->SetMscRangeFactor(0.04);
}

//_____________________________________________________________________________
TG4EmTrackingPhysics::~TG4EmTrackingPhysics()
{}

//_____________________________________________________________________________
void TG4EmTrackingPhysics::ConstructProcess()
{
  // Register custom tracking manager for e-/e+ and gammas.
  auto* trackingManager = new G4EmTrackingManager;

  G4Electron::Definition()->SetTrackingManager(trackingManager);
  G4Positron::Definition()->SetTrackingManager(trackingManager);
  G4Gamma::Definition()->SetTrackingManager(trackingManager);
}

#endif
