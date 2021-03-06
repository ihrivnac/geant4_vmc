//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup E03
/// \file E03/load_multi.C
/// \brief Macro for loading libraries to run Example E03 with mixed Geant3 and Geant4.

#include "../macro/g3libs.C"
#include "../macro/g4libs.C"

void load_multi()
{
  // Load Geant3 and Geant4 + VMC libraries
  g3libs();
  g4libs();

  // Load this example library
  gSystem->Load("libvmc_E03c");

  // Load library with a user run configuration
  gSystem->Load("libgeant4_E03c");
}
