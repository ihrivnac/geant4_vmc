// Source: g4hepem/apps/examples/TestEm3

#ifndef PhysListHepEmTracking_h
#define PhysListHepEmTracking_h 1
#ifdef USE_G4HEPEM

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysListHepEmTracking : public G4VPhysicsConstructor
{
  public: 
     PhysListHepEmTracking(const G4String& name = "HepEmTracking");
    ~PhysListHepEmTracking();

  public: 
    void ConstructParticle() override {}

    void ConstructProcess() override;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
#endif
