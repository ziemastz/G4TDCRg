
#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4RunManagerFactory.hh"
#include "G4String.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
// G4TDKg class
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc,char** argv)
{
    G4Random::setTheEngine(new CLHEP::HepJamesRandom());

    // detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = nullptr;
    if(argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }
        
    
    auto runManager = G4RunManagerFactory::CreateRunManager();
    
    runManager->SetUserInitialization(new DetectorConstruction());
    
    // Physics list:
    
    G4VModularPhysicsList* physicsList = new FTFP_BERT(); 
    physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
    physicsList->RegisterPhysics(new G4OpticalPhysics());
    
    runManager->SetUserInitialization(physicsList);
    
    runManager->SetUserInitialization(new ActionInitialization());
    
    // Initialize G4 kernel
    //
    runManager->Initialize();

    // User interface:
  
    // Initialize visualization
    //
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    //G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
    if ( ! ui ) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted 
    // in the main() program !
  
    delete visManager;
    delete runManager;
    return 0;
}