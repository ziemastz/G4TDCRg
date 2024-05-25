#include "DetectorConstruction.hh"
#include "Material.hh"
#include "CocktailSD.hh"
#include "VialSD.hh"
#include "CupSD.hh"
#include "GammaSD.hh"
#include "OpticalChamber.hh"
#include "PMT.hh"
#include "GammaDetector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
    checkOverlaps = true;
    // WORLD
    // Parameters
    world_size_Y = 60*cm;
    world_size_X = 60*cm;
    world_size_Z = 60*cm;

    // VIAL
    volumeCocktail = 10; // unit mL
    materialVial = Material::GetMaterial(MATERIALS::BoroSilicate);
    cocktailType = Material::GetMaterial(MATERIALS::UltimaGold);

    isVial = true;

    cocktail_lv = nullptr;
    vial_lv = nullptr;
    cup_lv = nullptr;

    fDetectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
    delete materialVial;
    delete cocktailType;
    delete fDetectorMessenger;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // build world
    G4Box *world_box = new G4Box("World",world_size_X,world_size_Y,world_size_Z);
    G4LogicalVolume *world_lv = new G4LogicalVolume(world_box, Material::GetMaterial(Air), "World");
    G4VPhysicalVolume* world_pv = new G4PVPlacement(0, G4ThreeVector(0,0,0), world_lv, "World", 0, false, 0);

    // build vials
    G4RotationMatrix* rotm_90X = new G4RotationMatrix();
    rotm_90X->rotateX(90*degree);
    
    // first cocktail
    cocktail_lv = vial.ConstructCocktail(volumeCocktail,cocktailType);

    cocktail_pv = new G4PVPlacement(rotm_90X,G4ThreeVector(0,0,0),cocktail_lv,"cocktail",world_lv,false,0,checkOverlaps);

    
    //vial
    vial_lv = vial.ConstructVial(materialVial);
    vial_pv = new G4PVPlacement(rotm_90X,G4ThreeVector(0,vial.GetPosYVial(),0),vial_lv,"vial",world_lv,false,0,checkOverlaps);
    //cup
    cup_lv = vial.ConstructCup();
    cup_pv = new G4PVPlacement(rotm_90X,G4ThreeVector(0,vial.GetPosYCup(),0),cup_lv,"cup",world_lv,false,0,checkOverlaps);

    //border
   // G4OpticalSurface* cocktail_sur = new G4OpticalSurface("cocktail_sur",  LUT, polishedteflonair, dielectric_LUT);
   // new G4LogicalBorderSurface("cocktail_sur",vial_pv,cocktail_pv,cocktail_sur);        
    

    //optical chamber
    opticalChamber_lv = OpticalChamber::Instance()->Construct();
    opticalChamber_pv = new G4PVPlacement(rotm_90X, G4ThreeVector(0,0.5*(OpticalChamber::Instance()->GetHeighOpticalChamber())-40*mm,0), opticalChamber_lv, "opticalChamber",world_lv,false,0,checkOverlaps);

    //gamma NaI detector
    GammaDetector *gd = GammaDetector::Instance();
    gammaDetector_lv = gd->Construct();
    gammaDetector_pv = new G4PVPlacement(rotm_90X, G4ThreeVector(0,-(0.5*gd->GetHeightShield())-40*mm,0),gammaDetector_lv,"gammaDetector",world_lv,false,0,checkOverlaps);

    // PMTs
    PMT* pmt = PMT::Instance();
    pmt_lv = pmt->Construct();
    G4double detectorPositionZ;
    G4double detectorPositionY = -1*mm;  
    G4double detectorPositionX;
    G4double distanseOfPMT = 16.6*mm;

    for(G4int i=0; i<3; i++)
    {
        //The azimuthal angle to arrange the detectors in a ring
        G4double thetaDetector = (double)(i*120*degree);
        //
        detectorPositionZ = (distanseOfPMT + pmt->GetLenghtPipe()/2)*std::cos(thetaDetector);
        detectorPositionX = (distanseOfPMT + pmt->GetLenghtPipe()/2)*std::sin(thetaDetector);
        //Define the rotation matrix for correct placement of detetors
        G4RotationMatrix rotm_PMT = G4RotationMatrix();
        rotm_PMT.rotateY(thetaDetector);
        G4ThreeVector uz_PMT = G4ThreeVector(detectorPositionX, detectorPositionY, detectorPositionZ);
        G4Transform3D transform = G4Transform3D(rotm_PMT, uz_PMT);
        //if(i!=1)
            new G4PVPlacement(transform, pmt_lv, "logicPMT", world_lv, false, i, checkOverlaps);
    }
    return world_pv;
}

void DetectorConstruction::ConstructSDandField()
{   
    CocktailSD* sd = new CocktailSD("/cocktailSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    SetSensitiveDetector(cocktail_lv,sd);
    
    VialSD * vSD = new VialSD("/vialSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(vSD);
    SetSensitiveDetector(vial_lv,vSD);

    CupSD * cSD = new CupSD("/cupSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(cSD);
    SetSensitiveDetector(cup_lv,cSD); 
    
    GammaSD* gSD = new GammaSD("/gammaSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(gSD);
    SetSensitiveDetector(GammaDetector::Instance()->GetCrystal(),gSD);
    
}

void DetectorConstruction::SetVolumeCocktail(const G4double& newVolume) {
    if(newVolume > 0.0 && newVolume <= 20) {
        volumeCocktail = newVolume;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
}

void DetectorConstruction::SetMaterialVial(const G4String &newMaterial)
{
    if(newMaterial == "BoroSilicate") {
        materialVial = Material::GetMaterial(MATERIALS::BoroSilicate);
    }else if(newMaterial == "SiO2") {
        materialVial = Material::GetMaterial(MATERIALS::SiO2);
    }else if(newMaterial == "PE") {
        materialVial = Material::GetMaterial(MATERIALS::PE);
    }
 }

 void DetectorConstruction::SetCocktailType(const G4String &newCocktail)
 {
    if(newCocktail == "UltimaGold") {
        cocktailType = Material::GetMaterial(MATERIALS::UltimaGold);
        cocktailType->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(MATERIALS::UltimaGold));
    }else if(newCocktail == "Water") {
        cocktailType = Material::GetMaterial(MATERIALS::Water);
        cocktailType->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(MATERIALS::Water));
    }
 }
