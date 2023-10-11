#ifndef TGEANT4_H
#define TGEANT4_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TGeant4.h
/// \brief Definition of the TGeant4 class
///
/// \author I. Hrivnacova; IPN Orsay

#include <TArrayI.h>
#include <TMCOptical.h>
#include <TMCProcess.h>
#include <TString.h>
#include <TVirtualMC.h>

class TG4RunConfiguration;
class TG4StateManager;
class TG4GeometryManager;
class TG4SDManager;
class TG4PhysicsManager;
class TG4StepManager;
class TG4VisManager;
class TG4RunManager;

class G4VisExecutive;

class TGeoHMatrix;
class TArrayD;
class TString;
class TVirtualMCApplication;
class TVirtualMCSensitiveDetector;

/// \ingroup run
/// \brief Implementation of the TVirtualMC interface for Geant4.
///
/// \author I. Hrivnacova; IPN, Orsay

class TGeant4 : public TVirtualMC
{
 public:
  TGeant4(const char* name, const char* title,
    TG4RunConfiguration* configuration, int argc = 0, char** argv = 0);
  ~TGeant4() override;

  //
  // methods for building/management of geometry
  // ------------------------------------------------
  //

  // info about supporting geometry defined via Root
  Bool_t IsRootGeometrySupported() const override;

  // detector composition
  void Material(Int_t& kmat, const char* name, Double_t a, Double_t z,
    Double_t dens, Double_t radl, Double_t absl, Float_t* buf, Int_t nwbuf) override;
  void Material(Int_t& kmat, const char* name, Double_t a, Double_t z,
    Double_t dens, Double_t radl, Double_t absl, Double_t* buf, Int_t nwbuf) override;
  void Mixture(Int_t& kmat, const char* name, Float_t* a, Float_t* z,
    Double_t dens, Int_t nlmat, Float_t* wmat) override;
  void Mixture(Int_t& kmat, const char* name, Double_t* a, Double_t* z,
    Double_t dens, Int_t nlmat, Double_t* wmat) override;
  void Medium(Int_t& kmed, const char* name, Int_t nmat, Int_t isvol,
    Int_t ifield, Double_t fieldm, Double_t tmaxfd, Double_t stemax,
    Double_t deemax, Double_t epsil, Double_t stmin, Float_t* ubuf, Int_t nbuf) override;
  void Medium(Int_t& kmed, const char* name, Int_t nmat, Int_t isvol,
    Int_t ifield, Double_t fieldm, Double_t tmaxfd, Double_t stemax,
    Double_t deemax, Double_t epsil, Double_t stmin, Double_t* ubuf,
    Int_t nbuf) override;
  void Matrix(Int_t& krot, Double_t thetaX, Double_t phiX,
    Double_t thetaY, Double_t phiY, Double_t thetaZ, Double_t phiZ) override;
  void SetCerenkov(Int_t itmed, Int_t npckov, Float_t* ppckov,
    Float_t* absco, Float_t* effic, Float_t* rindex, Bool_t aspline = false,
    Bool_t rspline = false) override;
  void SetCerenkov(Int_t itmed, Int_t npckov, Double_t* ppckov,
    Double_t* absco, Double_t* effic, Double_t* rindex, Bool_t aspline = false,
    Bool_t rspline = false) override;

  // new (more general functions) for definition of surfaces
  // and material properties for optical physics
  void DefineOpSurface(const char* name, EMCOpSurfaceModel model,
    EMCOpSurfaceType surfaceType, EMCOpSurfaceFinish surfaceFinish,
    Double_t sigmaAlpha) override;
  void SetBorderSurface(const char* name, const char* vol1Name,
    int vol1CopyNo, const char* vol2Name, int vol2CopyNo,
    const char* opSurfaceName) override;
  void SetSkinSurface(
    const char* name, const char* volName, const char* opSurfaceName) override;
  void SetMaterialProperty(Int_t itmed, const char* propertyName,
    Int_t np, Double_t* pp, Double_t* values, Bool_t createNewKey = false,
    Bool_t spline = false) override;
  void SetMaterialProperty(
    Int_t itmed, const char* propertyName, Double_t value) override;
  void SetMaterialProperty(const char* surfaceName,
    const char* propertyName, Int_t np, Double_t* pp, Double_t* values,
    Bool_t createNewKey = false, Bool_t spline = false) override;

  // functions for access to geometry
  Bool_t GetTransformation(
    const TString& volumePath, TGeoHMatrix& matrix) override;
  Bool_t GetShape(
    const TString& volumePath, TString& shapeType, TArrayD& par) override;
  Bool_t GetMaterial(Int_t imat, TString& name, Double_t& a,
    Double_t& z, Double_t& density, Double_t& radl, Double_t& inter,
    TArrayD& par) override;
  Bool_t GetMaterial(const TString& volumeName, TString& name,
    Int_t& imat, Double_t& a, Double_t& z, Double_t& density, Double_t& radl,
    Double_t& inter, TArrayD& par) override;
  Bool_t GetMedium(const TString& volumeName, TString& name,
    Int_t& imed, Int_t& nmat, Int_t& isvol, Int_t& ifield, Double_t& fieldm,
    Double_t& tmaxfd, Double_t& stemax, Double_t& deemax, Double_t& epsil,
    Double_t& stmin, TArrayD& par) override;

  // functions from GGEOM
  Int_t Gsvolu(
    const char* name, const char* shape, Int_t nmed, Double_t* upar, Int_t np) override;
  Int_t Gsvolu(
    const char* name, const char* shape, Int_t nmed, Float_t* upar, Int_t np) override;
  void Gsdvn(
    const char* name, const char* mother, Int_t ndiv, Int_t iaxis) override;
  void Gsdvn2(const char* name, const char* mother, Int_t ndiv,
    Int_t iaxis, Double_t c0i, Int_t numed) override;
  void Gsdvt(const char* name, const char* mother, Double_t step,
    Int_t iaxis, Int_t numed, Int_t ndvmx) override;
  void Gsdvt2(const char* name, const char* mother, Double_t step,
    Int_t iaxis, Double_t c0, Int_t numed, Int_t ndvmx) override;
  void Gsord(const char* name, Int_t iax) override;
  void Gspos(const char* name, Int_t nr, const char* mother, Double_t x,
    Double_t y, Double_t z, Int_t irot, const char* konly = "ONLY") override;
  void Gsposp(const char* name, Int_t nr, const char* mother,
    Double_t x, Double_t y, Double_t z, Int_t irot, const char* konly,
    Double_t* upar, Int_t np) override;
  void Gsposp(const char* name, Int_t nr, const char* mother,
    Double_t x, Double_t y, Double_t z, Int_t irot, const char* konly,
    Float_t* upar, Int_t np) override;
  void Gsbool(const char* onlyVolName, const char* manyVolName) override;

  // Euclid
  void WriteEuclid(
    const char* fileName, const char* topVol, Int_t number, Int_t nlevel) override;

  // set geometry from Root (built via TGeo)
  void SetRootGeometry() override;

  // Activate the parameters defined in tracking media
  // (DEEMAX, STMIN, STEMAX), which are, be default, ignored.
  // In Geant4 case, only STEMAX is taken into account.
  void SetUserParameters(Bool_t isUserParameters) override;

  // get methods
  Int_t VolId(const Text_t* volName) const override;
  const char* VolName(Int_t id) const override;
  Int_t MediumId(const Text_t* medName) const override;
  Int_t NofVolumes() const override;
  Int_t NofVolDaughters(const char* volName) const override;
  const char* VolDaughterName(const char* volName, Int_t i) const override;
  Int_t VolDaughterCopyNo(const char* volName, Int_t i) const override;
  Int_t VolId2Mate(Int_t id) const override;

  //
  // methods for sensitive detectors
  // ------------------------------------------------
  //

  void SetSensitiveDetector(
    const TString& volName, TVirtualMCSensitiveDetector* sd) override;
  TVirtualMCSensitiveDetector* GetSensitiveDetector(
    const TString& volName) const override;
  void SetExclusiveSDScoring(Bool_t exclusiveSDScoring) override;

  //
  // methods for physics management
  // ------------------------------------------------
  //

  void BuildPhysics() override;
  void Gstpar(Int_t itmed, const char* param, Double_t parval) override;

  // set methods
  Bool_t SetCut(const char* cutName, Double_t cutValue) override;
  Bool_t SetProcess(const char* flagName, Int_t flagValue) override;
  Bool_t DefineParticle(Int_t pdg, const char* name,
    TMCParticleType mcType, Double_t mass, Double_t charge, Double_t lifetime) override;
  Bool_t DefineParticle(Int_t pdg, const char* name,
    TMCParticleType mcType, Double_t mass, Double_t charge, Double_t lifetime,
    const TString& pType, Double_t width, Int_t iSpin, Int_t iParity,
    Int_t iConjugation, Int_t iIsospin, Int_t iIsospinZ, Int_t gParity,
    Int_t lepton, Int_t baryon, Bool_t stable, Bool_t shortlived = kFALSE,
    const TString& subType = "", Int_t antiEncoding = 0,
    Double_t magMoment = 0.0, Double_t excitation = 0.0) override;
  Bool_t DefineIon(const char* name, Int_t Z, Int_t A, Int_t Q,
    Double_t excEnergy, Double_t mass) override;
  Double_t Xsec(char* reac, Double_t energy, Int_t part, Int_t mate) override;

  // particle table usage
  Int_t IdFromPDG(Int_t pdgID) const override;
  Int_t PDGFromId(Int_t mcID) const override;

  // get methods
  TString ParticleName(Int_t pdg) const override;
  Double_t ParticleMass(Int_t pdg) const override;
  Double_t ParticleCharge(Int_t pdg) const override;
  Double_t ParticleLifeTime(Int_t pdg) const override;
  TMCParticleType ParticleMCType(Int_t pdg) const override;

  //
  // methods for step management
  // ------------------------------------------------
  //

  // action methods
  void StopTrack() override;
  void InterruptTrack() override;
  void StopEvent() override;
  void StopRun() override;

  // set methods
  void SetMaxStep(Double_t) override;
  void SetMaxNStep(Int_t) override;
  void SetUserDecay(Int_t) override;
  void ForceDecayTime(Float_t) override;
  Bool_t SetDecayMode(
    Int_t pdg, Float_t bratio[6], Int_t mode[6][3]) override;

  // get methods
  // tracking volume(s)
  Int_t CurrentVolID(Int_t& copyNo) const override;
  Int_t CurrentVolOffID(Int_t off, Int_t& copyNo) const override;
  const char* CurrentVolName() const override;
  const char* CurrentVolOffName(Int_t off) const override;
  const char* CurrentVolPath() override;
  Bool_t CurrentBoundaryNormal(
    Double_t& x, Double_t& y, Double_t& z) const override;
  Int_t CurrentMaterial(
    Float_t& a, Float_t& z, Float_t& dens, Float_t& radl, Float_t& absl) const override;
  Int_t CurrentMedium() const override;
  void Gmtod(Float_t* xm, Float_t* xd, Int_t iflag) override;
  void Gmtod(Double_t* xm, Double_t* xd, Int_t iflag) override;
  void Gdtom(Float_t* xd, Float_t* xm, Int_t iflag) override;
  void Gdtom(Double_t* xd, Double_t* xm, Int_t iflag) override;
  Double_t MaxStep() const override;
  Int_t GetMaxNStep() const override;

  // tracking particle
  // dynamic properties
  void TrackPosition(TLorentzVector& position) const override;
  void TrackPosition(Double_t& x, Double_t& y, Double_t& z) const override;
  void TrackPosition(Float_t& x, Float_t& y, Float_t& z) const override;
  void TrackMomentum(TLorentzVector& momentum) const override;
  void TrackMomentum(
    Double_t& px, Double_t& py, Double_t& pz, Double_t& etot) const override;
  void TrackMomentum(
    Float_t& px, Float_t& py, Float_t& pz, Float_t& etot) const override;
  Double_t TrackStep() const override;
  Double_t TrackLength() const override;
  Double_t TrackTime() const override;
  Double_t Edep() const override;
  Double_t NIELEdep() const override;
  Int_t StepNumber() const override;
  Double_t TrackWeight() const override;
  void TrackPolarization(
    Double_t& polX, Double_t& polY, Double_t& polZ) const override;
  void TrackPolarization(TVector3& pol) const override;
  // static properties
  Int_t TrackPid() const override;
  Double_t TrackCharge() const override;
  Double_t TrackMass() const override;
  Double_t Etot() const override;

  // track status
  Bool_t IsTrackInside() const override;
  Bool_t IsTrackEntering() const override;
  Bool_t IsTrackExiting() const override;
  Bool_t IsTrackOut() const override;
  Bool_t IsTrackDisappeared() const override;
  Bool_t IsTrackStop() const override;
  Bool_t IsTrackAlive() const override;
  Bool_t IsNewTrack() const override;

  // secondaries
  Int_t NSecondaries() const override;
  void GetSecondary(Int_t isec, Int_t& particleId,
    TLorentzVector& position, TLorentzVector& momentum) override;
  TMCProcess ProdProcess(Int_t isec) const override;
  Int_t StepProcesses(TArrayI& proc) const override;

  //
  // methods for visualization
  // ------------------------------------------------
  //
  // functions for drawing (removed from TVirtualMC)
  void DrawOneSpec(const char* name);
  void Gsatt(const char* name, const char* att, Int_t val);
  void Gdraw(const char*, Double_t theta, Double_t phi, Double_t psi,
    Double_t u0, Double_t v0, Double_t ul, Double_t vl);

  //
  // methods for lego transport
  // ------------------------------------------------
  //
  void InitLego() override;

  //
  // methods for run control
  // ------------------------------------------------
  //

  void Init() override;
  void ProcessEvent() override;
  void ProcessEvent(Int_t eventId) override;
  void ProcessEvent(Int_t eventId, Bool_t isInterruptible) override;
  Bool_t ProcessRun(Int_t nofEvents) override;
  Bool_t FinishRun();
  void SetCollectTracks(Bool_t collectTracks) override;
  Bool_t IsCollectTracks() const override;
  Bool_t IsMT() const override;
  void SetRandomSeed(); // set's random seed of engine based on status of ROOT gRandom

  // UI control methods
  void StartGeantUI();
  void StartRootUI();
  void ProcessGeantMacro(const char* macroName);
  void ProcessGeantCommand(const char* commandPath);

  // Methods for MT
  static TGeant4* MasterInstance();
  static TVirtualMCApplication* MasterApplicationInstance();
  TGeant4* CloneForWorker() const;

  // get methods
  Int_t CurrentEvent() const override;
  Bool_t SecondariesAreOrdered() const override;

 private:
  /// Not implemented
  TGeant4();
  /// Not implemented
  TGeant4(const TGeant4& right);
  /// Not implemented
  TGeant4& operator=(const TGeant4& right);

  // static data members

  /// master instance
  static TGeant4* fgMasterInstance;

  /// master application instance
  static TVirtualMCApplication* fgMasterApplicationInstance;

  // data members
  TG4StateManager* fStateManager;         ///< application state manager
  TG4GeometryManager* fGeometryManager;   ///< geometry manager
  TG4SDManager* fSDManager;               ///< sensitive detectors manager
  TG4PhysicsManager* fPhysicsManager;     ///< physics manager
  TG4StepManager* fStepManager;           ///< step manager
  TG4VisManager* fVisManager;             ///< visualization manager
  G4VisExecutive* fVisExecutive;          ///< Geant4 visualization manager
  TG4RunManager* fRunManager;             ///< run manager
  TG4RunConfiguration* fRunConfiguration; ///< run configuration
  Int_t fMediumCounter;                   ///< global medium counter
  Int_t fMaterialCounter;                 ///< global material counter
  Int_t fMatrixCounter;                   ///< global matrix counter
  TString fUserGeometry;                  ///< user geometry
  Bool_t fIsMT;                           ///< multi-threading mode

  ClassDefOverride(TGeant4, 0) // Geant4 implementation of the TVirtualMC interface
};

#ifndef __CINT__
#ifndef __CLING__

// inline methods
#include "TGeant4.icc"

#endif
#endif
#endif // TGEANT4_H
