//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2025 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file MCApplication.cxx
/// \brief Implementation of the MCApplication class
///
/// Geant4 TestEm3 adapted to Virtual Monte Carlo
///
/// \date 27/08/2025
/// \author I. Hrivnacova; IJCLab Orsay

#include "MCApplication.h"
#include "MCStack.h"

#include <TMCRootManager.h>

#include <Riostream.h>
#include <TInterpreter.h>
#include <TROOT.h>
#include <TVirtualMC.h>

using namespace std;

/// \cond CLASSIMP
ClassImp(MCApplication)
  /// \endcond

  //_____________________________________________________________________________
  MCApplication::MCApplication(const char* name, const char* title)
  : TVirtualMCApplication(name, title),
    fVerbose(0),
    fStack(0),
    fIsRootIO(false),
    fIsMaster(true)
{
  /// Standard constructor
  /// \param name   The MC application name
  /// \param title  The MC application description

  cout << "--------------------------------------------------------------"
       << endl;
  cout << " VMC Example TestEm3" << endl;
  cout << "--------------------------------------------------------------"
       << endl;

  // Create a user stack
  fStack = new MCStack(1000);
}

//_____________________________________________________________________________
MCApplication::MCApplication(const MCApplication& origin)
  : TVirtualMCApplication(origin.GetName(), origin.GetTitle()),
    fVerbose(origin.fVerbose),
    fStack(0),
    fIsRootIO(false),
    fIsMaster(false)
{
  /// Copy constructor for cloning application on workers (in multithreading
  /// mode) \param origin   The source MC application

  // Create new user stack
  fStack = new MCStack(1000);
}

//_____________________________________________________________________________
MCApplication::MCApplication()
  : TVirtualMCApplication(),
    fStack(0),
    fIsRootIO(false),
    fIsMaster(true)
{
  /// Default constructor
}

//_____________________________________________________________________________
MCApplication::~MCApplication()
{
  /// Destructor

  // cout << "MCApplication::~MCApplication " << this << endl;

  delete fStack;
  delete gMC;

  // cout << "Done MCApplication::~MCApplication " << this << endl;
}

//
// private methods
//

//_____________________________________________________________________________
void MCApplication::RegisterStack() const
{
  /// Register stack in the Root manager.

  if (fRootManager) {
    // cout << "MCApplication::RegisterStack: " << endl;
    fRootManager->Register("stack", "MCStack", &fStack);
  }
}

//
// public methods
//

//_____________________________________________________________________________
void MCApplication::InitMC(const char* setup, const char* setupParam)
{
  /// Initialize MC.
  /// The selection of the concrete MC is done in the macro.
  /// \param setup The name of the configuration macro

  // fVerbose.InitMC();

  cout << "Calling Init MC with " << setup << ", " << setupParam << endl;

  if (TString(setup) != "") {
    gROOT->LoadMacro(setup);
    TString macroCall = TString("Config(\"") + setupParam +  TString("\")");
    cout << "Go to process: " << macroCall << endl;
    gInterpreter->ProcessLine(macroCall);
    if (!gMC) {
      Fatal(
        "InitMC", "Processing Config() has failed. (No MC is instantiated.)");
    }
  }

  // Create Root manager
  if (!gMC->IsMT()) {
    if (fIsRootIO) {
      fRootManager = new TMCRootManager(GetName(), TMCRootManager::kWrite);
      // fRootManager->SetDebug(true);
    }
  }

  cout << "Stack set to gMC" << endl;
  gMC->SetStack(fStack);
  // gMC->SetMagField(fMagField);
  gMC->Init();
  gMC->BuildPhysics();

  RegisterStack();
}

//_____________________________________________________________________________
void MCApplication::RunMC(Int_t nofEvents)
{
  /// Run MC.
  /// \param nofEvents Number of events to be processed

  // fVerbose.RunMC(nofEvents);

  gMC->ProcessRun(nofEvents);
  FinishRun();
}

//_____________________________________________________________________________
void MCApplication::FinishRun()
{
  /// Finish MC run.

  // fVerbose.FinishRun();
  // cout << "MCApplication::FinishRun: " << endl;
  if (fRootManager) {
    fRootManager->WriteAll();
    fRootManager->Close();
  }
}

//_____________________________________________________________________________
TVirtualMCApplication* MCApplication::CloneForWorker() const
{
  auto mcApplication = new MCApplication(*this);
  mcApplication->SetIsRootIO(fIsRootIO);
  

  return mcApplication;
}

//_____________________________________________________________________________
void MCApplication::InitOnWorker()
{
  // cout << "MCApplication::InitForWorker " << this << endl;

  // Create Root manager
  if (fIsRootIO) {
    fRootManager = new TMCRootManager(GetName(), TMCRootManager::kWrite);
    // fRootManager->SetDebug(true);
  }

  // Set data to MC
  gMC->SetStack(fStack);
  // gMC->SetMagField(fMagField);

  RegisterStack();
}

//_____________________________________________________________________________
void MCApplication::FinishRunOnWorker()
{
  // cout << "MCApplication::FinishWorkerRun: " << endl;
  if (fRootManager) {
    fRootManager->WriteAll();
    fRootManager->Close();
  }
}

//_____________________________________________________________________________
void MCApplication::ReadEvent(Int_t i)
{
  /// Read \em i -th event and prints hits.
  /// \param i The number of event to be read

  RegisterStack();
  fRootManager->ReadEvent(i);
}

//_____________________________________________________________________________
void MCApplication::ConstructGeometry()
{
  /// Construct geometry using detector contruction class.
  /// The detector contruction class is using TGeo functions or
  /// TVirtualMC functions (if oldGeometry is selected)

  // fVerbose.ConstructGeometry();

  // Done via G4 user class
}

//_____________________________________________________________________________
void MCApplication::InitGeometry()
{
  /// Initialize geometry

  // fVerbose.InitGeometry();

  // Done via G4 user class  
}


//_____________________________________________________________________________
void MCApplication::GeneratePrimaries()
{
  /// Fill the user stack (derived from TVirtualMCStack) with primary particles.

  // fVerbose.GeneratePrimaries();

  // Done via G4 user class  
}

//_____________________________________________________________________________
void MCApplication::BeginEvent()
{
  /// User actions at beginning of event

  // fVerbose.BeginEvent();
}

//_____________________________________________________________________________
void MCApplication::BeginPrimary()
{
  /// User actions at beginning of a primary track.
  /// If test for user defined decay is activated,
  /// the primary track ID is printed on the screen.

  // fVerbose.BeginPrimary();
}

//_____________________________________________________________________________
void MCApplication::PreTrack()
{
  /// User actions at beginning of each track
  /// If test for user defined decay is activated,
  /// the decay products of the primary track (K0Short)
  /// are printed on the screen.

  // fVerbose.PreTrack();

}

//_____________________________________________________________________________
void MCApplication::Stepping()
{
  /// User actions at each step

  // fVerbose.Stepping();
}

//_____________________________________________________________________________
void MCApplication::PostTrack()
{
  /// User actions after finishing of each track

  // fVerbose.PostTrack();
}

//_____________________________________________________________________________
void MCApplication::FinishPrimary()
{
  /// User actions after finishing of a primary track

  // fVerbose.FinishPrimary();
}

//_____________________________________________________________________________
void MCApplication::FinishEvent()
{
  /// User actions after finishing of an event

  // fVerbose.FinishEvent();

  if (fRootManager) {
    fRootManager->Fill();
  }

  fStack->Reset();
}
