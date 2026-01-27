#ifndef TG4_V_SCORE_WEIGHT_CALCULATOR__H
#define TG4_V_SCORE_WEIGHT_CALCULATOR__H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4VScoreWeightCalculator.h
/// \brief Definition of the TG4VScoreWeightCalculator class
///
/// \author I. Hrivnacova, IJCLab Orsay

#include "G4Types.hh"

class G4Step;

class TG4VScoreWeightCalculator {
public:
    virtual ~TG4VScoreWeightCalculator() = default;

    virtual G4double GetWeight(const G4Step* step) const = 0;
};

#endif
