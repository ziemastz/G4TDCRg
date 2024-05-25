#ifndef CUPHIT_HH
#define CUPHIT_HH

#pragma once

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class CupHit : public G4VHit
{
public:
    CupHit() = default;
    CupHit(const CupHit&) = default;
    ~CupHit() override = default;
    
    inline void* operator new(size_t);
    inline void operator delete(void* aHit);
    
    inline void SetEventID(G4int id) { eventID = id; }
    inline G4int GetEventID() {return eventID;}

    inline void SetEdep(G4double e) {edep = e;}
    inline G4double GetEdep() {return edep;}
private:
    G4int eventID;
    G4double edep;
};
typedef G4THitsCollection<CupHit> CupHitsCollection;

extern G4ThreadLocal G4Allocator<CupHit>* CupHitAllocator;

inline void* CupHit::operator new(size_t)
{
  if(!CupHitAllocator)
    CupHitAllocator = new G4Allocator<CupHit>;
  return (void*) CupHitAllocator->MallocSingle();
}

inline void CupHit::operator delete(void* aHit)
{
  CupHitAllocator->FreeSingle((CupHit*) aHit);
}

#endif