#include "OpticalChamber.hh"
OpticalChamber *OpticalChamber::_instance = nullptr;

OpticalChamber::OpticalChamber()
{
    chamber = nullptr;
    // Material
    SetMaterial(MATERIALS::Aluminium);
    // Optical Chamber
    // Option of visualization
    start_ang = 0*degree;
    space_ang = 360*degree;
    // pipe
    radiusPipe = 29*mm;
    lenghtPipe = 130*mm;
    // main
    radiusOChamber = 59*mm;
    insertRadiusOChamber = 33*mm;
    heighOChamber = 51*mm;
    // bootom ring
    radiusBottomRingOChamber = 75*mm;
    heighBottomRingOChamber = 5*mm;
    // coin
    radiusMinCoinOChamber = 14*mm;
    radiusMaxCoinOChamber = insertRadiusOChamber;
    heighCoinOChamber = 19;
    // 1st small cylinder;
    insertRadiusSCOChamber1 = radiusMinCoinOChamber;
    heighSCOChamber1 = 7*mm;
    // 2nd small cylinder
    insertRadiusSCOChamber2 = 16.6*mm;
    heighSCOChamber2 = 8*mm;
    // top ring
    radiusTopRingOChamber = 25*mm;
    insertRadiusTopRingOChamber = insertRadiusSCOChamber2;
    heighTopRingOChamber = 5*mm;
    // bottom window Al
    radiusWindowAlOChamber = 45*mm;
    heighWindowAlOChamber = 0.2*mm;
}

OpticalChamber* OpticalChamber::Instance()
{
    if(_instance == nullptr) {
        _instance = new OpticalChamber();
    }
    return _instance;
}

void OpticalChamber::SetMaterial(const MATERIALS& newMaterial)
{
    type = newMaterial;
}

void OpticalChamber::SetRadiusPipe(const G4double& newRadius)
{
    radiusPipe = newRadius;
}

void OpticalChamber::SetLenghtPipe(const G4double& newLenght)
{
    lenghtPipe = newLenght;
}

G4LogicalVolume* OpticalChamber::Construct()
{
    if(chamber != nullptr)
        delete chamber;
    
    // main cylinder
    G4Tubs* mainCylinder = new G4Tubs("mainCylinder",insertRadiusOChamber,radiusOChamber,0.5*heighOChamber,start_ang,space_ang);
    // bottom ring
    G4Tubs* bottomRing = new G4Tubs("bottomRing",radiusOChamber,radiusBottomRingOChamber,0.5*heighBottomRingOChamber,start_ang,space_ang);
    // bottom window Al
    G4Tubs* windowAl = new G4Tubs("windowAl",0,radiusWindowAlOChamber,0.5*heighWindowAlOChamber,start_ang,space_ang);
    // coin
    G4Cons* coin = new G4Cons("coin",radiusMaxCoinOChamber,radiusOChamber,radiusMinCoinOChamber,radiusOChamber,0.5*heighCoinOChamber,start_ang,space_ang);
    // 1st small cylinder
    G4Tubs* smallCylinder1 = new G4Tubs("smallCylinder1",insertRadiusSCOChamber1,radiusOChamber,0.5*heighSCOChamber1,start_ang,space_ang);
    // 2nd small cylinder
    G4Tubs* smallCylinder2 = new G4Tubs("smallCylinder2",insertRadiusSCOChamber2,radiusOChamber,0.5*heighSCOChamber2,start_ang,space_ang);
    // top ring
    G4Tubs* topRing = new G4Tubs("topRing",insertRadiusTopRingOChamber,radiusTopRingOChamber,0.5*heighTopRingOChamber,start_ang,space_ang);
    //
    // union all elements
    G4UnionSolid* step1 = new G4UnionSolid("step1",mainCylinder,bottomRing,0,G4ThreeVector(0,0,-0.5*(heighOChamber-heighBottomRingOChamber)));
    G4UnionSolid* step2 = new G4UnionSolid("step2",step1,windowAl,0,G4ThreeVector(0,0,-0.5*(heighOChamber-heighWindowAlOChamber)));
    G4UnionSolid* step3 = new G4UnionSolid("step3",step2,coin,0,G4ThreeVector(0,0,0.5*(heighOChamber+heighCoinOChamber)));
    G4UnionSolid* step4 = new G4UnionSolid("step4",step3,smallCylinder1,0,G4ThreeVector(0,0,0.5*(heighOChamber+heighSCOChamber1)+heighCoinOChamber));
    G4UnionSolid* step5 = new G4UnionSolid("step5",step4,smallCylinder2,0,G4ThreeVector(0,0,0.5*(heighOChamber+heighSCOChamber2)+heighCoinOChamber+heighSCOChamber1));
    G4UnionSolid* step6 = new G4UnionSolid("step6",step5,topRing,0,G4ThreeVector(0,0,0.5*(heighOChamber+heighTopRingOChamber)+heighCoinOChamber+heighSCOChamber1+heighSCOChamber2));
    //
    // substration of hole for PMT
    //
    G4Tubs* subPMT = new G4Tubs("subPMT",0,radiusPipe,0.5*lenghtPipe,0,360*degree);
    G4RotationMatrix* rotm_PMT = new G4RotationMatrix();
    rotm_PMT->rotateX(90*degree);
    G4ThreeVector uz_PMT = G4ThreeVector(0,-0.5*(lenghtPipe),-0.5*(heighOChamber)+39*mm);
  
    G4SubtractionSolid* step7 = new G4SubtractionSolid("step7",step6,subPMT,rotm_PMT,uz_PMT);
    G4RotationMatrix* rotm_120Z = new G4RotationMatrix();
    rotm_120Z->rotateZ(120*degree);
    G4DisplacedSolid* step8 = new G4DisplacedSolid("step8",step7,rotm_120Z,G4ThreeVector());
    G4SubtractionSolid* step9 = new G4SubtractionSolid("step9",step8,subPMT,rotm_PMT,uz_PMT);
    G4DisplacedSolid* step10 = new G4DisplacedSolid("step10",step9,rotm_120Z,G4ThreeVector());
    G4SubtractionSolid* opticalChamberSolid = new G4SubtractionSolid("opticalChamberSolid",step10,subPMT,rotm_PMT,uz_PMT);
  
    chamber = new G4LogicalVolume(opticalChamberSolid,Material::GetMaterial(type),"opticalChamber");

    // Optical 
    G4OpticalSurface* tio2_sur = new G4OpticalSurface("tio2_sur", LUT, groundtioair, dielectric_LUT);
    tio2_sur->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(MATERIALS::TiO2));
    new G4LogicalSkinSurface("tio2_sur",chamber, tio2_sur);

    return chamber;
}
