#include "Material.hh"

G4Material *Material::GetMaterial(const MATERIALS &type)
{
    G4Material* ret = nullptr;
    switch(type) {
    case MATERIALS::Air: {
        ret = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
        break;
    }
    case MATERIALS::Aluminium: {
        ret = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
        break;
    }
    case MATERIALS::Lead:
    {
       ret = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
        break;
    }
    case MATERIALS::Teflon:
    {
        ret = G4NistManager::Instance()->FindOrBuildMaterial("G4_TEFLON");
        break;
    }
    case MATERIALS::Vacuum:
    {
        ret = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
        break;
    }
    case MATERIALS::NaI_Tl:
    {
        ret = G4Material::GetMaterial("NaI_Tl",false);
        if(ret != 0)
            break; 
        ret = new G4Material("NaI_Tl", 3.667*g/cm3,3, kStateSolid);
        G4Element* Na = G4NistManager::Instance()->FindOrBuildElement("Na");
        G4Element* I = G4NistManager::Instance()->FindOrBuildElement("I");
        G4Element* Tl = G4NistManager::Instance()->FindOrBuildElement("Tl");
        ret->AddElement(Na,15.153*perCent);
        ret->AddElement(I,84.547*perCent);
        ret->AddElement(Tl,0.3*perCent);
        break;
    }
    case MATERIALS::HPGe:
    {
        ret = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ge");
        break;
    }
    case MATERIALS::BoroSilicate: {
        ret = G4Material::GetMaterial("BoroSilicate",false);
        if(ret != 0)
            break;        
        ret = new G4Material("BoroSilicate", 2.23*g/cm3, 4, kStateSolid);
        G4Element* Si = G4NistManager::Instance()->FindOrBuildElement("Si");
        G4Element* B = G4NistManager::Instance()->FindOrBuildElement("B");
        G4Element* Na = G4NistManager::Instance()->FindOrBuildElement("Na");
        G4Element* O = G4NistManager::Instance()->FindOrBuildElement("O");
        ret->AddElement(Si,80*1);
        ret->AddElement(B,12*2);
        ret->AddElement(Na,5*2);
        ret->AddElement(O,80*2+12*3+5*1);
        break;
    }
    case MATERIALS::SiO2: //kwarc
    {
        ret = G4Material::GetMaterial("FusedSilica",false);
        if(ret != 0)
            break; 
        G4Element* Si = G4NistManager::Instance()->FindOrBuildElement("Si");
        G4Element* O = G4NistManager::Instance()->FindOrBuildElement("O");
        ret = new G4Material("FusedSilica", 2.2*g/cm3, 2, kStateSolid);
        ret->AddElement(Si,1);
        ret->AddElement(O,2);
        break;
    }
    case MATERIALS::PE:
    {
        ret = G4Material::GetMaterial("PE",false);
        if(ret != 0)
            break;
        ret = new G4Material("PE", 0.94*g/cm3,2, kStateSolid);
        G4Element* C = G4NistManager::Instance()->FindOrBuildElement("C");
        G4Element* H = G4NistManager::Instance()->FindOrBuildElement("H");
        ret->AddElement(C,0.856289);
        ret->AddElement(H,0.143711);
        break;
    }
    case MATERIALS::UltimaGold:
    {
        ret = G4Material::GetMaterial("UltimaGold",false);
        if(ret != 0)
            break; 
        ret = new G4Material("UltimaGold", 0.98*g/cm3,7, kStateLiquid);
        G4Element* C = G4NistManager::Instance()->FindOrBuildElement("C");
        G4Element* H = G4NistManager::Instance()->FindOrBuildElement("H");
        G4Element* N = G4NistManager::Instance()->FindOrBuildElement("N");
        G4Element* O = G4NistManager::Instance()->FindOrBuildElement("O");
        G4Element* P = G4NistManager::Instance()->FindOrBuildElement("P");
        G4Element* S = G4NistManager::Instance()->FindOrBuildElement("S");
        G4Element* Na = G4NistManager::Instance()->FindOrBuildElement("Na");
        ret->AddElement(C,78.9*perCent);
        ret->AddElement(H,9.6*perCent);
        ret->AddElement(N,0.2*perCent);
        ret->AddElement(O,9.5*perCent);
        ret->AddElement(P,1.4*perCent);
        ret->AddElement(S,0.2*perCent);
        ret->AddElement(Na,0.2*perCent);
        ret->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
        break;
    }
    case MATERIALS::Water:
    {
        ret = G4Material::GetMaterial("Water",false);
        if(ret != 0)
            break; 
        ret = new G4Material("Water", 1.00*g/cm3,2, kStateLiquid);
        G4Element* H = G4NistManager::Instance()->FindOrBuildElement("H");
        G4Element* O = G4NistManager::Instance()->FindOrBuildElement("O");
        ret->AddElement(H,2);
        ret->AddElement(O,1);
        break;
    }
    case MATERIALS::BialkaliHarmer:
    {
        ret = G4Material::GetMaterial("BialkaliHarmer",false);
        if(ret != 0)
            break; 
        ret = new G4Material("BialkaliHarmer", 1., 1.*g/mole, 1.e-20*g/cm3, kStateGas, 0.1*kelvin, 1.e-20*bar);
        break;
    }
    case MATERIALS::BialkaliMotta:
    {
        ret = G4Material::GetMaterial("BialkaliMotta",false);
        if(ret != 0)
            break; 
        ret = new G4Material("BialkaliMotta", 1., 1.*g/mole, 1.e-20*g/cm3, kStateGas, 0.1*kelvin, 1.e-20*bar);
        break;
    }
    case MATERIALS::TiO2:
    {
        ret = G4Material::GetMaterial("TiO2",false);
        if(ret != 0)
            break; 
        ret = new G4Material("TiO2", 4.23*g/cm3,2, kStateSolid);
        G4Element* Ti = G4NistManager::Instance()->FindOrBuildElement("H");
        G4Element* O = G4NistManager::Instance()->FindOrBuildElement("O");
        ret->AddElement(Ti,1);
        ret->AddElement(O,2);
        break;
    }
    }
    return ret;
}

G4MaterialPropertiesTable *Material::GetMaterialPropertiesTable(const MATERIALS &type)
{
    G4MaterialPropertiesTable* ret = new G4MaterialPropertiesTable();

    switch (type)
    {
    case MATERIALS::Air:
    {
        std::vector<G4double> pp = { 10.0*eV, 0.1*eV};
        std::vector<G4double> rindex = { 1.0, 1.0};
        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
        //ret->AddProperty("RINDEX","Air");
        break;
    }
    case MATERIALS::Aluminium:
    {
        break;
    }
    case MATERIALS::Lead:
    {
        break;
    }
    case MATERIALS::Vacuum:
    {
        break;
    }
    case MATERIALS::UltimaGold:
    {
        //Ref.:: K. Kossert / Applied Radiation and Isotopes 82 (2013) 382–388
        std::vector<G4double> pp = {3.0635*eV ,2.8449*eV ,2.5505*eV ,2.2703*eV ,2.1099*eV ,2.1039*eV ,1.9592*eV ,1.8891*eV ,1.7548*eV};
        std::vector<G4double> rindex = {1.5776, 1.5666, 1.5547, 1.5456, 1.5412, 1.541, 1.5375, 1.5358, 1.5329};

        std::vector<G4double> pe = {1.7548*eV, 3.0635*eV};
        std::vector<G4double> scintilFast = { 1.00, 1.00};
        std::vector<G4double> scintilSlow = { 1.00, 1.00};
 
 //G4double Ulg_ABSLEN[2] = { 50.0*m, 50.0*m};
 //Ulg_mpt->AddProperty("ABSLENGTH",Ulg_Energy,Ulg_ABSLEN,2);
 
        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
        //ret->AddProperty("FASTCOMPONENT",pe,scintilFast);
        //ret->AddProperty("SLOWCOMPONENT",pe,scintilSlow);
        ret->AddProperty("SCINTILLATIONCOMPONENT1",GetMPV(pe,scintilFast));
        ret->AddProperty("SCINTILLATIONCOMPONENT2",GetMPV(pe,scintilSlow));
        //ret->AddProperty("SCINTILLATIONCOMPONENT3",pe,scintilSlow);
        ret->AddConstProperty("SCINTILLATIONYIELD",8.2/keV);
        ret->AddConstProperty("SCINTILLATIONYIELD1",1.0);
        ret->AddConstProperty("SCINTILLATIONYIELD2",0.0);
        //ret->AddConstProperty("SCINTILLATIONYIELD3",0.1);
        //ret->AddConstProperty("ALPHASCINTILLATIONYIELD1",1.);
        //ret->AddConstProperty("ALPHASCINTILLATIONYIELD2",0.);
        ret->AddConstProperty("RESOLUTIONSCALE",1.0);
        //ret->AddConstProperty("FASTTIMECONSTANT",10.*ns);
        //ret->AddConstProperty("SLOWTIMECONSTANT",20.*ns);
        ret->AddConstProperty("SCINTILLATIONTIMECONSTANT1",10);
        ret->AddConstProperty("SCINTILLATIONTIMECONSTANT2",20);
       // ret->AddConstProperty("SCINTILLATIONTIMECONSTANT3",200);
        //ret->AddConstProperty("SCINTILLATIONRISETIME1",3);
        //ret->AddConstProperty("SCINTILLATIONRISETIME2",10);
        //ret->AddConstProperty("SCINTILLATIONRISETIME3",20);
        //
        //ret->AddConstProperty("YIELDRATIO",1.0);
        break;
    }
    case MATERIALS::Water:
    {
        //-------------------------- Kossert ---------------------------------------------
        std::vector<G4double> energy = { 7.086*eV, 6.200*eV, 5.511*eV, 4.960*eV, 4.509*eV,
                             4.133*eV, 3.815*eV, 3.543*eV, 3.307*eV, 3.100*eV,
                            2.918*eV, 2.756*eV, 2.611*eV, 2.480*eV, 2.362*eV,
                             2.255*eV, 2.157*eV, 2.067*eV, 1.984*eV, 1.908*eV,
                             1.837*eV, 1.771*eV};

        std::vector<G4double> rindex = { 1.424, 1.401, 1.385, 1.373, 1.365, 1.358,
                             1.353, 1.349, 1.346, 1.343, 1.341, 1.339,
                              1.338, 1.336, 1.335, 1.334, 1.333, 1.333,
                              1.332, 1.331, 1.331, 1.330};
        // Ref:R. M. Pope and E. S. Fry, "Absorption spectrum (380­700nm) of pure
        //      water. II. Integrating cavity measurements," Appl. Opt., 36, 8710--8723,
        //      (1997).
        std::vector<G4double> pe = { 3.263*eV, 3.241*eV, 3.220*eV, 3.199*eV, 3.179*eV, 3.159*eV, 3.139*eV,
        3.119*eV, 3.100*eV, 3.080*eV, 3.061*eV, 3.042*eV, 3.024*eV, 3.006*eV, 2.987*eV, 2.970*eV, 2.952*eV,
        2.934*eV, 2.917*eV, 2.900*eV, 2.883*eV, 2.867*eV, 2.850*eV, 2.834*eV, 2.818*eV, 2.802*eV, 2.786*eV,
        2.771*eV, 2.755*eV, 2.740*eV, 2.725*eV, 2.710*eV, 2.695*eV, 2.681*eV, 2.666*eV, 2.652*eV, 2.638*eV,
        2.624*eV, 2.610*eV, 2.596*eV, 2.583*eV, 2.570*eV, 2.556*eV, 2.543*eV, 2.530*eV, 2.517*eV, 2.505*eV,
        2.492*eV, 2.480*eV, 2.467*eV, 2.455*eV, 2.443*eV, 2.431*eV, 2.419*eV, 2.407*eV, 2.396*eV, 2.384*eV,
        2.373*eV, 2.362*eV, 2.350*eV, 2.339*eV, 2.328*eV, 2.317*eV, 2.307*eV, 2.296*eV, 2.285*eV, 2.275*eV,
        2.264*eV, 2.254*eV, 2.244*eV, 2.234*eV, 2.224*eV, 2.214*eV, 2.204*eV, 2.194*eV, 2.185*eV, 2.175*eV,
        2.166*eV, 2.156*eV, 2.147*eV, 2.138*eV, 2.128*eV, 2.119*eV, 2.110*eV, 2.101*eV, 2.092*eV, 2.084*eV,
        2.075*eV, 2.066*eV, 2.058*eV, 2.049*eV, 2.041*eV, 2.032*eV, 2.024*eV, 2.016*eV, 2.008*eV, 2.000*eV,
        1.992*eV, 1.984*eV, 1.976*eV, 1.968*eV, 1.960*eV, 1.952*eV, 1.945*eV, 1.937*eV, 1.930*eV, 1.922*eV,
        1.915*eV, 1.907*eV, 1.900*eV, 1.893*eV, 1.886*eV, 1.878*eV, 1.871*eV, 1.864*eV, 1.857*eV, 1.850*eV,
        1.844*eV, 1.837*eV, 1.830*eV, 1.823*eV, 1.817*eV, 1.810*eV, 1.803*eV, 1.797*eV, 1.790*eV, 1.784*eV,
        1.777*eV, 1.771*eV, 1.765*eV, 1.759*eV, 1.752*eV, 1.746*eV, 1.740*eV, 1.734*eV, 1.728*eV, 1.722*eV,
        1.716*eV, 1.710*eV, 1.704*eV};
        std::vector<G4double> absLength = {8795.07*cm, 9578.54*cm, 10626.99*cm, 10905.13*cm, 11750.88*cm,
        12062.73*cm, 12300.12*cm, 12903.23*cm, 15082.96*cm, 17271.16*cm, 18867.92*cm, 19880.72*cm, 21141.65*cm,
        22123.89*cm, 22522.52*cm, 22624.43*cm, 22026.43*cm, 21097.05*cm, 20920.50*cm, 20746.89*cm, 20202.02*cm,
        19841.27*cm, 18867.92*cm, 17241.38*cm, 15748.03*cm, 14367.82*cm, 13315.58*cm, 12048.19*cm, 10845.99*cm,
        10319.92*cm, 10395.01*cm, 10449.32*cm, 10214.50*cm, 9950.25*cm, 9891.20*cm, 9803.92*cm, 9433.96*cm,
        9174.31*cm, 8771.93*cm, 8264.46*cm, 7874.02*cm, 7633.59*cm, 7352.94*cm, 6944.44*cm, 6666.67*cm,
        6172.84*cm, 5780.35*cm, 5235.60*cm, 4901.96*cm, 4385.96*cm, 3906.25*cm, 3571.43*cm, 3076.92*cm,
        2688.17*cm, 2525.25*cm, 2506.27*cm, 2444.99*cm, 2403.85*cm, 2398.08*cm, 2336.45*cm, 2304.15*cm,
        2237.14*cm, 2212.39*cm, 2145.92*cm, 2109.70*cm, 2044.99*cm, 1956.95*cm, 1862.20*cm, 1769.91*cm,
        1686.34*cm, 1677.85*cm, 1650.17*cm, 1615.51*cm, 1562.50*cm, 1557.63*cm, 1488.10*cm, 1438.85*cm,
        1364.26*cm, 1295.34*cm, 1196.17*cm, 1116.07*cm, 1011.12*cm, 909.09*cm, 819.67*cm, 740.19*cm, 659.63*cm,
        598.09*cm, 519.48*cm, 449.64*cm, 404.86*cm, 388.05*cm, 380.37*cm, 378.21*cm, 375.23*cm, 373.41*cm,
        369.41*cm, 362.98*cm, 355.87*cm, 352.86*cm, 344.35*cm, 342.94*cm, 333.89*cm, 332.01*cm, 324.99*cm,
        321.75*cm, 310.56*cm, 307.69*cm, 298.51*cm, 294.12*cm, 279.33*cm, 269.54*cm, 254.45*cm, 243.90*cm,
        235.85*cm, 233.10*cm, 229.36*cm, 227.79*cm, 223.21*cm, 223.21*cm, 216.92*cm, 215.05*cm, 209.21*cm,
        205.76*cm, 199.20*cm, 193.80*cm, 185.87*cm, 178.89*cm, 168.92*cm, 160.26*cm, 150.83*cm, 142.05*cm,
        132.28*cm, 120.92*cm, 109.41*cm, 99.30*cm, 89.37*cm, 81.23*cm, 73.75*cm, 67.16*cm, 59.59*cm};

        ret->AddProperty("RINDEX", GetMPV(energy,rindex));
        ret->AddProperty("ABSLENGTH", GetMPV(pe,absLength));
       // G4cout << "Properties of wate: "<< G4endl;
        //ret->DumpTable();
        break;
    }
    case MATERIALS::TiO2:
    {
        std::vector<G4double> pe = {0.1*eV,10.*eV};
        std::vector<G4double> reflectivity = {0.99, 0.99}; // Ref from LUT Janacek IEEE TRANSACTIONS ON NUCLEAR SCIENCE, VOL. 57, NO. 3, JUNE 2010
        std::vector<G4double> efficiency = {0, 0};
        ret->AddProperty("REFLECTIVITY", GetMPV(pe, reflectivity));
        ret->AddProperty("EFFICIENCY", GetMPV(pe, efficiency)); 
        break;
    }
    case MATERIALS::Teflon:
    {
        std::vector<G4double> pp = { 10.0*eV, 0.1*eV};
        std::vector<G4double> rindex = { 1.38, 1.38};
        std::vector<G4double> reflectivity = {0.95, 0.95};
        std::vector<G4double> efficiency = {0, 0};
        ret->AddProperty("REFLECTIVITY", GetMPV(pp, reflectivity));
        ret->AddProperty("EFFICIENCY", GetMPV(pp, efficiency));
        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
        break;
    }
    case MATERIALS::BoroSilicate:
    {
    //Ref.:026003-2 Surface Science Spectra. Vol. 24. 2017 Optical properties of borosilicate glass
        std::vector<G4double> pp = { 1.170*eV, 2.271*eV, 3.397*eV ,3.968*eV};
        std::vector<G4double> rindex = { 1.5067,1.5187,1.5363 , 1.5486};
        //std::vector<G4double> pp = {1.6475*eV, 1.7871*eV, 1.9239*eV, 2.0835*eV, 2.2721*eV, 2.4984*eV, 2.7749*eV, 3.1204*eV, 3.5643*eV, 4.1554*eV, 4.9813*eV};
        //std::vector<G4double> rindex = {1.46357055, 1.46481952, 1.46607075, 1.46758817, 1.46948662, 1.47194705, 1.47526924, 1.47998228, 1.48710164, 1.49881664, 1.52075098};
        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
  
    // New data C Bobin KB7 Crystan Absleng
        /*std::vector<G4double> pe = {5.6364*eV, 5.1667*eV, 4.9600*eV, 4.8627*eV, 4.7692*eV, 4.6792*eV,
				4.5926*eV, 4.5091*eV, 4.4286*eV, 4.2759*eV, 4.1333*eV, 4.0000*eV,
				3.8750*eV, 3.7576*eV, 3.6471*eV, 3.5429*eV, 3.4444*eV, 3.3514*eV, 
				3.2632*eV, 3.1795*eV, 3.1000*eV, 2.9524*eV, 2.8182*eV, 2.6957*eV,
				2.5833*eV, 2.4800*eV, 2.2545*eV, 2.0667*eV, 1.9077*eV, 1.7714*eV,
				1.5500*eV};
        std::vector<G4double> abslength = {0.0100*cm, 0.0200*cm, 0.0476*cm, 0.0544*cm, 0.0642*cm, 0.0787*cm,
				0.1000*cm, 0.1300*cm, 0.1772*cm, 0.3397*cm, 0.7164*cm, 1.5002*cm,
				3.2894*cm, 7.3496*cm, 14.7191*cm, 29.7889*cm, 57.4150*cm, 98.6740*cm,
				115.1776*cm, 230.7023*cm, 346.2269*cm, 346.2269*cm, 346.2269*cm, 346.2269*cm,
				346.2269*cm, 346.2269*cm, 692.8005*cm, 692.8005*cm, 692.8005*cm, 692.8005*cm, 692.8005*cm};*/
        std::vector<G4double> pe = { 7.294*eV, 6.889*eV, 6.200*eV, 5.636*eV, 5.166*eV,
                                 4.769*eV, 4.428*eV, 4.133*eV, 3.875*eV, 3.647*eV,
                                 3.444*eV, 3.263*eV, 3.100*eV, 2.952*eV, 2.818*eV,
                                 2.695*eV, 2.583*eV, 2.480*eV, 2.384*eV, 2.296*eV,
                                 2.214*eV, 2.138*eV, 2.066*eV, 1.907*eV, 1.771*eV,
                                 1.653*eV, 1.550*eV, 1.458*eV};
        std::vector<G4double> abslength = { 0.01*cm, 0.02*cm, 0.026*cm, 0.03*cm, 0.05*cm, 0.0723*cm,
                                 0.2006*cm, 0.7537*cm, 2.521*cm, 5.6376*cm, 9.0736*cm,
                                 12.1729*cm, 19.6502*cm, 29.840*cm, 65.10*cm, 2440*cm, 2440*cm,
                                 2440*cm, 2440*cm, 2440*cm, 2440*cm, 2440*cm, 2440*cm,
                                 2440*cm, 2440*cm, 2440*cm, 2440*cm, 2440*cm};
        ret->AddProperty("ABSLENGTH",GetMPV(pe,abslength));
        break;
    }
    case MATERIALS::SiO2:
    {
        
        std::vector<G4double> pp = {7.7500*eV, 7.2941*eV, 6.8889*eV, 6.5263*eV, 6.2000*eV,
			    5.9048*eV, 5.6364*eV, 5.3913*eV, 5.1667*eV, 4.9600*eV,
			    4.7692*eV, 4.5926*eV, 4.4286*eV, 4.2759*eV, 4.1333*eV, 
			    4.0000*eV, 3.8750*eV, 3.7576*eV, 3.6471*eV, 3.5429*eV,
			    3.4444*eV, 3.3514*eV, 3.2632*eV, 3.1795*eV, 3.1000*eV,
			    3.0244*eV, 2.9524*eV, 2.8837*eV, 2.8182*eV, 2.7556*eV, 
			    2.6957*eV, 2.6383*eV, 2.5833*eV, 2.5306*eV, 2.4800*eV,
			    2.4314*eV, 2.3846*eV, 2.3396*eV, 2.2963*eV, 2.2545*eV,
			    2.2143*eV, 2.1754*eV, 2.1379*eV, 2.1017*eV, 2.0667*eV,
			    2.0328*eV, 2.0000*eV, 1.9683*eV, 1.9375*eV, 1.9077*eV,
			    1.8788*eV, 1.8507*eV, 1.8235*eV, 1.7971*eV, 1.7714*eV,
			    1.7465*eV, 1.7222*eV, 1.6986*eV, 1.6757*eV, 1.6533*eV,
			    1.6316*eV, 1.6104*eV, 1.5897*eV, 1.5696*eV, 1.5500*eV,
			    1.5309*eV, 1.5122*eV, 1.4940*eV, 1.4762*eV, 1.4588*eV,
			    1.4419*eV, 1.4253*eV, 1.4091*eV, 1.3933*eV, 1.3778*eV,
			    1.3626*eV, 1.3478*eV, 1.3333*eV, 1.3191*eV, 1.3053*eV};

        std::vector<G4double> rindex = {1.6479, 1.6114, 1.5853, 1.5657, 1.5505, 1.5384, 1.5285,
                            1.5202, 1.5133, 1.5074, 1.5024, 1.4980, 1.4942, 1.4908,
                            1.4878, 1.4851, 1.4827, 1.4806, 1.4787, 1.4769, 1.4753,
                            1.4738, 1.4725, 1.4713, 1.4701, 1.4691, 1.4681, 1.4672,
                            1.4663, 1.4656, 1.4648, 1.4641, 1.4635, 1.4629, 1.4623,
                            1.4618, 1.4613, 1.4608, 1.4603, 1.4599, 1.4595, 1.4591,
                            1.4587, 1.4584, 1.4580, 1.4577, 1.4574, 1.4571, 1.4568,
                            1.4565, 1.4563, 1.4560, 1.4558, 1.4555, 1.4553, 1.4551,
                            1.4549, 1.4546, 1.4544, 1.4542, 1.4540, 1.4539, 1.4537,
                            1.4535, 1.4533, 1.4531, 1.4530, 1.4528, 1.4527, 1.4525,
                            1.4523, 1.4522, 1.4520, 1.4519, 1.4518, 1.4516, 1.4515,
                            1.4513, 1.4512, 1.4511};
        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
        //ret->AddProperty("RINDEX", "Fused Silica");
        break;
    }
    case MATERIALS::PE:
    {
        std::vector<G4double> pp = { 3.263*eV,3.061*eV,2.883*eV,2.725*eV,2.583*eV,2.455*eV,2.339*eV,2.234*eV,2.138*eV,2.049*eV,1.968*eV,1.893*eV,1.823*eV,1.759*eV,1.698*eV,1.642*eV,1.589*eV,1.540*eV};
        std::vector<G4double> rindex = {1.5159,1.5137,1.5116,1.5096,1.5078,1.5061,1.5046,1.5033,1.502,1.5009,1.4999,1.4989,1.4981,1.4973,1.4966,1.496,1.4954,1.4948};
        // ref: https://www.filmetrics.com/refractive-index-database/Polyethylene/PE-Polyethene

        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
        break;
    }
    case MATERIALS::BialkaliHarmer:
    {
    // Ref.: S W Harmer et al J. Phys. D: Appl. Phys. 45 (2012) 055102
        std::vector<G4double> pp = { 7.290*eV, 6.200*eV, 5.511*eV, 4.960*eV, 4.510*eV, 4.130*eV, 3.810*eV, 3.540*eV, 3.310*eV, 3.100*eV, 2.920*eV, 2.750*eV, 2.660*eV, 2.480*eV, 2.360*eV, 2.250*eV, 2.160*eV, 2.070*eV};
        std::vector<G4double> rindex = { 1.409, 1.409, 1.409, 1.409, 1.483, 1.582, 1.883, 2.052, 2.305, 2.422, 2.509, 2.776, 2.913, 2.976, 3.089, 2.948, 2.873, 2.777}; // From HARMER
        ret->AddProperty("RINDEX",GetMPV(pp,rindex));
        
        std::vector<G4double> pe = {0.1*eV,10.0*eV};
        std::vector<G4double> refl = { 0.9, 0.9};
        std::vector<G4double> eff = { .0, .0};
        ret->AddProperty("REFLECTIVITY",GetMPV(pe, refl));  
        ret->AddProperty("EFFICIENCY",  GetMPV(pe, eff));
        break;
    }
    case MATERIALS::BialkaliMotta:
    {
    // Ref.: D. Motta. S. Scho¨nert / Nuclear Instruments and Methods in Physics Research A 539 (2005) 217–235
        std::vector<G4double> pp = {1.8232*eV ,1.8644*eV ,1.9074*eV ,1.9524*eV ,1.999*eV ,2.0493*eV ,2.1014*eV ,2.1562*eV ,2.2139*eV ,2.2749*eV ,2.3392*eV ,2.4074*eV ,2.4796*eV ,2.5563*eV ,2.6379*eV ,2.7248*eV ,2.8177*eV ,2.9172*eV ,3.0239*eV ,3.1387*eV ,3.2626*eV};
        std::vector<G4double> realRIndex = {3.13, 3.14, 3.14, 3.15, 3.18, 3.22, 3.28, 3.39, 3.32, 3.23, 3.21, 3.22, 3.16, 2.99, 2.81, 2.63, 2.50, 2.40,2.30, 2.22, 2.07};
        std::vector<G4double> imaginaryRIndex = {0.35, 0.37, 0.37, 0.38, 0.40, 0.43, 0.46, 0.59, 0.76, 0.86, 0.90, 1.04, 1.21, 1.37, 1.41, 1.40, 1.35, 1.27, 1.21, 1.17, 1.22};
        ret->AddProperty("REALRINDEX",GetMPV(pp,realRIndex));
        ret->AddProperty("IMAGINARYRINDEX",GetMPV(pp,imaginaryRIndex));
        
        std::vector<G4double> pe = { 0.1*eV,10.0*eV};
        std::vector<G4double> refl = { 0.9, 0.9};
        std::vector<G4double> eff = { .0, .0};
        ret->AddProperty("REFLECTIVITY", GetMPV(pe, refl));  
        ret->AddProperty("EFFICIENCY",  GetMPV(pe, eff));
        break;
    }
    default:
        break;
    }
    return ret;
}

G4MaterialPropertyVector* Material::GetMPV(const std::vector<G4double>& energy, const std::vector<G4double>& value)
{
    G4MaterialPropertyVector* mpv = new G4MaterialPropertyVector();
    if(energy.size() != value.size()) {
        G4cout << " ******* ERROR ******** -> Wrong size table with material property Energy size: "<<energy.size()<<" Value size: "<<value.size()<<G4endl;
        return mpv;
    }
    for(int i=0; i<energy.size(); i++){
            mpv->InsertValues(energy.at(i),value.at(i));
    }
    return mpv;
}