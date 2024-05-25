#ifndef COCKTAILHIT_HH
#define COCKTAILHIT_HH

#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include <map>

class CocktailHit : public G4VHit
{
public:
    CocktailHit() = default;
    CocktailHit(const CocktailHit&) = default;
    ~CocktailHit() override = default;

    inline void* operator new(size_t);
    inline void operator delete(void* aHit);
    
    inline void SetEventID(G4int id) { eventID = id; }
    inline void AddPrimary(G4int trackID, G4double edep);
    inline void AddSecendary(G4int trackID, G4double edep);
    
    inline G4int GetEventID() {return eventID;}
    inline std::map<G4int,G4double> GetPrimary() {return primary;}
    inline std::map<G4int,G4double> GetSecendary() {return secendary;}

private:
    G4int eventID;
    std::map<G4int,G4double> primary;
    std::map<G4int,G4double> secendary;
};

typedef G4THitsCollection<CocktailHit> CocktailHitsCollection;

extern G4ThreadLocal G4Allocator<CocktailHit>* CocktailHitAllocator;

inline void* CocktailHit::operator new(size_t)
{
  if(!CocktailHitAllocator)
    CocktailHitAllocator = new G4Allocator<CocktailHit>;
  return (void*) CocktailHitAllocator->MallocSingle();
}

inline void CocktailHit::operator delete(void* aHit)
{
  CocktailHitAllocator->FreeSingle((CocktailHit*) aHit);
}

inline void CocktailHit::AddPrimary(G4int trackID, G4double edep)
{
  if(primary.count(trackID)) {
    primary[trackID] += edep;
  }else {
    primary[trackID] = edep;
  }
}

inline void CocktailHit::AddSecendary(G4int trackID, G4double edep)
{
  if(secendary.count(trackID)) {
    secendary[trackID] += edep;
  }else {
    secendary[trackID] = edep;
  }
}
#endif