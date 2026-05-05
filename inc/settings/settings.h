#if defined(_MSC_VER) && defined(__clang__)
#pragma once
#endif

#ifndef __Settings_H__
#define __Settings_H__

#include <stdio.h>
#include <vector>
#include <windows.h>
#include <io.h>
#include "../third_party/inc/yyjson.h"

using FilePtr = FILE*;

template <typename T>
struct __JsonValue {
    T value;
    const char* name;
};

struct JsonValue {
    __JsonValue<bool>* booleans;
    size_t booleanArraySize;

    __JsonValue<char>* chars;
    size_t charArraySize;

    __JsonValue<double>* doubles;
    size_t doublesArraySize;
};

namespace Dev
{
namespace JoerAndMj
{

class SettingsJsonFileReader final
{
private:
public:
    bool useRandomCharacters = false;
    bool noBgColor = false;
    bool showMenu = false;
    char customCharacter = '*';
    double colorRed = 1.0;
    double colorGreen = 1.0;
    double colorBlue = 1.0;
    SettingsJsonFileReader(void) = default;
    ~SettingsJsonFileReader() = default;

    int __cdecl ReadSettings(_In_ FilePtr* jsonFiles, _In_ JsonValue* jsonVal);
};

class SettingsJsonFileFinder final
{
public:
    SettingsJsonFileFinder(void) = default;
    ~SettingsJsonFileFinder() = default;

    int __cdecl FindJsonFiles(_In_ Dev::JoerAndMj::SettingsJsonFileReader* fileReader);
};

}
}

#endif
