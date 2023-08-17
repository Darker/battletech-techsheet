import json
import re
import os

from typing import TypedDict, Union

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

class AllWeapons(TypedDict):
    weapons: list[WeaponEntry]

data: AllWeapons = json.load(open("../static_data/weapons.json"))



REGEX_PREFIXES = re.compile(r"((?:(?:Heavy|Improved|Chemical|Large|Medium|Small|(?:X-)?Pulse) ?)+)")
REGEX_ROCKET_ARRAYS = re.compile(r"Streak ([SML])RM ([0-9]{1,2})")
REGEX_MULTIPLE_SPACES = re.compile(r" {2,}")

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

RANGES = ["sht", "med", "lon", "exlon"]

class WeaponDef:
    def __init__(self, name: str, src: WeaponEntry) -> None:
        self.name = name
        self.megamek_name = src["name"]
        self.name_quoted = json.dumps(base_name)
        self.ammo_type = weapon["ammoType"]
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
                    and other.ranges_str == self.ranges_str \
                    and other.heat == self.heat \
                    and other.damage == self.damage \
                    and other.heatDmg == self.heatDmg
        else:
            return False
        
    def __ne__(self, __value: object) -> bool:
        return not self.__eq__(__value)
    
    def __hash__(self) -> int:
        return hash((self.name, self.ammo_type_str, self.ranges_str, self.heat, self.damage, self.heatDmg))

if "weapons" in data:

    weapon_set = set() # type: set[WeaponDef]
    weapon_names = set() # type: set[str]
    lookup_names = dict() # type: dict[str, set[str]]

    for weapon in data["weapons"]:
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
            print(f"{orig} -> {base_name} [{matched_prefixes}]")
        # else:
        #     print(f"{base_name} -> {base_name} [no match]")

        base_name = re.sub(REGEX_MULTIPLE_SPACES, " ", base_name)
        base_name = base_name.strip()

        if len(base_name) >= 16:
            print(f"Name too long, skiping: {base_name}")
        else:
            w = WeaponDef(base_name, weapon)
            if w not in weapon_set:
                suffix_num = 0
                suffixless_name = w.name
                while w.name in weapon_names:
                    suffix_num += 1
                    w.name = suffixless_name + "_" + str(suffix_num)
                if suffix_num != 0:
                    print(f"Duplicate name, rename: {suffixless_name} -> {w.name}")
                weapon_names.add(w.name)
                weapon_set.add(w)
            else:
                print(f"Duplicate definition: {megamek_name}")
            
            if w.name not in lookup_names:
                lookup_names[w.name] = set()
            lookup_names[w.name] = lookup_names[w.name].union(set(weapon["names"]))

    output_f = open("./weapon_db.h", "w")

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

    output_f = open("./weapon_name_db.h", "w")

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
        
        name_array = list(alt_names)
        while len(name_array) < 11:
            name_array.append("")
        name_array_str = "{" + ", ".join((json.dumps(name) for name in name_array)) + "}"
        if len(name_array) > 11:
            raise RuntimeError("Too many alt names, aborting")
        # crit size lookup
        current_weapon = next(x for x in weapon_set if x.name == weapon_name)
        crit_size = current_weapon.slots
        output_f.write(f"    // {current_weapon.megamek_name}\n")
        output_f.write(
            f"    WeaponMetaInfo{{{current_weapon.name_quoted}, {crit_size}, {name_array_str}}}"
        )


    output_f.write("\n};\n}\n")

else:
    print("Cannot find weapons key")