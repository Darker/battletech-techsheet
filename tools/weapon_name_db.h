

#include <mtfparser/WeaponMetaInfo.h>

#include <array>
namespace mtfparser {
constexpr std::array Weapon_name_db
{
    // Medium Laser
    WeaponMetaInfo{"MLaser", 1, {"ISMediumLaser", "Medium Laser", "IS Medium Laser", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype Medium Laser
    WeaponMetaInfo{"P_PROTO MLaser", 1, {"IS Medium Laser Prototype", "ISMediumLaserPrototype", "Primitive Prototype Medium Laser", "", "", "", "", "", "", "", ""}},
    // Large Laser
    WeaponMetaInfo{"LLaser", 2, {"ISLargeLaser", "Large Laser", "IS Large Laser", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype Large Laser
    WeaponMetaInfo{"P_PROTO LLaser", 2, {"Primitive Prototype Large Laser", "ISLargeLaserPrototype", "IS Large Laser Prototype", "", "", "", "", "", "", "", ""}},
    // Small Laser
    WeaponMetaInfo{"SLaser", 1, {"ISSmallLaser", "CL Small Laser", "Small Laser", "CLSmallLaser", "ClSmall Laser", "ISSmall Laser", "", "", "", "", ""}},
    // Primitive Prototype Small Laser
    WeaponMetaInfo{"P_PROTO SLaser", 1, {"ISSmall Laser Primitive", "Primitive Prototype Small Laser", "ISSmallLaserPrimitive", "", "", "", "", "", "", "", ""}},
    // Large Pulse Laser
    WeaponMetaInfo{"LPLaser", 2, {"IS Pulse Large Laser", "ISLargePulseLaser", "IS Large Pulse Laser", "", "", "", "", "", "", "", ""}},
    // Prototype Large Pulse Laser
    WeaponMetaInfo{"PROTO LPLaser", 2, {"IS Pulse Large Laser Prototype", "IS Prototype Large Pulse Laser", "ISLargePulseLaserPrototype", "", "", "", "", "", "", "", ""}},
    // Large X-Pulse Laser
    WeaponMetaInfo{"LX-PLaser", 2, {"IS Large X-Pulse Laser", "IS X-Pulse Large Laser", "ISLargeXPulseLaser", "", "", "", "", "", "", "", ""}},
    // ER Large Laser
    WeaponMetaInfo{"ER LLaser", 2, {"IS ER Large Laser", "ISERLargeLaser", "", "", "", "", "", "", "", "", ""}},
    // Prototype ER Large Laser
    WeaponMetaInfo{"PROTO ER LLaser", 2, {"IS ER Large Laser Prototype", "ISERLargeLaserPrototype", "", "", "", "", "", "", "", "", ""}},
    // ER Medium Laser
    WeaponMetaInfo{"ER MLaser", 1, {"ISERMediumLaser", "IS ER Medium Laser", "", "", "", "", "", "", "", "", ""}},
    // Medium Pulse Laser
    WeaponMetaInfo{"MPLaser", 1, {"IS Pulse Med Laser", "IS Medium Pulse Laser", "ISMediumPulseLaser", "", "", "", "", "", "", "", ""}},
    // Prototype Medium Pulse Laser
    WeaponMetaInfo{"PROTO MPLaser", 1, {"ISMediumPulseLaserPrototype", "IS Pulse Med Laser Prototype", "IS Medium Pulse Laser Prototype", "", "", "", "", "", "", "", ""}},
    // Medium X-Pulse Laser
    WeaponMetaInfo{"MX-PLaser", 1, {"IS X-Pulse Med Laser", "ISMediumXPulseLaser", "IS Medium X-Pulse Laser", "", "", "", "", "", "", "", ""}},
    // Small Pulse Laser
    WeaponMetaInfo{"SPLaser", 1, {"ISSmallPulseLaser", "IS Small Pulse Laser", "ISSmall Pulse Laser", "", "", "", "", "", "", "", ""}},
    // Small X-Pulse Laser
    WeaponMetaInfo{"SX-PLaser", 1, {"ISSmallXPulseLaser", "IS X-Pulse Small Laser", "IS Small X-Pulse Laser", "", "", "", "", "", "", "", ""}},
    // Prototype Small Pulse Laser
    WeaponMetaInfo{"PROTO SPLaser", 1, {"ISSmall Pulse Laser Prototype", "IS Prototype Small Pulse Laser", "ISSmallPulseLaserPrototype", "", "", "", "", "", "", "", ""}},
    // ER Small Laser
    WeaponMetaInfo{"ER SLaser", 1, {"IS ER Small Laser", "ISERSmallLaser", "", "", "", "", "", "", "", "", ""}},
    // Medium VSP Laser
    WeaponMetaInfo{"VSP MLaser", 2, {"ISMediumVSPLaser", "ISMediumVariableSpeedLaser", "ISMediumVSP", "ISMVSPL", "", "", "", "", "", "", ""}},
    // Small VSP Laser
    WeaponMetaInfo{"VSP SLaser", 1, {"ISSmallVSPLaser", "ISSmallVSP", "ISSVSPL", "ISSmallVariableSpeedLaser", "", "", "", "", "", "", ""}},
    // Large VSP Laser
    WeaponMetaInfo{"VSP LLaser", 4, {"ISLVSPL", "ISLargeVSP", "ISLargeVSPLaser", "ISLargeVariableSpeedLaser", "", "", "", "", "", "", ""}},
    // Bombast Laser
    WeaponMetaInfo{"Bombast Laser", 3, {"IS Bombast Laser", "ISBombastLaser", "Bombast Laser", "", "", "", "", "", "", "", ""}},
    // ER Large Laser
    WeaponMetaInfo{"ER LLaser", 1, {"Clan ER Large Laser", "CLERLargeLaser", "", "", "", "", "", "", "", "", ""}},
    // Heavy Large Laser
    WeaponMetaInfo{"HV LLaser", 3, {"CLHeavyLargeLaser", "Clan Large Heavy Laser", "", "", "", "", "", "", "", "", ""}},
    // Large Pulse Laser
    WeaponMetaInfo{"LPLaser", 2, {"CLLargePulseLaser", "Clan Pulse Large Laser", "Clan Large Pulse Laser", "", "", "", "", "", "", "", ""}},
    // ER Large Pulse Laser
    WeaponMetaInfo{"ER LPLaser", 3, {"Clan ER Pulse Large Laser", "CLERLargePulseLaser", "Clan ER Large Pulse Laser", "", "", "", "", "", "", "", ""}},
    // ER Medium Laser
    WeaponMetaInfo{"ER MLaser", 1, {"CLERMediumLaser", "Clan ER Medium Laser", "", "", "", "", "", "", "", "", ""}},
    // Prototype ER Medium Laser
    WeaponMetaInfo{"PROTO ER MLaser", 1, {"CLERMediumLaserPrototype", "", "", "", "", "", "", "", "", "", ""}},
    // Heavy Medium Laser
    WeaponMetaInfo{"HV MLaser", 2, {"Clan Medium Heavy Laser", "CLHeavyMediumLaser", "", "", "", "", "", "", "", "", ""}},
    // Medium Pulse Laser
    WeaponMetaInfo{"MPLaser", 1, {"CLMediumPulseLaser", "Clan Pulse Med Laser", "Clan Medium Pulse Laser", "", "", "", "", "", "", "", ""}},
    // ER Medium Pulse Laser
    WeaponMetaInfo{"ER MPLaser", 2, {"CLERMediumPulseLaser", "Clan ER Medium Pulse Laser", "Clan ER Pulse Med Laser", "", "", "", "", "", "", "", ""}},
    // ER Small Laser
    WeaponMetaInfo{"ER SLaser", 1, {"Clan ER Small Laser", "CLERSmallLaser", "", "", "", "", "", "", "", "", ""}},
    // Prototype ER Small Laser
    WeaponMetaInfo{"PROTO ER SLaser", 1, {"CLERSmallLaserPrototype", "", "", "", "", "", "", "", "", "", ""}},
    // Small Pulse Laser
    WeaponMetaInfo{"SPLaser", 1, {"Clan Pulse Small Laser", "Clan Small Pulse Laser", "CLSmallPulseLaser", "", "", "", "", "", "", "", ""}},
    // ER Small Pulse Laser
    WeaponMetaInfo{"ER SPLaser", 1, {"CLERSmallPulseLaser", "Clan ER Small Pulse Laser", "ClanERSmallPulseLaser", "Clan ER Pulse Small Laser", "", "", "", "", "", "", ""}},
    // Heavy Small Laser
    WeaponMetaInfo{"HV SLaser", 1, {"Clan Small Heavy Laser", "CLHeavySmallLaser", "", "", "", "", "", "", "", "", ""}},
    // ER Micro Laser
    WeaponMetaInfo{"ER Micro Laser", 1, {"CLERMicroLaser", "Clan ER Micro Laser", "", "", "", "", "", "", "", "", ""}},
    // Micro Pulse Laser
    WeaponMetaInfo{"Micro PLaser", 1, {"Clan Micro Pulse Laser", "CLMicroPulseLaser", "", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Large Laser
    WeaponMetaInfo{"HV IMPR LLaser", 3, {"Clan Improved Large Heavy Laser", "CLImprovedHeavyLargeLaser", "", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Medium Laser
    WeaponMetaInfo{"HV IMPR MLaser", 2, {"Clan Improved Heavy Medium Laser", "CLImprovedMediumHeavyLaser", "CLImprovedHeavyMediumLaser", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Small Laser
    WeaponMetaInfo{"HV IMPR SLaser", 1, {"CLImprovedHeavySmallLaser", "Clan Improved Small Heavy Laser", "CLImprovedSmallHeavyLaser", "", "", "", "", "", "", "", ""}},
    // Large Chemical Laser
    WeaponMetaInfo{"CHEM LLaser", 2, {"CLLargeChemicalLaser", "Large Chem Laser", "CLLargeChemLaser", "", "", "", "", "", "", "", ""}},
    // Medium Chemical Laser
    WeaponMetaInfo{"CHEM MLaser", 1, {"Medium Chem Laser", "CLMediumChemicalLaser", "CLMediumChemLaser", "", "", "", "", "", "", "", ""}},
    // Small Chemical Laser
    WeaponMetaInfo{"CHEM SLaser", 1, {"CLSmallChemLaser", "CLSmallChemicalLaser", "Small Chem Laser", "", "", "", "", "", "", "", ""}},
    // PPC
    WeaponMetaInfo{"PPC", 3, {"IS PPC", "ISPPC", "PPC", "Particle Cannon", "", "", "", "", "", "", ""}},
    // Primitive Prototype PPC
    WeaponMetaInfo{"P_PROTO PPC", 3, {"ISPPCp", "Particle Cannon Primitive", "Primitive Prototype PPC", "IS PPCp", "", "", "", "", "", "", ""}},
    // ER PPC
    WeaponMetaInfo{"ER PPC", 3, {"ISERPPC", "IS ER PPC", "", "", "", "", "", "", "", "", ""}},
    // ER PPC
    WeaponMetaInfo{"ER PPC", 2, {"CLERPPC", "Clan ER PPC", "", "", "", "", "", "", "", "", ""}},
    // Snub-Nose PPC
    WeaponMetaInfo{"Snub-Nose PPC", 2, {"ISSnubNosedPPC", "ISSNPPC", "", "", "", "", "", "", "", "", ""}},
    // Light PPC
    WeaponMetaInfo{"Light PPC", 2, {"Light PPC", "ISLPPC", "ISLightPPC", "", "", "", "", "", "", "", ""}},
    // Heavy PPC
    WeaponMetaInfo{"HV PPC", 4, {"ISHPPC", "Heavy PPC", "ISHeavyPPC", "", "", "", "", "", "", "", ""}},
    // Flamer
    WeaponMetaInfo{"Flamer", 1, {"ISFlamer", "CLFlamer", "Flamer", "IS Flamer", "Clan Flamer", "", "", "", "", "", ""}},
    // Heavy Flamer
    WeaponMetaInfo{"HV Flamer", 1, {"Clan Heavy Flamer", "IS Heavy Flamer", "Heavy Flamer", "CLHeavyFlamer", "CL Heavy Flamer", "ISHeavyFlamer", "", "", "", "", ""}},
    // ER Flamer
    WeaponMetaInfo{"ER Flamer", 1, {"IS ER Flamer", "CL ER Flamer", "ER Flamer", "ISERFlamer", "CLERFlamer", "", "", "", "", "", ""}},
    // AC/2
    WeaponMetaInfo{"AC/2", 1, {"IS Auto Cannon/2", "AC/2", "IS Autocannon/2", "Autocannon/2", "Auto Cannon/2", "AutoCannon/2", "ISAC2", "", "", "", ""}},
    // AC/5
    WeaponMetaInfo{"AC/5", 4, {"Autocannon/5", "Auto Cannon/5", "ISAC5", "IS Autocannon/5", "AutoCannon/5", "IS Auto Cannon/5", "AC/5", "", "", "", ""}},
    // AC/10
    WeaponMetaInfo{"AC/10", 7, {"Autocannon/10", "IS Auto Cannon/10", "ISAC10", "AC/10", "Auto Cannon/10", "IS Autocannon/10", "AutoCannon/10", "", "", "", ""}},
    // AC/20
    WeaponMetaInfo{"AC/20", 10, {"AutoCannon/20", "IS Auto Cannon/20", "ISAC20", "IS Autocannon/20", "Auto Cannon/20", "Autocannon/20", "", "", "", "", ""}},
    // ProtoMech AC/2
    WeaponMetaInfo{"ProtoMech AC/2", 2, {"CLProtoMechAC2", "Clan ProtoMech AC/2", "", "", "", "", "", "", "", "", ""}},
    // ProtoMech AC/4
    WeaponMetaInfo{"ProtoMech AC/4", 3, {"Clan ProtoMech AC/4", "CLProtoMechAC4", "", "", "", "", "", "", "", "", ""}},
    // ProtoMech AC/8
    WeaponMetaInfo{"ProtoMech AC/8", 4, {"Clan ProtoMech AC/8", "CLProtoMechAC8", "", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype Autocannon/2
    WeaponMetaInfo{"P_PROTO AC/2", 1, {"AutoCannon/2 Primitive", "IS Auto Cannon/2 Primitive", "Auto Cannon/2 Primitive", "Autocannon/2p", "ISAC2p", "IS Autocannon/2 Primitive", "AC/2p", "", "", "", ""}},
    // Primitive Prototype Autocannon/5
    WeaponMetaInfo{"P_PROTO AC/5", 4, {"IS Auto Cannon/5 Primitive", "Auto Cannon/5 Primitive", "AutoCannon/5 Primitive", "Autocannon/5 Primitive", "AC/5p", "IS Autocannon/5 Primitive", "ISAC5p", "", "", "", ""}},
    // Primitive Prototype Autocannon/10
    WeaponMetaInfo{"P_PROTO AC/10", 7, {"Auto Cannon/10 Primitive", "Autocannon/10 Primitive", "AutoCannon/10 Primitive", "IS Auto Cannon/10 Primitive", "IS Autocannon/10 Primitive", "AC/10p", "ISAC10p", "", "", "", ""}},
    // Primitive Prototype Autocannon/20
    WeaponMetaInfo{"P_PROTO AC/20", 10, {"ISAC20p", "Auto Cannon/20 Primitive", "AutoCannon/20 Primitive", "IS Auto Cannon/20 Primitive", "IS Autocannon/20 Primitive", "Autocannon/20 Primitive", "", "", "", "", ""}},
    // Ultra AC/2
    WeaponMetaInfo{"Ultra AC/2", 3, {"IS Ultra AC/2", "ISUltraAC2", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/5
    WeaponMetaInfo{"Ultra AC/5", 5, {"ISUltraAC5", "IS Ultra AC/5", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/10
    WeaponMetaInfo{"Ultra AC/10", 7, {"IS Ultra AC/10", "ISUltraAC10", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/20
    WeaponMetaInfo{"Ultra AC/20", 10, {"ISUltraAC20", "IS Ultra AC/20", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/2
    WeaponMetaInfo{"Ultra AC/2", 2, {"Clan Ultra AC/2", "CLUltraAC2", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/5
    WeaponMetaInfo{"Ultra AC/5", 3, {"CLUltraAC5", "Clan Ultra AC/5", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/10
    WeaponMetaInfo{"Ultra AC/10", 4, {"Clan Ultra AC/10", "CLUltraAC10", "", "", "", "", "", "", "", "", ""}},
    // Ultra AC/20
    WeaponMetaInfo{"Ultra AC/20", 8, {"CLUltraAC20", "Clan Ultra AC/20", "", "", "", "", "", "", "", "", ""}},
    // LB 2-X AC
    WeaponMetaInfo{"LB 2-X AC", 4, {"ISLBXAC2", "IS LB 2-X AC", "", "", "", "", "", "", "", "", ""}},
    // LB 5-X AC
    WeaponMetaInfo{"LB 5-X AC", 5, {"IS LB 5-X AC", "ISLBXAC5", "", "", "", "", "", "", "", "", ""}},
    // LB 10-X AC
    WeaponMetaInfo{"LB 10-X AC", 6, {"ISLBXAC10", "Clan LB 10-X AC", "CLLBXAC10", "IS LB 10-X AC", "", "", "", "", "", "", ""}},
    // LB 20-X AC
    WeaponMetaInfo{"LB 20-X AC", 11, {"IS LB 20-X AC", "CLLBXAC20", "Clan LB 20-X AC", "ISLBXAC20", "", "", "", "", "", "", ""}},
    // LB 2-X AC
    WeaponMetaInfo{"LB 2-X AC", 3, {"CLLBXAC2", "Clan LB 2-X AC", "", "", "", "", "", "", "", "", ""}},
    // Prototype LB 2-X Autocannon
    WeaponMetaInfo{"PROTO LB 2-X AC", 5, {"CLLBXAC2Prototype", "", "", "", "", "", "", "", "", "", ""}},
    // LB 5-X AC
    WeaponMetaInfo{"LB 5-X AC", 4, {"Clan LB 5-X AC", "CLLBXAC5", "", "", "", "", "", "", "", "", ""}},
    // Prototype LB 5-X Autocannon
    WeaponMetaInfo{"PROTO LB 5-X AC", 6, {"CLLBXAC5Prototype", "", "", "", "", "", "", "", "", "", ""}},
    // Rotary AC/2
    WeaponMetaInfo{"Rotary AC/2", 3, {"ISRAC2", "ISRotaryAC2", "IS Rotary AC/2", "", "", "", "", "", "", "", ""}},
    // Rotary AC/5
    WeaponMetaInfo{"Rotary AC/5", 6, {"IS Rotary AC/5", "ISRAC5", "ISRotaryAC5", "", "", "", "", "", "", "", ""}},
    // Light AC/2
    WeaponMetaInfo{"Light AC/2", 1, {"LAC/2", "IS Light AutoCannon/2", "Light Auto Cannon/2", "IS Light Autocannon/2", "ISLAC2", "", "", "", "", "", ""}},
    // Light AC/5
    WeaponMetaInfo{"Light AC/5", 2, {"ISLAC5", "IS Light Autocannon/5", "Light Auto Cannon/5", "IS Light Auto Cannon/5", "LAC/5", "", "", "", "", "", ""}},
    // LAC/10
    WeaponMetaInfo{"LAC/10", 4, {"IS Light Autocannon/10", "ISLAC10", "IS Light AutoCannon/10", "Light Auto Cannon/10", "", "", "", "", "", "", ""}},
    // LAC/20
    WeaponMetaInfo{"LAC/20", 6, {"IS Light Autocannon/20", "ISLAC20", "IS Light AutoCannon/20", "Light Auto Cannon/20", "", "", "", "", "", "", ""}},
    // HVAC/2
    WeaponMetaInfo{"HVAC/2", 2, {"IS Hyper Velocity Auto Cannon/2", "IS Hyper Velocity Autocannon/2", "Hyper Velocity Auto Cannon/2", "ISHVAC2", "", "", "", "", "", "", ""}},
    // HVAC/5
    WeaponMetaInfo{"HVAC/5", 4, {"ISHVAC5", "IS Hyper Velocity Autocannon/5", "IS Hyper Velocity Auto Cannon/5", "Hyper Velocity Auto Cannon/5", "", "", "", "", "", "", ""}},
    // HVAC/10
    WeaponMetaInfo{"HVAC/10", 6, {"Hyper Velocity Auto Cannon/10", "IS Hyper Velocity Autocannon/10", "IS Hyper Velocity Auto Cannon/10", "ISHVAC10", "", "", "", "", "", "", ""}},
    // Gauss Rifle
    WeaponMetaInfo{"GAUSS", 7, {"ISGaussRifle", "CLGaussRifle", "Clan Gauss Rifle", "IS Gauss Rifle", "", "", "", "", "", "", ""}},
    // Prototype Gauss Rifle
    WeaponMetaInfo{"PROTO GAUSS", 8, {"ISGaussRiflePrototype", "IS Gauss Rifle Prototype", "", "", "", "", "", "", "", "", ""}},
    // Light Gauss Rifle
    WeaponMetaInfo{"Light GAUSS", 5, {"ISLightGaussRifle", "IS Light Gauss Rifle", "", "", "", "", "", "", "", "", ""}},
    // Heavy Gauss Rifle
    WeaponMetaInfo{"HV GAUSS", 11, {"ISHeavyGaussRifle", "IS Heavy Gauss Rifle", "", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Gauss Rifle
    WeaponMetaInfo{"HV IMPR GAUSS", 11, {"IS Improved Heavy Gauss Rifle", "ISImprovedHeavyGaussRifle", "", "", "", "", "", "", "", "", ""}},
    // HAG/20
    WeaponMetaInfo{"HAG/20", 6, {"CLHAG20", "Clan HAG/20", "", "", "", "", "", "", "", "", ""}},
    // HAG/30
    WeaponMetaInfo{"HAG/30", 8, {"Clan HAG/30", "CLHAG30", "", "", "", "", "", "", "", "", ""}},
    // HAG/40
    WeaponMetaInfo{"HAG/40", 10, {"CLHAG40", "Clan HAG/40", "", "", "", "", "", "", "", "", ""}},
    // AP Gauss Rifle
    WeaponMetaInfo{"AP GAUSS", 1, {"CLAPGaussRifle", "Clan AP Gauss Rifle", "", "", "", "", "", "", "", "", ""}},
    // Machine Gun
    WeaponMetaInfo{"Machine Gun", 1, {"Machine Gun", "CLMG", "IS Machine Gun", "ISMachine Gun", "Clan Machine Gun", "ISMG", "", "", "", "", ""}},
    // Heavy Machine Gun
    WeaponMetaInfo{"HV Machine Gun", 1, {"CLHeavyMG", "Heavy Machine Gun", "Clan Heavy Machine Gun", "ISHeavyMG", "IS Heavy Machine Gun", "", "", "", "", "", ""}},
    // LRM 5
    WeaponMetaInfo{"LRM 5", 1, {"Clan LRM 5", "LRM 5", "IS LRM-5", "CLLRM5", "IS LRM 5", "Clan LRM-5", "ISLRM5", "", "", "", ""}},
    // LRM 10
    WeaponMetaInfo{"LRM 10", 2, {"LRM 10", "Clan LRM 10", "ISLRM10", "CLLRM10", "Clan LRM-10", "IS LRM-10", "IS LRM 10", "", "", "", ""}},
    // LRM 15
    WeaponMetaInfo{"LRM 15", 3, {"ISLRM15", "Clan LRM 15", "CLLRM15", "IS LRM-15", "Clan LRM-15", "LRM 15", "IS LRM 15", "", "", "", ""}},
    // LRM 20
    WeaponMetaInfo{"LRM 20", 5, {"IS LRM-20", "Clan LRM 20", "CLLRM20", "Clan LRM-20", "ISLRM20", "LRM 20", "IS LRM 20", "", "", "", ""}},
    // LRM 1
    WeaponMetaInfo{"LRM 1", 0, {"CLLRM1OS", "", "", "", "", "", "", "", "", "", ""}},
    // Streak LRM 5
    WeaponMetaInfo{"SLRM 5", 1, {"CLStreakLRM5", "Clan Streak LRM-5", "Clan Streak LRM 5", "", "", "", "", "", "", "", ""}},
    // Streak LRM 10
    WeaponMetaInfo{"SLRM 10", 2, {"CLStreakLRM10", "Clan Streak LRM-10", "Clan Streak LRM 10", "", "", "", "", "", "", "", ""}},
    // Streak LRM 15
    WeaponMetaInfo{"SLRM 15", 3, {"CLStreakLRM15", "Clan Streak LRM-15", "Clan Streak LRM 15", "", "", "", "", "", "", "", ""}},
    // Streak LRM 20
    WeaponMetaInfo{"SLRM 20", 5, {"Clan Streak LRM-20", "CLStreakLRM20", "Clan Streak LRM 20", "", "", "", "", "", "", "", ""}},
    // Extended LRM 5
    WeaponMetaInfo{"Extended LRM 5", 1, {"ELRM-5 (THB)", "IS Extended LRM 5", "ISExtendedLRM5", "IS Extended LRM-5", "Extended LRM 5", "", "", "", "", "", ""}},
    // Extended LRM 10
    WeaponMetaInfo{"Extended LRM 10", 4, {"IS Extended LRM 10", "ISExtendedLRM10", "Extended LRM 10", "IS Extended LRM-10", "ELRM-10 (THB)", "", "", "", "", "", ""}},
    // Extended LRM 15
    WeaponMetaInfo{"Extended LRM 15", 6, {"ELRM-15 (THB)", "Extended LRM 15", "IS Extended LRM 15", "IS Extended LRM-15", "ISExtendedLRM15", "", "", "", "", "", ""}},
    // Extended LRM 20
    WeaponMetaInfo{"Extended LRM 20", 8, {"Extended LRM 20", "IS Extended LRM-20", "ISExtendedLRM20", "IS Extended LRM 20", "ELRM-20 (THB)", "", "", "", "", "", ""}},
    // Enhanced LRM 5
    WeaponMetaInfo{"Enhanced LRM 5", 2, {"Enhanced LRM 5", "ISEnhancedLRM5", "", "", "", "", "", "", "", "", ""}},
    // Enhanced LRM 10
    WeaponMetaInfo{"Enhanced LRM 10", 4, {"ISEnhancedLRM10", "Enhanced LRM 10", "", "", "", "", "", "", "", "", ""}},
    // Enhanced LRM 15
    WeaponMetaInfo{"Enhanced LRM 15", 6, {"Enhanced LRM 15", "ISEnhancedLRM15", "", "", "", "", "", "", "", "", ""}},
    // Enhanced LRM 20
    WeaponMetaInfo{"Enhanced LRM 20", 9, {"ISEnhancedLRM20", "Enhanced LRM 20", "", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype LRM 5
    WeaponMetaInfo{"P_PROTO LRM 5", 1, {"IS LRM-5 Primitive", "IS LRM 5 Primitive", "Primitive Prototype LRM 5", "ISLRM5p", "", "", "", "", "", "", ""}},
    // Primitive Prototype LRM 10
    WeaponMetaInfo{"P_PROTO LRM 10", 2, {"IS LRM-10 Primitive", "IS LRM 10 Primitive", "ISLRM10p", "Primitive Prototype LRM 10", "", "", "", "", "", "", ""}},
    // Primitive Prototype LRM 15
    WeaponMetaInfo{"P_PROTO LRM 15", 3, {"IS LRM-15 Primitive", "ISLRM15p", "Primitive Prototype LRM 15", "IS LRM 15 Primitive", "", "", "", "", "", "", ""}},
    // Primitive Prototype LRM 20
    WeaponMetaInfo{"P_PROTO LRM 20", 5, {"IS LRM-20 Primitive", "IS LRM 20 Primitive", "Primitive Prototype LRM 20", "ISLRM20p", "", "", "", "", "", "", ""}},
    // LRT 5
    WeaponMetaInfo{"LRT 5", 1, {"Clan LRT 5", "ISLRTorpedo5", "IS LRT-5", "CLLRT5", "Clan LRT-5", "ISLRT5", "CLLRTorpedo5", "LRT 5", "IS LRT 5", "", ""}},
    // LRT 10
    WeaponMetaInfo{"LRT 10", 2, {"LRT 10", "IS LRT-10", "CLLRTorpedo10", "ISLRT10", "ISLRTorpedo10", "Clan LRT-10", "Clan LRT 10", "IS LRT 10", "CLLRT10", "", ""}},
    // LRT 15
    WeaponMetaInfo{"LRT 15", 3, {"LRT 15", "ISLRTorpedo15", "Clan LRT-15", "CLLRTorpedo15", "IS LRT-15", "CLLRT15", "IS LRT 15", "Clan LRT 15", "ISLRT15", "", ""}},
    // LRT 20
    WeaponMetaInfo{"LRT 20", 5, {"LRT 20", "ISLRT20", "ISLRTorpedo20", "CLLRT20", "IS LRT-20", "Clan LRT-20", "CLLRTorpedo20", "IS LRT 20", "Clan LRT 20", "", ""}},
    // SRM 2
    WeaponMetaInfo{"SRM 2", 1, {"Clan SRM-2", "Clan SRM 2", "CLSRM2", "SRM 2", "ISSRM2", "IS SRM-2", "IS SRM 2", "", "", "", ""}},
    // SRM 4
    WeaponMetaInfo{"SRM 4", 1, {"CLSRM4", "Clan SRM-4", "IS SRM 4", "SRM 4", "Clan SRM 4", "IS SRM-4", "ISSRM4", "", "", "", ""}},
    // SRM 6
    WeaponMetaInfo{"SRM 6", 2, {"CLSRM6", "IS SRM 6", "SRM 6", "Clan SRM-6", "IS SRM-6", "ISSRM6", "Clan SRM 6", "", "", "", ""}},
    // Streak SRM 2
    WeaponMetaInfo{"SSRM 2", 1, {"IS Streak SRM 2", "ISStreakSRM2", "IS Streak SRM-2", "", "", "", "", "", "", "", ""}},
    // Streak SRM 4
    WeaponMetaInfo{"SSRM 4", 1, {"ISStreakSRM4", "IS Streak SRM-4", "IS Streak SRM 4", "", "", "", "", "", "", "", ""}},
    // Streak SRM 6
    WeaponMetaInfo{"SSRM 6", 2, {"IS Streak SRM-6", "ISStreakSRM6", "IS Streak SRM 6", "", "", "", "", "", "", "", ""}},
    // Streak SRM 2
    WeaponMetaInfo{"SSRM 2", 1, {"Clan Streak SRM 2", "Clan Streak SRM-2", "CLStreakSRM2", "", "", "", "", "", "", "", ""}},
    // Streak SRM 4
    WeaponMetaInfo{"SSRM 4", 1, {"Clan Streak SRM 4", "Clan Streak SRM-4", "CLStreakSRM4", "", "", "", "", "", "", "", ""}},
    // Prototype Streak SRM 4
    WeaponMetaInfo{"PROTO SSRM 4", 2, {"CLStreakSRM4Prototype", "", "", "", "", "", "", "", "", "", ""}},
    // Streak SRM 6
    WeaponMetaInfo{"SSRM 6", 2, {"Clan Streak SRM 6", "CLStreakSRM6", "Clan Streak SRM-6", "", "", "", "", "", "", "", ""}},
    // Prototype Streak SRM 6
    WeaponMetaInfo{"PROTO SSRM 6", 2, {"CLStreakSRM6Prototype", "", "", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype SRM 2
    WeaponMetaInfo{"P_PROTO SRM 2", 1, {"ISSRM2p", "Primitive Prototype SRM 2", "IS SRM 2 Primitive", "IS SRM-2 Primitive", "", "", "", "", "", "", ""}},
    // Primitive Prototype SRM 4
    WeaponMetaInfo{"P_PROTO SRM 4", 1, {"ISSRM4p", "IS SRM-4 Primitive", "IS SRM 4 Primitive", "Primitive Prototype SRM 4", "", "", "", "", "", "", ""}},
    // Primitive Prototype SRM 6
    WeaponMetaInfo{"P_PROTO SRM 6", 2, {"ISSRM6p", "IS SRM-6 Primitive", "Primitive Prototype SRM 6", "IS SRM 6 Primitive", "", "", "", "", "", "", ""}},
    // SRT 2
    WeaponMetaInfo{"SRT 2", 1, {"Clan SRT-2", "ISSRT2", "Clan SRT 2", "CLSRT2", "IS SRT 2", "IS SRT-2", "SRT 2", "", "", "", ""}},
    // SRT 4
    WeaponMetaInfo{"SRT 4", 1, {"SRT 4", "IS SRT 4", "IS SRT-4", "Clan SRT-4", "CLSRT4", "Clan SRT 4", "ISSRT4", "", "", "", ""}},
    // SRT 6
    WeaponMetaInfo{"SRT 6", 2, {"ISSRT6", "IS SRT 6", "CLSRT6", "Clan SRT 6", "Clan SRT-6", "SRT 6", "IS SRT-6", "", "", "", ""}},
    // ATM 3
    WeaponMetaInfo{"ATM 3", 2, {"CLATM3", "Clan ATM-3", "", "", "", "", "", "", "", "", ""}},
    // ATM 6
    WeaponMetaInfo{"ATM 6", 3, {"Clan ATM-6", "CLATM6", "", "", "", "", "", "", "", "", ""}},
    // ATM 9
    WeaponMetaInfo{"ATM 9", 4, {"CLATM9", "Clan ATM-9", "", "", "", "", "", "", "", "", ""}},
    // ATM 12
    WeaponMetaInfo{"ATM 12", 5, {"CLATM12", "Clan ATM-12", "", "", "", "", "", "", "", "", ""}},
    // Improved ATM 3
    WeaponMetaInfo{"IMPR ATM 3", 2, {"CLiATM3", "Clan iATM-3", "", "", "", "", "", "", "", "", ""}},
    // Improved ATM 6
    WeaponMetaInfo{"IMPR ATM 6", 3, {"CLiATM6", "Clan iATM-6", "", "", "", "", "", "", "", "", ""}},
    // Improved ATM 9
    WeaponMetaInfo{"IMPR ATM 9", 4, {"CLiATM9", "Clan iATM-9", "", "", "", "", "", "", "", "", ""}},
    // Improved ATM 12
    WeaponMetaInfo{"IMPR ATM 12", 5, {"Clan iATM-12", "CLiATM12", "", "", "", "", "", "", "", "", ""}},
    // MRM 1
    WeaponMetaInfo{"MRM 1", 0, {"MRM-1", "IS MRM 1", "ISMRM1", "MRM 1", "", "", "", "", "", "", ""}},
    // MRM 2
    WeaponMetaInfo{"MRM 2", 0, {"MRM-2", "ISMRM2", "MRM 2", "IS MRM 2", "", "", "", "", "", "", ""}},
    // MRM 3
    WeaponMetaInfo{"MRM 3", 0, {"ISMRM3", "MRM-3", "IS MRM 3", "MRM 3", "", "", "", "", "", "", ""}},
    // MRM 4
    WeaponMetaInfo{"MRM 4", 0, {"MRM-4", "ISMRM4", "IS MRM 4", "MRM 4", "", "", "", "", "", "", ""}},
    // MRM 5
    WeaponMetaInfo{"MRM 5", 0, {"MRM-5", "IS MRM 5", "ISMRM5", "MRM 5", "", "", "", "", "", "", ""}},
    // MRM 10
    WeaponMetaInfo{"MRM 10", 2, {"MRM-10", "ISMRM10", "MRM 10", "IS MRM 10", "", "", "", "", "", "", ""}},
    // MRM 20
    WeaponMetaInfo{"MRM 20", 3, {"ISMRM20", "MRM 20", "IS MRM 20", "MRM-20", "", "", "", "", "", "", ""}},
    // MRM 30
    WeaponMetaInfo{"MRM 30", 5, {"MRM 30", "IS MRM 30", "ISMRM30", "MRM-30", "", "", "", "", "", "", ""}},
    // MRM 40
    WeaponMetaInfo{"MRM 40", 7, {"IS MRM 40", "ISMRM40", "MRM-40", "MRM 40", "", "", "", "", "", "", ""}},
    // Narc
    WeaponMetaInfo{"Narc", 2, {"ISNarcBeacon", "IS Narc Beacon", "IS Narc Missile Beacon", "", "", "", "", "", "", "", ""}},
    // Narc
    WeaponMetaInfo{"Narc", 1, {"Clan Narc Beacon", "Clan Narc Missile Beacon", "CLNarcBeacon", "", "", "", "", "", "", "", ""}},
    // iNarc
    WeaponMetaInfo{"iNarc", 3, {"IS iNarc Missile Beacon", "ISImprovedNarc", "IS iNarc Beacon", "", "", "", "", "", "", "", ""}},
    // Laser AMS
    WeaponMetaInfo{"Laser AMS", 2, {"IS Laser Anti-Missile System", "IS Laser AMS", "ISLaserAMS", "ISLaserAntiMissileSystem", "", "", "", "", "", "", ""}},
    // Laser AMS
    WeaponMetaInfo{"Laser AMS", 1, {"CLLaserAntiMissileSystem", "Clan Laser AMS", "Clan Laser Anti-Missile Sys", "", "", "", "", "", "", "", ""}},
    // TAG
    WeaponMetaInfo{"TAG", 1, {"ISTAG", "IS TAG", "", "", "", "", "", "", "", "", ""}},
    // Light TAG
    WeaponMetaInfo{"Light TAG", 1, {"Clan Light TAG", "Light TAG [Clan]", "CLLightTAG", "", "", "", "", "", "", "", ""}},
    // TAG (Clan)
    WeaponMetaInfo{"TAG (Clan)", 1, {"CLTAG", "Clan TAG", "", "", "", "", "", "", "", "", ""}},
    // Prototype TAG
    WeaponMetaInfo{"PROTO TAG", 1, {"ISProtoTypeTAG", "IS Prototype TAG", "", "", "", "", "", "", "", "", ""}},
    // MML 3
    WeaponMetaInfo{"MML 3", 2, {"IS MML-3", "ISMML3", "", "", "", "", "", "", "", "", ""}},
    // MML 5
    WeaponMetaInfo{"MML 5", 3, {"ISMML5", "IS MML-5", "", "", "", "", "", "", "", "", ""}},
    // MML 7
    WeaponMetaInfo{"MML 7", 4, {"ISMML7", "IS MML-7", "", "", "", "", "", "", "", "", ""}},
    // MML 9
    WeaponMetaInfo{"MML 9", 5, {"ISMML9", "IS MML-9", "", "", "", "", "", "", "", "", ""}},
    // Long Tom
    WeaponMetaInfo{"Long Tom", 30, {"Clan Long Tom", "IS Long Tom", "ISLongTomArtillery", "ISLongTom", "CLLongTom", "CLLongTomArtillery", "", "", "", "", ""}},
    // Thumper
    WeaponMetaInfo{"Thumper", 15, {"IS Thumper", "Clan Thumper", "ISThumper", "CLThumper", "ISThumperArtillery", "CLThumperArtillery", "", "", "", "", ""}},
    // Sniper
    WeaponMetaInfo{"Sniper", 20, {"Clan Sniper", "CLSniperArtillery", "ISSniperArtillery", "CLSniper", "ISSniper", "IS Sniper", "", "", "", "", ""}},
    // Arrow IV
    WeaponMetaInfo{"Arrow IV", 15, {"ISArrowIV", "IS Arrow IV System", "IS Arrow IV Missile System", "ISArrowIVSystem", "", "", "", "", "", "", ""}},
    // Arrow IV
    WeaponMetaInfo{"Arrow IV", 12, {"CLArrowIVSystem", "CLArrowIV", "Clan Arrow IV System", "Clan Arrow IV Missile System", "", "", "", "", "", "", ""}},
    // Prototype Arrow IV
    WeaponMetaInfo{"PROTO Arrow IV", 16, {"ProtoTypeArrowIV", "ProtoArrowIVSystem", "", "", "", "", "", "", "", "", ""}},
    // Long Tom Cannon
    WeaponMetaInfo{"Long Tom Cannon", 15, {"IS Long Tom Cannon", "CLLongTomArtilleryCannon", "ISLongTomCannon", "CL Long Tom Cannon", "ISLongTomArtilleryCannon", "CLLongTomCannon", "", "", "", "", ""}},
    // Thumper Cannon
    WeaponMetaInfo{"Thumper Cannon", 7, {"CLThumper Cannon", "CLThumperArtilleryCannon", "CL Thumper Cannon", "IS Thumper Cannon", "ISThumperArtilleryCannon", "ISThumperCannon", "", "", "", "", ""}},
    // Sniper Cannon
    WeaponMetaInfo{"Sniper Cannon", 10, {"ISSniperArtilleryCannon", "IS Sniper Cannon", "CL Sniper Cannon", "CLSniper Cannon", "CLSniperArtilleryCannon", "ISSniperCannon", "", "", "", "", ""}},
    // Plasma Rifle
    WeaponMetaInfo{"Plasma Rifle", 2, {"Clan Plasma Rifle", "MFUK Plasma Rifle", "CL Plasma Rifle", "MFUKCLPlasmaRifle", "CLPlasmaRifle", "", "", "", "", "", ""}},
    // Rotary AC/2
    WeaponMetaInfo{"Rotary AC/2", 4, {"CLRotaryAC2", "Clan Rotary Assault Cannon/2", "Clan Rotary AC/2", "", "", "", "", "", "", "", ""}},
    // Rotary AC/5
    WeaponMetaInfo{"Rotary AC/5", 8, {"Clan Rotary AC/5", "CLRotaryAC5", "Clan Rotary Assault Cannon/5", "", "", "", "", "", "", "", ""}},
    // Rotary AC/10
    WeaponMetaInfo{"Rotary AC/10", 7, {"Clan Rotary AC/10", "Clan Rotary Assault Cannon/10", "CLRotaryAC10", "", "", "", "", "", "", "", ""}},
    // Rotary AC/20
    WeaponMetaInfo{"Rotary AC/20", 10, {"Clan Rotary AC/20", "Clan Rotary Assault Cannon/20", "CLRotaryAC20", "", "", "", "", "", "", "", ""}},
    // Rail Gun
    WeaponMetaInfo{"Rail Gun", 9, {"IS Rail Gun", "ISRailGun", "", "", "", "", "", "", "", "", ""}},
    // Fluid Gun
    WeaponMetaInfo{"Fluid Gun", 2, {"Clan Fluid Gun", "CLFluidGun", "IS Fluid Gun", "ISFluidGun", "", "", "", "", "", "", ""}},
    // Magshot
    WeaponMetaInfo{"Magshot", 2, {"ISMagshotGR", "", "", "", "", "", "", "", "", "", ""}},
    // M-Pod
    WeaponMetaInfo{"M-Pod", 1, {"ISMPod", "ISM-Pod", "", "", "", "", "", "", "", "", ""}},
    // Thunderbolt 5
    WeaponMetaInfo{"Thunderbolt 5", 1, {"Thunderbolt 5", "IS Thunderbolt 5", "IS Thunderbolt-5", "ISThunderbolt5", "", "", "", "", "", "", ""}},
    // Thunderbolt 10
    WeaponMetaInfo{"Thunderbolt 10", 2, {"ISThunderbolt10", "Thunderbolt 10", "IS Thunderbolt 10", "IS Thunderbolt-10", "ISTBolt10", "", "", "", "", "", ""}},
    // Thunderbolt 15
    WeaponMetaInfo{"Thunderbolt 15", 3, {"IS Thunderbolt-15", "ISTBolt15", "IS Thunderbolt 15", "ISThunderbolt15", "Thunderbolt 15", "", "", "", "", "", ""}},
    // Thunderbolt 20
    WeaponMetaInfo{"Thunderbolt 20", 5, {"ISThunderbolt20", "ISTBolt20", "IS Thunderbolt-20", "Thunderbolt 20", "IS Thunderbolt 20", "", "", "", "", "", ""}},
    // Nail/Rivet Gun
    WeaponMetaInfo{"Nail/Rivet Gun", 1, {"ISNail Gun", "Nail/Rivet Gun", "ISRivet Gun", "ISNailRivet Gun", "CLRivet Gun", "CLNailRivetGun", "Nail Gun", "CLNail/Rivet Gun", "CLNailRivet Gun", "CLNail Gun", ""}},
    // Improved Autocannon/2
    WeaponMetaInfo{"IMPR AC/2", 1, {"CLIMPAC2", "Improved Autocannon/2", "", "", "", "", "", "", "", "", ""}},
    // Improved Autocannon/5
    WeaponMetaInfo{"IMPR AC/5", 2, {"CLIMPAC5", "Improved Autocannon/5", "", "", "", "", "", "", "", "", ""}},
    // Improved Autocannon/10
    WeaponMetaInfo{"IMPR AC/10", 6, {"Improved Autocannon/10", "CLIMPAC10", "", "", "", "", "", "", "", "", ""}},
    // Improved Autocannon/20
    WeaponMetaInfo{"IMPR AC/20", 9, {"Improved Autocannon/20", "CLIMPAC20", "", "", "", "", "", "", "", "", ""}},
    // Improved SRM 2
    WeaponMetaInfo{"IMPR SRM 2", 1, {"CLImprovedSRM2", "Improved SRM 2", "", "", "", "", "", "", "", "", ""}},
    // Improved SRM 4
    WeaponMetaInfo{"IMPR SRM 4", 1, {"Improved SRM 4", "CLImprovedSRM4", "", "", "", "", "", "", "", "", ""}},
    // Improved SRM 6
    WeaponMetaInfo{"IMPR SRM 6", 2, {"CLImprovedSRM6", "Improved SRM 6", "", "", "", "", "", "", "", "", ""}},
    // Improved LRM 5
    WeaponMetaInfo{"IMPR LRM 5", 1, {"CLImpLRM5", "CLImprovedLRM5", "Improved LRM 5", "", "", "", "", "", "", "", ""}},
    // Improved LRM 10
    WeaponMetaInfo{"IMPR LRM 10", 1, {"CLImpLRM10", "Improved LRM 10", "CLImprovedLRM10", "", "", "", "", "", "", "", ""}},
    // Improved LRM 15
    WeaponMetaInfo{"IMPR LRM 15", 2, {"CLImprovedLRM15", "Improved LRM 15", "CLImpLRM15", "", "", "", "", "", "", "", ""}},
    // Improved LRM 20
    WeaponMetaInfo{"IMPR LRM 20", 4, {"CLImprovedLRM20", "Improved LRM 20", "CLImpLRM20", "", "", "", "", "", "", "", ""}},
    // Improved Gauss Rifle
    WeaponMetaInfo{"IMPR GAUSS", 6, {"Improved Gauss Rifle", "CLIMPGaussRifle", "", "", "", "", "", "", "", "", ""}},
    // Improved Large Laser
    WeaponMetaInfo{"IMPR LLaser", 1, {"Improved Large Laser", "ImpLargeLaser", "", "", "", "", "", "", "", "", ""}},
    // Improved Large Pulse Laser
    WeaponMetaInfo{"IMPR LPLaser", 2, {"ImprovedLargePulseLaser", "ImpLargePulseLaser", "Improved Pulse Large Laser", "", "", "", "", "", "", "", ""}},
    // Improved PPC
    WeaponMetaInfo{"IMPR PPC", 2, {"CLIMPPPC", "Improved PPC", "Improved Particle Cannon", "", "", "", "", "", "", "", ""}},
    // Plasma Rifle
    WeaponMetaInfo{"Plasma Rifle", 2, {"ISPlasmaRifle", "", "", "", "", "", "", "", "", "", ""}},
    // Plasma Cannon
    WeaponMetaInfo{"Plasma Cannon", 1, {"CLPlasmaCannon", "", "", "", "", "", "", "", "", "", ""}},
    // 'Mech Mortar 1
    WeaponMetaInfo{"'Mech Mortar 1", 1, {"Clan Mech Mortar-1", "IS Mek Mortar 1", "IS Mech Mortar-1", "Clan Mek Mortar 1", "CLMekMortar1", "ISMekMortar1", "", "", "", "", ""}},
    // 'Mech Mortar 2
    WeaponMetaInfo{"'Mech Mortar 2", 2, {"IS Mech Mortar-2", "CLMekMortar2", "Clan Mech Mortar-2", "ISMekMortar2", "IS Mek Mortar 2", "Clan Mek Mortar 2", "", "", "", "", ""}},
    // 'Mech Mortar 4
    WeaponMetaInfo{"'Mech Mortar 4", 3, {"Clan Mech Mortar-4", "IS Mek Mortar 4", "CLMekMortar4", "IS Mech Mortar-4", "ISMekMortar4", "Clan Mek Mortar 4", "", "", "", "", ""}},
    // 'Mech Mortar 8
    WeaponMetaInfo{"'Mech Mortar 8", 5, {"IS Mech Mortar-8", "CLMekMortar8", "ISMekMortar8", "IS Mek Mortar 8", "Clan Mek Mortar 8", "Clan Mech Mortar-8", "", "", "", "", ""}},
    // AC/10i
    WeaponMetaInfo{"AC/10i", 7, {"ISAutocannon10i", "ISAC10i", "ISAC/10i", "", "", "", "", "", "", "", ""}},
    // AC/15
    WeaponMetaInfo{"AC/15", 8, {"ISAC15", "IS Autocannon/15", "AC/15", "Autocannon/15", "AutoCannon/15", "Auto Cannon/15", "IS Auto Cannon/15", "", "", "", ""}},
    // Enhanced PPC
    WeaponMetaInfo{"Enhanced PPC", 3, {"IS EH ER PPC", "CLWERPPC", "Wolverine ER PPC", "ISEHERPPC", "", "", "", "", "", "", ""}},
    // TSEMP Cannon
    WeaponMetaInfo{"TSEMP Cannon", 5, {"ISTSEMP", "TSEMP Cannon", "", "", "", "", "", "", "", "", ""}},
    // TSEMP One-Shot
    WeaponMetaInfo{"TSEMP One-Shot", 3, {"TSEMP One-Shot", "ISTSEMPOS", "", "", "", "", "", "", "", "", ""}}
};
}
