
#include <techsheet/Weapon.h>

#include <array>
namespace mtfparser {

constexpr std::array Weapon_db
{
    // ER Small Laser
    techsheet::Weapon("ER SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 6, 8}, techsheet::heat{2}, techsheet::damage{5}, techsheet::heat{0}),
    // Improved Large Laser
    techsheet::Weapon("IMPR LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{8}, techsheet::damage{8}, techsheet::heat{0}),
    // ER Medium Laser
    techsheet::Weapon("ER MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{5}, techsheet::damage{7}, techsheet::heat{0}),
    // MRM 3
    techsheet::Weapon("MRM 3", techsheet::Ammo::MRM_3, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{0}, techsheet::damage{3}, techsheet::heat{0}),
    // MRM 4
    techsheet::Weapon("MRM 4", techsheet::Ammo::MRM_4, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{0}, techsheet::damage{4}, techsheet::heat{0}),
    // ER Large Pulse Laser
    techsheet::Weapon("ER LPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{7, 15, 23, 30}, techsheet::heat{13}, techsheet::damage{10}, techsheet::heat{0}),
    // Enhanced PPC
    techsheet::Weapon("Enhanced PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{7, 14, 23, 28}, techsheet::heat{15}, techsheet::damage{12}, techsheet::heat{0}),
    // Heavy Medium Laser
    techsheet::Weapon("HV MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{7}, techsheet::damage{10}, techsheet::heat{0}),
    // Primitive Prototype Small Laser
    techsheet::Weapon("P_PROTO SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{2}, techsheet::damage{3}, techsheet::heat{0}),
    // ER Small Laser
    techsheet::Weapon("ER SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 5, 8}, techsheet::heat{2}, techsheet::damage{3}, techsheet::heat{0}),
    // MRM 5
    techsheet::Weapon("MRM 5", techsheet::Ammo::MRM_5, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{0}, techsheet::damage{5}, techsheet::heat{0}),
    // LRM 15
    techsheet::Weapon("LRM 15", techsheet::Ammo::LRM_15, techsheet::RangeLimits{7, 14, 21, 28}, techsheet::heat{5}, techsheet::damage{15}, techsheet::heat{0}),
    // Heavy PPC
    techsheet::Weapon("HV PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 12, 18, 24}, techsheet::heat{15}, techsheet::damage{15}, techsheet::heat{0}),
    // Small Chemical Laser
    techsheet::Weapon("CHEM SLaser", techsheet::Ammo::CHEMICAL_LASER, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{1}, techsheet::damage{3}, techsheet::heat{0}),
    // MRM 1
    techsheet::Weapon("MRM 1", techsheet::Ammo::MRM_1, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{0}, techsheet::damage{1}, techsheet::heat{0}),
    // Heavy Large Laser
    techsheet::Weapon("HV LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{18}, techsheet::damage{16}, techsheet::heat{0}),
    // ER Large Laser
    techsheet::Weapon("ER LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{8, 15, 25, 30}, techsheet::heat{12}, techsheet::damage{10}, techsheet::heat{0}),
    // Improved Heavy Medium Laser
    techsheet::Weapon("HV IMPR MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{7}, techsheet::damage{10}, techsheet::heat{0}),
    // Prototype ER Small Laser
    techsheet::Weapon("PROTO ER SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 5, 8}, techsheet::heat{2}, techsheet::damage{3}, techsheet::heat{0}),
    // Heavy Small Laser
    techsheet::Weapon("HV SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{3}, techsheet::damage{6}, techsheet::heat{0}),
    // Light Gauss Rifle
    techsheet::Weapon("Light GAUSS", techsheet::Ammo::GAUSS_LIGHT, techsheet::RangeLimits{8, 17, 25, 34}, techsheet::heat{1}, techsheet::damage{8}, techsheet::heat{0}),
    // MRM 30
    techsheet::Weapon("MRM 30", techsheet::Ammo::MRM_30, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{10}, techsheet::damage{30}, techsheet::heat{0}),
    // Large X-Pulse Laser
    techsheet::Weapon("LX-PLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{14}, techsheet::damage{9}, techsheet::heat{0}),
    // LRM 20
    techsheet::Weapon("LRM 20", techsheet::Ammo::LRM_20, techsheet::RangeLimits{7, 14, 21, 28}, techsheet::heat{6}, techsheet::damage{20}, techsheet::heat{0}),
    // Rail Gun
    techsheet::Weapon("Rail Gun", techsheet::Ammo::RAIL_GUN, techsheet::RangeLimits{6, 13, 19, 26}, techsheet::heat{1}, techsheet::damage{22}, techsheet::heat{0}),
    // LRM 5
    techsheet::Weapon("LRM 5", techsheet::Ammo::LRM_5, techsheet::RangeLimits{7, 14, 21, 28}, techsheet::heat{2}, techsheet::damage{5}, techsheet::heat{0}),
    // LRM 10
    techsheet::Weapon("LRM 10", techsheet::Ammo::LRM_10, techsheet::RangeLimits{7, 14, 21, 28}, techsheet::heat{4}, techsheet::damage{10}, techsheet::heat{0}),
    // Plasma Rifle
    techsheet::Weapon("Plasma Rifle", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 14, 22, 28}, techsheet::heat{15}, techsheet::damage{10}, techsheet::heat{0}),
    // Improved Large Pulse Laser
    techsheet::Weapon("IMPR LPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 7, 10, 14}, techsheet::heat{10}, techsheet::damage{9}, techsheet::heat{0}),
    // Medium Chemical Laser
    techsheet::Weapon("CHEM MLaser", techsheet::Ammo::CHEMICAL_LASER, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{2}, techsheet::damage{5}, techsheet::heat{0}),
    // Laser AMS
    techsheet::Weapon("Laser AMS", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 1, 1, 1}, techsheet::heat{7}, techsheet::damage{3}, techsheet::heat{0}),
    // Large Chemical Laser
    techsheet::Weapon("CHEM LLaser", techsheet::Ammo::CHEMICAL_LASER, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{6}, techsheet::damage{8}, techsheet::heat{0}),
    // MRM 10
    techsheet::Weapon("MRM 10", techsheet::Ammo::MRM_10, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{4}, techsheet::damage{10}, techsheet::heat{0}),
    // AC/10
    techsheet::Weapon("AC/10", techsheet::Ammo::AC_10, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{3}, techsheet::damage{10}, techsheet::heat{0}),
    // Large Pulse Laser
    techsheet::Weapon("LPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 7, 10, 14}, techsheet::heat{10}, techsheet::damage{9}, techsheet::heat{0}),
    // Heavy Machine Gun
    techsheet::Weapon("HV Machine Gun", techsheet::Ammo::MG_HEAVY, techsheet::RangeLimits{1, 2, 2, 2}, techsheet::heat{0}, techsheet::damage{3}, techsheet::heat{0}),
    // Micro Pulse Laser
    techsheet::Weapon("Micro PLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{1}, techsheet::damage{3}, techsheet::heat{0}),
    // ER Small Pulse Laser
    techsheet::Weapon("ER SPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 6, 8}, techsheet::heat{3}, techsheet::damage{5}, techsheet::heat{0}),
    // Large Pulse Laser
    techsheet::Weapon("LPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 14, 20, 28}, techsheet::heat{10}, techsheet::damage{10}, techsheet::heat{0}),
    // SRM 6
    techsheet::Weapon("SRM 6", techsheet::Ammo::SRM_6, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{4}, techsheet::damage{6}, techsheet::heat{0}),
    // Prototype Large Pulse Laser
    techsheet::Weapon("PROTO LPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 7, 10, 14}, techsheet::heat{10}, techsheet::damage{9}, techsheet::heat{0}),
    // HAG/30
    techsheet::Weapon("HAG/30", techsheet::Ammo::HAG_30, techsheet::RangeLimits{8, 16, 24, 32}, techsheet::heat{6}, techsheet::damage{30}, techsheet::heat{0}),
    // Light PPC
    techsheet::Weapon("Light PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 12, 18, 24}, techsheet::heat{5}, techsheet::damage{5}, techsheet::heat{0}),
    // Plasma Rifle
    techsheet::Weapon("Plasma Rifle", techsheet::Ammo::PLASMA, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{10}, techsheet::damage{10}, techsheet::heat{0}),
    // Primitive Prototype PPC
    techsheet::Weapon("P_PROTO PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 12, 18, 24}, techsheet::heat{15}, techsheet::damage{10}, techsheet::heat{0}),
    // AC/5
    techsheet::Weapon("AC/5", techsheet::Ammo::AC_5, techsheet::RangeLimits{6, 12, 18, 24}, techsheet::heat{1}, techsheet::damage{5}, techsheet::heat{0}),
    // HAG/20
    techsheet::Weapon("HAG/20", techsheet::Ammo::HAG_20, techsheet::RangeLimits{8, 16, 24, 32}, techsheet::heat{4}, techsheet::damage{20}, techsheet::heat{0}),
    // Prototype ER Medium Laser
    techsheet::Weapon("PROTO ER MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{4, 8, 12, 16}, techsheet::heat{5}, techsheet::damage{5}, techsheet::heat{0}),
    // ER Micro Laser
    techsheet::Weapon("ER Micro Laser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 4, 4}, techsheet::heat{1}, techsheet::damage{2}, techsheet::heat{0}),
    // MRM 20
    techsheet::Weapon("MRM 20", techsheet::Ammo::MRM_20, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{6}, techsheet::damage{20}, techsheet::heat{0}),
    // AC/15
    techsheet::Weapon("AC/15", techsheet::Ammo::AC_15, techsheet::RangeLimits{4, 8, 12, 16}, techsheet::heat{5}, techsheet::damage{15}, techsheet::heat{0}),
    // Primitive Prototype Large Laser
    techsheet::Weapon("P_PROTO LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{12}, techsheet::damage{8}, techsheet::heat{0}),
    // Small Laser
    techsheet::Weapon("SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{1}, techsheet::damage{3}, techsheet::heat{0}),
    // Medium Pulse Laser
    techsheet::Weapon("MPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{4, 8, 12, 16}, techsheet::heat{4}, techsheet::damage{7}, techsheet::heat{0}),
    // Improved PPC
    techsheet::Weapon("IMPR PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 12, 18, 24}, techsheet::heat{10}, techsheet::damage{10}, techsheet::heat{0}),
    // Machine Gun
    techsheet::Weapon("Machine Gun", techsheet::Ammo::MG, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{0}, techsheet::damage{2}, techsheet::heat{0}),
    // SRM 2
    techsheet::Weapon("SRM 2", techsheet::Ammo::SRM_2, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{2}, techsheet::damage{2}, techsheet::heat{0}),
    // Improved Heavy Large Laser
    techsheet::Weapon("HV IMPR LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{18}, techsheet::damage{16}, techsheet::heat{0}),
    // Prototype ER Large Laser
    techsheet::Weapon("PROTO ER LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{7, 14, 19, 28}, techsheet::heat{18}, techsheet::damage{8}, techsheet::heat{0}),
    // Primitive Prototype Medium Laser
    techsheet::Weapon("P_PROTO MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{5}, techsheet::damage{5}, techsheet::heat{0}),
    // AC/20
    techsheet::Weapon("AC/20", techsheet::Ammo::AC_20, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{7}, techsheet::damage{20}, techsheet::heat{0}),
    // ER PPC
    techsheet::Weapon("ER PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{7, 14, 23, 28}, techsheet::heat{15}, techsheet::damage{10}, techsheet::heat{0}),
    // ER Flamer
    techsheet::Weapon("ER Flamer", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 5, 7, 10}, techsheet::heat{4}, techsheet::damage{2}, techsheet::heat{2}),
    // HAG/40
    techsheet::Weapon("HAG/40", techsheet::Ammo::HAG_40, techsheet::RangeLimits{8, 16, 24, 32}, techsheet::heat{8}, techsheet::damage{40}, techsheet::heat{0}),
    // MRM 2
    techsheet::Weapon("MRM 2", techsheet::Ammo::MRM_2, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{0}, techsheet::damage{2}, techsheet::heat{0}),
    // Small Pulse Laser
    techsheet::Weapon("SPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 6, 8}, techsheet::heat{2}, techsheet::damage{3}, techsheet::heat{0}),
    // Magshot
    techsheet::Weapon("Magshot", techsheet::Ammo::MAGSHOT, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{1}, techsheet::damage{2}, techsheet::heat{0}),
    // Bombast Laser
    techsheet::Weapon("Bombast Laser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{12}, techsheet::damage{12}, techsheet::heat{0}),
    // Prototype Medium Pulse Laser
    techsheet::Weapon("PROTO MPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 6, 8}, techsheet::heat{4}, techsheet::damage{6}, techsheet::heat{0}),
    // Prototype Gauss Rifle
    techsheet::Weapon("PROTO GAUSS", techsheet::Ammo::GAUSS, techsheet::RangeLimits{7, 15, 22, 30}, techsheet::heat{1}, techsheet::damage{15}, techsheet::heat{0}),
    // Flamer
    techsheet::Weapon("Flamer", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{3}, techsheet::damage{2}, techsheet::heat{2}),
    // Improved Heavy Small Laser
    techsheet::Weapon("HV IMPR SLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{3}, techsheet::damage{6}, techsheet::heat{0}),
    // Prototype Small Pulse Laser
    techsheet::Weapon("PROTO SPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{2}, techsheet::damage{3}, techsheet::heat{0}),
    // Large Laser
    techsheet::Weapon("LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 10, 15, 20}, techsheet::heat{8}, techsheet::damage{8}, techsheet::heat{0}),
    // MRM 40
    techsheet::Weapon("MRM 40", techsheet::Ammo::MRM_40, techsheet::RangeLimits{3, 8, 15, 16}, techsheet::heat{12}, techsheet::damage{40}, techsheet::heat{0}),
    // AC/2
    techsheet::Weapon("AC/2", techsheet::Ammo::AC_2, techsheet::RangeLimits{8, 16, 24, 32}, techsheet::heat{1}, techsheet::damage{2}, techsheet::heat{0}),
    // ER Large Laser
    techsheet::Weapon("ER LLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{7, 14, 19, 28}, techsheet::heat{12}, techsheet::damage{8}, techsheet::heat{0}),
    // LRM 1
    techsheet::Weapon("LRM 1", techsheet::Ammo::LRM_1, techsheet::RangeLimits{7, 14, 21, 28}, techsheet::heat{0}, techsheet::damage{1}, techsheet::heat{0}),
    // ER PPC
    techsheet::Weapon("ER PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{7, 14, 23, 28}, techsheet::heat{15}, techsheet::damage{15}, techsheet::heat{0}),
    // Medium Laser
    techsheet::Weapon("MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{3}, techsheet::damage{5}, techsheet::heat{0}),
    // Laser AMS
    techsheet::Weapon("Laser AMS", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 1, 1, 1}, techsheet::heat{5}, techsheet::damage{3}, techsheet::heat{0}),
    // SRM 4
    techsheet::Weapon("SRM 4", techsheet::Ammo::SRM_4, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{3}, techsheet::damage{4}, techsheet::heat{0}),
    // Medium X-Pulse Laser
    techsheet::Weapon("MX-PLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{3, 6, 9, 12}, techsheet::heat{6}, techsheet::damage{6}, techsheet::heat{0}),
    // Medium Pulse Laser
    techsheet::Weapon("MPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 6, 8}, techsheet::heat{4}, techsheet::damage{6}, techsheet::heat{0}),
    // ER Medium Pulse Laser
    techsheet::Weapon("ER MPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{5, 9, 14, 18}, techsheet::heat{6}, techsheet::damage{7}, techsheet::heat{0}),
    // Gauss Rifle
    techsheet::Weapon("GAUSS", techsheet::Ammo::GAUSS, techsheet::RangeLimits{7, 15, 22, 30}, techsheet::heat{1}, techsheet::damage{15}, techsheet::heat{0}),
    // Small X-Pulse Laser
    techsheet::Weapon("SX-PLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{2, 4, 5, 8}, techsheet::heat{3}, techsheet::damage{3}, techsheet::heat{0}),
    // ER Medium Laser
    techsheet::Weapon("ER MLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{4, 8, 12, 16}, techsheet::heat{5}, techsheet::damage{5}, techsheet::heat{0}),
    // Small Pulse Laser
    techsheet::Weapon("SPLaser", techsheet::Ammo::NONE, techsheet::RangeLimits{1, 2, 3, 4}, techsheet::heat{2}, techsheet::damage{3}, techsheet::heat{0}),
    // PPC
    techsheet::Weapon("PPC", techsheet::Ammo::NONE, techsheet::RangeLimits{6, 12, 18, 24}, techsheet::heat{10}, techsheet::damage{10}, techsheet::heat{0})
};
}
