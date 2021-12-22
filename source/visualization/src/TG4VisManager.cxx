//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4VisManager.cxx
/// \brief Implementation of the TG4VisManager class
///
/// According to visualization/management/include/MyVisManager.*
/// by John Allison 24th January 1998 \n
/// I. Hrivnacova 12.5.98
///
/// Renamed to TG4VisManager \n
/// I. Hrivnacova, 3.9.99
///
/// Added AliMC implementation \n
/// A. Gheata, 22.2.00
///
/// Added OpenGL*Win32, RayTracer (as replacement of RayX) drivers
/// based on G4 suggestions.\n
/// I. Gonzalez, 4.4.2000
///
/// Removed inheritance from G4VisManager.
/// I. Hrivnacova, 05/03/2009
///
/// \author I. Hrivnacova, IPN Orsay; A, Gheata

#include "TG4VisManager.h"
#include "TG4Globals.h"

#include <G4LogicalVolumeStore.hh>
#include <G4Material.hh>
#include <G4PhysicalVolumeModel.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4SystemOfUnits.hh>
#include <G4TransportationManager.hh>
#include <G4VVisManager.hh>

//_____________________________________________________________________________
TG4VisManager::TG4VisManager(G4int verboseLevel)
  : fColourFlag(true), fVerboseLevel(verboseLevel)
{
  /// Standard constructor
}

//_____________________________________________________________________________
TG4VisManager::~TG4VisManager()
{
  /// Destructor
}

//
// private methods
//

//_____________________________________________________________________________
G4bool TG4VisManager::Contains(
  const LogicalVolumesVector& lvVector, const G4LogicalVolume* lv) const
{
  /// Return true if the vector contains specified logical volume.

  LogicalVolumesVector::const_iterator i;

  for (i = lvVector.begin(); i != lvVector.end(); i++)
    if (*i == lv) return true;

  return false;
}

//_____________________________________________________________________________
G4bool TG4VisManager::Contains(
  const PhysicalVolumesVector& pvVector, const G4VPhysicalVolume* pv) const
{
  /// Return true if the vector contains specified physical volume.

  PhysicalVolumesVector::const_iterator i;

  for (i = pvVector.begin(); i != pvVector.end(); i++)
    if (*i == pv) return true;

  return false;
}

//_____________________________________________________________________________
TG4VisManager::LogicalVolumesVector TG4VisManager::GetLVList(G4String name)
{
  /// Get function returning the list of logical volumes
  /// associated to NAME; G4 built clones of a G3 volume (identified
  /// with NAME_NUMBER will be added to the list)
  ///  NAME can be the name of a logical or physical volume

  LogicalVolumesVector lvList;
  G4LogicalVolumeStore* pLVStore = G4LogicalVolumeStore::GetInstance();
  G4LogicalVolume* pLV = 0;
  if (pLVStore) {
    for (G4int i = 0; i < G4int(pLVStore->size()); i++) {
      pLV = (*pLVStore)[i];
      if (CaseInsensitiveEqual(name, pLV->GetName())) {
        if (!Contains(lvList, pLV)) lvList.push_back(pLV);
      }
    }
  }
  if (lvList.size() > 0) return lvList;

  G4PhysicalVolumeStore* pPVStore = G4PhysicalVolumeStore::GetInstance();
  G4VPhysicalVolume* pPV = 0;
  if (pPVStore) {
    for (G4int i = 0; i < G4int(pPVStore->size()); i++) {
      pPV = (*pPVStore)[i];
      if (CaseInsensitiveEqual(name, pPV->GetName())) {
        pLV = pPV->GetLogicalVolume();
        if (!Contains(lvList, pLV)) lvList.push_back(pLV);
      }
    }
  }
  return lvList;
}

//_____________________________________________________________________________
TG4VisManager::PhysicalVolumesVector TG4VisManager::GetPVList(G4String name)
{
  /// Get function returning the physical volume pointer for NAME

  PhysicalVolumesVector pvList;
  G4PhysicalVolumeStore* pPVStore = G4PhysicalVolumeStore::GetInstance();
  G4VPhysicalVolume* pPV = 0;
  for (G4int i = 0; i < G4int(pPVStore->size()); i++) {
    pPV = (*pPVStore)[i];
    if (CaseInsensitiveEqual(name, pPV->GetName())) {
      if (!Contains(pvList, pPV)) pvList.push_back(pPV);
    }
  }
  return pvList;
}

//_____________________________________________________________________________
G4bool TG4VisManager::CaseInsensitiveEqual(
  const G4String string1, const G4String string2)
{
  /// Case insensitive comparison of 2 strings

  G4String str1Cpy(string1);
  G4String str2Cpy(string2);
  std::transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower );
  std::transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower );
  return (str1Cpy == str2Cpy);
}

//_____________________________________________________________________________
void TG4VisManager::SetAtt4Daughters(
  G4LogicalVolume* const lv, const TG4G3Attribute att, const G4int val)
{
  /// Iterator for setting a visual attribute for all daughters

  SetG4Attribute(lv, att, val);

  G4String lvName = lv->GetName();
  G4int nOfDaughters = lv->GetNoDaughters();
  if (nOfDaughters > 0) {
    G4String previousName = "";
    for (G4int i = 0; i < nOfDaughters; i++) {
      G4LogicalVolume* lvd = lv->GetDaughter(i)->GetLogicalVolume();
      G4String currentName = lvd->GetName();
      if (currentName != lvName && currentName != previousName) {
        SetAtt4Daughters(lvd, att, val);
        previousName = currentName;
      }
    }
  }
}

//_____________________________________________________________________________
G4bool TG4VisManager::IsSharedVisAttributes(const G4LogicalVolume* pLV)
{
  /// Function seeking if the volume's visible attributes are shared with
  /// other volumes

  G4LogicalVolumeStore* pLVStore = G4LogicalVolumeStore::GetInstance();
  G4LogicalVolume* pLVCurrent = 0;
  const G4VisAttributes* pVisAtt = pLV->GetVisAttributes();
  if (!pVisAtt) return false;
  for (G4int i = 0; i < G4int(pLVStore->size()); i++) {
    pLVCurrent = (*pLVStore)[i];
    if (pLVCurrent != pLV) {
      if (pLVCurrent->GetVisAttributes() == pVisAtt) {
        return true;
      }
    }
  }
  return false;
}

//_____________________________________________________________________________
void TG4VisManager::SetG4Attribute(
  G4LogicalVolume* const lv, const TG4G3Attribute att, const G4int val)
{
  /// Set the G4 attribute fo volume LV accordingly to the G3 description
  /// of (att- val)
  // --

  if (!lv) return;
  // Dupplicating old vis. attributes
  const G4VisAttributes* visAttributes = lv->GetVisAttributes();
  G4VisAttributes* newVisAttributes;
  if (!visAttributes)
    newVisAttributes = new G4VisAttributes(false);
  else {
    G4bool visibility = visAttributes->IsVisible();
    G4Colour colour = visAttributes->GetColour();
    newVisAttributes = new G4VisAttributes(visibility, colour);
  }

  const G4int kAbsVal = abs(val); // the functionality is given by the abs value

  // Default visible attributes
  G4double red(0), green(0), blue(0); // default is black
  G4bool isVisible(false);
  G4bool isDaughtersInvisible(false);
  G4VisAttributes::LineStyle lineStyle = G4VisAttributes::unbroken;
  G4double lineWidth = 1.0;
  G4bool isForceDrawingStyle(false);
  G4VisAttributes::ForcedDrawingStyle drawingStyle = G4VisAttributes::wireframe;

  // a 'hardcopy' of old vis attributes is needed because the copy constructor
  // resets to defaults some of the data members of G4VisAttributes class
  if (visAttributes) {
    isVisible = visAttributes->IsVisible();
    isDaughtersInvisible = visAttributes->IsDaughtersInvisible();
    red = visAttributes->GetColour().GetRed();
    green = visAttributes->GetColour().GetGreen();
    blue = visAttributes->GetColour().GetBlue(); // old RGB components
    lineStyle = visAttributes->GetLineStyle();
    lineWidth = visAttributes->GetLineWidth();
    isForceDrawingStyle = visAttributes->IsForceDrawingStyle();
    if (isForceDrawingStyle)
      drawingStyle = visAttributes->GetForcedDrawingStyle();
  }
  G4double luminosityBin(0.04), // bin for luminosity
    luminosity(0);              // colour luminosity

  // Delete old vis. attributes if they are not shared
  if (visAttributes && !IsSharedVisAttributes(lv)) delete visAttributes;

  // Set the required attribute
  switch (att) {
    case kSEEN:
      switch (val) {
        case 0:
          isVisible = false;
          break;
        case 1:
          isVisible = true;
          break;
        case -1:
          isVisible = false;
          break;
        case -2:
          isVisible = false;
          break;
        default:
          isVisible = false;
      }
      break;
    case kLSTY:
      switch (kAbsVal) {
        case 1:
          lineStyle = G4VisAttributes::unbroken;
          break;
        case 2:
          lineStyle = G4VisAttributes::dashed;
          break;
        case 3:
          lineStyle = G4VisAttributes::dotted;
          break;
        default:
          if (fVerboseLevel > 0)
            G4cout << "TG4VisManager::Gsatt() Usage of LSTY :" << G4endl
                   << "ATT = 1,2,3 means line unbroken, dashed or dotted"
                   << G4endl
                   << "any other value resets to the default : unbroken"
                   << G4endl;
          lineStyle = G4VisAttributes::unbroken;
      }
      break;
    case kLWID:
      lineWidth = kAbsVal;
      if (lineWidth > 7) lineWidth = 7;
      if (fVerboseLevel > 0)
        G4cout << "TG4VisManager::Gsatt() Usage for LWID :" << G4endl
               << "  The VAL you supply means the width of lines in pixels "
               << "for the screen and in 0.1*mm for paper." << G4endl
               << "  Negative values means the same, but for all daughters"
               << G4endl;
      break;
    case kCOLO:
      if (kAbsVal < 8) // G3 base colours
      {
        switch (kAbsVal) {
          case 1:
            red = 0;
            green = 0;
            blue = 0; // black
            break;
          case 2:
            red = 1;
            green = 0;
            blue = 0; // red
            break;
          case 3:
            red = 0;
            green = 1;
            blue = 0; // green
            break;
          case 4:
            red = 0;
            green = 0;
            blue = 1; // blue
            break;
          case 5:
            red = 1;
            green = 1;
            blue = 0; // yellow
            break;
          case 6:
            red = 1;
            green = 0;
            blue = 1; // violet
            break;
          case 7:
            red = 0;
            green = 1;
            blue = 1; // lightblue (almost !)
        }
        luminosity = 0.;
      }
      if (kAbsVal >= 8 && kAbsVal <= 16) {
        red = 0;
        green = 0;
        blue = 0;
        luminosity = (kAbsVal - 7) * luminosityBin;
      }
      if (kAbsVal >= 17 && kAbsVal <= 41) {
        red = 1;
        green = 0;
        blue = 0;
        luminosity = (kAbsVal - 16) * luminosityBin;
      }
      if (kAbsVal >= 67 && kAbsVal <= 91) {
        red = 0;
        green = 1;
        blue = 0;
        luminosity = (kAbsVal - 66) * luminosityBin;
      }
      if (kAbsVal >= 117 && kAbsVal <= 141) {
        red = 0;
        green = 0;
        blue = 1;
        luminosity = (kAbsVal - 116) * luminosityBin;
      }
      if (kAbsVal >= 42 && kAbsVal <= 66) {
        red = 1;
        green = 1;
        blue = 0;
        luminosity = (kAbsVal - 41) * luminosityBin;
      }
      if (kAbsVal >= 142 && kAbsVal <= 166) {
        red = 1;
        green = 0;
        blue = 1;
        luminosity = (kAbsVal - 141) * luminosityBin;
      }
      if (kAbsVal >= 92 && kAbsVal <= 116) {
        red = 0;
        green = 1;
        blue = 1;
        luminosity = (kAbsVal - 91) * luminosityBin;
      }
      if (red < luminosityBin) red += luminosity;
      if (green < luminosityBin) green += luminosity;
      if (blue < luminosityBin) blue += luminosity;
      break;
    case kFILL:
      isForceDrawingStyle = true;
      switch (kAbsVal) {
        case 0:
          drawingStyle = G4VisAttributes::wireframe;
          break;
        case 1:
          drawingStyle = G4VisAttributes::solid;
          break;
        default:
          if (fVerboseLevel > 0)
            G4cout << "TG4VisManager::Gsatt() FILL usage :" << G4endl
                   << "  The FILL values you can supply are only :" << G4endl
                   << "+/- 1 : forces wireframe drawing (default)" << G4endl
                   << "+/- 2 : forces solid drawing" << G4endl
                   << "other values sets the drawing style to solid" << G4endl;
          drawingStyle = G4VisAttributes::solid;
      }
    default:;
      ;
  }
  // Register vis. attributes
  newVisAttributes->SetVisibility(isVisible);
  newVisAttributes->SetDaughtersInvisible(isDaughtersInvisible);
  newVisAttributes->SetColour(red, green, blue);
  newVisAttributes->SetLineStyle(lineStyle);
  newVisAttributes->SetLineWidth(lineWidth);
  if (drawingStyle == G4VisAttributes::wireframe)
    newVisAttributes->SetForceWireframe(isForceDrawingStyle);
  if (drawingStyle == G4VisAttributes::solid)
    newVisAttributes->SetForceSolid(isForceDrawingStyle);

  lv->SetVisAttributes(newVisAttributes);
}

//
// functions for drawing
//

//_____________________________________________________________________________
void TG4VisManager::DrawOneSpec(const char* /*name*/)
{
  /// Function called when one double-clicks on a volume name
  /// in a TPaveLabel drawn by Gdtree

  G4cout << "TG4VisManager::DrawOneSpec() Not yet implemented";
}

//_____________________________________________________________________________
void TG4VisManager::SetColors()
{
  /// Function for setting default volume colours

  G4LogicalVolumeStore* pLVStore = G4LogicalVolumeStore::GetInstance();
  const G4LogicalVolume* pLV = 0;
  // parse the LV tree and set colours according to material density
  for (G4int i = 0; i < G4int(pLVStore->size()); i++) {
    pLV = (*pLVStore)[i];
    //    G4cout << "VOLUME : " << pLV->GetName() << G4endl;
    const G4Material* pMaterial = pLV->GetMaterial();
    const G4State kState = pMaterial->GetState();
    G4double density = (pMaterial->GetDensity()) * cm3 / g;
    G4String nState = "Undefined";
    G4int colour = 1; // black by default
    G4double luminosity = 0.;
    if (kState == kStateUndefined) {
      nState = "Undefined";
    }
    if (kState == kStateSolid) {
      nState = "Solid";
      if (density < 2) {
        colour = 17; // red
        luminosity = 25 - 25 * density / 2;
      }
      else if (density < 3) {
        colour = 117; // blue
        luminosity = 25 - 25 * (density - 2);
      }
      else if (density < 10) {
        colour = 67; // green
        luminosity = 25 - 25 * (density - 5) / 5;
      }
      else if (density < 15) {
        colour = 92; // cyan
        luminosity = 25 - 25 * (density - 10) / 5;
      }
      else if (density < 20) {
        colour = 8; // black
        luminosity = 9 - 9 * (density - 15) / 5;
      }
    }
    if (kState == kStateLiquid) {
      nState = "Liquid";
      colour = 142; // violet
      luminosity = 25 - 25 * density / 2;
    }
    if (kState == kStateGas) {
      nState = "Gas";
      if (density < 0.001) {
        colour = 42;
      } // yellow
      else if (density < 0.002) {
        colour = 27;
      } // light red
      else if (density < 0.003) {
        colour = 77;
      } // light green
      else {
        colour = 102;
      } // light cyan
      luminosity = 0;
    }
    if (luminosity < 0) luminosity = 0;
    colour += (G4int)luminosity;
    //  Setting the corresponding colour
    Gsatt(pLV->GetName(), "COLO", colour);
  }
}

//_____________________________________________________________________________
void TG4VisManager::Gsatt(const char* name, const char* att, Int_t val)
{
  /// Geant3 description :
  ///
  ///   - NAME   Volume name
  ///   - IOPT   Name of the attribute to be set
  ///   - IVAL   Value to which the attribute is to be set
  ///
  ///   - name= "*" stands for all the volumes.
  ///   - iopt can be chosen among the following :
  ///     kWORK, kSEEN, kLSTY, kLWID, kCOLO, kFILL, kSET, kDET, kDTYP

  G4int ival = val;
  G4LogicalVolume* lv = 0;
  LogicalVolumesVector lvList;
  G4String sname(name), satt(att);

  // seek for known attributes
  TG4G3Attribute attribute = kUNKNOWN;
  if (CaseInsensitiveEqual(att, "WORK")) {
    TG4Globals::Warning("TG4VisManager", "Gsatt",
      "G3Attribute " + TString(satt) + " not used in G4");
    return;
  }
  if (CaseInsensitiveEqual(att, "SEEN")) attribute = kSEEN;
  if (CaseInsensitiveEqual(att, "LSTY")) attribute = kLSTY;
  if (CaseInsensitiveEqual(att, "LWID")) attribute = kLWID;
  if (CaseInsensitiveEqual(att, "COLO")) attribute = kCOLO;
  if (CaseInsensitiveEqual(att, "FILL")) attribute = kFILL;

  if (CaseInsensitiveEqual(att, "SET") || CaseInsensitiveEqual(att, "DET") ||
      CaseInsensitiveEqual(att, "DTYP")) {
    TG4Globals::Warning("TG4VisManager", "Gsatt",
      "G3Attribute " + TString(satt) + " not used in G4");
    return;
  }
  if (attribute == kUNKNOWN) {
    TG4Globals::Warning(
      "TG4VisManager", "Gsatt", "G3Attribute " + TString(satt) + " unknown");
    return;
  }
  G4bool doForDaughters(false), // tree iterator flag
    doForAll(false),            // activated if NAME is "*"
    topVisible(false);          // activated for kSEEN/-2
  if (sname == "*") doForAll = true;
  if (val < 0 && sname != "*") doForDaughters = true;
  if (attribute == kSEEN && val == -2) topVisible = true;

  // parse all the tree
  if (doForAll) {
    G4LogicalVolumeStore* pLVStore = G4LogicalVolumeStore::GetInstance();
    for (G4int i = 0; i < G4int(pLVStore->size()); i++) {
      lv = (*pLVStore)[i];
      SetG4Attribute(lv, attribute, ival);
    }
    return;
  }

  // get the logical volume pointer corresponding to NAME
  lvList = GetLVList(name);
  if (lvList.size() == 0) {
    TG4Globals::Warning("TG4VisManager", "Gsatt",
      "Logical volume " + TString(sname) + " has not been found.");
    return;
  }
  // set attribute for all descendents
  if (doForDaughters) {
    for (G4int i = 0; i < G4int(G4int(lvList.size())); i++) {
      lv = lvList[i];
      SetAtt4Daughters(lv, attribute, ival);
    }
  }
  else {
    for (G4int i = 0; i < G4int(G4int(lvList.size())); i++) {
      lv = lvList[i];
      SetG4Attribute(lv, attribute, ival);
    }
  }
  if (topVisible) {
    for (G4int i = 0; i < G4int(G4int(lvList.size())); i++) {
      lv = lvList[i];
      SetG4Attribute(lv, attribute, 1);
    }
  }
}

//_____________________________________________________________________________
void TG4VisManager::Gdraw(const char* /*name*/, Float_t /*theta*/,
  Float_t /*phi*/, Float_t /*psi*/, Float_t /*u0*/, Float_t /*v0*/,
  Float_t /*ul*/, Float_t /*vl*/)
{
  /// Draw the physical volume NAME and all descendents; \n Mandatory : the
  /// graphics system, scene and view must be
  ///        initialized, e.g. "/vis~/create_view/new_graphics_system OGLSX";
  ///        Any call of Gdraw() will use the current graphics system and
  ///        the current window. \n
  /// The result will be a centered view drawing of the designated volume,
  ///        lights moving with camera, viewpoint direction given by theta/phi
  ///        and rotation on the screen given by psi; \n
  /// The u0, v0, ul, vl factors are ignored since the object will be
  ///         automatically centered and will be confortable in the window
  ///        at any viewing angle.
  ///
  /// check if G4 graphics is ready for drawing

  /*
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (!pVVisManager) {
      TG4Globals::Warning(
         "TG4VisManager", "Gdraw", "Ignored - No graphics driver is built.");
      return;
    }
    if (NeedSetColours())
    {
      SetColors();
      SetColourFlag(false);
    }

    const G4double kRad = M_PI/180.;
    PhysicalVolumesVector pvList;
    G4String sname(name);
    G4bool  successful                 = false;

    pvList = GetPVList(name);
    if (pvList.size()==0)
    {
      TG4Globals::Warning(
        "TG4VisManager", "Gdraw",
        "Volume " + TString(sname) + " not found.");
      return;
    }

    G4VPhysicalVolume *pPV = 0;

    // clear the current scene if not empty
    // if (!fpScene->IsEmpty()) fpScene->Clear();
            // G4Scene::Clear() function not available since Geant4 8.1

    // create and add object's model list to the runtime-duration model
    // list and draw it
    // (it is deleted in the VisManager destructor within
    // all the vectors of the scene)
    for (G4int i=0; i<G4int(pvList.size()); i++)
    {
      pPV = pvList[i];
      successful = fpScene->AddRunDurationModel(new G4PhysicalVolumeModel(pPV));
      if (!successful)
      {
        TG4Globals::Warning(
          "TG4VisManager", "Gdraw",
          "Could not add " + TString(pPV->GetName()) + " to the drawing list."
          + TG4Globals::Endl() +
          "Probably it is already in the list.");
      }
    }
    // get the standard target point of the scene
    const G4Point3D kTargetPoint = fpScene->GetStandardTargetPoint();

    // set the viewpoint and the rotation on the screen
    G4Vector3D viewpointDirection(sin(theta*kRad)*cos(phi*kRad),
                                  sin(theta*kRad)*sin(phi*kRad),
    cos(theta*kRad)); G4Vector3D upVector(sin(psi*kRad), cos(psi*kRad),0);

    // set and register view parameters to the viewer

    G4ViewParameters vp;;
    vp.SetLightsMoveWithCamera(true);
    vp.SetViewGeom();
    vp.UnsetViewHits();
    vp.UnsetViewDigis();
    vp.SetNoOfSides(48);
    vp.SetCurrentTargetPoint(kTargetPoint);
    vp.SetViewpointDirection(viewpointDirection);
    vp.SetUpVector(upVector);
    vp.SetDensityCulling(true);
    fpViewer->SetViewParameters(vp);

    if (IsValidView())
    {
      fpSceneHandler->SetScene(fpScene);
      fpSceneHandler->SetCurrentViewer(fpViewer);
      fpViewer->DrawView();
      fpViewer->ShowView();
    }
    else
      TG4Globals::Warning(
        "TG4VisManager", "Gdraw", "Ignored - Failed to register volume");
  */

  TG4Globals::Warning("TG4VisManager", "Gdraw", "Not implemented");
}
