//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4ExtraPhysicsList.cxx
/// \brief Implementation of the TG4ExtraPhysicsList class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4ExtraPhysicsList.h"
#include "TG4G3Units.h"
#include "TG4Globals.h"

#include <G4EmExtraPhysics.hh>
#include <G4GenericBiasingPhysics.hh>
#include <G4MonopolePhysics.hh>
#include <G4OpticalPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4ProcessTable.hh>
#include <G4SystemOfUnits.hh>

// According to G4VModularPhysicsList.cc
#include <G4StateManager.hh>
// This macros change the references to fields that are now encapsulated
// in the class G4VMPLData.
#define G4MT_physicsVector \
  ((G4VMPLsubInstanceManager.offset[g4vmplInstanceID]).physicsVector)

const G4double TG4ExtraPhysicsList::fgkDefaultCutValue = 1.0 * mm;

namespace
{

//_____________________________________________________________________________
void SetParameters(G4MonopolePhysics* monopolePhysics,
  const std::map<TString, Double_t>& parameters)
{
  /// Set special parameters which need to be set before creating TGeant4
  /// Actually used for monopole properties:
  /// monopoleMass, monopoleElCharge, monopoleMagCharge

  std::map<TString, Double_t>::const_iterator it;
  for (it = parameters.begin(); it != parameters.end(); it++) {
    if (it->first == "monopoleMass") {
      monopolePhysics->SetMonopoleMass(it->second * TG4G3Units::Energy());
    }
    else if (it->first == "monopoleElCharge") {
      monopolePhysics->SetElectricCharge(it->second * TG4G3Units::Charge());
    }
    else if (it->first == "monopoleMagCharge") {
      monopolePhysics->SetMagneticCharge(it->second * TG4G3Units::Charge());
    }
    else {
      TString text = "Invalid parameter name = ";
      text += it->second;
      TG4Globals::Warning("TG4ParticlesManager", "SetParameters", text);
    }
  }
}

} // namespace

//
// static methods
//

//_____________________________________________________________________________
G4String TG4ExtraPhysicsList::AvailableSelections()
{
  /// Return list of all available selections

  G4String selections;
  selections += "biasing extra monopole optical radDecay ";

  return selections;
}

//_____________________________________________________________________________
G4bool TG4ExtraPhysicsList::IsAvailableSelection(const G4String& selection)
{
  /// Return list of all available selections

  G4String available = AvailableSelections();
  G4String checkSelection = selection;
  checkSelection += " ";

  return G4StrUtil::contains(available, checkSelection);
}

//
// ctors, dtor
//

//_____________________________________________________________________________
TG4ExtraPhysicsList::TG4ExtraPhysicsList(
  const G4String& selection, const std::map<TString, Double_t>& parameters)
  : G4VModularPhysicsList(), TG4Verbose("extraPhysicsList")
{
  /// Default constructor

  Configure(selection, parameters);

  defaultCutValue = fgkDefaultCutValue;

  SetVerboseLevel(TG4Verbose::VerboseLevel());
}

//_____________________________________________________________________________
TG4ExtraPhysicsList::~TG4ExtraPhysicsList()
{
  /// Destructor
}

//
// private methods
//

//_____________________________________________________________________________
void TG4ExtraPhysicsList::Configure(
  const G4String& selection, const std::map<TString, Double_t>& parameters)
{
  /// Create the selected physics constructors
  /// and registeres them in the modular physics list.

  // Generic biasing physics
  if (G4StrUtil::contains(selection, "biasing")) {
    G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics;
    // we may need to make this configurable later
    biasingPhysics->Bias("proton");
    biasingPhysics->Bias("neutron");
    biasingPhysics->Bias("pi+");
    biasingPhysics->Bias("pi-");
    RegisterPhysics(biasingPhysics);
  }

  // Extra electromagnetic physics
  if (G4StrUtil::contains(selection, "extra")) {
    G4EmExtraPhysics* extraPhysics = new G4EmExtraPhysics();
#if G4VERSION_NUMBER >= 1012
    extraPhysics->Synch(false);
    extraPhysics->GammaNuclear(false);
    extraPhysics->MuonNuclear(false);
#else
    G4String state("off");
    extraPhysics->Synch(state);
    extraPhysics->GammaNuclear(state);
    extraPhysics->MuonNuclear(state);
#endif
    RegisterPhysics(extraPhysics);
  }

  // Monopole physics
  if (G4StrUtil::contains(selection, "monopole")) {
    G4MonopolePhysics* monopolePhysics = new G4MonopolePhysics();
    SetParameters(monopolePhysics, parameters);
    RegisterPhysics(monopolePhysics);
  }

  // Optical physics
  if (G4StrUtil::contains(selection, "optical")) {
    G4OpticalPhysics* g4OpticalPhysics = new G4OpticalPhysics();
    RegisterPhysics(g4OpticalPhysics);
  }

  // Radioactive decay physics
  if (G4StrUtil::contains(selection, "radDecay")) {
    RegisterPhysics(new G4RadioactiveDecayPhysics());
  }
}

//
// public methods
//

//_____________________________________________________________________________
void TG4ExtraPhysicsList::ConstructProcess()
{
  /// Call base class method + add verbose info

  // create processes for registered physics
  // G4VModularPhysicsList::ConstructProcess();
  G4PhysConstVector::iterator itr;
  for (itr = G4MT_physicsVector->begin(); itr != G4MT_physicsVector->end();
       ++itr) {
    (*itr)->ConstructProcess();
  }

  if (VerboseLevel() > 0) {
    G4cout << "### Extra physics constructed: ";
    G4PhysConstVector::iterator it;
    for (it = G4MT_physicsVector->begin(); it != G4MT_physicsVector->end();
         ++it) {
      G4cout << (*it)->GetPhysicsName() << " ";
    }
    G4cout << G4endl;
  }
}

//_____________________________________________________________________________
G4int TG4ExtraPhysicsList::VerboseLevel() const
{
  /// Return verbose level (via TG4Verbose)

  return TG4Verbose::VerboseLevel();
}

//_____________________________________________________________________________
void TG4ExtraPhysicsList::VerboseLevel(G4int level)
{
  /// Set the specified level to both TG4Verbose and
  /// G4VModularPhysicsList.
  /// The verbose level is also propagated to registered physics contructors.

  TG4Verbose::VerboseLevel(level);
  SetVerboseLevel(level);

  G4PhysConstVector::iterator it;
  for (it = G4MT_physicsVector->begin(); it != G4MT_physicsVector->end();
       ++it) {
    TG4Verbose* verbose = dynamic_cast<TG4Verbose*>(*it);
    if (verbose)
      verbose->VerboseLevel(level);
    else
      (*it)->SetVerboseLevel(level);
  }
}

//_____________________________________________________________________________
void TG4ExtraPhysicsList::SetRangeCut(G4double value)
{
  /// Reset the default cut to a given value.                                 \n
  /// !!! Should be used only in PreInit phase,
  /// use SetDefaultCutValue() method of base class to reset
  /// the cut value in later phases.

  defaultCutValue = value;
}
