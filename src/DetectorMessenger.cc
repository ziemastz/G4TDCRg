#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* det) : G4UImessenger(), fDetector(det)
{
    fG4TDRCgDir = new G4UIdirectory("/tdcrg/");
    fG4TDRCgDir->SetGuidance("Parameters of simulations.");

    fVolumeCocktailCmd = new G4UIcmdWithADouble("/tdcrg/volumeCoctail", this);
    fVolumeCocktailCmd->SetGuidance("Volume of coctail in vial.");
    fVolumeCocktailCmd->SetGuidance("Value: 0.1-20 mL (empty not available)");
    fVolumeCocktailCmd->SetGuidance("Defualt: 10 mL");
    fVolumeCocktailCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fVolumeCocktailCmd->SetToBeBroadcasted(false);

    fMaterialVialCmd = new G4UIcmdWithAString("/tdcrg/materialVial",this);
    fMaterialVialCmd->SetGuidance("Set material of vial.");
    fMaterialVialCmd->SetGuidance("Value: BoroSilicate, SiO2, PE");
    fMaterialVialCmd->SetGuidance("Defualt: BoroSilicate");
    fMaterialVialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fMaterialVialCmd->SetToBeBroadcasted(false);

    fCocktailTypeCmd = new G4UIcmdWithAString("/tdcrg/cocktailType",this);
    fCocktailTypeCmd->SetGuidance("Set cocktail type filled in a vial.");
    fCocktailTypeCmd->SetGuidance("Value: UltimaGold, Water");
    fCocktailTypeCmd->SetGuidance("Defualt: UltimaGold");
    fCocktailTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fCocktailTypeCmd->SetToBeBroadcasted(false);
}

DetectorMessenger::~DetectorMessenger()
{
    delete fG4TDRCgDir;
    delete fVolumeCocktailCmd;
    delete fMaterialVialCmd;
    delete fCocktailTypeCmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
    if(command == fVolumeCocktailCmd) {
        fDetector->SetVolumeCocktail(G4UIcmdWithADouble::GetNewDoubleValue(newValue));
    }else if(command == fMaterialVialCmd) {
        fDetector->SetMaterialVial(newValue);
    }else if(command == fCocktailTypeCmd) {
        fDetector->SetCocktailType(newValue);
    }
}