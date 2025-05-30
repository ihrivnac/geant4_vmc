//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4HadronPhysicsList.cxx
/// \brief Implementation of the TG4HadronPhysicsList class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4HadronPhysicsList.h"
#include "TG4PhysListFactory.h"

#include <G4SystemOfUnits.hh>

const G4double TG4HadronPhysicsList::fgkDefaultCutValue = 1.0 * mm;

//
// static methods
//

//_____________________________________________________________________________
G4String TG4HadronPhysicsList::AvailableHadronSelections()
{
  /// Return list of all available hadron physics lists selections

  TG4PhysListFactory phyListFactory;
  const std::vector<G4String>& availablePhysLists =
    phyListFactory.AvailablePhysLists();

  G4String selections;
  for (const auto& option : phyListFactory.AvailablePhysLists()) {
    selections += option;
    selections += " ";
  }
  // selections += "ShieldingLEND ";

  return selections;
}

//_____________________________________________________________________________
G4String TG4HadronPhysicsList::AvailableEMSelections()
{
  /// Return list of all available EM options selections

  TG4PhysListFactory phyListFactory;

  G4String selections;
  for (const auto& option : phyListFactory.AvailablePhysListsG4EM()) {
    selections += option;
    selections += " ";
  }
  for (const auto& option : phyListFactory.AvailablePhysListsHepEM()) {
    selections += option;
    selections += " ";
  }

  return selections;
}

//_____________________________________________________________________________
G4bool TG4HadronPhysicsList::IsAvailableSelection(const G4String& selection)
{
  /// Return list of all available selections

  G4cout << "TG4HadronPhysicsList::IsAvailableSelection" << G4endl;

  TG4PhysListFactory physListFactory;
  return physListFactory.IsReferencePhysList(selection);
}

//
// ctors, dtor
//

//_____________________________________________________________________________
TG4HadronPhysicsList::TG4HadronPhysicsList(const G4String& selection)
  : G4VUserPhysicsList(), TG4Verbose("hadronPhysicsList")
{
  /// Standard constructor

  Configure(selection);

  defaultCutValue = fgkDefaultCutValue;

  SetVerboseLevel(TG4Verbose::VerboseLevel());
}

//_____________________________________________________________________________
TG4HadronPhysicsList::~TG4HadronPhysicsList()
{
  /// Destructor

  // delete fExtDecayer;
  // fExtDecayer is deleted in G4Decay destructor
}

//
// private methods
//

//_____________________________________________________________________________
void TG4HadronPhysicsList::Configure(const G4String& sel)
{
  /// Create the selected physics constructors
  /// and registeres them in the modular physics list.

  TG4PhysListFactory phyListFactory;

  fPhysicsList = phyListFactory.GetReferencePhysList(sel);
}

//
// public methods
//

//_____________________________________________________________________________
void TG4HadronPhysicsList::ConstructParticle()
{
  /// Construct particles.

  // create processes for registered physics
  fPhysicsList->ConstructParticle();
}

//_____________________________________________________________________________
void TG4HadronPhysicsList::ConstructProcess()
{
  /// Construct processes.

  // create processes for registered physics
  fPhysicsList->ConstructProcess();

  if (VerboseLevel() > 0)
    G4cout << "### Hadron physics constructed. " << G4endl;
}

//_____________________________________________________________________________
G4int TG4HadronPhysicsList::VerboseLevel() const
{
  /// Return verbose level (via TG4Verbose)

  return TG4Verbose::VerboseLevel();
}

//_____________________________________________________________________________
void TG4HadronPhysicsList::VerboseLevel(G4int level)
{
  /// Set the specified level to both TG4Verbose and
  /// G4VModularPhysicsList.
  /// The verbose level is also propagated to the registered physics list.

  TG4Verbose::VerboseLevel(level);
  fPhysicsList->SetVerboseLevel(level);
}

//_____________________________________________________________________________
void TG4HadronPhysicsList::SetRangeCut(G4double value)
{
  /// Reset the default cut to a given value.                                 \n
  /// !!! Should be used only in PreInit phase,
  /// use SetDefaultCutValue() method of base class to reset
  /// the cut value in later phases.

  defaultCutValue = value;
}
