#ifndef TG4_HEP_EM_TRACKING_PHYSICS_H
#define TG4_HEP_EM_TRACKING_PHYSICS_H 1

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4HepEmTrackingPhysics.h
/// \brief Definition of the TG4HepEmTrackingPhysics class
///
/// \author I. Hrivnacova; IPN Orsay

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

/// \ingroup physics_list
/// \brief Physics constructor for G4HepEmTracking physics
///
/// According to the PhysListHepEmTracking class provided 
/// with G4HepEm example. 
///
/// \author I. Hrivnacova; IJClab Orsay

class TG4HepEmTrackingPhysics : public G4VPhysicsConstructor
{
  public: 
    TG4HepEmTrackingPhysics(const G4String& name = "HepEmTracking");
    ~TG4HepEmTrackingPhysics();

  public: 
    void ConstructParticle() override {}

    void ConstructProcess() override;
};

#endif // TG4_HEP_EM_TRACKING_PHYSICS_H
