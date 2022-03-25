#ifndef TG4_RUN_ACTION_MESSENGER_H
#define TG4_RUN_ACTION_MESSENGER_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4RunActionMessenger.h
/// \brief Definition of the TG4RunActionMessenger class
///
/// \author I. Hrivnacova; IPN, Orsay

#include <G4UImessenger.hh>

class TG4RunAction;

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

/// \ingroup event
/// \brief Messenger class that defines commands for TG4RunAction.
///
/// Implements command
/// - /mcRun/storePhysicsTable [true|false]
/// - /mcRun/setPhysicsTableDir dirName
/// - /mcRun/saveRandom [true|false]
/// - /mcRun/readRandom [true|false]
/// - /mcRun/setRandomFile fileName
/// - /mcRun/setLooperThresholdWarningEnergy value unit
/// - /mcRun/setLooperThresholImportantEnergy value unit
/// - /mcRun/setNumberOfLooperThresholdTrials value
///
/// \author I. Hrivnacova; IPN, Orsay

class TG4RunActionMessenger : public G4UImessenger
{
 public:
  TG4RunActionMessenger(TG4RunAction* runAction);
  virtual ~TG4RunActionMessenger();

  // methods
  virtual void SetNewValue(G4UIcommand* command, G4String string);

 private:
  /// Not implemented
  TG4RunActionMessenger();
  /// Not implemented
  TG4RunActionMessenger(const TG4RunActionMessenger& right);
  /// Not implemented
  TG4RunActionMessenger& operator=(const TG4RunActionMessenger& right);

  // data members
  TG4RunAction* fRunAction;                 ///< associated class
  G4UIdirectory* fRunDirectory;             ///< command directory
  G4UIcmdWithABool* fStorePhysicsTableCmd;  ///< command: saveRandom
  G4UIcmdWithAString* fPhysicsTableDirCmd;  ///< command: setRandomFile
  G4UIcmdWithABool* fSaveRandomStatusCmd;   ///< command: saveRandom
  G4UIcmdWithABool* fReadRandomStatusCmd;   ///< command: readRandom
  G4UIcmdWithAString* fRandomStatusFileCmd; ///< command: setRandomFile

  /// setLooperThresholdWarningEnergy command
  G4UIcmdWithADoubleAndUnit* fSetLooperThresholdWarningEnergyCmd;

  /// setLooperThresholImportantEnergy command
  G4UIcmdWithADoubleAndUnit* fSetLooperThresholdImportantEnergyCmd;

  /// setNumberOfLooperThresholdTrials
  G4UIcmdWithAnInteger* fSetNumberOfLooperThresholdTrialsCmd;
};

#endif // TG4_RUN_ACTION_MESSENGER_H
#ifndef TG4_RUN_ACTION_MESSENGER_H
#define TG4_RUN_ACTION_MESSENGER_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4RunActionMessenger.h
/// \brief Definition of the TG4RunActionMessenger class
///
/// \author I. Hrivnacova; IPN, Orsay

#include <G4UImessenger.hh>

class TG4RunAction;

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

/// \ingroup event
/// \brief Messenger class that defines commands for TG4RunAction.
///
/// Implements command
/// - /mcRun/saveRandom [true|false]
/// - /mcRun/readRandom [true|false]
/// - /mcRun/setRandomFile fileName
///
/// \author I. Hrivnacova; IPN, Orsay

class TG4RunActionMessenger : public G4UImessenger
{
 public:
  TG4RunActionMessenger(TG4RunAction* runAction);
  virtual ~TG4RunActionMessenger();

  // methods
  virtual void SetNewValue(G4UIcommand* command, G4String string);

 private:
  /// Not implemented
  TG4RunActionMessenger();
  /// Not implemented
  TG4RunActionMessenger(const TG4RunActionMessenger& right);
  /// Not implemented
  TG4RunActionMessenger& operator=(const TG4RunActionMessenger& right);

  // data members
  TG4RunAction* fRunAction;                 ///< associated class
  G4UIdirectory* fRunDirectory;             ///< command directory
  G4UIcmdWithABool* fSaveRandomStatusCmd;   ///< command: saveRandom
  G4UIcmdWithABool* fReadRandomStatusCmd;   ///< command: readRandom
  G4UIcmdWithAString* fRandomStatusFileCmd; ///< command: setRandomFile
};

#endif // TG4_RUN_ACTION_MESSENGER_H
