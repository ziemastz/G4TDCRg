#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"

HistoManager::HistoManager() : fFileName("g4tdcrg.root")
{
    Book();
}

HistoManager::~HistoManager()
{

    
}

void HistoManager::Book()
{
    // Create or get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetFileName(fFileName);
    analysisManager->SetNtupleMerging(true);

    analysisManager->SetVerboseLevel(1);

    //analysisManager->SetActivation(true);  // enable inactivation of histograms

    // Define histogram indices, titles
    // Default values (to be reset via /analysis/h1/set command)
    G4int nbins   = 100;
    G4double vmin = 0.;
    G4double vmax = 2.*MeV;
    // 0
    analysisManager->CreateH1("Epri", "Energy deposition from primary particles in cocktail", nbins, vmin, vmax);
    analysisManager->CreateH1("Esec", "Energy deposition from secendary particles in cocktail", nbins, vmin, vmax);
    analysisManager->CreateH1("Etot", "Total energy deposition in cocktail", nbins, vmin, vmax);
    analysisManager->CreateH1("Eg", "Total energy deposition in gamma detector", nbins, vmin, vmax);      
    
    // Create 1st ntuple (id = 0)
    analysisManager->CreateNtuple("Cocktail","Energy deposite");
    analysisManager->CreateNtupleIColumn("EventID");
    analysisManager->CreateNtupleIColumn("TrackID");
    analysisManager->CreateNtupleIColumn("ParrentID");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple();

    analysisManager->CreateNtuple("Vial","Energy deposite");
    analysisManager->CreateNtupleIColumn("EventID");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple();

    analysisManager->CreateNtuple("Cup","Energy deposite");
    analysisManager->CreateNtupleIColumn("EventID");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple();


    // Create all histograms as inactivated
    //for(G4int i = 0; i < analysisManager->GetNofH1s(); ++i)
    //{
    //    analysisManager->SetH1Activation(i, false);
    //}
}