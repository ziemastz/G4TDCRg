#ifndef HISTOMANAGER_HH
#define HISTOMANAGER_HH

#pragma once
#include "globals.hh"
#include "G4AnalysisManager.hh"

class HistoManager
{
public:
    HistoManager();
    ~HistoManager();

private:
    void Book();
    G4String fFileName;
};

#endif