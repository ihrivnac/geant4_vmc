#ifndef TG4_MODEL_CONFIGURATION_H
#define TG4_MODEL_CONFIGURATION_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4ModelConfiguration.h
/// \brief Definition of the TG4ModelConfiguration class
///
/// \author I. Hrivnacova; IPN Orsay

#include <globals.hh>

#include <vector>

class G4VFastSimulationModel;

/// \ingroup global
/// \brief A helper class to hold a configuration of a special physics model.
///
/// The class holds the information about the association of
/// the special physics model (EM physics or fast simulation model)
/// and the applicable regions (G4Region) defined via tracking media
/// and particles.
///
/// \author I. Hrivnacova; IPN Orsay

class TG4ModelConfiguration
{
 public:
  TG4ModelConfiguration(const G4String& modelName);

  // methods
  void Print() const;

  // set methods
  void SetParticles(const G4String& particles);
  void SetExcludedParticles(const G4String& particles);
  void SetRegionsMedia(const G4String& regionsMedia);
  void SetOneRegionMedium(const G4String& regionMedium);
  void SetOneRegion(const G4String& region);
  void SetFastSimulationModel(G4VFastSimulationModel* fastSimulationModel);

  // get methods
  const G4String& GetModelName() const;
  const G4String& GetParticles() const;
  const G4String& GetExcludedParticles() const;
  const std::vector<G4String>& GetRegionsMedia() const;
  const std::vector<G4String>& GetRegions() const;
  G4VFastSimulationModel* GetFastSimulationModel() const;

  G4bool HasParticle(const G4String& particleName);
  G4bool HasRegion(const G4String& regionName);

 private:
  /// not implemented
  TG4ModelConfiguration(const TG4ModelConfiguration& right);
  /// not implemented
  TG4ModelConfiguration& operator=(const TG4ModelConfiguration& right);

  // data members
  G4String fModelName;                 ///< the EM model name
  G4String fParticles;                 ///< the list of particle names
  G4String fExcludedParticles;         ///< the list of excluded particle names
  std::vector<G4String> fRegionsMedia; ///< the vector of regions media
  std::vector<G4String>
    fRegions; ///< the vector of created regions (per materials)
  G4VFastSimulationModel* fFastSimulationModel; ///< fast simulation model
};

// inline functions

inline void TG4ModelConfiguration::SetParticles(const G4String& particles)
{
  /// Set the list of particles
  fParticles = particles;
}

inline void TG4ModelConfiguration::SetExcludedParticles(const G4String& particles)
{
  /// Set the list of particles
  fExcludedParticles = particles;
}

inline void TG4ModelConfiguration::SetFastSimulationModel(
  G4VFastSimulationModel* fastSimulationModel)
{
  /// Set fast simulation model
  fFastSimulationModel = fastSimulationModel;
}

inline const G4String& TG4ModelConfiguration::GetModelName() const
{
  /// Return the energy loss model name
  return fModelName;
}

inline const G4String& TG4ModelConfiguration::GetParticles() const
{
  /// Return the list of particles
  return fParticles;
}

inline const G4String& TG4ModelConfiguration::GetExcludedParticles() const
{
  /// Return the list of particles
  return fExcludedParticles;
}

inline const std::vector<G4String>&
TG4ModelConfiguration::GetRegionsMedia() const
{
  /// Return the list of regions
  return fRegionsMedia;
}

inline const std::vector<G4String>& TG4ModelConfiguration::GetRegions() const
{
  /// Return the list of regions
  return fRegions;
}

inline G4VFastSimulationModel*
TG4ModelConfiguration::GetFastSimulationModel() const
{
  /// Return fast simulation model
  return fFastSimulationModel;
}

#endif // TG4_MODEL_CONFIGURATION_H
