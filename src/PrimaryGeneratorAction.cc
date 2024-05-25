#include "PrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4RandomDirection.hh"
#include "Randomize.hh"
#include "G4Tubs.hh"
#include "G4ParticleDefinition.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DecayEnergyData* data) : decayData(data)
{
    G4int n_particle = 1;
    fParticleGun     = new G4ParticleGun(n_particle);
    logicCocktail = nullptr;
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    pElectron = particleTable->FindParticle("e-");
    pGamma = particleTable->FindParticle("gamma");
    
    fParticleGun->SetParticleDefinition(pElectron);
    // Default energy,position,momentum
    fParticleGun->SetParticleEnergy(0. * keV);
    fParticleGun->SetParticleTime(0.0*ns);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    isCenter = false;    
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event * anEvent)
{
    RandomPosition();

    std::vector<G4double> electrons = decayData->GetElectrons(anEvent->GetEventID()+1);
    //G4cout << anEvent->GetEventID() << " Electrons: "<<electrons.size()<<G4endl;
    fParticleGun->SetParticleDefinition(pElectron);
    for(size_t i=0; i<electrons.size(); i++) {
        //G4cout << anEvent->GetEventID() << " Set energy electron :" << electrons.at(i)*keV << G4endl;
        fParticleGun->SetParticleEnergy(electrons.at(i)*keV);
        fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
    std::vector<G4double> gammas = decayData->GetGammas(anEvent->GetEventID()+1);
    fParticleGun->SetParticleDefinition(pGamma);
    for(size_t i=0; i<gammas.size(); i++) {
        //G4cout << anEvent->GetEventID() << " Set energy gamma :" << gammas.at(i)*keV << G4endl;
        fParticleGun->SetParticleEnergy(gammas.at(i)*keV);
        fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}

void PrimaryGeneratorAction::RandomPosition()
{
    G4ThreeVector randPos;
    G4double x = 0, y = 0, z = 0;
    if(!isCenter) {
      if(logicCocktail == nullptr) {
        G4LogicalVolume* cocktailLV = G4PhysicalVolumeStore::GetInstance()->GetVolume("cocktail")->GetLogicalVolume();
        if(cocktailLV)
            logicCocktail = dynamic_cast<G4Tubs*>(cocktailLV->GetSolid());
      }

      G4double radius = 0;
      G4double height = 0;
  
      if(logicCocktail) {
        radius = logicCocktail->GetOuterRadius();
        height = logicCocktail->GetZHalfLength();
        //G4cout << "R: " << radius << " H: " << height << G4endl;  
      }else {
        //G4ExceptionDescription msg;
        G4cerr << "Missing or wrong name of logical volume cocktail" << G4endl;
        //G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",JustWarning,msg);
      }
     
      x = radius*2;
      z = radius*2;
      y = height;
      while (((x*x)+(z*z)) > (radius*radius))
      {
        x = G4UniformRand();
        z = G4UniformRand();
        y = G4UniformRand();

        x = (x*2.*radius) - radius;
        z = (z*2.*radius) - radius;
        y = (y*2.*height) - height;
      }
    }
  
    randPos.setX(x);
    randPos.setY(y);
    randPos.setZ(z);

    randPos = G4PhysicalVolumeStore::GetInstance()->GetVolume("cocktail")->GetTranslation() + randPos;
    fParticleGun->SetParticlePosition(randPos);
}
