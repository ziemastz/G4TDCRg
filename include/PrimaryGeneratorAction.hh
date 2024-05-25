#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "DecayEnergyData.hh"

class G4ParticleGun;
class G4Event;
class G4Tubs;
class G4ParticleDefinition;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction(DecayEnergyData* data);
    ~PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* anEvent) override;

private:
    void RandomPosition();
    G4Tubs* logicCocktail;
    G4bool isCenter;
    G4ParticleGun* fParticleGun;
    DecayEnergyData *decayData;
    G4ParticleDefinition *pElectron;
    G4ParticleDefinition *pGamma;
};

#endif