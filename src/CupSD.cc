#include "CupSD.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

CupSD::CupSD(G4String name) :
    G4VSensitiveDetector(name),
    fHitsCID(-1)
{
    fCupCollection = nullptr;
    collectionName.insert("cupCollection");
}

CupSD::~CupSD() { }

void CupSD::Initialize(G4HCofThisEvent *hitsCE)
{
    fCupCollection =
        new CupHitsCollection(SensitiveDetectorName, collectionName[0]);

    if(fHitsCID < 0)
    {
        fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fCupCollection);
    }
    hitsCE->AddHitsCollection(fHitsCID, fCupCollection);
}

G4bool CupSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep == 0.)
        return false;

    const G4Event *event = G4EventManager::GetEventManager()->GetConstCurrentEvent();
    G4int eventID;
    if(event != nullptr) {
        eventID = event->GetEventID();
    }

    CupHit * cupHit = new CupHit();
    cupHit->SetEventID(eventID);
    cupHit->SetEdep(edep);

    fCupCollection->insert(cupHit);
    return true;
}
