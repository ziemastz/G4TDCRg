#ifndef DECAYENERGYDATA_HH
#define DECAYENERGYDATA_HH

#pragma once
#include "globals.hh"
#include <map>
#include <vector>

class DecayEnergyData
{
public:
    DecayEnergyData();
    ~DecayEnergyData();

    void loadElectrons(const G4String& filename);
    void loadGammas(const G4String& filename);
    
    std::vector<G4double> GetElectrons(const G4int& eventID);
    std::vector<G4double> GetGammas(const G4int& eventID);
    
    size_t GetMaxDecayElectrons() const {return maxDecayElektrons;}
    size_t GetMaxDecayGammas() const {return maxDecayGammas;}
private:
    std::map<int,std::vector<double> > electrons; //key->evenID,value-> lists of energy in keV
    std::map<int,std::vector<double> > gammas;
    size_t maxDecayElektrons;
    size_t maxDecayGammas;
};

#endif