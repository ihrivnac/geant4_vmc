#ifndef TG4_SPECIAL_CUTS_H
#define TG4_SPECIAL_CUTS_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4SpecialCuts.h
/// \brief Definition of the TG4SpecialCutsFor* classes
///
/// The specifications of TG4VSpecialCuts process class
/// for different particle types. They implement only
/// the GetMinEkine() abstract function.
///
/// \author I. Hrivnacova; IPN Orsay

#include "TG4VSpecialCuts.h"

class TG4Limits;

class G4Track;

/// \ingroup physics
/// \class TG4SpecialCutsForChargedHadron
/// \brief Special process that activates kinetic energy cuts
/// for charged hadrons.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SpecialCutsForChargedHadron : public TG4VSpecialCuts
{
 public:
  TG4SpecialCutsForChargedHadron(
    const G4String& processName = "specialCutForChargedHadron");
  ~TG4SpecialCutsForChargedHadron() override;

  // methods
  G4double GetMinEkine(
    const TG4Limits& limits, const G4Track& track) const override;
};

/// \ingroup physics
/// \class TG4SpecialCutsForElectron
/// \brief Special process that activates kinetic energy cuts
/// for e-.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SpecialCutsForElectron : public TG4VSpecialCuts
{
 public:
  TG4SpecialCutsForElectron(
    const G4String& processName = "specialCutForElectron");
  ~TG4SpecialCutsForElectron() override;

  // methods
  G4double GetMinEkine(
    const TG4Limits& limits, const G4Track& track) const override;
};

/// \ingroup physics
/// \class TG4SpecialCutsForGamma
/// \brief Special process that activates kinetic energy cuts
/// for gamma.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SpecialCutsForGamma : public TG4VSpecialCuts
{
 public:
  TG4SpecialCutsForGamma(const G4String& processName = "specialCutForGamma");
  ~TG4SpecialCutsForGamma() override;

  // methods
  G4double GetMinEkine(
    const TG4Limits& limits, const G4Track& track) const override;
};

/// \ingroup physics
/// \class TG4SpecialCutsForMuon
/// \brief Special process that activates kinetic energy cuts
/// for muon.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SpecialCutsForMuon : public TG4VSpecialCuts
{
 public:
  TG4SpecialCutsForMuon(const G4String& processName = "specialCutForMuon");
  ~TG4SpecialCutsForMuon() override;

  // methods
  G4double GetMinEkine(
    const TG4Limits& limits, const G4Track& track) const override;
};

/// \ingroup physics
/// \class TG4SpecialCutsForNeutralHadron
/// \brief Special process that activates kinetic energy cuts
/// for neutral hadrons.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SpecialCutsForNeutralHadron : public TG4VSpecialCuts
{
 public:
  TG4SpecialCutsForNeutralHadron(
    const G4String& processName = "specialCutForNeutralHadron");
  ~TG4SpecialCutsForNeutralHadron() override;

  // methods
  G4double GetMinEkine(
    const TG4Limits& limits, const G4Track& track) const override;
};

/// \ingroup physics
/// \class TG4SpecialCutsForNeutron
/// \brief Special process that activates kinetic energy cuts
/// for neutrons,
///
/// This process overrides also the default PostStepDoIt() and
/// sets the particle status to fStopAndKill instead of fStopButAlive.
/// It is activated in TG4SpeialCutsPhysics only when neutron killer
/// process was applied by Geant4 physics list.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SpecialCutsForNeutron : public TG4VSpecialCuts
{
 public:
  TG4SpecialCutsForNeutron(
    const G4String& processName = "specialCutForNeutron");
  ~TG4SpecialCutsForNeutron() override;

  // methods
  G4double GetMinEkine(
    const TG4Limits& limits, const G4Track& track) const override;
  G4VParticleChange* PostStepDoIt(
    const G4Track& track, const G4Step& /*step*/) override;
};

#endif // TG4_SPECIAL_CUTS_H
