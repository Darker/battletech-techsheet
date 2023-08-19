

#include <mtfparser/WeaponMetaInfo.h>

#include <array>
namespace mtfparser {
constexpr std::array Weapon_name_db
{
    // Medium Laser
    WeaponMetaInfo{"MLaser", 1, {"ismediumlaser", "is medium laser", "medium laser", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype Medium Laser
    WeaponMetaInfo{"P_PROTO MLaser", 1, {"ismediumlaserprototype", "is medium laser prototype", "primitive prototype medium laser", "", "", "", "", "", "", "", ""}},
    // Large Laser
    WeaponMetaInfo{"LLaser", 2, {"large laser", "is large laser", "islargelaser", "", "", "", "", "", "", "", ""}},
    // Primitive Prototype Large Laser
    WeaponMetaInfo{"P_PROTO LLaser", 2, {"is large laser prototype", "primitive prototype large laser", "islargelaserprototype", "", "", "", "", "", "", "", ""}},
    // Small Laser
    WeaponMetaInfo{"SLaser", 1, {"cl small laser", "clsmalllaser", "issmalllaser", "clsmall laser", "small laser", "issmall laser", "", "", "", "", ""}},
    // Primitive Prototype Small Laser
    WeaponMetaInfo{"P_PROTO SLaser", 1, {"primitive prototype small laser", "issmall laser primitive", "issmalllaserprimitive", "", "", "", "", "", "", "", ""}},
    // Large Pulse Laser
    WeaponMetaInfo{"LPLaser", 2, {"is pulse large laser", "islargepulselaser", "is large pulse laser", "", "", "", "", "", "", "", ""}},
    // Prototype Large Pulse Laser
    WeaponMetaInfo{"PROTO LPLaser", 2, {"is prototype large pulse laser", "islargepulselaserprototype", "is pulse large laser prototype", "", "", "", "", "", "", "", ""}},
    // Large X-Pulse Laser
    WeaponMetaInfo{"LX-PLaser", 2, {"is large x-pulse laser", "is x-pulse large laser", "islargexpulselaser", "", "", "", "", "", "", "", ""}},
    // ER Large Laser
    WeaponMetaInfo{"ER LLaser", 2, {"iserlargelaser", "is er large laser", "", "", "", "", "", "", "", "", ""}},
    // Prototype ER Large Laser
    WeaponMetaInfo{"PROTO ER LLaser", 2, {"is er large laser prototype", "iserlargelaserprototype", "", "", "", "", "", "", "", "", ""}},
    // ER Medium Laser
    WeaponMetaInfo{"ER MLaser", 1, {"isermediumlaser", "is er medium laser", "", "", "", "", "", "", "", "", ""}},
    // Medium Pulse Laser
    WeaponMetaInfo{"MPLaser", 1, {"is pulse med laser", "ismediumpulselaser", "is medium pulse laser", "", "", "", "", "", "", "", ""}},
    // Prototype Medium Pulse Laser
    WeaponMetaInfo{"PROTO MPLaser", 1, {"ismediumpulselaserprototype", "is medium pulse laser prototype", "is pulse med laser prototype", "", "", "", "", "", "", "", ""}},
    // Medium X-Pulse Laser
    WeaponMetaInfo{"MX-PLaser", 1, {"ismediumxpulselaser", "is x-pulse med laser", "is medium x-pulse laser", "", "", "", "", "", "", "", ""}},
    // Small Pulse Laser
    WeaponMetaInfo{"SPLaser", 1, {"issmall pulse laser", "is small pulse laser", "issmallpulselaser", "", "", "", "", "", "", "", ""}},
    // Small X-Pulse Laser
    WeaponMetaInfo{"SX-PLaser", 1, {"is x-pulse small laser", "is small x-pulse laser", "issmallxpulselaser", "", "", "", "", "", "", "", ""}},
    // Prototype Small Pulse Laser
    WeaponMetaInfo{"PROTO SPLaser", 1, {"is prototype small pulse laser", "issmallpulselaserprototype", "issmall pulse laser prototype", "", "", "", "", "", "", "", ""}},
    // ER Small Laser
    WeaponMetaInfo{"ER SLaser", 1, {"is er small laser", "isersmalllaser", "", "", "", "", "", "", "", "", ""}},
    // Bombast Laser
    WeaponMetaInfo{"Bombast Laser", 3, {"bombast laser", "is bombast laser", "isbombastlaser", "", "", "", "", "", "", "", ""}},
    // ER Large Laser
    WeaponMetaInfo{"ER LLaser", 1, {"clan er large laser", "clerlargelaser", "", "", "", "", "", "", "", "", ""}},
    // Heavy Large Laser
    WeaponMetaInfo{"HV LLaser", 3, {"clan large heavy laser", "clheavylargelaser", "", "", "", "", "", "", "", "", ""}},
    // Large Pulse Laser
    WeaponMetaInfo{"LPLaser", 2, {"cllargepulselaser", "clan large pulse laser", "clan pulse large laser", "", "", "", "", "", "", "", ""}},
    // ER Large Pulse Laser
    WeaponMetaInfo{"ER LPLaser", 3, {"clerlargepulselaser", "clan er pulse large laser", "clan er large pulse laser", "", "", "", "", "", "", "", ""}},
    // ER Medium Laser
    WeaponMetaInfo{"ER MLaser", 1, {"clan er medium laser", "clermediumlaser", "", "", "", "", "", "", "", "", ""}},
    // Prototype ER Medium Laser
    WeaponMetaInfo{"PROTO ER MLaser", 1, {"clermediumlaserprototype", "", "", "", "", "", "", "", "", "", ""}},
    // Heavy Medium Laser
    WeaponMetaInfo{"HV MLaser", 2, {"clheavymediumlaser", "clan medium heavy laser", "", "", "", "", "", "", "", "", ""}},
    // Medium Pulse Laser
    WeaponMetaInfo{"MPLaser", 1, {"clan medium pulse laser", "clan pulse med laser", "clmediumpulselaser", "", "", "", "", "", "", "", ""}},
    // ER Medium Pulse Laser
    WeaponMetaInfo{"ER MPLaser", 2, {"clan er pulse med laser", "clan er medium pulse laser", "clermediumpulselaser", "", "", "", "", "", "", "", ""}},
    // ER Small Laser
    WeaponMetaInfo{"ER SLaser", 1, {"clersmalllaser", "clan er small laser", "", "", "", "", "", "", "", "", ""}},
    // Prototype ER Small Laser
    WeaponMetaInfo{"PROTO ER SLaser", 1, {"clersmalllaserprototype", "", "", "", "", "", "", "", "", "", ""}},
    // Small Pulse Laser
    WeaponMetaInfo{"SPLaser", 1, {"clan pulse small laser", "clsmallpulselaser", "clan small pulse laser", "", "", "", "", "", "", "", ""}},
    // ER Small Pulse Laser
    WeaponMetaInfo{"ER SPLaser", 1, {"clersmallpulselaser", "clan er pulse small laser", "clan er small pulse laser", "clanersmallpulselaser", "", "", "", "", "", "", ""}},
    // Heavy Small Laser
    WeaponMetaInfo{"HV SLaser", 1, {"clan small heavy laser", "clheavysmalllaser", "", "", "", "", "", "", "", "", ""}},
    // ER Micro Laser
    WeaponMetaInfo{"ER Micro Laser", 1, {"clan er micro laser", "clermicrolaser", "", "", "", "", "", "", "", "", ""}},
    // Micro Pulse Laser
    WeaponMetaInfo{"Micro PLaser", 1, {"clmicropulselaser", "clan micro pulse laser", "", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Large Laser
    WeaponMetaInfo{"HV IMPR LLaser", 3, {"climprovedheavylargelaser", "clan improved large heavy laser", "", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Medium Laser
    WeaponMetaInfo{"HV IMPR MLaser", 2, {"clan improved heavy medium laser", "climprovedheavymediumlaser", "climprovedmediumheavylaser", "", "", "", "", "", "", "", ""}},
    // Improved Heavy Small Laser
    WeaponMetaInfo{"HV IMPR SLaser", 1, {"clan improved small heavy laser", "climprovedsmallheavylaser", "climprovedheavysmalllaser", "", "", "", "", "", "", "", ""}},
    // Large Chemical Laser
    WeaponMetaInfo{"CHEM LLaser", 2, {"large chem laser", "cllargechemicallaser", "cllargechemlaser", "", "", "", "", "", "", "", ""}},
    // Medium Chemical Laser
    WeaponMetaInfo{"CHEM MLaser", 1, {"clmediumchemlaser", "medium chem laser", "clmediumchemicallaser", "", "", "", "", "", "", "", ""}},
    // Small Chemical Laser
    WeaponMetaInfo{"CHEM SLaser", 1, {"clsmallchemlaser", "small chem laser", "clsmallchemicallaser", "", "", "", "", "", "", "", ""}},
    // PPC
    WeaponMetaInfo{"PPC", 3, {"is ppc", "ppc", "isppc", "particle cannon", "", "", "", "", "", "", ""}},
    // Primitive Prototype PPC
    WeaponMetaInfo{"P_PROTO PPC", 3, {"primitive prototype ppc", "is ppcp", "isppcp", "particle cannon primitive", "", "", "", "", "", "", ""}},
    // ER PPC
    WeaponMetaInfo{"ER PPC", 3, {"is er ppc", "iserppc", "", "", "", "", "", "", "", "", ""}},
    // ER PPC
    WeaponMetaInfo{"ER PPC", 2, {"clerppc", "clan er ppc", "", "", "", "", "", "", "", "", ""}},
    // Light PPC
    WeaponMetaInfo{"Light PPC", 2, {"islppc", "islightppc", "light ppc", "", "", "", "", "", "", "", ""}},
    // Heavy PPC
    WeaponMetaInfo{"HV PPC", 4, {"ishppc", "isheavyppc", "heavy ppc", "", "", "", "", "", "", "", ""}},
    // Flamer
    WeaponMetaInfo{"Flamer", 1, {"isflamer", "clflamer", "clan flamer", "is flamer", "flamer", "", "", "", "", "", ""}},
    // ER Flamer
    WeaponMetaInfo{"ER Flamer", 1, {"cl er flamer", "clerflamer", "iserflamer", "is er flamer", "er flamer", "", "", "", "", "", ""}},
    // AC/2
    WeaponMetaInfo{"AC/2", 1, {"auto cannon/2", "ac/2", "is autocannon/2", "isac2", "autocannon/2", "is auto cannon/2", "", "", "", "", ""}},
    // AC/5
    WeaponMetaInfo{"AC/5", 4, {"auto cannon/5", "ac/5", "isac5", "autocannon/5", "is auto cannon/5", "is autocannon/5", "", "", "", "", ""}},
    // AC/10
    WeaponMetaInfo{"AC/10", 7, {"isac10", "is autocannon/10", "autocannon/10", "ac/10", "auto cannon/10", "is auto cannon/10", "", "", "", "", ""}},
    // AC/20
    WeaponMetaInfo{"AC/20", 10, {"auto cannon/20", "isac20", "is autocannon/20", "is auto cannon/20", "autocannon/20", "", "", "", "", "", ""}},
    // Gauss Rifle
    WeaponMetaInfo{"GAUSS", 7, {"clgaussrifle", "is gauss rifle", "clan gauss rifle", "isgaussrifle", "", "", "", "", "", "", ""}},
    // Prototype Gauss Rifle
    WeaponMetaInfo{"PROTO GAUSS", 8, {"isgaussrifleprototype", "is gauss rifle prototype", "", "", "", "", "", "", "", "", ""}},
    // Light Gauss Rifle
    WeaponMetaInfo{"Light GAUSS", 5, {"islightgaussrifle", "is light gauss rifle", "", "", "", "", "", "", "", "", ""}},
    // HAG/20
    WeaponMetaInfo{"HAG/20", 6, {"clhag20", "clan hag/20", "", "", "", "", "", "", "", "", ""}},
    // HAG/30
    WeaponMetaInfo{"HAG/30", 8, {"clhag30", "clan hag/30", "", "", "", "", "", "", "", "", ""}},
    // HAG/40
    WeaponMetaInfo{"HAG/40", 10, {"clhag40", "clan hag/40", "", "", "", "", "", "", "", "", ""}},
    // Machine Gun
    WeaponMetaInfo{"Machine Gun", 1, {"clan machine gun", "ismachine gun", "is machine gun", "ismg", "machine gun", "clmg", "", "", "", "", ""}},
    // Heavy Machine Gun
    WeaponMetaInfo{"HV Machine Gun", 1, {"isheavymg", "is heavy machine gun", "clan heavy machine gun", "heavy machine gun", "clheavymg", "", "", "", "", "", ""}},
    // LRM 5
    WeaponMetaInfo{"LRM 5", 1, {"clan lrm-5", "islrm5", "is lrm 5", "clan lrm 5", "lrm 5", "cllrm5", "is lrm-5", "", "", "", ""}},
    // LRM 10
    WeaponMetaInfo{"LRM 10", 2, {"islrm10", "is lrm-10", "lrm 10", "cllrm10", "is lrm 10", "clan lrm 10", "clan lrm-10", "", "", "", ""}},
    // LRM 15
    WeaponMetaInfo{"LRM 15", 3, {"islrm15", "cllrm15", "clan lrm-15", "is lrm 15", "clan lrm 15", "is lrm-15", "lrm 15", "", "", "", ""}},
    // LRM 20
    WeaponMetaInfo{"LRM 20", 5, {"cllrm20", "clan lrm-20", "islrm20", "lrm 20", "is lrm 20", "clan lrm 20", "is lrm-20", "", "", "", ""}},
    // LRM 1
    WeaponMetaInfo{"LRM 1", 0, {"cllrm1os", "", "", "", "", "", "", "", "", "", ""}},
    // SRM 2
    WeaponMetaInfo{"SRM 2", 1, {"issrm2", "clan srm-2", "is srm-2", "srm 2", "clan srm 2", "is srm 2", "clsrm2", "", "", "", ""}},
    // SRM 4
    WeaponMetaInfo{"SRM 4", 1, {"is srm-4", "clsrm4", "srm 4", "is srm 4", "clan srm-4", "clan srm 4", "issrm4", "", "", "", ""}},
    // SRM 6
    WeaponMetaInfo{"SRM 6", 2, {"is srm-6", "issrm6", "clan srm 6", "srm 6", "clan srm-6", "is srm 6", "clsrm6", "", "", "", ""}},
    // MRM 1
    WeaponMetaInfo{"MRM 1", 0, {"mrm 1", "mrm-1", "ismrm1", "is mrm 1", "", "", "", "", "", "", ""}},
    // MRM 2
    WeaponMetaInfo{"MRM 2", 0, {"mrm 2", "is mrm 2", "mrm-2", "ismrm2", "", "", "", "", "", "", ""}},
    // MRM 3
    WeaponMetaInfo{"MRM 3", 0, {"mrm-3", "mrm 3", "is mrm 3", "ismrm3", "", "", "", "", "", "", ""}},
    // MRM 4
    WeaponMetaInfo{"MRM 4", 0, {"is mrm 4", "ismrm4", "mrm-4", "mrm 4", "", "", "", "", "", "", ""}},
    // MRM 5
    WeaponMetaInfo{"MRM 5", 0, {"is mrm 5", "mrm 5", "mrm-5", "ismrm5", "", "", "", "", "", "", ""}},
    // MRM 10
    WeaponMetaInfo{"MRM 10", 2, {"mrm-10", "mrm 10", "ismrm10", "is mrm 10", "", "", "", "", "", "", ""}},
    // MRM 20
    WeaponMetaInfo{"MRM 20", 3, {"is mrm 20", "mrm-20", "ismrm20", "mrm 20", "", "", "", "", "", "", ""}},
    // MRM 30
    WeaponMetaInfo{"MRM 30", 5, {"mrm 30", "is mrm 30", "ismrm30", "mrm-30", "", "", "", "", "", "", ""}},
    // MRM 40
    WeaponMetaInfo{"MRM 40", 7, {"mrm-40", "is mrm 40", "ismrm40", "mrm 40", "", "", "", "", "", "", ""}},
    // Laser AMS
    WeaponMetaInfo{"Laser AMS", 2, {"islaserantimissilesystem", "is laser ams", "islaserams", "is laser anti-missile system", "", "", "", "", "", "", ""}},
    // Laser AMS
    WeaponMetaInfo{"Laser AMS", 1, {"cllaserantimissilesystem", "clan laser anti-missile sys", "clan laser ams", "", "", "", "", "", "", "", ""}},
    // Plasma Rifle
    WeaponMetaInfo{"Plasma Rifle", 2, {"clan plasma rifle", "mfuk plasma rifle", "cl plasma rifle", "mfukclplasmarifle", "clplasmarifle", "", "", "", "", "", ""}},
    // Rail Gun
    WeaponMetaInfo{"Rail Gun", 9, {"israilgun", "is rail gun", "", "", "", "", "", "", "", "", ""}},
    // Magshot
    WeaponMetaInfo{"Magshot", 2, {"ismagshotgr", "", "", "", "", "", "", "", "", "", ""}},
    // Improved Large Laser
    WeaponMetaInfo{"IMPR LLaser", 1, {"improved large laser", "implargelaser", "", "", "", "", "", "", "", "", ""}},
    // Improved Large Pulse Laser
    WeaponMetaInfo{"IMPR LPLaser", 2, {"implargepulselaser", "improvedlargepulselaser", "improved pulse large laser", "", "", "", "", "", "", "", ""}},
    // Improved PPC
    WeaponMetaInfo{"IMPR PPC", 2, {"improved ppc", "climpppc", "improved particle cannon", "", "", "", "", "", "", "", ""}},
    // Plasma Rifle
    WeaponMetaInfo{"Plasma Rifle", 2, {"isplasmarifle", "", "", "", "", "", "", "", "", "", ""}},
    // AC/15
    WeaponMetaInfo{"AC/15", 8, {"isac15", "is autocannon/15", "ac/15", "autocannon/15", "auto cannon/15", "is auto cannon/15", "", "", "", "", ""}},
    // Enhanced PPC
    WeaponMetaInfo{"Enhanced PPC", 3, {"is eh er ppc", "clwerppc", "iseherppc", "wolverine er ppc", "", "", "", "", "", "", ""}}
};
}
