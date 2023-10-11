#ifndef TG4_SD_MESSENGER_H
#define TG4_SD_MESSENGER_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4SDMessenger.h
/// \brief Definition of the TG4SDMessenger class
///
/// \author I. Hrivnacova; IPN Orsay

#include <G4UImessenger.hh>
#include <globals.hh>

class TG4SDConstruction;

class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

/// \ingroup physics_list
/// \brief Messenger class that defines commands for the SD construction
///
/// Implements commands:
/// - /mcDet/addSDSelection volName1 [volName2 ...]
/// - /mcDet/setSDSelectionFromTGeo  true|false
/// - /mcDet/setSVLabel label
/// - /mcDet/setGflash  true|false
/// - /mcDet/setExclusiveSDScoring true|false
/// - /mcDet/printUserSDs
///
/// \author I. Hrivnacova; IPN Orsay

class TG4SDMessenger : public G4UImessenger
{
 public:
  TG4SDMessenger(TG4SDConstruction* sdConstruction);
  ~TG4SDMessenger() override;

  // methods
  void SetNewValue(G4UIcommand* command, G4String string) override;

 private:
  /// Not implemented
  TG4SDMessenger();
  /// Not implemented
  TG4SDMessenger(const TG4SDMessenger& right);
  /// Not implemented
  TG4SDMessenger& operator=(const TG4SDMessenger& right);

  //
  // data members

  /// associated class
  TG4SDConstruction* fSDConstruction;

  /// addSDSelection command
  G4UIcmdWithAString* fAddSDSelectionCmd;

  /// getSDSelectionFromTGeo command
  G4UIcmdWithABool* fSetSDSelectionFromTGeoCmd;

  /// setSVLabel command
  G4UIcmdWithAString* fSetSVLabelCmd;

  /// setGflash command
  G4UIcmdWithABool* fSetGflashCmd;

  /// setExclusiveSDScoring command
  G4UIcmdWithABool* fSetExclusiveSDScoringCmd;

  /// command: printVolumes
  G4UIcmdWithoutParameter* fPrintUserSDsCmd;
};

#endif // TG4_SD_MESSENGER_H
