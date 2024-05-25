#ifndef VIALSD_HH
#define VIALSD_HH

#pragma once
#include "VialHit.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class VialSD : public G4VSensitiveDetector
{
public:
    VialSD(G4String name);
    ~VialSD();
    void Initialize(G4HCofThisEvent*) override;
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*) override;

private:
    VialHitsCollection* fVialCollection;
    G4int fHitsCID;
};

#endif