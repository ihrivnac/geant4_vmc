#ifndef TG4_RUN_MESSENGER_H
#define TG4_RUN_MESSENGER_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4RunMessenger.h
/// \brief Definition of the TG4RunMessenger class
///
/// \author I. Hrivnacova; IPN Orsay

#include <G4UImessenger.hh>
#include <globals.hh>

class TG4RunManager;
class TG4UICmdWithAComplexString;

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

/// \ingroup run
/// \brief Messenger class that defines commands for TG4RunManager
///
/// Implements commands:
/// - /mcControl/root
/// - /mcControl/rootMacro [macroName]
/// - /mcControl/rootCmd [cmdString]
/// - /mcControl/useRootRandom [true|false]
/// - /mcControl/g3Defaults
///
/// \author I. Hrivnacova; IPN, Orsay

class TG4RunMessenger : public G4UImessenger
{
 public:
  TG4RunMessenger(TG4RunManager* runManager);
  ~TG4RunMessenger() override;

  // methods
  void SetNewValue(G4UIcommand* command, G4String string) override;

 private:
  /// Not implemented
  TG4RunMessenger();
  /// Not implemented
  TG4RunMessenger(const TG4RunMessenger& right);
  /// Not implemented
  TG4RunMessenger& operator=(const TG4RunMessenger& right);

  // data members
  TG4RunManager* fRunManager; ///< associated class
  G4UIdirectory* fDirectory;  ///< command directory

  G4UIcmdWithoutParameter* fRootCmd;           ///< command: root
  G4UIcmdWithAString* fRootMacroCmd;           ///< command: rootMacro
  TG4UICmdWithAComplexString* fRootCommandCmd; ///< command: rootCmd
  G4UIcmdWithABool* fUseRootRandomCmd;         ///< command: useRootRandom
  G4UIcmdWithoutParameter* fG3DefaultsCmd;     ///< command: g3Defaults
};

#endif // TG4_RUN_MESSENGER_H
