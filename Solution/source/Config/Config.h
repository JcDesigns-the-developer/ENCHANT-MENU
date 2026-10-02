#pragma once
#include <string>

struct Config
{
    int toggleKey = 115;
    int upKey = 38;
    int downKey = 40;
    int leftKey = 37;
    int rightKey = 39;
    int enterKey = 13;
    int backKey = 8;

    bool engineEnabled = true;
    bool autoEvents = true;
    int minDelayMs = 12000;
    int maxDelayMs = 42000;
    int intensity = 2;
    int cooldownMs = 5000;

    bool ambientAudio = true;
    bool npcReactions = true;
    bool vehicleReactions = true;
    bool cameraEffects = true;
    bool worldEffects = true;
    bool notifications = false;

    bool storyModeOnly = true;
    float maxEventDistance = 45.0f;
};

Config& GetConfig();
void LoadConfig();
