#ifndef CALORIMETER_SD_H
#define CALORIMETER_SD_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2014 - 2018 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file E03/E03b/include/ CalorimeterSD.h
/// \brief Definition of the CalorimeterSD class
///
/// Geant4 ExampleN03 adapted to Virtual Monte Carlo: \n
/// Id: ExN03CalorimeterSD.hh,v 1.4 2002/01/09 17:24:11 ranjard Exp
/// GEANT4 tag Name: geant4-05-00
///
/// \author I. Hrivnacova; IPN, Orsay

#include <TVirtualMCSensitiveDetector.h>
#include <TClonesArray.h>

class TVirtualMC;

namespace VMC
{
namespace E03
{

class DetectorConstruction;
class CalorHit;

/// \ingroup E03b
/// \brief The calorimeter sensitive detector
///
/// \date 06/03/2003
/// \author I. Hrivnacova; IPN, Orsay

class CalorimeterSD : public TVirtualMCSensitiveDetector
{
  public:
    CalorimeterSD(const char* name,
                      DetectorConstruction* detector);
    CalorimeterSD(const CalorimeterSD& origin,
                      DetectorConstruction* detector);
    CalorimeterSD();
    virtual ~CalorimeterSD();

    // methods
    void    Initialize();
    virtual void  ProcessHits();
    void    EndOfEvent();
    void    Register();
    virtual void  Print(Option_t* option = "") const;
    void    PrintTotal() const;


    // set methods
    void SetVerboseLevel(Int_t level);
    void SetPrintModulo(Int_t value);

    // get methods
    CalorHit* GetHit(Int_t i) const;

  private:
    // methods
    void  ResetHits();

    // data members
    TVirtualMC*    fMC;            ///< The VMC implementation
    DetectorConstruction*  fDetector; ///< Detector construction
    TClonesArray*  fCalCollection; ///< Hits collection
    Int_t          fAbsorberVolId; ///< The absorber volume Id
    Int_t          fGapVolId;      ///< The gap volume Id
    Int_t          fVerboseLevel;  ///< Verbosity level
    Int_t          fPrintModulo;   ///< The event modulus number to be printed

  ClassDef(CalorimeterSD,1) //CalorimeterSD

};

/// Set verbose level
/// \param level The new verbose level value
inline void CalorimeterSD::SetVerboseLevel(Int_t level)
{ fVerboseLevel = level; }

/// Set the event modulus number to be printed
/// \param value  The new event modulus number value
inline void  CalorimeterSD::SetPrintModulo(Int_t value)
{ fPrintModulo = value; }

}
}

#endif //EX02_CALORIMETER_SD_H
