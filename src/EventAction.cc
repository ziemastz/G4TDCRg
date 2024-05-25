
#include "EventAction.hh"
#include "CocktailHit.hh"
#include "VialHit.hh"
#include "CupHit.hh"
#include "GammaHit.hh"

#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"

EventAction::EventAction()
{
    fcocktailCollID = -1;
    fvialCollID = -1;
    fcupCollID = -1;
    fgammaCollID = -1;
}

EventAction::~EventAction()
{

    
}

void EventAction::BeginOfEventAction(const G4Event *anEvent)
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    if(fcocktailCollID < 0) {
        fcocktailCollID = SDman->GetCollectionID("cocktailCollection");
    }
    if(fvialCollID < 0) {
        fvialCollID = SDman->GetCollectionID("vialCollection");
    }
    if(fcupCollID < 0) {
        fcupCollID = SDman->GetCollectionID("cupCollection");
    }
    if(fgammaCollID < 0) {
        fgammaCollID = SDman->GetCollectionID("gammaCollection");
    }

}

void EventAction::EndOfEventAction(const G4Event *anEvent)
{
    CocktailHitsCollection* cocktailHC = nullptr;
    VialHitsCollection* vialHC = nullptr;
    CupHitsCollection* cupHC = nullptr;
    GammaHitsCollection* gammaHC = nullptr;


    G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent();

    if(hitsCE) {
        if(fcocktailCollID >= 0) {
            cocktailHC = (CocktailHitsCollection*) (hitsCE->GetHC(fcocktailCollID));
        }
        if(fvialCollID >= 0) {
            vialHC = (VialHitsCollection*) (hitsCE->GetHC(fvialCollID));
        }
        if(fcupCollID >= 0) {
            cupHC = (CupHitsCollection*) (hitsCE->GetHC(fcupCollID));
        }
        if(fgammaCollID >= 0) {
            gammaHC = (GammaHitsCollection*) (hitsCE->GetHC(fgammaCollID));
        }
    }

    if(cocktailHC) {
        size_t n_hit = cocktailHC->entries();
        if(n_hit >0) {
           std::map<G4int,G4double> primary;
        std::map<G4int,G4double> secendary;
        std::map<G4int,G4double> primaryTot;
        std::map<G4int,G4double> secendaryTot;
        G4int eventID;

        for(size_t i = 0; i < n_hit; ++i) {
            eventID = (*cocktailHC)[i]->GetEventID();
            primary = (*cocktailHC)[i]->GetPrimary();
            secendary = (*cocktailHC)[i]->GetSecendary();
            for(const auto& [key, value] : primary) {
                if(primaryTot.count(key) == 0) {
                    primaryTot[key] = value;
                }else {
                    primaryTot[key] += value;
                }
            }
            for(const auto& [key, value] : secendary) {
                if(secendaryTot.count(key) == 0) {
                    secendaryTot[key] = value;
                }else {
                    secendaryTot[key] += value;
                }
            }
        }
        // get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();
        for(const auto& [key, value] : primaryTot) {
                //G4cout << "EventID-> "<<eventID<<" Primary ID-> "<<key << " Energy-> "<<value<<G4endl;

                analysisManager->FillH1(0,value);
                analysisManager->FillH1(2,value);

                analysisManager->FillNtupleIColumn(0,0,eventID);
                analysisManager->FillNtupleIColumn(0,1,key);
                analysisManager->FillNtupleIColumn(0,2,0);
                analysisManager->FillNtupleDColumn(0,3,value);
                analysisManager->AddNtupleRow(0);

            }
        for(const auto& [key, value] : secendaryTot) {
                //G4cout << "EventID-> "<<eventID<<" Secendary ID-> "<<key << " Energy-> "<<value<<G4endl;

                analysisManager->FillH1(1,value);
                analysisManager->FillH1(2,value);

                analysisManager->FillNtupleIColumn(0,0,eventID);
                analysisManager->FillNtupleIColumn(0,1,key);
                analysisManager->FillNtupleIColumn(0,2,1);
                analysisManager->FillNtupleDColumn(0,3,value);
                analysisManager->AddNtupleRow(0);
            } 
        }
        
    }

    if(vialHC) {
        size_t n_hit = vialHC->entries();
        if(n_hit > 0) {
            G4int eventID;
        G4double totEnergy = 0.;

        for(size_t i=0; i<n_hit; i++) {
            eventID = (*vialHC)[i]->GetEventID();
            totEnergy += (*vialHC)[i]->GetEdep();
        }
        
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleIColumn(1,0,eventID);
        analysisManager->FillNtupleDColumn(1,1,totEnergy);
        analysisManager->AddNtupleRow(1); 
        }
    }

    if(cupHC) {
        size_t n_hit = cupHC->entries();
        G4int eventID;
        G4double totEnergy = 0.;

        for(size_t i=0; i<n_hit; i++) {
            eventID = (*cupHC)[i]->GetEventID();
            totEnergy += (*cupHC)[i]->GetEdep();
        }
        if(totEnergy >0.) {
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillNtupleIColumn(2,0,eventID);
            analysisManager->FillNtupleDColumn(2,1,totEnergy);
            analysisManager->AddNtupleRow(2);
        }
        
    }
    if(gammaHC) {
        size_t n_hit = gammaHC->entries();
        if(n_hit > 0) {
            G4double totEnergy = 0.;
            G4int eventID;
            for(size_t i=0; i<n_hit; i++) {
                totEnergy += (*gammaHC)[i]->GetEdep();
            }
        
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillH1(3,totEnergy);
        }
    }
}
