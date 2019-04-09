//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03a/geant4/src/RunConfiguration2.cxx
/// \brief Implementation of the RunConfiguration2 class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo \n
///
/// \author I. Hrivnacova; IPN, Orsay

#include "RunConfiguration2.h"
//#include "ExN03PrimaryGeneratorAction.hh"
//#include "ExN03DetectorConstruction.hh"

#include "TG4ComposedPhysicsList.h"
#include "TG4SpecialPhysicsList.h"

#include <QGSP_BERT.hh>

namespace VMC
{
namespace E03
{

//_____________________________________________________________________________
RunConfiguration2::RunConfiguration2(const TString& userGeometry,
                                     const TString& specialProcess)
  : TG4RunConfiguration(userGeometry, "FTFP_BERT", specialProcess)
{
/// Standard constructor
/// \param userGeometry    Selection of geometry input and navigation
/// \param specialProcess  Selection of the special processes
///
/// The physics physics list selection ("FTFP_BERT") is not used,
/// \see More on the available option in class TG4RunConfiguration:
/// http://ivana.home.cern.ch/ivana/g4vmc_html/classTG4RunConfiguration.html
}

//_____________________________________________________________________________
RunConfiguration2::~RunConfiguration2()
{
/// Destructor
}

//
// protected methods
//


//_____________________________________________________________________________
G4VUserPhysicsList*  RunConfiguration2::CreatePhysicsList()
{
/// Override the default physics list with user defined physics list;
/// LHEP_BERT physics list should be replaced with user own physics list

  TG4ComposedPhysicsList* builder = new TG4ComposedPhysicsList();

  // User physics list
  G4cout << "Adding user physics list " << G4endl;
  builder->AddPhysicsList(new QGSP_BERT());

  G4cout << "Adding SpecialPhysicsList " << G4endl;
  builder->AddPhysicsList(new TG4SpecialPhysicsList(
                                 fSpecialProcessSelection.Data()));

  return builder;
}


/*
//_____________________________________________________________________________
G4VUserDetectorConstruction*  RunConfiguration2::CreateDetectorConstruction()
{
/// Create detector construction

  return new ExN03DetectorConstruction();
}


//_____________________________________________________________________________
G4VUserPrimaryGeneratorAction* RunConfiguration2::CreatePrimaryGenerator()
{
/// Create primary generator

  return new ExN03PrimaryGeneratorAction();
}
*/

}
}
