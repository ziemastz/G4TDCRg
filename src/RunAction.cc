#include "RunAction.hh"

#include "HistoManager.hh"
#include "Run.hh"

RunAction::RunAction() : fRun(nullptr), fHistoManager(nullptr)
{
    fHistoManager = new HistoManager();
}

RunAction::~RunAction()
{
    delete fHistoManager;
}

G4Run *RunAction::GenerateRun()
{
    fRun = new Run();
    return fRun;
}

void RunAction::BeginOfRunAction(const G4Run *)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //if(analysisManager->IsActive())
    //{
        analysisManager->OpenFile();
    //}
}

void RunAction::EndOfRunAction(const G4Run *)
{
    if(isMaster)
    fRun->EndOfRun();

    // save histograms
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //if(analysisManager->IsActive())
    //{
        analysisManager->Write();
        analysisManager->CloseFile();
    //}
}
