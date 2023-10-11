#ifndef TG4_EVENT_ACTION_H
#define TG4_EVENT_ACTION_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4EventAction.h
/// \brief Definition of the TG4EventAction class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4EventActionMessenger.h"
#include "TG4Verbose.h"

#include <TStopwatch.h>

#include <G4UserEventAction.hh>
#include <globals.hh>

class TG4TrackingAction;
class TG4TrackManager;
class TG4StateManager;

class TVirtualMCApplication;
class TVirtualMCStack;

class G4Event;

/// \ingroup event
/// \brief Actions at the beginning and the end of event.
///
/// \author I. Hrivnacova; IPN, Orsay

class TG4EventAction : public G4UserEventAction, public TG4Verbose
{
 public:
  TG4EventAction();
  ~TG4EventAction() override;

  // methods
  void LateInitialize();
  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;

  // set methods
  void SetMCStack(TVirtualMCStack* mcStack);
  void SetPrintMemory(G4bool printMemory);
  void SetSaveRandomStatus(G4bool saveRandomStatus);
  void SetIsInterruptibleEvent(G4bool isInterruptible);

  // get methods
  G4bool GetPrintMemory() const;
  G4bool GetSaveRandomStatus() const;
  G4bool IsInterruptibleEvent() const;

 private:
  /// Not implemented
  TG4EventAction(const TG4EventAction& right);
  /// Not implemented
  TG4EventAction& operator=(const TG4EventAction& right);

  // data members
  TG4EventActionMessenger fMessenger; ///< messenger
  TStopwatch fTimer;                  ///< timer

  /// Cached pointer to thread-local VMC application
  TVirtualMCApplication* fMCApplication;

  /// Cached pointer to thread-local VMC stack
  TVirtualMCStack* fMCStack;

  /// Cached pointer to thread-local tracking action
  TG4TrackingAction* fTrackingAction;

  /// Cached pointer to thread-local track manager
  TG4TrackManager* fTrackManager;

  /// Cached pointer to thread-local state manager
  TG4StateManager* fStateManager;

  /// Control for printing memory usage
  G4bool fPrintMemory;

  /// Control for saving random engine status for each event
  G4bool fSaveRandomStatus;

  /// flag if event is interruptible meaning that GEANT4_VMC relies on
  /// TVirtualMCApplication::BeginEvent() and ::FinishEvent() will be called
  ///  from outside.
  G4bool fIsInterruptibleEvent;
};

// inline methods

inline void TG4EventAction::SetMCStack(TVirtualMCStack* mcStack)
{
  /// Set cached pointer to thread-local VMC stack
  fMCStack = mcStack;
}

inline void TG4EventAction::SetPrintMemory(G4bool printMemory)
{
  /// Set option for printing memory usage
  fPrintMemory = printMemory;
}

inline G4bool TG4EventAction::GetPrintMemory() const
{
  /// Return the option for printing memory usage
  return fPrintMemory;
}

inline G4bool TG4EventAction::GetSaveRandomStatus() const
{
  /// Return the option for printing memory usage
  return fSaveRandomStatus;
}

inline G4bool TG4EventAction::IsInterruptibleEvent() const
{
  /// Return whether the current event is flagged as being interruptible
  return fIsInterruptibleEvent;
}

inline void TG4EventAction::SetSaveRandomStatus(G4bool saveRandomStatus)
{
  /// Set option for saving random engine status for each event
  fSaveRandomStatus = saveRandomStatus;
}

inline void TG4EventAction::SetIsInterruptibleEvent(G4bool isInterruptible)
{
  /// Flag whether the current event is interruptible
  fIsInterruptibleEvent = isInterruptible;
}

#endif // TG4_EVENT_ACTION_H
