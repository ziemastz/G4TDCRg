
#include "CocktailSD.hh"
#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

CocktailSD::CocktailSD(G4String name) :
    G4VSensitiveDetector(name), 
    fHitsCID(-1)
{
    fCocktailCollection = nullptr;
    collectionName.insert("cocktailCollection");
}

CocktailSD::~CocktailSD()
{

    
}

void CocktailSD::Initialize(G4HCofThisEvent *hitsCE)
{
    fCocktailCollection =
        new CocktailHitsCollection(SensitiveDetectorName, collectionName[0]);

    if(fHitsCID < 0)
    {
        fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fCocktailCollection);
    }
    hitsCE->AddHitsCollection(fHitsCID, fCocktailCollection);
}

G4bool CocktailSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep == 0.)
        return false;
    G4double l = aStep->GetStepLength();
    const G4Event *event = G4EventManager::GetEventManager()->GetConstCurrentEvent();
    G4int eventID;
    if(event != nullptr) {
        eventID = event->GetEventID();
    }
     
    G4int trackID = aStep->GetTrack()->GetTrackID();
    
    CocktailHit* cockHit = new CocktailHit();

    cockHit->SetEventID(eventID);
    if(aStep->GetTrack()->GetParentID() > 0) {
        //secendary
        cockHit->AddSecendary(trackID,edep);
    }else {
        //primary
        cockHit->AddPrimary(trackID,edep);
    }

    fCocktailCollection->insert(cockHit);

    return true;
}
