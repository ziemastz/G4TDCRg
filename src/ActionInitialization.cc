#include "ActionInitialization.hh"

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
{   
    G4cout<< "**** Decay Energy Data *****"<<G4endl;
    decayData = new DecayEnergyData();
    G4cout<< "Loading electrons ..."<<G4endl;
    decayData->loadElectrons("emittedElectrons.txt");
    G4cout<< "Loaded electrons - Done ("<<decayData->GetMaxDecayElectrons() <<")"<<G4endl;
    G4cout<< "Loading gammas ..."<<G4endl;
    decayData->loadGammas("emittedGammas.txt");
    G4cout<< "Loaded gammas - Done ("<<decayData->GetMaxDecayGammas() <<")"<<G4endl;
}

ActionInitialization::~ActionInitialization()
{

}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction(decayData));
    
    SetUserAction(new RunAction());
    
    EventAction* eventAction = new EventAction();
    SetUserAction(eventAction);

    //SetUserAction(new SteppingAction(eventAction));
}
