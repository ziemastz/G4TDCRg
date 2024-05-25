#ifndef GAMMADETECTOR_H
#define GAMMADETECTOR_H 1

#pragma once
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "Material.hh"
class GammaDetector
{
public:
    GammaDetector(GammaDetector& other) = delete;
    void operator=(const GammaDetector& other) = delete;

    void SetCrystal(const MATERIALS& newCrystal);
    
    static GammaDetector* Instance();
    
    G4LogicalVolume* Construct();
    G4String GetLogicNameDetector() {return nameDetector;}
    G4String GetLogicNameDetectorShield() {return nameDetectorShield;}
    G4String GetLogicNameCrystalPipe() {return nameCrystalPipe;}
    G4String GetLogicNameCrystal() {return nameCrystal;}

    G4double GetHeightShield() const {return heighPbCylinder;}
    G4LogicalVolume* GetCrystal() const {return crystal;}
private:
    GammaDetector();
    static GammaDetector* _instance;
    MATERIALS type;

    G4LogicalVolume* detector;
    G4LogicalVolume* detectorShield;
    G4LogicalVolume* crystalPipe;
    G4LogicalVolume* crystal;
    
    G4String nameDetector;
    G4String nameDetectorShield;
    G4String nameCrystalPipe;
    G4String nameCrystal;
    
    // Gamma Detector
    // Option of visualization
    G4double start_ang;
    G4double space_ang;
    G4bool checkOverlaps;
    // Lead cylinder
    G4double radiusPbCylinder;
    G4double insertRadiusPbCylinder;
    G4double heighPbCylinder;
    // pipe of NaI detector
    G4double radiusNaIDetector;
    G4double insertRadiusNaIDetector;
    G4double heighNaIDetector;
    // NaI crystal
    G4double radiusNaICrystal;
    G4double heighNaICrystal;
};

#endif