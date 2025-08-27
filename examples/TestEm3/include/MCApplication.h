#ifndef MC_APPLICATION_H
#define MC_APPLICATION_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file MCApplication.h
/// \brief Definition of the MCApplication class
///
/// Geant4 TestEm3 adapted to Virtual Monte Carlo
///
/// \author I. Hrivnacova; IJCLab Orsay

#include <TVirtualMCApplication.h>

#include <TMCVerbose.h>

class MCStack;

class TMCRootManager;

/// \ingroup TestEm3
/// \brief Implementation of the TVirtualMCApplication
///
/// \date 27/08/2025
/// \author I. Hrivnacova; IJCLab Orsay

class MCApplication : public TVirtualMCApplication
{
 public:
  MCApplication(const char* name, const char* title);
  MCApplication();
  virtual ~MCApplication();

  // methods
  void InitMC(const char* setup, const char* setupParam = "");
  void RunMC(Int_t nofEvents);
  void FinishRun();
  void ReadEvent(Int_t i);

  virtual TVirtualMCApplication* CloneForWorker() const;
  virtual void InitOnWorker();
  virtual void FinishRunOnWorker();

  virtual void ConstructGeometry();
  virtual void InitGeometry();
  virtual void GeneratePrimaries();
  virtual void BeginEvent();
  virtual void BeginPrimary();
  virtual void PreTrack();
  virtual void Stepping();
  virtual void PostTrack();
  virtual void FinishPrimary();
  virtual void FinishEvent();

  // set methods
  void SetVerboseLevel(Int_t verboseLevel);
  void SetIsRootIO(Bool_t isRootIO)  { fIsRootIO = isRootIO; }

 private:
  // methods
  MCApplication(const MCApplication& origin);
  void RegisterStack() const;

  // data members
  mutable TMCRootManager* fRootManager = nullptr; //!< Root manager
  TMCVerbose fVerbose;                  ///< VMC verbose helper
  MCStack* fStack;                      ///< VMC stack
  Bool_t  fIsRootIO;                    ///< option to activate ROOT IO 
  Bool_t fIsMaster;                     ///< If is on master thread

  ClassDef(MCApplication, 1) // Interface to MonteCarlo application
};

#endif // MC_APPLICATION_H
