#pragma region Copyright (c) 2014-2017 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include "../core/Memory.hpp"
#include "../core/String.hpp"
#include "../localisation/Language.h"
#include "../localisation/StringIds.h"
#include "Object.h"
#include "ObjectLimits.h"


Object::Object(const rct_object_entry &entry)
{
    _objectEntry = entry;

    char name[DAT_NAME_LENGTH + 1] = { 0 };
    Memory::Copy(name, entry.name, DAT_NAME_LENGTH);
    _identifier = String::Duplicate(name);
}

Object::~Object()
{
    Memory::Free(_identifier);
}

std::string Object::GetOverrideString(uint8 index) const
{
    const char * identifier = GetIdentifier();
    rct_string_id stringId = language_get_object_override_string_id(identifier, index);

    const utf8 * result = nullptr;
    if (stringId != STR_NONE)
    {
        result = language_get_string(stringId);
    }
    return String::ToStd(result);
}

std::string Object::GetString(uint8 index) const
{
    auto sz = GetOverrideString(index);
    if (sz.empty())
    {
        sz = GetStringTable()->GetString(index);
    }
    return sz;
}

rct_object_entry Object::GetScgWallsHeader()
{
    return Object::CreateHeader("SCGWALLS", 207140231, 3518650219);
}

rct_object_entry Object::GetScgPathXHeader()
{
    return Object::CreateHeader("SCGPATHX", 207140231, 890227440);
}

rct_object_entry Object::CreateHeader(const char name[DAT_NAME_LENGTH + 1], uint32 flags, uint32 checksum)
{
    rct_object_entry header = { 0 };
    header.flags = flags;
    Memory::Copy(header.name, name, DAT_NAME_LENGTH);
    header.checksum = checksum;
    return header;
}


#ifdef __WARN_SUGGEST_FINAL_METHODS__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsuggest-final-methods"
#endif

std::string Object::GetName() const
{
    return GetString(OBJ_STRING_ID_NAME);
}

#ifdef __WARN_SUGGEST_FINAL_METHODS__
    #pragma GCC diagnostic pop
#endif
