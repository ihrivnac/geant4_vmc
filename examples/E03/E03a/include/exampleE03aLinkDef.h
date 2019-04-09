//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2014 - 2018 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file  exampleE03LinkDef.h
/// \brief The CINT link definitions for example E03 classes

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class  VMC::E03::MCApplication+;
#pragma link C++ class  VMC::E03::MCStack+;
#pragma link C++ class  VMC::E03::DetectorConstruction+;
#pragma link C++ class  VMC::E03::DetectorConstructionOld+;
#pragma link C++ class  VMC::E03::CalorHit+;
#pragma link C++ class  VMC::E03::CalorimeterSD+;
#pragma link C++ class  VMC::E03::PrimaryGenerator+;
#pragma link C++ class  std::stack<TParticle*,deque<TParticle*> >+;

#endif





