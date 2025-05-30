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
{}


//_____________________________________________________________________________
TG4PhysListFactory::~TG4PhysListFactory()
{}

//
// private methods
//
 
// //_____________________________________________________________________________
// G4String TG4PhysListFactory::ExtractEmOption(
//   const G4String& name, G4bool& isHepEmOption) const
// {
//   // last characters in the string
//   G4String emOption = "";
//   if (nameSize <= 4) return emOption;
 
//   emOption = name.substr(nameSize - 4, 4);
//   isHepEmOption = false;

//   // Check if it is  EM options defined in G4 or in fG4HepEmNames
//   auto& g4EmOptions = fG4PhysListFactory.AvailablePhysListsEM();

//   // check EM options
//   for (const auto& value : g4EmOptions) { 
//     if (emOption == value) {
//       // the option is valid G4 option
//       return emOption;
//     }
//   }

//   // check G4HepEmOptions
//   for (const auto& value : fG4HepEmOptions) { 
//     if (emOption == value) {
//       // the option is valid G4 option
//       isHepEmOption = true;
//       return emOption;
//     }
//   }

//   // otherwise not valid option
//   return "";
// }

//_____________________________________________________________________________
G4String TG4PhysListFactory::GetHepEmOption(
  const G4String& name) const
{
  G4cout << "processing " << name << " " << name.size() << G4endl;

  // last characters in the string
  G4String emOption = "";
  if (name.size() < 4) return emOption;
 
  emOption = name.substr(name.size() - 4, 4);
  G4cout << emOption  << G4endl;

  // check G4HepEmOptions
  for (const auto& value : fHepEmOptions) {
    G4cout << value << " vs " << emOption << G4endl;
    if (emOption == value) {
      // the option is valid G4 option
      G4cout << "Go to return " << emOption << G4endl;
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

  G4cout << "TG4PhysListFactory::GetReferencePhysList" << G4endl;

#ifndef USE_G4HEPEM
    // construct PL via G4PhysListFactory
    return fG4PhysListFactory.GetReferencePhysList(name);
#else
  auto hepEmOption = GetHepEmOption(name);
  G4cout << "hepEmOption: " << hepEmOption << G4endl;

  if (hepEmOption.empty()) {
    // construct PL via G4PhysListFactory
    G4cout << "go to call fG4PhysListFactory " << G4endl;
    return fG4PhysListFactory.GetReferencePhysList(name);
  }

  // construct PL with G4HepEmPhysics
  
  // get hadronic physics list name
  size_t nsize = name.size();
  auto hadName = name.substr(0, nsize - 4);

  G4cout << "hadName: " << hadName << G4endl;

  // get PL constructed by G4 factory with EM option 0
  auto physList = fG4PhysListFactory.GetReferencePhysList(hadName);
  G4cout << "got PL: " << physList  << G4endl;


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

  return physList;
#endif
} 

//_____________________________________________________________________________
G4VModularPhysicsList* TG4PhysListFactory::ReferencePhysList()
{
  // Instantiate PhysList by environment variable "PHYSLIST"

  auto name = GetPhysListNameFromEnv();

  // auto hepEmOption = GetHepEmOption(name);

  // if (hepEmOption.empty()) {
  //   // construct PL via G4PhysListFactory
  //   return fG4PhysListFactory.ReferencePhysList();
  // }

  // // construct PL with G4HepEmPhysics  
  return GetReferencePhysList(name);
}
 
//_____________________________________________________________________________
G4bool TG4PhysListFactory::IsReferencePhysList(const G4String& name) const
{
  // Check if the name is in the list of PhysLists names

  G4cout << "TG4PhysListFactory::IsReferencePhysList" << G4endl;

  auto hepEmOption = GetHepEmOption(name);

  G4cout << "hepEmOption: " << hepEmOption << G4endl;

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
