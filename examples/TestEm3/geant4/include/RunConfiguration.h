#ifndef RUN_CONFIGURATION1_H
#define RUN_CONFIGURATION1_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file RunConfiguration1.h
/// \brief Definition of the Ex03RunConfiguration1 class
///
/// Geant4 TestEm3 adapted to Virtual Monte Carlo
///
/// \author I. Hrivnacova; IJCLab, Orsay

#include "TG4RunConfiguration.h"

/// \ingroup TestEm3
/// \brief User Geant4 VMC run configuration
///
/// This class overrides setting of the default Geant4 VMC geometry
/// construction and primary generator with Geant4 user classes
///
/// \author I. Hrivnacova; IJCLab, Orsay

class RunConfiguration : public TG4RunConfiguration
{
 public:
  RunConfiguration(const TString& physicsList = "FTFP_BERT",
    const TString& specialProcess = "stepLimiter");
  virtual ~RunConfiguration();

  // methods
  virtual G4VUserDetectorConstruction* CreateDetectorConstruction();
  virtual G4VUserPhysicsList* CreatePhysicsList();
  virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGenerator();

  virtual G4UserRunAction* CreateRunAction();
  virtual G4UserEventAction* CreateEventAction();
  virtual TG4TrackingAction* CreateTrackingAction();
  virtual TG4SteppingAction* CreateSteppingAction();

 private:
   G4VUserDetectorConstruction* fDetector = nullptr;
   G4VUserPrimaryGeneratorAction* fGenerator = nullptr;
   G4UserEventAction* fEventAction = nullptr;
   G4UserRunAction* fRunAction = nullptr;
   Bool_t fIsLocalPhysicsList = false;
};

#endif // RUN_CONFIGURATION1_H
