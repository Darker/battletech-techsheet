import json
import re
import os

from typing import Iterable, TypedDict, Union

class WeaponEntry(TypedDict):
    name: str
    names: list[str]
    sht: int
    med: int
    lon: int
    exlon: int
    dmg: int
    heatDmg: Union[None, int]
    heat: int
    slots: int
    ammoType: str
    rackSize: int

class AllWeapons(TypedDict):
    weapons: list[WeaponEntry]

weaponData: AllWeapons = json.load(open("../static_data/weapons.json"))

class AmmoEntry(TypedDict):
    name: str
    names: list[str]
    enumName: str
    rackSize: int
    shots: int
    damagePerShot: int
    ammoType: str

class AllAmmo(TypedDict):
    ammo: list[AmmoEntry]

ammoData: AllAmmo = json.load(open("../static_data/ammo.json"))

REGEX_PREFIXES = re.compile(r"((?:(?:Heavy|Improved|Chemical|Large|Medium|Small|(?:X-)?Pulse) ?)+)")
REGEX_ROCKET_ARRAYS = re.compile(r"Streak ([SML])RM ([0-9]{1,2})")
REGEX_MULTIPLE_SPACES = re.compile(r" {2,}")

def make_array_str(string_vals: Iterable[str], size: int):
    vals_list = list(string_vals)
    if len(vals_list) > size:
        print("Note: too many names - "+",".join(vals_list))
        raise RuntimeError(f"Cannot fit {len(vals_list)} into target std:array of size {size}")
    while len(vals_list ) < size:
        vals_list.append("")
    return "{" + ", ".join((json.dumps(name) for name in vals_list)) + "}"


def replace_prefixes(matched_prefixes: str, current_name: str):
    space_prefixes = []
    # no space only if this goes before the word Laser
    nospace_prefixes = []
    is_laser = "Laser" in current_name

    if "Heavy" in matched_prefixes:
        space_prefixes += ["HV"]
    if "Improved" in matched_prefixes:
        space_prefixes += ["IMPR"]

    if "Chemical" in matched_prefixes:
        space_prefixes += ["CHEM"]

    for size in ["Small", "Medium", "Large"]:
        if size in matched_prefixes:
            nospace_prefixes += size[0]
            break
    
    if "Pulse" in matched_prefixes:
        nospace_prefixes += ["X-P" if "X-Pu" in matched_prefixes else "P"]
    
    if is_laser:
        laser_prefix = "".join(nospace_prefixes)
        current_name = current_name.replace("Laser", laser_prefix + "Laser")
    else:
        space_prefixes += nospace_prefixes
    
    return re.sub(REGEX_PREFIXES, " ".join(space_prefixes)+" ", current_name)


RACK_AMMO_TYPES = ["LRM", "SRM", "MRM", "AC", "LRM_STREAK", "HAG"]
# these are valid names but we don't implement them yet
BANNED_AMMO_TYPES = ["AC_PRIMITIVE", "AC_ULTRA", "AC_ROTARY", "NARC", "LRM_TORPEDO", "SRM_TORPEDO", "ATM",
                     "ACi", "LAC", "MML", "HYPER_VELOCITY", "IATM"
                     "SRM_PRIMITIVE", "LRM_PRIMITIVE", "GAUSS_IMP", "AC_LBX", "EXLRM", "SRM_IMP", "TBOLT_10", "TBOLT_5", "PAC",
                     "NLRM", "AC_IMP", "IGAUSS_HEAVY", "LRM_STREAK", "SRM_STREAK", "TBOLT_20", "MEK_MORTAR",
                     "IATM", "HEAVY_FLAMER", "TBOLT_15", "LRM_IMP", "MPOD", "INARC", "IATM", "SRM_PRIMITIVE", "APGAUSS"
                     ]
def apply_rack_size(ammo_name: str, rack_size: int):
    if ammo_name in RACK_AMMO_TYPES:
        return ammo_name + "_" + str(rack_size)
    else:
        if rack_size > 1:
            print(f"Ammo '{ammo_name}' with size {rack_size} but isn't known as multi shot ammo")
        return ammo_name

RANGES = ["sht", "med", "lon", "exlon"]

class WeaponDef:
    def __init__(self, name: str, src: WeaponEntry) -> None:
        self.name = name
        self.megamek_name = src["name"]
        self.name_quoted = json.dumps(base_name)
        self.rack_size = src["rackSize"]
        self.ammo_type = weapon["ammoType"]
        self.ammo_type = apply_rack_size(self.ammo_type, self.rack_size)
        # Fix for accidentally marking GAUSS as AC_0 ammo type
        if "GAUSS" in name and self.ammo_type == "AC_0":
            self.ammo_type = "GAUSS"

        self.ammo_type_str = f"Ammo::{self.ammo_type}"
        self.ranges_str = ", ".join((str(src[x]) for x in RANGES)) 
        self.heat = src['heat']
        self.damage = src["dmg"]
        self.heatDmg = 0
        self.slots = src["slots"]
        if 'heatDmg' in src:
            self.heatDmg = src["heatDmg"]

    def __eq__(self, other: 'WeaponDef'):
        if isinstance(other, WeaponDef):
            return other.name == self.name \
                    and other.ammo_type_str == self.ammo_type_str \
                    and other.rack_size == self.rack_size \
                    and other.ranges_str == self.ranges_str \
                    and other.heat == self.heat \
                    and other.damage == self.damage \
                    and other.heatDmg == self.heatDmg
        else:
            return False
        
    def __ne__(self, __value: object) -> bool:
        return not self.__eq__(__value)
    
    def __hash__(self) -> int:
        return hash((self.name, self.ammo_type_str, self.ranges_str, self.heat, self.damage, self.heatDmg, self.rack_size))

if "weapons" in weaponData and "ammo" in ammoData:

    weapon_set = set() # type: set[WeaponDef]
    weapon_names = set() # type: set[str]
    lookup_names = dict() # type: dict[str, set[str]]
    used_ammo_set = set() # type: set[str]

    for weapon in weaponData["weapons"]:
        megamek_name = weapon["name"]
        base_name = weapon["name"]

        if base_name.endswith("(OS)") or base_name.endswith("(I-OS)") or base_name.endswith("(THB)"):
            continue
        if base_name.startswith("Naval "):
            continue
        if "GAC/" in base_name:
            continue

        base_name = base_name.replace("Primitive Prototype", "P_PROTO")
        base_name = base_name.replace("Prototype", "PROTO")
        base_name = base_name.replace("Autocannon/", "AC/")
        base_name = base_name.replace("Gauss Rifle", "GAUSS")
        base_name = base_name.replace("-X Autocannon", "-X AC")
        base_name = re.sub(REGEX_ROCKET_ARRAYS, r"S\1RM \2", base_name)
        
        pref_match = re.search(REGEX_PREFIXES, base_name)
        if pref_match:
            orig = base_name
            matched_prefixes = pref_match.group(1)
            base_name = replace_prefixes(pref_match.group(1), base_name)
            # print(f"{orig} -> {base_name} [{matched_prefixes}]")
        # else:
        #     print(f"{base_name} -> {base_name} [no match]")

        base_name = re.sub(REGEX_MULTIPLE_SPACES, " ", base_name)
        base_name = base_name.strip()

        if len(base_name) >= 16:
            print(f"Name too long, skiping: {base_name} ({megamek_name})")
        elif weapon["ammoType"] in BANNED_AMMO_TYPES:
            continue
        else:
            w = WeaponDef(base_name, weapon)
            if w.damage <= 0:
                print(f"Skiping weapon with special damage {w.damage}: {base_name} ({megamek_name})")
                continue
            if w not in weapon_set:
                suffix_num = 0
                suffixless_name = w.name
                while w.name in weapon_names:
                    suffix_num += 1
                    w.name = suffixless_name + "_" + str(suffix_num)
                if suffix_num != 0:
                    print(f"Duplicate name, rename: {suffixless_name} -> {w.name}")
                weapon_names.add(w.name)
                used_ammo_set.add(w.ammo_type)
                weapon_set.add(w)
            else:
                print(f"Duplicate definition: {base_name} ({megamek_name})")
            
            if w.name not in lookup_names:
                lookup_names[w.name] = set()
            lookup_names[w.name] = lookup_names[w.name].union(set((x.lower() for x in weapon["names"])))

    output_f = open("../src/MtfParser/weapon_db.h", "w")

    output_f.write(
"""
#include <techsheet/Weapon.h>

#include <array>
namespace mtfparser {

constexpr std::array Weapon_db
{
"""
    )
    first = True
    t_ns = "techsheet::"
    for weapon in weapon_set:
        if first:
            first = False
        else:
            output_f.write(",\n")
            pass

        output_f.write(f"    // {weapon.megamek_name}\n")

        output_f.write(
            f"    {t_ns}Weapon({weapon.name_quoted}, {t_ns}{weapon.ammo_type_str}, {t_ns}RangeLimits{{{weapon.ranges_str}}}, {t_ns}heat{{{weapon.heat}}}, {t_ns}damage{{{weapon.damage}}}, {t_ns}heat{{{weapon.heatDmg}}})"
        )
    output_f.write("\n};\n}\n")
    output_f.close()
    output_f = open("../src/MtfParser/weapon_name_db.h", "w")

    output_f.write(
"""

#include <mtfparser/WeaponMetaInfo.h>

#include <array>
namespace mtfparser {
constexpr std::array Weapon_name_db
{
"""
    )
    first = True
    for weapon_name, alt_names in lookup_names.items():
        if first:
            first = False
        else:
            output_f.write(",\n")
            pass
        

        name_array_str = make_array_str(alt_names, 11)
        # crit size lookup
        current_weapon = next(x for x in weapon_set if x.name == weapon_name)
        crit_size = current_weapon.slots
        output_f.write(f"    // {current_weapon.megamek_name}\n")
        output_f.write(
            f"    WeaponMetaInfo{{{current_weapon.name_quoted}, {crit_size}, {name_array_str}}}"
        )


    output_f.write("\n};\n}\n")
    output_f.close()

    # now load ammo, only ammo types that are used will be written

    output_f = open("../src/MtfParser/ammo_db.h", "w")

    output_f.write(
"""

#include <mtfparser/AmmoMetaInfo.h>

#include <array>
namespace mtfparser {
constexpr std::array Ammo_db
{
"""
    )
    first = True
    for ammo_entry in ammoData["ammo"]:
        rack_name = apply_rack_size(ammo_entry["ammoType"], ammo_entry["rackSize"])
        if rack_name in used_ammo_set:
            if first:
                first = False
            else:
                output_f.write(",\n")
                pass
            all_names = ammo_entry["names"] + [ammo_entry["name"]]
            names_str = make_array_str((x.lower() for x in all_names), 15)
            shot_damage = ammo_entry["damagePerShot"]
            if shot_damage < 0:
                shot_damage = 0

            output_f.write(f"    // {ammo_entry['name']}\n")
            output_f.write(
                f"    AmmoMetaInfo{{techsheet::ammo_count{{{ammo_entry['shots']}}}, techsheet::Ammo::{rack_name}, techsheet::damage{{{shot_damage}}}, {names_str}}}"
            )

        else:
            print(f"Unused ammo: {ammo_entry['name']}")
    output_f.write("\n};\n}\n")
    output_f.close()
else:
    print("Cannot find weapons key")