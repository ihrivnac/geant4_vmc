//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4EmPhysicsList.cxx
/// \brief Implementation of the TG4EmPhysicsList class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4EmPhysicsList.h"

#include <G4DecayPhysics.hh>
#include <G4EmStandardPhysics.hh>
#include <G4SystemOfUnits.hh>

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4ProcessTable.hh>

// According to G4VModularPhysicsList.cc
#include <G4StateManager.hh>
// This macros change the references to fields that are now encapsulated
// in the class G4VMPLData.
#define G4MT_physicsVector \
  ((G4VMPLsubInstanceManager.offset[g4vmplInstanceID]).physicsVector)

const G4double TG4EmPhysicsList::fgkDefaultCutValue = 1.0 * mm;

//
// static methods
//

//_____________________________________________________________________________
G4String TG4EmPhysicsList::AvailableSelections()
{
  /// Return list of all available selections

  G4String selections;
  selections += "emStandard ";

  return selections;
}

//_____________________________________________________________________________
G4bool TG4EmPhysicsList::IsAvailableSelection(const G4String& selection)
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
TG4EmPhysicsList::TG4EmPhysicsList(const G4String& selection)
  : G4VModularPhysicsList(), TG4Verbose("emPhysicsList")
{
  /// Default constructor

  Configure(selection);

  defaultCutValue = fgkDefaultCutValue;

  SetVerboseLevel(TG4Verbose::VerboseLevel());
}

//_____________________________________________________________________________
TG4EmPhysicsList::~TG4EmPhysicsList()
{
  /// Destructor

  // delete fExtDecayer;
  // fExtDecayer is deleted in G4Decay destructor
}

//
// private methods
//

//_____________________________________________________________________________
void TG4EmPhysicsList::Configure(const G4String& /*selection*/)
{
  /// Create the selected physics constructors
  /// and registeres them in the modular physics list.

  // Standard electromagnetic physics
  RegisterPhysics(new G4EmStandardPhysics(1));

  // decay physics
  RegisterPhysics(new G4DecayPhysics());
}

//
// public methods
//

//_____________________________________________________________________________
void TG4EmPhysicsList::ConstructProcess()
{
  /// Call ase class method + add verbose info

  // create processes for registered physics
  G4VModularPhysicsList::ConstructProcess();

  if (VerboseLevel() > 0) G4cout << "### EM physics constructed. " << G4endl;
}

//_____________________________________________________________________________
G4int TG4EmPhysicsList::VerboseLevel() const
{
  /// Return verbose level (via TG4Verbose)

  return TG4Verbose::VerboseLevel();
}

//_____________________________________________________________________________
void TG4EmPhysicsList::VerboseLevel(G4int level)
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
void TG4EmPhysicsList::SetRangeCut(G4double value)
{
  /// Reset the default cut to a given value.                                 \n
  /// !!! Should be used only in PreInit phase,
  /// use SetDefaultCutValue() method of base class to reset
  /// the cut value in later phases.

  defaultCutValue = value;
}
