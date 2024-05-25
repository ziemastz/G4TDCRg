#ifndef OPTICALCHAMBER_H
#define OPTICALCHAMBER_H 1

#pragma once
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "Material.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

class OpticalChamber
{
public:
    OpticalChamber(OpticalChamber& other) = delete;
    void operator=(const OpticalChamber&) = delete;

    static OpticalChamber* Instance();
    
    void SetMaterial(const MATERIALS& newMaterial);
    void SetRadiusPipe(const G4double& newRadius);
    void SetLenghtPipe(const G4double& newLenght);

    G4LogicalVolume* Construct();

    G4double GetHeighOpticalChamber() const {return heighOChamber;}
private:
    OpticalChamber();
    static OpticalChamber* _instance;
    G4LogicalVolume* chamber;
    
    MATERIALS type;
    // Optical Chamber
    // Option of visualization
    G4double start_ang;
    G4double space_ang;
    // pipe
    G4double radiusPipe;
    G4double lenghtPipe;
    // main
    G4double radiusOChamber;
    G4double insertRadiusOChamber;
    G4double heighOChamber;
    // bootom ring
    G4double radiusBottomRingOChamber;
    G4double heighBottomRingOChamber;
    // coin
    G4double radiusMinCoinOChamber;
    G4double radiusMaxCoinOChamber;
    G4double heighCoinOChamber;
    // 1st small cylinder;
    G4double insertRadiusSCOChamber1;
    G4double heighSCOChamber1;
    // 2nd small cylinder
    G4double insertRadiusSCOChamber2;
    G4double heighSCOChamber2;
    // top ring
    G4double radiusTopRingOChamber;
    G4double insertRadiusTopRingOChamber;
    G4double heighTopRingOChamber;
    // bottom window Al
    G4double radiusWindowAlOChamber;
    G4double heighWindowAlOChamber;
    //************************************//
};
#endif