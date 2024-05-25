#ifndef COCKTAILSD_HH
#define COCKTAILSD_HH

#pragma once
#include "CocktailHit.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class CocktailSD : public G4VSensitiveDetector
{
public:
    CocktailSD(G4String name);
    ~CocktailSD();
    
    void Initialize(G4HCofThisEvent*) override;
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*) override;

private:
    CocktailHitsCollection* fCocktailCollection;
    G4int fHitsCID;
};

#endif