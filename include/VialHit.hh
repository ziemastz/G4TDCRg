#ifndef VIALHIT_HH
#define VIALHIT_HH

#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class VialHit : public G4VHit
{
public:
    VialHit() = default;
    VialHit(const VialHit&) = default;
    ~VialHit() override = default;

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
typedef G4THitsCollection<VialHit> VialHitsCollection;

extern G4ThreadLocal G4Allocator<VialHit>* VialHitAllocator;

inline void* VialHit::operator new(size_t)
{
  if(!VialHitAllocator)
    VialHitAllocator = new G4Allocator<VialHit>;
  return (void*) VialHitAllocator->MallocSingle();
}

inline void VialHit::operator delete(void* aHit)
{
  VialHitAllocator->FreeSingle((VialHit*) aHit);
}
#endif