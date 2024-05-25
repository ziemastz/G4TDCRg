#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#pragma once

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    ~EventAction();

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

private:
     G4int fcocktailCollID;
     G4int fvialCollID;
     G4int fcupCollID;
     G4int fgammaCollID;
};

#endif