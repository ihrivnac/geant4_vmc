//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file RunConfiguration.cxx
/// \brief Implementation of the RunConfiguration class
///
/// Geant4 TestEm3 adapted to Virtual Monte Carlo \n
///
/// \author I. Hrivnacova; IJCLab, Orsay

#include "RunConfiguration.h"

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

#include "TG4PrimaryGeneratorAction.h"

//_____________________________________________________________________________
RunConfiguration::RunConfiguration(
  const TString& physicsList, const TString& specialProcess)
  : TG4RunConfiguration("geomGeant4", physicsList, specialProcess)
{
  /// Standard constructor
  /// \param physicsList     Selection of physics
  /// \param specialProcess  Selection of the special processes
  ///
  /// The option for geometry selection has to be set here to "geomGeant4",
  /// as geometry will be defined directly via Geant4.
  /// \see More on the available option in class TG4RunConfiguration:
  /// http://ivana.home.cern.ch/ivana/g4vmc_html/classTG4RunConfiguration.html

  if (physicsList == "local") {
    fIsLocalPhysicsList = true;
  }
}

//_____________________________________________________________________________
RunConfiguration::~RunConfiguration()
{
  /// Destructor
}

//
// protected methods
//

//_____________________________________________________________________________
G4VUserDetectorConstruction* RunConfiguration::CreateDetectorConstruction()
{
  fDetector = new DetectorConstruction();
  return fDetector;
}

//_____________________________________________________________________________
G4VUserPhysicsList* RunConfiguration::CreatePhysicsList()
{
  if (! fIsLocalPhysicsList) {
    return TG4RunConfiguration::CreatePhysicsList();
  }

  return new PhysicsList();
}

//_____________________________________________________________________________
G4VUserPrimaryGeneratorAction* RunConfiguration::CreatePrimaryGenerator()
{
  fGenerator = new PrimaryGeneratorAction(fDetector);
  return fGenerator;
}

//_____________________________________________________________________________
G4UserRunAction*  RunConfiguration::CreateRunAction()
{
  fRunAction = new RunAction(fDetector, fGenerator);
  return fRunAction;
}

//_____________________________________________________________________________
G4UserEventAction* RunConfiguration::CreateEventAction()
{
  fEventAction = new EventAction(fDetector);
  return fEventAction;
}

//_____________________________________________________________________________
TG4TrackingAction* RunConfiguration::CreateTrackingAction()
{
  return new TrackingAction(fDetector, fEventAction);
}

//_____________________________________________________________________________
TG4SteppingAction* RunConfiguration::CreateSteppingAction()
{
  return new SteppingAction(fDetector, fEventAction);  
}
