
#include "VialSD.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

VialSD::VialSD(G4String name) :
    G4VSensitiveDetector(name),
    fHitsCID(-1)
{
    fVialCollection = nullptr;
    collectionName.insert("vialCollection");
}
VialSD::~VialSD()
{

}

void VialSD::Initialize(G4HCofThisEvent *hitsCE)
{
    fVialCollection =
        new VialHitsCollection(SensitiveDetectorName, collectionName[0]);

    if(fHitsCID < 0)
    {
        fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fVialCollection);
    }
    hitsCE->AddHitsCollection(fHitsCID, fVialCollection);
}

G4bool VialSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep == 0.)
        return false;

    const G4Event *event = G4EventManager::GetEventManager()->GetConstCurrentEvent();
    G4int eventID;
    if(event != nullptr) {
        eventID = event->GetEventID();
    }

    VialHit * vialHit = new VialHit();
    vialHit->SetEventID(eventID);
    vialHit->SetEdep(edep);

    fVialCollection->insert(vialHit);
    return true;
}
