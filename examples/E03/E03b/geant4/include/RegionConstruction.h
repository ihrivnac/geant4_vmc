#ifndef REGION_CONSTRUCTION_H
#define REGION_CONSTRUCTION_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03a/geant4/include/RegionConstruction.h
/// \brief Definition of the RegionConstruction class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4VUserRegionConstruction.h"

namespace VMC
{
namespace E03
{

/// \ingroup E03
/// \brief Special class for definition of regions
///
/// \author I. Hrivnacova; IPN, Orsay

class RegionConstruction : public TG4VUserRegionConstruction
{
  public:
    RegionConstruction();
    virtual ~RegionConstruction();

    // methods
    virtual void Construct();
};

}
}

#endif //REGION_CONSTRUCTION_H

