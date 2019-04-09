#ifndef PRIMARY_GENERATOR_H
#define PRIMARY_GENERATOR_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2014 - 2018 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03/E03b/include/PrimaryGenerator.h
/// \brief Definition of the PrimaryGenerator class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo: \n
/// Id: ExN03PrimaryGeneratorAction.hh,v 1.5 2002/01/09 17:24:11 ranjard Exp
/// GEANT4 tag Name: geant4-05-00
///
/// \author I. Hrivnacova; IPN, Orsay

#include <TVirtualMCApplication.h>

class TVirtualMCStack;
class TVector3;

namespace VMC
{
namespace E03
{

class DetectorConstruction;

/// \ingroup E03b
/// \brief The primary generator
///
/// \date 06/03/2003
/// \author I. Hrivnacova; IPN, Orsay

class PrimaryGenerator : public TObject
{
  public:
    /// Predefined primary generators
    enum Type {
      kDefault,    ///< default (e-)
      kUser,       ///< user defined particle and ion
      kUserDecay,  ///< particle with user defined decay (K0Short)
      kAnti,       ///< light anti-nuclei (with Geant4 only)
      kTestField   ///< mu+ with a suitable energy to test magnetic field
    };

  public:
    PrimaryGenerator(TVirtualMCStack* stack);
    PrimaryGenerator(const PrimaryGenerator& origin,
                         TVirtualMCStack* stack);
    PrimaryGenerator();
    virtual ~PrimaryGenerator();

    // methods
    virtual void GeneratePrimaries(const TVector3& worldSize);

    // set methods
    void  SetIsRandom(Bool_t isRandomGenerator);
    void  SetPrimaryType(Type primaryType);
    void  SetNofPrimaries(Int_t nofPrimaries);

    // get methods
    Bool_t GetUserDecay() const;

  private:
    // methods
    void GeneratePrimary1(const TVector3& origin);
    void GeneratePrimary2(const TVector3& origin);
    void GeneratePrimary3(const TVector3& origin);
    void GeneratePrimary4(const TVector3& origin);
    void GeneratePrimary5(const TVector3& origin);

    // data members
    TVirtualMCStack*  fStack;         ///< VMC stack
    Bool_t            fIsRandom;      ///< Switch to random generator
    Type              fPrimaryType;   ///< Primary generator selection
    Int_t             fNofPrimaries;  ///< Number of primary particles

  ClassDef(PrimaryGenerator,1)  //PrimaryGenerator
};

// inline functions

/// Switch on/off the random generator
/// \param isRandom  If true, the position is randomized
inline void  PrimaryGenerator::SetIsRandom(Bool_t isRandom)
{ fIsRandom = isRandom; }

/// Set the primary particle type to be generated
/// \param  primaryType The primary particle type \see Primary
inline void  PrimaryGenerator::SetPrimaryType(
                        PrimaryGenerator::Type primaryType)
{ fPrimaryType = primaryType; }

/// Set the number of particles to be generated
/// \param nofPrimaries The number of particles to be generated
inline void  PrimaryGenerator::SetNofPrimaries(Int_t nofPrimaries)
{ fNofPrimaries = nofPrimaries; }

/// Return true if particle with user decay is activated
inline Bool_t PrimaryGenerator::GetUserDecay() const
{ return fPrimaryType == PrimaryGenerator::kUserDecay; }

}
}

#endif //PRIMARY_GENERATOR_H
