#ifndef TG4_EM_TRACKING_PHYSICS_H
#define TG4_EM_TRACKING_PHYSICS_H 1
#ifdef USE_G4HEPEM

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4EmTrackingPhysics
/// \brief Definition of the TG4EmTrackingPhysics class
///
/// \author I. Hrivnacova; IPN Orsay

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

/// \ingroup physics_list
/// \brief Physics constructor to register custom tracking manager
///        for e-/e+ and gammas
///
/// According to the PhysListG4EmTracking class provided 
/// with G4HepEm example. 
///
/// \author I. Hrivnacova; IJClab Orsay

class TG4EmTrackingPhysics : public G4VPhysicsConstructor
{
  public: 
    TG4EmTrackingPhysics(const G4String& name = "G4EmTracking");
    ~TG4EmTrackingPhysics();

  public: 
    void ConstructParticle() override {}

    void ConstructProcess() override;
};

#endif
#endif // TG4_EM_TRACKING_PHYSICS_H
