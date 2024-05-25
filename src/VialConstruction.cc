#include "VialConstruction.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "Material.hh"

VialConstruction::VialConstruction()
{
  // Option of visualization
  start_ang = 0*degree;
  space_ang = 360*degree;
// Vial Cap & Cocktail
/*
*      
*   _| r |_h
*  |       |
*  |       |
*  |   R   | H
*  |       |
*  |       |
*  ---------
*/
// Vial
    h = 12*mm;
    H = 58*mm - h;
    r = 0.5 * 16*mm;
    R = 0.5 * 27.6*mm;  // Radius Glass Vial
    t = 1.1*mm;

  radiusGlassVial = (27.6*mm)/2;
  openRadiusGlassVial = (16.0*mm)/2;
  thciknessGlassVial = 1.1*mm;
  
  topHeightGlassVial = 12*mm;
  totalHeightGlassVial = 59*mm;
  //cocktail
  heightCockail = 19.7*mm;
  optPositionYCocktail = 0*mm;
  // cap & foil Al
  radiusCap = 16*mm;
  insertRadiusCap = 11*mm;
  topThicknessCap = 2.65*mm;
  heightCup = topHeightGlassVial+topThicknessCap-1;
  
  thicknessFoilAlCap = 0.35*mm;
  optDistanceVial = 2*mm;
  insertHeighCap = topHeightGlassVial-optDistanceVial+thicknessFoilAlCap;
}

VialConstruction::~VialConstruction()
{

}

void VialConstruction::Construct(G4LogicalVolume *world)
{
    //build vial
    G4Tubs* tub = new G4Tubs("tub",0,R,(H+h)*0.5,start_ang,space_ang);
    G4Tubs* subOutTopVial = new G4Tubs("subOutTopVial",r+t,R,h*0.5,start_ang,space_ang);
    G4SubtractionSolid* tub2 = new G4SubtractionSolid("tub2",tub,subOutTopVial);

    G4LogicalVolume *vial_lv = new G4LogicalVolume(tub2,material,"vial");
    
    G4RotationMatrix* rotm_90X = new G4RotationMatrix();
    rotm_90X->rotateX(90*degree);

    new G4PVPlacement(rotm_90X, G4ThreeVector(),vial_lv,"vial_lv",world,false,0,true);

}

G4LogicalVolume* VialConstruction::ConstructCocktail(const G4double &volumeCocktail, G4Material *cocktailType)
{
    G4Tubs* cocktailSolid = new G4Tubs("cocktail_tub", 0, radiusGlassVial-thciknessGlassVial, 0.5*heightCockail, start_ang, space_ang);
    
    G4LogicalVolume* cocktailLogic = new G4LogicalVolume(cocktailSolid,cocktailType,"cocktail");
    
    G4OpticalSurface* cocktail_sur = new G4OpticalSurface("cocktail_sur", unified, polished, dielectric_dielectric);
    new G4LogicalSkinSurface("cocktail_lss",cocktailLogic,cocktail_sur);
    
    return cocktailLogic;
}

G4LogicalVolume *VialConstruction::ConstructVial(G4Material *materialVial)
{
    G4Tubs* mainSolid = new G4Tubs("mainSolid",0,radiusGlassVial, 0.5*totalHeightGlassVial,start_ang,360*degree);
    G4Tubs* subTopRing = new G4Tubs("subTopRing", openRadiusGlassVial+thciknessGlassVial,radiusGlassVial+thciknessGlassVial,0.5*topHeightGlassVial,start_ang,space_ang);
    G4SubtractionSolid* mainSolid2 = new G4SubtractionSolid("mainSolid2",mainSolid,subTopRing,nullptr,G4ThreeVector(0,0,0.5*(totalHeightGlassVial-topHeightGlassVial)));
    
    G4Tubs* subTopOpen = new G4Tubs("subTopOpen", 0, openRadiusGlassVial, 0.5*totalHeightGlassVial, start_ang, space_ang);
    G4SubtractionSolid* mainSolid3 = new G4SubtractionSolid("mainSolid3",mainSolid2,subTopOpen,nullptr,G4ThreeVector(0,0,0.5*(totalHeightGlassVial-topHeightGlassVial)));
    
    G4double hInner = totalHeightGlassVial - topHeightGlassVial -(2.0*thciknessGlassVial);
    G4Tubs* subInside = new G4Tubs("subInside", 0, radiusGlassVial-thciknessGlassVial, 0.5*hInner, start_ang, space_ang);
    G4SubtractionSolid* mainSolid4 = new G4SubtractionSolid("mainSolid4",mainSolid3,subInside,nullptr,G4ThreeVector(0,0,-0.5*(totalHeightGlassVial-hInner)+thciknessGlassVial));

    G4LogicalVolume* vialLogic = new G4LogicalVolume(mainSolid4,materialVial,"vial");
    
    // optical
    G4OpticalSurface* vial_sur = new G4OpticalSurface("vial_sur", LUT, polishedteflonair, dielectric_LUT);
    new G4LogicalSkinSurface("vial_skin",vialLogic,vial_sur);

    return vialLogic;
}

G4LogicalVolume *VialConstruction::ConstructCup()
{
    G4Tubs* mainSolid = new G4Tubs("mainSolid",0,radiusGlassVial+2.5, 0.5*heightCup,start_ang,360*degree);
    G4Tubs* subInside = new G4Tubs("subInside",0,openRadiusGlassVial+thciknessGlassVial, 0.5*heightCup,start_ang,space_ang);
    G4SubtractionSolid* mainSolid2 = new G4SubtractionSolid("mainSolid2",mainSolid,subInside,nullptr,G4ThreeVector(0,0,-topThicknessCap));
    
    G4LogicalVolume* cupLogic = new G4LogicalVolume(mainSolid2,Material::GetMaterial(MATERIALS::PE),"cup");
    
    G4OpticalSurface* cap_sur = new G4OpticalSurface("cap_sur", unified, groundfrontpainted, dielectric_dielectric);
    new G4LogicalSkinSurface("cap_skin",cupLogic,cap_sur);

    return cupLogic;
}

G4double VialConstruction::GetPosYVial() const
{
    return 0.5*(totalHeightGlassVial-heightCockail)-thciknessGlassVial;
}

G4double VialConstruction::GetPosYCup() const
{
    return totalHeightGlassVial - (0.5*heightCockail + thciknessGlassVial)-0.5*heightCup+topThicknessCap;
}
