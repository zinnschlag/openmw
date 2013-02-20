/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "attr.hpp"

using namespace ESM;

const Attribute::AttributeID Attribute::sAttributeIds[Attribute::Length] = {
    Attribute::Strength,
    Attribute::Intelligence,
    Attribute::Willpower,
    Attribute::Agility,
    Attribute::Speed,
    Attribute::Endurance,
    Attribute::Personality,
    Attribute::Luck
};

const std::string Attribute::sGmstAttributeIds[Attribute::Length] = {
    "sAttributeStrength",
    "sAttributeIntelligence",
    "sAttributeWillpower",
    "sAttributeAgility",
    "sAttributeSpeed",
    "sAttributeEndurance",
    "sAttributePersonality",
    "sAttributeLuck"
};

const std::string Attribute::sGmstAttributeDescIds[Attribute::Length] = {
    "sStrDesc",
    "sIntDesc",
    "sWilDesc",
    "sAgiDesc",
    "sSpdDesc",
    "sEndDesc",
    "sPerDesc",
    "sLucDesc"
};

const std::string Attribute::sAttributeIcons[Attribute::Length] = {
    "icons\\k\\attribute_strength.dds",
    "icons\\k\\attribute_int.dds",
    "icons\\k\\attribute_wilpower.dds",
    "icons\\k\\attribute_agility.dds",
    "icons\\k\\attribute_speed.dds",
    "icons\\k\\attribute_endurance.dds",
    "icons\\k\\attribute_personality.dds",
    "icons\\k\\attribute_luck.dds"
};
