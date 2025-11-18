#ifndef TG4_G4_PHYS_LIST_FACTORY_H
#define TG4_G4_PHYS_LIST_FACTORY_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4PhysListFactory.h
/// \brief Definition of the TG4PhysListFactory class
///
/// \author I. Hrivnacova; IPN Orsay

#include "TG4Verbose.h"

#include <G4PhysListFactory.hh>
#include <globals.hh>

/// \ingroup physics_list
/// \brief Class G4PhysListFactory functionality extended
///        extended with G4HepEm physics
///
/// \author I. Hrivnacova; IJClab Orsay

class TG4PhysListFactory : public TG4Verbose
{
  public:
    TG4PhysListFactory(G4int verbose = 1);
    TG4PhysListFactory(const TG4PhysListFactory& right) = delete;
    TG4PhysListFactory& operator=(const TG4PhysListFactory& right) = delete;
    ~TG4PhysListFactory();
 
    // Reimplemented G4PhysListFactory functions
 
    /// Instantiate PhysList by name
    G4VModularPhysicsList* GetReferencePhysList(const G4String&);
 
    /// Instantiate PhysList by environment variable "PHYSLIST"
    G4VModularPhysicsList* ReferencePhysList();
 
    /// Check if the name is in the list of PhysLists names
    G4bool IsReferencePhysList(const G4String&) const;
 
    /// List of avalable base Phys Lists
    const std::vector<G4String>& AvailablePhysLists() const;
 
    /// List of avalable EM options
    const std::vector<G4String>& AvailablePhysListsG4EM() const;
    const std::vector<G4String>& AvailablePhysListsHepEM() const;
 
  private:
    // G4String ExtractEmOption(const G4String& name, G4bool& isHepEmOption) const;
    G4String GetHepEmOption(const G4String& name) const;
    G4String GetPhysListNameFromEnv() const;

    G4PhysListFactory fG4PhysListFactory;
#ifdef USE_G4HEPEM
    std::vector<G4String> fHepEmOptions { "_HEP", "_EMT" };
       // _HEP for G4HepEmTracking
       // _EMT for G4EmTracking
#else
     std::vector<G4String> fHepEmOptions;
#endif
};

#endif // TG4_G4_PHYS_LIST_FACTORY_H
