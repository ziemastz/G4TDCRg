#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#pragma once
#include "G4VUserActionInitialization.hh"
#include "DecayEnergyData.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    ~ActionInitialization();
    
    void BuildForMaster() const override;
    void Build() const override;
    
private:
    DecayEnergyData *decayData;
};

#endif