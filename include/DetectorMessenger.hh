#ifndef DETECTORMESSENGER_HH
#define DETECTORMESSENGER_HH

#pragma once
#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIcommand;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIdirectory;

class DetectorMessenger  : public G4UImessenger
{
public:
    DetectorMessenger(DetectorConstruction* det);
    ~DetectorMessenger();

    void SetNewValue(G4UIcommand *command, G4String newValue) override;

private:
    DetectorConstruction* fDetector;

    G4UIdirectory* fG4TDRCgDir;

    //vial
    G4UIcmdWithADouble* fVolumeCocktailCmd;
    G4UIcmdWithAString* fMaterialVialCmd;
    G4UIcmdWithAString* fCocktailTypeCmd;
};
#endif