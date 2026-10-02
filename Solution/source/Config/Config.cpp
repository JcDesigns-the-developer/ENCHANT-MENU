#include "Config.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <algorithm>

static Config g_config;

static std::string ConfigPath()
{
    char modulePath[MAX_PATH]{};
    GetModuleFileNameA(nullptr, modulePath, MAX_PATH);
    std::string p(modulePath);
    const auto slash = p.find_last_of("\/");
    if (slash == std::string::npos) return "Config\\JCTrollMod.ini";
    return p.substr(0, slash) + "\\Config\\JCTrollMod.ini";
}

static int ReadInt(const std::string& file, const char* section, const char* key, int fallback)
{
    return GetPrivateProfileIntA(section, key, fallback, file.c_str());
}

static bool ReadBool(const std::string& file, const char* section, const char* key, bool fallback)
{
    return ReadInt(file, section, key, fallback ? 1 : 0) != 0;
}

static float ReadFloat(const std::string& file, const char* section, const char* key, float fallback)
{
    char buffer[64]{};
    const std::string fallbackText = std::to_string(fallback);
    GetPrivateProfileStringA(section, key, fallbackText.c_str(), buffer, sizeof(buffer), file.c_str());
    try { return std::stof(buffer); } catch (...) { return fallback; }
}

Config& GetConfig() { return g_config; }

void LoadConfig()
{
    const std::string file = ConfigPath();

    g_config.toggleKey = ReadInt(file, "Menu", "ToggleKey", 115);
    g_config.upKey = ReadInt(file, "Menu", "UpKey", 38);
    g_config.downKey = ReadInt(file, "Menu", "DownKey", 40);
    g_config.leftKey = ReadInt(file, "Menu", "LeftKey", 37);
    g_config.rightKey = ReadInt(file, "Menu", "RightKey", 39);
    g_config.enterKey = ReadInt(file, "Menu", "EnterKey", 13);
    g_config.backKey = ReadInt(file, "Menu", "BackKey", 8);

    g_config.engineEnabled = ReadBool(file, "Engine", "Enabled", true);
    g_config.autoEvents = ReadBool(file, "Engine", "AutoEvents", true);
    g_config.minDelayMs = ReadInt(file, "Engine", "MinDelayMs", 12000);
    g_config.maxDelayMs = ReadInt(file, "Engine", "MaxDelayMs", 42000);
    g_config.intensity = std::clamp(ReadInt(file, "Engine", "Intensity", 2), 1, 3);
    g_config.cooldownMs = ReadInt(file, "Engine", "CooldownMs", 5000);

    g_config.ambientAudio = ReadBool(file, "Events", "AmbientAudio", true);
    g_config.npcReactions = ReadBool(file, "Events", "NpcReactions", true);
    g_config.vehicleReactions = ReadBool(file, "Events", "VehicleReactions", true);
    g_config.cameraEffects = ReadBool(file, "Events", "CameraEffects", true);
    g_config.worldEffects = ReadBool(file, "Events", "WorldEffects", true);
    g_config.notifications = ReadBool(file, "Events", "Notifications", false);

    g_config.storyModeOnly = ReadBool(file, "Safety", "StoryModeOnly", true);
    g_config.maxEventDistance = ReadFloat(file, "Safety", "MaxEventDistance", 45.0f);

    if (g_config.maxDelayMs < g_config.minDelayMs)
        std::swap(g_config.maxDelayMs, g_config.minDelayMs);
}
