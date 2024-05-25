#ifndef MATERIAL_HH
#define MATERIAL_HH

#pragma once
#include "globals.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"

enum MATERIALS {
    Air,
    Aluminium,
    Lead,
    Teflon,
    Vacuum,
    NaI_Tl,
    HPGe,
    UltimaGold,
    Water,
    BoroSilicate,
    SiO2,
    PE,
    BialkaliHarmer,
    BialkaliMotta,
    TiO2
};

class Material
{
public:

    static G4Material* GetMaterial(const MATERIALS& type);
    static G4MaterialPropertiesTable* GetMaterialPropertiesTable(const MATERIALS& type);

private:
    static G4MaterialPropertyVector* GetMPV(const std::vector<G4double>& energy, const std::vector<G4double>& value);
};

#endif