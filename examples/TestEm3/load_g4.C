//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup TestEm3
/// \file TestEm3/load_g4a.C
/// \brief Macro for loading libraries to run example TestEm3 with Geant4.

#include "../macro/g4libs.C"

void load_g4()
{
  // Load Geant4 + VMC libraries
  g4libs();

  // Load this example library
  gSystem->Load("libvmc_TestEm3");

  // Load library with a user run configuration
  gSystem->Load("libgeant4_TestEm3");
}
