#ifndef RUNACTION_HH
#define RUNACTION_HH

#pragma once
#include "G4UserRunAction.hh"

class Run;
class HistoManager;
class G4Run;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();

    G4Run* GenerateRun() override;
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

private:
    Run* fRun;
    HistoManager* fHistoManager;
};

#endif