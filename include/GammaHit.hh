#ifndef GAMMAHIT_HH
#define GAMMAHIT_HH

#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
class GammaHit : public G4VHit
{
public:
    GammaHit() = default;
    GammaHit(const GammaHit&) = default;
    ~GammaHit() override = default;

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
typedef G4THitsCollection<GammaHit> GammaHitsCollection;

extern G4ThreadLocal G4Allocator<GammaHit>* GammaHitAllocator;

inline void* GammaHit::operator new(size_t)
{
  if(!GammaHitAllocator)
    GammaHitAllocator = new G4Allocator<GammaHit>;
  return (void*) GammaHitAllocator->MallocSingle();
}

inline void GammaHit::operator delete(void* aHit)
{
  GammaHitAllocator->FreeSingle((GammaHit*) aHit);
}
#endif