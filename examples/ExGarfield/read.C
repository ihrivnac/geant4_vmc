//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2016 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file ExGarfield/read.C
/// \brief Macro for reading the Garfield simulated data from Root file

void read()
{
/// Macro for reading the Garfield simulated data from Root file
/// Note that since Root 6 the libraries have to be loaded first
/// via load_g4.C.

  // MC application
  VMC::Garfield::MCApplication* appl
    =  new VMC::ExGarfield::MCApplication("ExampleGarfield", "The example ExGarfield MC application");

  for (Int_t i=0; i<5; i++) {
    cout << "   Event no " << i+1 << ":" << endl;
    appl->ReadEvent(i);
    appl->GetCalorimeterSD()->PrintTotal();
    cout << endl;
  }
}
