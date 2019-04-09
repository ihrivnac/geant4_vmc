//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03a/geant4/src/RunConfiguration4.cxx
/// \brief Implementation of the RunConfiguration4 class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo \n
///
/// \author I. Hrivnacova; IPN, Orsay

#include "RunConfiguration4.h"
#include "PostDetConstruction.h"


namespace VMC
{
namespace E03
{

//_____________________________________________________________________________
RunConfiguration4::RunConfiguration4(const TString& userGeometry,
                                     const TString& physicsList,
                                     const TString& specialProcess,
                                     Bool_t specialStacking,
                                     Bool_t mtApplication)
  : TG4RunConfiguration(userGeometry, physicsList, specialProcess,
  	                specialStacking, mtApplication)
{
/// Standard constructor
}

//_____________________________________________________________________________
RunConfiguration4::~RunConfiguration4()
{
/// Destructor
}

//
// protected methods
//

//_____________________________________________________________________________
TG4VUserPostDetConstruction*  RunConfiguration4::CreateUserPostDetConstruction()
{
/// User defined detector construction

  return new PostDetConstruction();
}

}
}
