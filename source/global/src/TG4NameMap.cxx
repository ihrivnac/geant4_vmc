// $Id: TG4NameMap.cxx,v 1.1.1.1 2002/09/27 10:00:03 rdm Exp $
// Category: global
//
// Author: I. Hrivnacova
//
// Class TG4NameMap
// ----------------
// See the class description in the header file.

#include "TG4NameMap.h"
#include "TG4Globals.h"

#include "g4std/iomanip"
#include "globals.hh"

G4String TG4NameMap::fgUndefined = "Undefined";

//_____________________________________________________________________________
TG4NameMap::TG4NameMap() 
  : fSecond(fgUndefined) {
//
}

//_____________________________________________________________________________
TG4NameMap::TG4NameMap(const TG4NameMap& right) {
//
  TG4Globals::Exception("TG4NameMap is protected from copying.");
}  

//_____________________________________________________________________________
TG4NameMap::~TG4NameMap() {
//
}

// operators

//_____________________________________________________________________________
TG4NameMap& TG4NameMap::operator=(const TG4NameMap& right)
{
  // check assignement to self
  if (this == &right) return *this;

  TG4Globals::Exception("TG4NameMap is protected from assigning.");
    
  return *this;  
}    
          
// public methods

//_____________________________________________________________________________
G4bool TG4NameMap::Add(const G4String& first, const G4String& second)
{  
// Adds names pair to the map.
// fSecond is not used in this add method.
// ---

  if (GetSecond(first) == fgUndefined) {
    // insert into map 
    // only in case it is not yet here
    fMap[first] = second;
    return true;
  }
  return false;
}

//_____________________________________________________________________________
G4bool TG4NameMap::AddName(const G4String& name)
{  
// Adds name to the map.
// ---

  if (GetSecond(name) == fgUndefined) {
    // insert into map 
    // only in case it is not yet here
    fMap[name] = fSecond;
    return true;
  }
  return false;
}

//_____________________________________________________________________________
const G4String& TG4NameMap::GetSecond(const G4String& name) const
{
// Gets second name associated with given name.
// ---

  MapConstIterator i = fMap.find(name);
  if (i == fMap.end()) 
    return fgUndefined;
  else                 
    return (*i).second;
}

//_____________________________________________________________________________
void TG4NameMap::PrintAll() const
{
// Dumps all map.
// ---

  if (fMap.size()) {
    G4cout << "Dump of TG4NameMap - " << fMap.size() << " entries:" << G4endl;
    G4int counter = 0;
    for (MapConstIterator i=fMap.begin(); i != fMap.end(); i++) {
      const G4String& first  = (*i).first;
      const G4String& second = (*i).second;
      G4cout << "Map element " << G4std::setw(3) << counter++ << "   " 
             << first << "   " << second << G4endl;
    }
  }
}

//_____________________________________________________________________________
void TG4NameMap::Clear() 
{
// Clears the map.
// ---

  fMap.clear();
  fSecond = "Undefined";
}  
