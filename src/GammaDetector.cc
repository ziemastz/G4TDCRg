#include "GammaDetector.hh"
GammaDetector *GammaDetector::_instance = nullptr;
GammaDetector::GammaDetector()
{
  nameDetector = "gammaDetector";
  nameDetectorShield = "GDShield";
  nameCrystalPipe = "GDCrystalPipe";
  nameCrystal = "GDCrystal";
  // Gamma Detector
  SetCrystal(MATERIALS::NaI_Tl);
  // Option of visualization
  start_ang = 0*degree;
  space_ang = 360*degree;
  checkOverlaps = true;
  // Lead cylinder
  radiusPbCylinder = 92.5*mm;
  insertRadiusPbCylinder = 41*mm;
  heighPbCylinder = 157*mm;
  // pipe of NaI detector
  radiusNaIDetector = 41*mm;
  insertRadiusNaIDetector = 40.5*mm;
  heighNaIDetector = 112*mm;
  // NaI crystal
  radiusNaICrystal = 38.1*mm;
  heighNaICrystal = 76.2*mm;
}

void GammaDetector::SetCrystal(const MATERIALS& newCrystal)
{
    type = newCrystal;
}

GammaDetector* GammaDetector::Instance()
{
    if(_instance == nullptr)
        _instance = new GammaDetector();
    
    return _instance;
}

G4LogicalVolume* GammaDetector::Construct()
{
  //
  // cylinder Pb - main solid
  //
  G4Tubs* shieldSolid = new G4Tubs("shieldSolid",insertRadiusPbCylinder,radiusPbCylinder,0.5*heighPbCylinder,start_ang, space_ang);
  detectorShield = new G4LogicalVolume(shieldSolid,Material::GetMaterial(MATERIALS::Lead),nameDetectorShield);
  G4Tubs* detectorSolid = new G4Tubs("detectorSolid",0,radiusPbCylinder,0.5*heighPbCylinder,start_ang, space_ang);
  detector = new G4LogicalVolume(detectorSolid,Material::GetMaterial(MATERIALS::Air),nameDetector);
  new G4PVPlacement(0, G4ThreeVector(0,0,0), detectorShield, nameDetectorShield, detector,false,0,checkOverlaps);
  //
  // Start create of gamma detector
  // Top of gamma detector - main solid
  //
  G4Tubs* topGammaDetector = new G4Tubs("topGammaDetector",0,radiusNaIDetector,0.5*(radiusNaIDetector-insertRadiusNaIDetector), start_ang, space_ang);
  //
  // pipe of NaI
  //
  G4Tubs* pipeSolid = new G4Tubs("pipeSolid",insertRadiusNaIDetector,radiusNaIDetector,0.5*heighNaIDetector, start_ang, space_ang);
  // union of top and pipe NaI
  G4UnionSolid* crystalPipeSolid = new G4UnionSolid("crystalPipeSolid",topGammaDetector,pipeSolid,0,G4ThreeVector(0,0,-0.5*(heighNaIDetector+radiusNaIDetector-insertRadiusNaIDetector)));
  
  crystalPipe = new G4LogicalVolume(crystalPipeSolid, Material::GetMaterial(MATERIALS::Aluminium), nameCrystalPipe);
  new G4PVPlacement(0,G4ThreeVector(0,0,0.5*(heighPbCylinder-radiusNaIDetector+insertRadiusNaIDetector)),crystalPipe,nameCrystalPipe,detector,false,0,checkOverlaps);
  //
  // next insert crystal into pipe
  //
  G4Tubs* crystalSolid = new G4Tubs("crystalSolid",0,38.1*mm,0.5*76.2*mm,start_ang, space_ang);
  crystal = new G4LogicalVolume(crystalSolid,Material::GetMaterial(type),nameCrystal);
  new G4PVPlacement(0,G4ThreeVector(0,0,0.5*(heighPbCylinder-heighNaICrystal)-((radiusNaIDetector-insertRadiusNaIDetector))),crystal,nameCrystal,detector,false,0,checkOverlaps);
  //
  return detector;
}