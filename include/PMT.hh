#ifndef PMT_H
#define PMT_H 1

#pragma once
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4Sphere.hh"
#include "G4IntersectionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "Material.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4PVPlacement.hh"

class PMT
{
public:
    PMT(PMT& other) = delete;

    void operator=(const PMT& other) = delete;
    void SetWindowPMTMaterial(const MATERIALS& newGlass);
    void SetPhotocathodeMaterial(const MATERIALS& newPhotocathode);
    void SetPipePMTMaterial(const MATERIALS& newMaterial);
    
    static PMT* Instance();

    G4LogicalVolume* Construct();
    G4double GetLenghtPipe() const {return lenghtPipe;}
private:
    PMT();
    static PMT* _instance;

    MATERIALS windowGlass;
    MATERIALS photocathode;
    MATERIALS pipeMaterial;

    G4LogicalVolume* logicPMT;
    G4LogicalVolume* logicPipe;
    G4LogicalVolume* logicTeflonRing;
    G4LogicalVolume* logicGlassTube;
    G4LogicalVolume* logicVacuumTube;
    G4LogicalVolume* logicPhotocathode;
    G4LogicalVolume* logicActivePhotocathode;

    G4bool checkOverlaps;
    // Option of visualization
    G4double start_ang;
    G4double space_ang;
    // PMT:
    // pipe 
    G4double radiusPipe;
    G4double insideRadiusPipe;
    G4double lenghtPipe;
    G4double windowRadiusPipe;
    G4double windowLenghtPipe;
    // teflon ring
    G4double radiusTRing;
    G4double insideRadiusTRing;
    G4double lenghtTRing;
    G4double windowRadiusTRing;
    G4double windowLenghtTRing;
    // glass tube
    G4double radiusGTube;
    G4double thciknessGTube;
    G4double insideRadiusGTube;
    G4double lenghtGTube;
    // photocathode
    G4double heighSphereOfPhotocathode;
    G4double radiusPhotocathode;
    G4double activePhotocathode;
    G4double thicknessPhotocathode;
    G4double distancePhotocathode;
};

#endif