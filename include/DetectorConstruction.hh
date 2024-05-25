#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "VialConstruction.hh"
#include "DetectorMessenger.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    // setter
    void SetVolumeCocktail(const G4double& newVolume);
    void SetMaterialVial(const G4String &newMaterial);
    void SetCocktailType(const G4String &newCocktail);
    
private:
    DetectorMessenger* fDetectorMessenger;
    VialConstruction vial;
    G4bool checkOverlaps;
    // WORLD
    G4double world_size_Y;
    G4double world_size_X;
    G4double world_size_Z;

    // vial
    G4bool isVial;
    G4LogicalVolume *cocktail_lv;
    G4VPhysicalVolume* cocktail_pv;

    G4LogicalVolume *vial_lv;
    G4VPhysicalVolume* vial_pv;

    G4LogicalVolume *cup_lv;
    G4VPhysicalVolume* cup_pv;
    //G4LogicalVolume *cupAlFoil_lv;
    
    G4LogicalVolume* opticalChamber_lv;
    G4VPhysicalVolume* opticalChamber_pv;

    G4LogicalVolume* gammaDetector_lv;
    G4VPhysicalVolume* gammaDetector_pv;
    
    G4LogicalVolume* pmt_lv;
    G4VPhysicalVolume* pmt_pv;

    G4double volumeCocktail;
    G4Material *materialVial;
    G4Material *cocktailType;
};

#endif