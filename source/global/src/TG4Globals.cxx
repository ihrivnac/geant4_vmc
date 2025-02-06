//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4Globals.cxx
/// \brief Implementation of the TG4Globals class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4Globals.h"

#include <stdlib.h>

const TString TG4Globals::fgkEndl = "x\n";
const char TG4Globals::fgkTokenSeparator = '+';

//_____________________________________________________________________________
TG4Globals::~TG4Globals()
{
  /// Destructor
}

//
// public static methods
//

//_____________________________________________________________________________
void TG4Globals::Exception(
  const TString& className, const TString& methodName, const TString& text)
{
  /// Print error message end exit the program.

  TString newText = "x\n" + className + "::" + methodName + ":x\n";
  newText += text + "\n";
  newText += "*** TG4Exception: Aborting execution ***";
  newText.ReplaceAll("x\n", "\n    ");

  G4cerr << newText.Data() << G4endl << G4endl;
  abort();
}

//_____________________________________________________________________________
void TG4Globals::Warning(
  const TString& className, const TString& methodName, const TString& text)
{
  /// Print warning message.

  TString newText = "++++  TG4Warning:  ++++x\n";
  newText += className + "::" + methodName + ":x\n";
  newText += text + "\n";
  newText += "+++++++++++++++++++++++";
  newText.ReplaceAll("x\n", "\n    ");

  G4cerr << newText.Data() << G4endl << G4endl;
}

//_____________________________________________________________________________
void TG4Globals::AppendNumberToString(G4String& s, G4int a)
{
  /// Append number to string.

  const char* kpNumber = "0123456789";
  G4String p = "";
  G4String q = "";
  do {
    G4int b = a / 10;
    G4int c = a % 10;
    p = kpNumber[c];
    q = p.append(q);
    a = b;
  } while (a > 0);
  s.append(q);
}

//_____________________________________________________________________________
G4bool TG4Globals::Compare(G4bool activation, TG4G3ControlValue controlValue)
{
  /// Compare the boolean value of the process activation
  /// with the process control value.
  /// Return true if the values correspond, false otherwise.

  if (controlValue == kUnsetControlValue) {
    TG4Globals::Warning("TG4Globals", "Compare", "Control value = kUnset.");
    return false;
  }

  if (controlValue == kActivate || controlValue == kActivate2)
    return activation;
  else
    return !activation;
}

//_____________________________________________________________________________
void TG4Globals::PrintStars(G4bool emptyLineFirst)
{
  /// Print stars.

  if (emptyLineFirst) G4cout << G4endl;

  G4cout << "**********************************************" << G4endl;

  if (!emptyLineFirst) G4cout << G4endl;
}

//_____________________________________________________________________________
G4String TG4Globals::Help()
{
  /// Return VMC mailing list address.

  return G4String("vmc@root.cern.ch");
}

//_____________________________________________________________________________
G4String TG4Globals::GetToken(Int_t i, const TString& s)
{
  /// Tokenize the given string and return the i-th token

  std::vector<G4String> tokens;
  std::string ss = s.Data();

  /*
    std::string::size_type idx0 = 0;
    std::string::size_type idx1 = ss.find(fgkTokenSeparator,idx0);
    if ( idx1 == std::string::npos ) idx1 = ss.length();
    do {
      tokens.push_back(TString(ss.substr(idx0, idx1-idx0)));
      idx0 = idx1+1;
      idx1 = ss.find(fgkTokenSeparator,idx0);
      if ( idx1 == std::string::npos ) idx1 = ss.length();
    }
    while ( idx0 <= ss.length() );
  */
  std::string::size_type idx0 = 0;
  do {
    std::string::size_type idx1 = ss.find(fgkTokenSeparator, idx0);
    if (idx1 == std::string::npos) idx1 = ss.length();
    tokens.push_back(G4String(ss.substr(idx0, idx1 - idx0)));
    idx0 = idx1 + 1;
  } while (idx0 <= ss.length());

  if (i < 0 || i >= Int_t(tokens.size()))
    return "";
  else
    return tokens[i];
}

//_____________________________________________________________________________
G4bool TG4Globals::Contains(const G4String& name, const G4String& nameList)
{
  /// Append a space to both searched name and the list
  /// in order to exclude a match for names which are only substrings of
  /// some name present in the list.
  /// Eg. when omega_c0 is in the list and omega is checked for a presence

  if (nameList.empty()) return false;

  G4String checkName(name);
  checkName.append(" ");

  G4String checkNameList(nameList);
  checkNameList.append(" ");

  return (checkNameList.find(checkName) != std::string::npos);
}
