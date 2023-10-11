#ifndef TG4_WORKER_INITIALIZATION_H
#define TG4_WORKER_INITIALIZATION_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4WorkerInitialization.h
/// \brief Definition of the TG4WorkerInitialization class
///
/// \author I. Hrivnacova; IPN Orsay

#include <G4UserWorkerInitialization.hh>

/// \ingroup run
/// \brief Actions at start and end of run on a worker (call in MT mode only)
///
/// \author I. Hrivnacova; IPN, Orsay

class TG4WorkerInitialization : public G4UserWorkerInitialization
{
 public:
  TG4WorkerInitialization();
  ~TG4WorkerInitialization() override;

  // methods
  //
  // void WorkerInitialize() const override;
  // This method is called after the tread is created but before the
  // G4WorkerRunManager is instantiated.

  // void WorkerStart() const override;
  // This method is called once at the beginning of simulation job
  // when kernel classes and user action classes have already instantiated
  // but geometry and physics have not been yet initialized. This situation
  // is identical to "PreInit" state in the sequential mode.

  void WorkerRunStart() const override;
  // This method is called before an event loop. Geometry and physics have
  // already been set up for the thread. All threads are synchronized and
  // ready to start the local event loop. This situation is identical to
  // "Idle" state in the sequential mode.

  void WorkerRunEnd() const override;
  // This method is called for each thread, when the local event loop has
  // finished but before the synchronization over threads.

  void WorkerStop() const override;
  // This method is called once at the end of simulation job.
  // Implement here a clean up action.

 private:
  /// Not implemented
  TG4WorkerInitialization(const TG4WorkerInitialization& right);
  /// Not implemented
  TG4WorkerInitialization& operator=(const TG4WorkerInitialization& right);
};

#endif // TG4_WORKER_INITIALIZATION_H
