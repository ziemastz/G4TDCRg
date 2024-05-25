#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction *ea) : fEvenAction(ea)
{

}

SteppingAction::~SteppingAction()
{

   
}

void SteppingAction::UserSteppingAction(const G4Step *)
{

}