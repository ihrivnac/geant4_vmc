//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4PhysListFactory.cxx
/// \brief Implementation of the TG4PhysListFactory class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4PhysListFactory.h"
#ifdef USE_G4HEPEM
#include "TG4HepEmPhysics.h"
#include "TG4HepEmTrackingPhysics.h"
#include "TG4EmTrackingPhysics.h"
#endif

#include <G4DecayPhysics.hh>
#include <G4EmStandardPhysics.hh>
#include <G4SystemOfUnits.hh>

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4ProcessTable.hh>

//
// ctors, dtor
//

//_____________________________________________________________________________
TG4PhysListFactory::TG4PhysListFactory(G4int verbose)
  : TG4Verbose("physListFactory", verbose)
{
  if (verbose > 0) {
    fG4PhysListFactory.SetVerbose(verbose - 1);
  }
}


//_____________________________________________________________________________
TG4PhysListFactory::~TG4PhysListFactory()
{}

//
// private methods
//

//_____________________________________________________________________________
G4String TG4PhysListFactory::GetHepEmOption(
  const G4String& name) const
{
  // last characters in the string
  G4String emOption = "";
  if (name.size() < 4) return emOption;
 
  emOption = name.substr(name.size() - 4, 4);

  // check G4HepEmOptions
  for (const auto& value : fHepEmOptions) {
    if (emOption == value) {
      // the option is valid G4 option
      return emOption;
    }
  }

  // otherwise not valid option
  return "";
}

//_____________________________________________________________________________
G4String TG4PhysListFactory::GetPhysListNameFromEnv() const
{
  // Get PhysList by environment variable "PHYSLIST"
  // From G4PhysListFactory::ReferencePhysList()

  G4String name = "";
  char* path = std::getenv("PHYSLIST");
  if (path) {
    name = G4String(path);
  } 
  return name;
}

//
// public methods
//

//_____________________________________________________________________________
G4VModularPhysicsList* TG4PhysListFactory::GetReferencePhysList(
  const G4String& name)
{
  // Instantiate PhysList by name

#ifndef USE_G4HEPEM
    // construct PL via G4PhysListFactory
    return fG4PhysListFactory.GetReferencePhysList(name);
#else
  auto hepEmOption = GetHepEmOption(name);

  if (hepEmOption.empty()) {
    // construct PL via G4PhysListFactory
    return fG4PhysListFactory.GetReferencePhysList(name);
  }

  // construct PL with G4HepEmPhysics
  
  // get hadronic physics list name
  size_t nsize = name.size();
  auto hadName = name.substr(0, nsize - 4);

  // get PL constructed by G4 factory with EM option 0
  auto physList = fG4PhysListFactory.GetReferencePhysList(hadName);

  // now replace EM option 0 with G4HepEm
  if (hepEmOption == "_HEP") {
    physList->ReplacePhysics(new TG4HepEmPhysics()); // add verbose to PL
  }
  if (hepEmOption == "_HET") {
    physList->ReplacePhysics(new TG4HepEmTrackingPhysics()); // add verbose to PL
  }
  else if (hepEmOption == "_EMT") {
    // only add 
    physList->RegisterPhysics(new TG4EmTrackingPhysics()); // add verbose to PL
  }

  if (VerboseLevel() > 0) {
    G4cout << "Geant4 Physics List simulation engine: " << name << G4endl << G4endl;
  }

  return physList;
#endif
} 

//_____________________________________________________________________________
G4VModularPhysicsList* TG4PhysListFactory::ReferencePhysList()
{
  // Instantiate PhysList by environment variable "PHYSLIST"

  auto name = GetPhysListNameFromEnv();

  return GetReferencePhysList(name);
}
 
//_____________________________________________________________________________
G4bool TG4PhysListFactory::IsReferencePhysList(const G4String& name) const
{
  // Check if the name is in the list of PhysLists names

  auto hepEmOption = GetHepEmOption(name);

  if (hepEmOption.empty()) {
    return fG4PhysListFactory.IsReferencePhysList(name);
  }

  // check with HepEmOption
  // TO DO
  return true;
}
 
//_____________________________________________________________________________
const std::vector<G4String>& TG4PhysListFactory::AvailablePhysLists() const
{
  // List of avalable base Phys Lists
  return fG4PhysListFactory.AvailablePhysLists();
}

//_____________________________________________________________________________
const std::vector<G4String>& TG4PhysListFactory::AvailablePhysListsG4EM() const
{
  /// List of avalable EM options in Geant4
  return fG4PhysListFactory.AvailablePhysListsEM();
}

//_____________________________________________________________________________
const std::vector<G4String>& TG4PhysListFactory::AvailablePhysListsHepEM() const
{
  /// List of avalable HEP EM options in Geant4
  return fHepEmOptions;
}
