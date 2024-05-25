#include "PMT.hh"
PMT *PMT::_instance = nullptr;
PMT::PMT()
{
  // Option to switch on/off checking of volumes overlaps
  checkOverlaps = true;
  // Option of visualization
  start_ang = 0*degree;
  space_ang = 360*degree;
  windowGlass = MATERIALS::BoroSilicate;
  photocathode = MATERIALS::BialkaliHarmer;
  pipeMaterial = MATERIALS::Aluminium;
  //
  // PMT
  //
  // pipe
  radiusPipe = 29*mm;
  insideRadiusPipe = 27.5*mm;
  lenghtPipe = 130*mm;
  windowRadiusPipe = 24*mm;
  windowLenghtPipe = 1.5*mm;
  // Teflon ring
  radiusTRing = 27.5*mm;
  insideRadiusTRing = 26*mm;
  lenghtTRing = 12*mm;
  windowRadiusTRing = 24*mm;
  windowLenghtTRing = 2*mm;
  // glass tube Ref. datasheet
  radiusGTube = 51.5*0.5*mm;
  thciknessGTube = 2.25*mm;
  insideRadiusGTube = radiusGTube - thciknessGTube;
  lenghtGTube = 100*mm;
  // photocathode
  heighSphereOfPhotocathode = 5*mm; 
  //radiusPhotocathode = (insideRadiusGTube*insideRadiusGTube + heighSphereOfPhotocathode*heighSphereOfPhotocathode) / (2*heighSphereOfPhotocathode);
  radiusPhotocathode = 58*mm;
  thicknessPhotocathode = 100*nm;
  distancePhotocathode = thciknessGTube+1*mm;
  activePhotocathode = (46*mm)/2;

}

void PMT::SetWindowPMTMaterial(const MATERIALS& newGlass)
{
    windowGlass = newGlass;
}

void PMT::SetPhotocathodeMaterial(const MATERIALS& newPhotocathode)
{
    photocathode = newPhotocathode;
}
void PMT::SetPipePMTMaterial(const MATERIALS& newMaterial)
{
    pipeMaterial = newMaterial;
}

PMT* PMT::Instance()
{
    if(_instance == nullptr)
        _instance = new PMT();
    
    return _instance;
}

G4LogicalVolume* PMT::Construct()
{
// PMT 
  G4Tubs* pmtSolid = new G4Tubs("pmtSolid", 0, radiusPipe, 0.5*lenghtPipe, start_ang, space_ang);
  logicPMT = new G4LogicalVolume(pmtSolid,Material::GetMaterial(MATERIALS::Air),"logicPMT");
  
  // Define all solid of PMT
  // pipe
  G4Tubs* window = new G4Tubs("windowPipe", windowRadiusPipe, radiusPipe, 0.5*windowLenghtPipe, start_ang, space_ang);
  G4Tubs* pipe = new G4Tubs("pipe", insideRadiusPipe, radiusPipe, 0.5*lenghtPipe, start_ang, space_ang);
  G4UnionSolid* pipeSolid = new G4UnionSolid("pipeSolid",pipe,window,0,G4ThreeVector(0,0,-0.5*(lenghtPipe-windowLenghtPipe)));
  
  // teflon ring
  G4Tubs* windowTRing = new G4Tubs("windowTRing", windowRadiusTRing, radiusTRing, 0.5*windowLenghtTRing, start_ang, space_ang);
  G4Tubs* teflonRing = new G4Tubs("teflonRing", insideRadiusTRing, radiusTRing, 0.5*lenghtTRing, start_ang, space_ang);
  G4UnionSolid* teflonRingSolid = new G4UnionSolid("teflonRingSolid", teflonRing, windowTRing,0,G4ThreeVector(0,0,-0.5*(lenghtTRing-windowLenghtTRing)));
  
  // glass tube
  G4Tubs* glassTubeSolid = new G4Tubs("glassTubeSolid", 0, radiusGTube, 0.5*lenghtGTube,start_ang, space_ang);
  
  // Photocathode: bialkali
  G4Tubs* cutTube = new G4Tubs("cutTube", 0, insideRadiusGTube, lenghtGTube, 0, 360*degree);
  G4RotationMatrix* rotmCSphere = new G4RotationMatrix();
  rotmCSphere->rotateX(90*deg);

  G4Sphere* cutSphere = new G4Sphere("cutSphere", heighSphereOfPhotocathode, radiusPhotocathode, 0, 180*degree, 0, 180*degree);
  G4IntersectionSolid* fullSphereSolid = new G4IntersectionSolid("fullSphereSolid", cutSphere, cutTube, rotmCSphere, G4ThreeVector(0,radiusPhotocathode,0));
  // Photocathoda: active bialkali
  G4Tubs* cutTubeAct = new G4Tubs("cutTubeAct", 0, activePhotocathode, lenghtGTube, 0, 360*degree);

  // vacuum step 1
  G4double lenghtVacuumTube = lenghtGTube- (radiusGTube - insideRadiusGTube) - distancePhotocathode - heighSphereOfPhotocathode;
  G4Tubs* vacuumTube1 = new G4Tubs("vacuumTube1", 0, insideRadiusGTube, 0.5*lenghtVacuumTube, start_ang, space_ang);
  G4UnionSolid* vacuumTubeSolid = new G4UnionSolid("vacuumTubeSolid",vacuumTube1,fullSphereSolid,rotmCSphere,G4ThreeVector(0,0,-heighSphereOfPhotocathode-0.5*lenghtVacuumTube+radiusPhotocathode));

  G4Sphere* sphere = new G4Sphere("sphere", radiusPhotocathode-thicknessPhotocathode, radiusPhotocathode,0,180*degree,0,180*degree);
  G4IntersectionSolid* photocathodeSolid = new G4IntersectionSolid("photocathodeSolid", sphere, cutTube, rotmCSphere, G4ThreeVector(0,radiusPhotocathode,0));
  G4IntersectionSolid* activePhotocathodeSolid = new G4IntersectionSolid("photocathodeSolid", sphere, cutTubeAct, rotmCSphere, G4ThreeVector(0,radiusPhotocathode,0));
  // glass part in front photocathode

  // end solid
  //
  // Add to logic
    // Pipe
  logicPipe = new G4LogicalVolume(pipeSolid,Material::GetMaterial(pipeMaterial),"logicPipe");
    // Pipe - optical
  G4OpticalSurface* tio2_sur = new G4OpticalSurface("tio2_sur", unified, groundfrontpainted, dielectric_metal);
  tio2_sur->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(MATERIALS::TiO2));
  new G4LogicalSkinSurface("tio2_sur",logicPipe, tio2_sur);
    // Teflon ring
  G4Material* teflon_mat = Material::GetMaterial(MATERIALS::Teflon);
  teflon_mat->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(MATERIALS::Teflon));
  logicTeflonRing = new G4LogicalVolume(teflonRingSolid,teflon_mat,"logicTRing");
    // Teflon ring - optical
  G4OpticalSurface* teflon_sur = new G4OpticalSurface("teflon_sur", LUT, groundteflonair, dielectric_LUT);
  teflon_sur->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(MATERIALS::Teflon));
  new G4LogicalSkinSurface("teflon_sur",logicTeflonRing, teflon_sur);
    // Glass Tube
  G4Material* glassTube_mat = Material::GetMaterial(windowGlass);
  glassTube_mat->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(windowGlass));
  logicGlassTube = new G4LogicalVolume(glassTubeSolid,glassTube_mat,"logicGlassTube");
    // Glass Tube - optical
  G4OpticalSurface* glassTube_sur = new G4OpticalSurface("glassTube_sur", unified, polished, dielectric_dielectric);
  glassTube_sur->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(windowGlass));
  new G4LogicalSkinSurface("glassTube_sur", logicGlassTube, glassTube_sur);
    // Photocathode
  G4Material* photocathode_mat = Material::GetMaterial(photocathode);
  photocathode_mat->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(photocathode));
  logicPhotocathode = new G4LogicalVolume(photocathodeSolid,photocathode_mat,"logicPhotocathode");
    // Active photocathode
  logicActivePhotocathode = new G4LogicalVolume(activePhotocathodeSolid,photocathode_mat,"logicActivePhotocathode");
    // Vacuum
  logicVacuumTube = new G4LogicalVolume(vacuumTubeSolid,Material::GetMaterial(MATERIALS::Vacuum),"logicVacuumTube");
  new G4PVPlacement(0, G4ThreeVector(), logicPipe,"logicPipe",logicPMT,false,0,checkOverlaps);
  G4PVPlacement* teflonRing_phy = new G4PVPlacement(0, G4ThreeVector(0,0,-0.5*(lenghtPipe-lenghtTRing)+windowLenghtPipe), logicTeflonRing,"logicTRing",logicPMT,false,0,checkOverlaps);
  G4PVPlacement* activePhotocathode_phy = new G4PVPlacement(0,G4ThreeVector(), logicActivePhotocathode, "logicActivePhotocathode", logicPhotocathode,false,0,checkOverlaps);
  G4PVPlacement* photocathode_phy = new G4PVPlacement(rotmCSphere, G4ThreeVector(0,0,-heighSphereOfPhotocathode-0.5*lenghtVacuumTube+radiusPhotocathode), logicPhotocathode,"logicPhotocathode",logicVacuumTube,false,0,checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0,0,0.5*(distancePhotocathode+heighSphereOfPhotocathode-(radiusGTube - insideRadiusGTube))), logicVacuumTube,"logicVacuumTube",logicGlassTube,false,0,checkOverlaps);
  G4PVPlacement* glassTube_phy = new G4PVPlacement(0, G4ThreeVector(0,0,-0.5*(lenghtPipe-lenghtGTube)+windowLenghtPipe+windowLenghtTRing), logicGlassTube,"logicGlassTube",logicPMT,false,0,checkOverlaps);
  
    // Photocathode - optical
  G4OpticalSurface* photocathode_sur = new G4OpticalSurface("photocathode_sur", unified, polished, dielectric_metal);
  photocathode_sur->SetMaterialPropertiesTable(Material::GetMaterialPropertiesTable(photocathode));
  new G4LogicalBorderSurface("photocathode_sur",glassTube_phy,photocathode_phy,photocathode_sur);
  G4OpticalSurface* activePhotocathode_sur = new G4OpticalSurface("activePhotocathode_sur", unified, polished, dielectric_dielectric);
  new G4LogicalBorderSurface("activePhotocathode_sur",glassTube_phy,activePhotocathode_phy,activePhotocathode_sur);
   // Teflon surface
   G4OpticalSurface* teflonRing_sur = new G4OpticalSurface("teflonRing_sur", LUT, RoughTeflon_LUT, dielectric_metal);
   new G4LogicalBorderSurface("teflonRing_bor",glassTube_phy,teflonRing_phy,teflonRing_sur);

  return logicPMT;
}