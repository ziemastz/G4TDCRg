#include "DecayEnergyData.hh"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

void split(const std::string& str, std::vector<std::string>& v) {
  std::istringstream ss(str);
  std::string del;
  while(std::getline(ss, del, '	')) {
    v.push_back(del);
  }
}

DecayEnergyData::DecayEnergyData()
{

}

DecayEnergyData::~DecayEnergyData()
{

    
}

void DecayEnergyData::loadElectrons(const G4String &filename)
{
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        G4cout << "******** ERROR ********* Wrong open file: "<< filename << G4endl;
        return;
    }
    G4double tot_e = 0.;
    G4int pCounts = 0;
    electrons.clear();
    std::vector<std::string> record;
    std::string line;
    while(!file.eof()) {
        line.clear();
        record.clear();

        std::getline(file,line);
        split(line,record);
        int id = 0;
        std::vector<double> energy;
        for (size_t i = 0; i < record.size(); i++)
        {
            if(i==0) {
                id = std::stoi(record[i]);
            }else {
                double d;
                try
                {
                    d =  std::stod(record[i]);
                }
                catch (std::invalid_argument const& ex)
                {
                    d = 0;
                }
                
                energy.push_back(d);
                tot_e += d;
                pCounts++;
            }

        }
        electrons[id] = energy;
    }
    maxDecayElektrons = electrons.size();
    G4cout << "--> Total emitted energy of electrons: "<< tot_e << G4endl;
    G4cout << "--> Number electrons: "<< pCounts << G4endl;
}

void DecayEnergyData::loadGammas(const G4String &filename)
{
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        G4cout << "******** ERROR ********* Wrong open file: "<< filename << G4endl;
        return;
    }
    
    gammas.clear();
    G4double tot_g = 0.;
    G4int pCounts = 0;
    std::vector<std::string> record;
    std::string line;
    while(!file.eof()) {
        line.clear();
        record.clear();
        std::getline(file,line);
        split(line,record);
        int id = 0;
        std::vector<double> energy;
        for (size_t i = 0; i < record.size(); i++)
        {
            if(i==0) {
                id = std::stoi(record[i]);
            }else {
                double d;
                try
                {
                    d =  std::stod(record[i]);
                }
                catch (std::invalid_argument const& ex)
                {
                    d = 0;
                }
                energy.push_back(d);
                tot_g += d;
                pCounts++;
            }

        }
        gammas[id] = energy;
    }
    maxDecayGammas = gammas.size();
    G4cout << "--> Total emitted energy of gammas: "<<tot_g << G4endl;
    G4cout << "--> Number gammas: "<<pCounts << G4endl;
}

std::vector<G4double> DecayEnergyData::GetElectrons(const G4int &eventID)
{   
    size_t index = eventID;
    while (index > maxDecayElektrons) {
        index -= maxDecayElektrons;
    }
    //G4cout << "Event "<<eventID<<"="<<index<<" index"<<G4endl;
    return electrons[index];
}

std::vector<G4double> DecayEnergyData::GetGammas(const G4int &eventID)
{
    size_t index = eventID;
    while (index > maxDecayGammas) {
        index -= maxDecayGammas;
    }
    //G4cout << "Event "<<eventID<<"="<<index<<" index"<<G4endl;
    return gammas[index];
}
