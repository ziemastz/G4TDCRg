#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#pragma once
#include "globals.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UserSteppingAction.hh"

#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction*);
    ~SteppingAction();
    
    void UserSteppingAction(const G4Step*) override;

private:
    EventAction *fEvenAction;
};

#endif