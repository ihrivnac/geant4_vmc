#ifndef POST_DET_CONSTRUCTION_H
#define POST_DET_CONSTRUCTION_H 1

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03a/geant4/include/PostDetConstruction.h
/// \brief Definition of the PostDetConstruction class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4VUserPostDetConstruction.h"
#include "globals.hh"

namespace VMC
{
namespace E03
{

/// Post detector construction class which integrates
/// user defined magnetic field equation of motion and integrator

class PostDetConstruction : public TG4VUserPostDetConstruction
{
  public:
    PostDetConstruction();
    virtual ~PostDetConstruction();

  public:
    virtual void Construct();
};

}
}

#endif //POST_DET_CONSTRUCTION_H

