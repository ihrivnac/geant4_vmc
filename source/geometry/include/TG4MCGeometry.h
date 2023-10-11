#ifndef TG4_G3_MC_GEOMETRY_H
#define TG4_G3_MC_GEOMETRY_H

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4MCGeometry.h
/// \brief Definition of the TG4MCGeometry class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4Globals.h"
#include "TG4IntMap.h"
#include "TG4OpSurfaceMap.h"
#include "TG4Verbose.h"

#include <globals.hh>

#include <Rtypes.h>
#include <TMCOptical.h>
#include <TVirtualMCGeometry.h>

class TG4GeometryServices;
class TG4G3CutVector;
class TG4G3ControlVector;

class G4VPhysicalVolume;
class G4OpticalSurface;

class TGeoHMatrix;
class TArrayD;
class TString;

/// \ingroup geometry
/// \brief Geant4 implementation of the TVirtualMCGeometry interface
///
/// This interfaces defines methods for building geometry a la geant3
/// and is implemented with use og G3toG4
///
/// \author: V. Berejnoi, CERN; I. Hrivnacova, IPN Orsay

class TG4MCGeometry : public TVirtualMCGeometry, public TG4Verbose
{
 public:
  TG4MCGeometry();
  ~TG4MCGeometry() override;

  //
  // methods (from the base class)

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

  // functions from GBASE
  void Ggclos();

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
    Double_t y, Double_t z, Int_t irot, const char* konly) override;
  void Gsposp(const char* name, Int_t nr, const char* mother,
    Double_t x, Double_t y, Double_t z, Int_t irot, const char* konly,
    Double_t* upar, Int_t np) override;
  void Gsposp(const char* name, Int_t nr, const char* mother,
    Double_t x, Double_t y, Double_t z, Int_t irot, const char* konly,
    Float_t* upar, Int_t np) override;
  void Gsbool(const char* onlyVolName, const char* manyVolName) override;

  // functions for access to geometry
  Bool_t GetTransformation(
    const TString& volumePath, TGeoHMatrix& matrix) override;
  Bool_t GetShape(
    const TString& volumePath, TString& shapeType, TArrayD& par) override;
  Bool_t GetMaterial(const TString& volumeName, TString& name,
    Int_t& imat, Double_t& a, Double_t& z, Double_t& density, Double_t& radl,
    Double_t& inter, TArrayD& par) override;
  Bool_t GetMedium(const TString& volumeName, TString& name,
    Int_t& imed, Int_t& nmat, Int_t& isvol, Int_t& ifield, Double_t& fieldm,
    Double_t& tmaxfd, Double_t& stemax, Double_t& deemax, Double_t& epsil,
    Double_t& stmin, TArrayD& par) override;
  Int_t MediumId(const Text_t* mediumName) const override;

  //
  // Not implemented functions from the base class
  // (these functions are implemented in SDmanager)
  //

  Int_t VolId(const Text_t* volName) const override;
  const char* VolName(Int_t id) const override;
  Int_t NofVolumes() const override;
  Int_t NofVolDaughters(const char* volName) const override;
  const char* VolDaughterName(const char* volName, Int_t i) const override;
  Int_t VolDaughterCopyNo(const char* volName, Int_t i) const override;
  Int_t VolId2Mate(Int_t id) const override;

 private:
  /// Not implemented
  TG4MCGeometry(const TG4MCGeometry& right);
  /// Not implemented
  TG4MCGeometry& operator=(const TG4MCGeometry& right);

  //
  // data members

  /// geometry services
  TG4GeometryServices* fGeometryServices;

  /// vector of material names sorted in the order of materials in G3Mat
  TG4StringVector fMaterialNameVector;
};

#endif // TG4_VMC_GEOMETRY_MANAGER_H
