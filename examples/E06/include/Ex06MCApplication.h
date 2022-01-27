#ifndef EX06_MC_APPLICATION_H
#define EX06_MC_APPLICATION_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file Ex06MCApplication.h
/// \brief Definition of the Ex06MCApplication class
///
/// Geant4 ExampleN06 adapted to Virtual Monte Carlo \n
///
/// \author I. Hrivnacova; IPN, Orsay

#include <TLorentzVector.h>
#include <TMCVerbose.h>
#include <TVirtualMCApplication.h>

class TCanvas;
class TVirtualMagField;

class Ex03MCStack;
class Ex06DetectorConstruction;
class Ex06PrimaryGenerator;

/// \ingroup E06
/// \brief Implementation of the TVirtualMCApplication
///
/// \date 16/05/2005
/// \author I. Hrivnacova; IPN, Orsay

class Ex06MCApplication : public TVirtualMCApplication
{
 public:
  Ex06MCApplication(const char* name, const char* title);
  Ex06MCApplication();
  virtual ~Ex06MCApplication();

  // static access method
  static Ex06MCApplication* Instance();

  // methods
  void InitMC(const char* setup);
  void RunMC(Int_t nofEvents);

  virtual TVirtualMCApplication* CloneForWorker() const;
  virtual void InitOnWorker();
  virtual void Merge(TVirtualMCApplication* localMCApplication);

  virtual void ConstructGeometry();
  virtual void ConstructOpGeometry();
  virtual void InitGeometry();
  virtual void GeneratePrimaries();
  virtual void BeginEvent();
  virtual void BeginPrimary();
  virtual void PreTrack();
  virtual void Stepping();
  virtual void PostTrack();
  virtual void FinishPrimary();
  virtual void FinishEvent();
  void FinishRun();

  // set methods
  void SetVerboseLevel(Int_t verboseLevel);

  // get methods
  Ex06PrimaryGenerator* GetPrimaryGenerator() const;

  // method for tests
  void SetOldGeometry(Bool_t oldGeometry = kTRUE);
  void SetTestStackPopper(Bool_t option = kFALSE);

 private:
  // methods
  Ex06MCApplication(const Ex06MCApplication& origin);

  // stack popper test
  void GenerateFeedback(Int_t nofPhotons, TLorentzVector momentum);

  // data members
  Int_t fGammaCounter;                        ///< Optical photons counter
  Int_t fFeedbackCounter;                     ///< Feedback photons counter
  Int_t fRunGammaCounter;                     ///< Optical photons counter2
  Int_t fRunFeedbackCounter;                  ///< Feedback photons counter2
  TMCVerbose fVerbose;                        ///< VMC verbose helper
  Ex03MCStack* fStack;                        ///< VMC stack
  TVirtualMagField* fMagField;                ///< The magnetic field
  Ex06DetectorConstruction* fDetConstruction; ///< Dector construction
  Ex06PrimaryGenerator* fPrimaryGenerator;    ///< Primary generator
  Bool_t fOldGeometry;     ///< Option for geometry definition
  Bool_t fTestStackPopper; ///< Option for stack popper test
  Bool_t fIsMaster;        ///< If is on master thread

  ClassDef(Ex06MCApplication, 1) // Interface to MonteCarlo application
};

// inline functions

/// \return The singleton instance
inline Ex06MCApplication* Ex06MCApplication::Instance()
{
  return (Ex06MCApplication*)(TVirtualMCApplication::Instance());
}

/// Set verbosity
/// \param verboseLevel  The new verbose level value
inline void Ex06MCApplication::SetVerboseLevel(Int_t verboseLevel)
{
  fVerbose.SetLevel(verboseLevel);
}

/// \return The primary generator
inline Ex06PrimaryGenerator* Ex06MCApplication::GetPrimaryGenerator() const
{
  return fPrimaryGenerator;
}

/// Switch on/off the old geometry definition  (via VMC functions)
/// \param oldGeometry  If true, geometry definition via VMC functions
inline void Ex06MCApplication::SetOldGeometry(Bool_t oldGeometry)
{
  fOldGeometry = oldGeometry;
}

/// Switch on/off the stack popper test
/// \param option stack popper test activation option
inline void Ex06MCApplication::SetTestStackPopper(Bool_t option)
{
  fTestStackPopper = option;
}

#endif // EX06_MC_APPLICATION_H
