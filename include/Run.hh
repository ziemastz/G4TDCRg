#ifndef RUN_HH
#define RUN_HH

#pragma once

#include "globals.hh"
#include "G4Run.hh"

class Run : public G4Run
{
public:
    Run();
    ~Run();
    void Merge(const G4Run* run) override;

    void EndOfRun();

private:
    //data kolection of one run
};

#endif