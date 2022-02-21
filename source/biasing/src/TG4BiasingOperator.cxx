//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2019 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4BiasingOperator.cxx
/// \brief Definition of the TG4BiasingOperator class
///
/// \author Alberto Ribon, CERN

#include "TG4BiasingOperator.h"
#include "TG4BiasingOperation.h"

#include "G4BiasingProcessInterface.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"

TG4BiasingOperator::TG4BiasingOperator() : G4VBiasingOperator("BiasingOperator")
{
  G4cout << "TG4BiasingOperator::TG4BiasingOperator constructed" << G4endl;
  fBiasingOperation = new TG4BiasingOperation("BiasingOperation");
}

void TG4BiasingOperator::AddParticle(G4String particleName)
{
  const G4ParticleDefinition* particle =
    G4ParticleTable::GetParticleTable()->FindParticle(particleName);
  if (particle == 0) {
    G4ExceptionDescription ed;
    ed << "Particle `" << particleName << "' not found !" << G4endl;
    G4Exception(
      "TG4BiasingOperator::AddParticle(...)", "BiasError", JustWarning, ed);
    return;
  }
  fParticlesToBias.push_back(particle);
}

G4VBiasingOperation* TG4BiasingOperator::ProposeFinalStateBiasingOperation(
  const G4Track*, const G4BiasingProcessInterface* callingProcess)
{
  // G4cout << "In TG4BiasingOperator::ProposeFinalStateTG4BiasingOperation "
  //        << " calling process: " << callingProcess
  //        << " wrapper process: " << callingProcess->GetWrappedProcess();
  // if ( callingProcess->GetWrappedProcess() ) {
  //   G4cout << " wrapper process name: " <<
  //   callingProcess->GetWrappedProcess()->GetProcessName();
  // }
  // G4cout << G4endl;

  // Fill processes to be biased (only once)
  if ( fProcessesToBias.empty()) {
    for (auto particle: fParticlesToBias) {
      auto processVector = particle->GetProcessManager()->GetProcessList();
      for (size_t i = 0; i < processVector->length(); ++i) {
        auto wrapper = dynamic_cast<G4BiasingProcessInterface*>((*processVector)[i]);
        if (wrapper == nullptr || wrapper->GetWrappedProcess() == nullptr) continue;

        if (G4StrUtil::contains(wrapper->GetWrappedProcess()->GetProcessName(), "Inelastic")) {
          // G4cout << "Adding " << wrapper->GetWrappedProcess()->GetProcessName()
          //        << " to Processes to Bias" << G4endl;
          fProcessesToBias.insert(wrapper->GetWrappedProcess());
        }
      }
    }
  }

  // Apply the biasing operation only for registered inelastic processes
  if (callingProcess && callingProcess->GetWrappedProcess() &&
      fProcessesToBias.find(callingProcess->GetWrappedProcess()) != fProcessesToBias.end()) {
    // G4cout << "In TG4BiasingOperator: Returning operation " << G4endl;
    return fBiasingOperation;
  }
  else {
    // G4cout << "In TG4BiasingOperator: Returning 0 " << G4endl;
    return nullptr;
  }
}
