
#ifndef TG4_HEP_EM_PHYSICS_H
#define TG4_HEP_EM_PHYSICS_H 1

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4HepEmPhysics.h
/// \brief Definition of the TG4HepEmPhysics class
///
/// \author I. Hrivnacova; IPN Orsay

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

/// \ingroup physics_list
/// \brief Physics constructor for G4HepEm physics
///
/// According to the PhysListHepEm class provided 
/// with G4HepEm example. 
///
/// \author I. Hrivnacova; IJClab Orsay

class TG4HepEmPhysics : public G4VPhysicsConstructor {
  public:
     TG4HepEmPhysics (const G4String& name = "G4HepEm-physics-list");
     ~TG4HepEmPhysics();

  public:
    // This method is dummy for physics: particles are constructed in PhysicsList
    void ConstructParticle() override {};

    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type
    void ConstructProcess() override;
};

#endif // TG4_HEP_EM_PHYSICS_H
