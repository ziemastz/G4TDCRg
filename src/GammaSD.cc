#include "GammaSD.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

GammaSD::GammaSD(G4String name) :
    G4VSensitiveDetector(name),
    fHitsCID(-1)
{
    fGammaCollection = nullptr;
    collectionName.insert("gammaCollection");
}

GammaSD::~GammaSD()
{
}

void GammaSD::Initialize(G4HCofThisEvent *hitsCE)
{
    fGammaCollection =
        new GammaHitsCollection(SensitiveDetectorName, collectionName[0]);

    if(fHitsCID < 0)
    {
        fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fGammaCollection);
    }
    hitsCE->AddHitsCollection(fHitsCID, fGammaCollection);

}

G4bool GammaSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep == 0.)
        return false;

    const G4Event *event = G4EventManager::GetEventManager()->GetConstCurrentEvent();
    G4int eventID;
    if(event != nullptr) {
        eventID = event->GetEventID();
    }

    GammaHit * gHit = new GammaHit();
    gHit->SetEventID(eventID);
    gHit->SetEdep(edep);

    fGammaCollection->insert(gHit);
    return true;
}
