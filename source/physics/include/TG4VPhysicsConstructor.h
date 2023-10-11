#ifndef TG4_V_PHYSICS_CONSTRUCTOR_H
#define TG4_V_PHYSICS_CONSTRUCTOR_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4VPhysicsConstructor.h
/// \brief Definition of the TG4VPhysicsConstructor class
///
/// \author I. Hrivnacova; IPN Orsay

#include "TG4Verbose.h"

#include <G4VPhysicsConstructor.hh>
#include <globals.hh>

/// \ingroup physics
/// \brief Abstract base class for physics constructors with verbose.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4VPhysicsConstructor : public G4VPhysicsConstructor, public TG4Verbose
{
 public:
  TG4VPhysicsConstructor(const G4String& name);
  TG4VPhysicsConstructor(const G4String& name, G4int theVerboseLevel);
  ~TG4VPhysicsConstructor() override;

  // methods
  /// Construct particles
  void ConstructParticle() override = 0;

  /// Construct physics processes
  void ConstructProcess() override = 0;

 protected:
  // overridden verbose methods
  void VerboseLevel(G4int level) override;
  G4int VerboseLevel() const override;

 private:
  /// Not implemented
  TG4VPhysicsConstructor();
  /// Not implemented
  TG4VPhysicsConstructor(const TG4VPhysicsConstructor& right);
};

#endif // TG4_V_PHYSICS_CONSTRUCTOR_H
