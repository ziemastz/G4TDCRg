#ifndef GAMMASD_HH
#define GAMMASD_HH

#pragma once
#include "GammaHit.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class GammaSD : public G4VSensitiveDetector
{
public:
    GammaSD(G4String name);
    ~GammaSD();
    void Initialize(G4HCofThisEvent*) override;
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*) override;

private:
    GammaHitsCollection* fGammaCollection;
    G4int fHitsCID;
};

#endif