#ifndef VIALCONSTRUCTION_HH
#define VIALCONSTRUCTION_HH

#pragma once
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVPlacement.hh"

#include "Material.hh"
class VialConstruction
{
public:
    VialConstruction();
    ~VialConstruction();
    void Construct(G4LogicalVolume* world);
    G4LogicalVolume* ConstructCocktail(const G4double& volumeCocktail,  G4Material* cocktailType);
    G4LogicalVolume* ConstructVial(G4Material* materialVial);
    G4LogicalVolume* ConstructCup();
    G4double GetPosYVial() const;
    G4double GetPosYCup() const;
private:
    G4double volume;
    G4Material* material;
    G4Material* cocktail;

    // Option of visualization
    G4double start_ang;
    G4double space_ang;  
    //
    // Vial, Cap & Cocktail
    // Vial 20mL
    G4double h;
    G4double H;
    G4double r;
    G4double R;
    G4double t;

    G4double radiusGlassVial;
    G4double openRadiusGlassVial;
    G4double thciknessGlassVial;
    G4double totalHeightGlassVial;
    G4double wallHeightViall;
    G4double topHeightGlassVial;
    // Cap of vial
    G4double radiusCap;
    G4double insertRadiusCap;
    G4double insertHeighCap;
    G4double topThicknessCap;
    G4double heightCup;
    G4double thicknessFoilAlCap;
    G4double optDistanceVial;
    // Cockaitl
    G4double heightCockail;
    G4double optPositionYCocktail;

};

#endif