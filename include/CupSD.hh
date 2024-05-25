#ifndef CUPSD_HH
#define CUPSD_HH

#pragma once

#include "CupHit.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class CupSD : public G4VSensitiveDetector
{
public:
    CupSD(G4String name);
    ~CupSD();
    
    void Initialize(G4HCofThisEvent*) override;
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*) override;
private:
    CupHitsCollection* fCupCollection;
    G4int fHitsCID;
};

#endif