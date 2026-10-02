#include "EventManager.h"
#include "../Config/Config.h"
#include "script.h"
#include "natives.h"
#include <random>
#include <algorithm>

namespace
{
    std::mt19937& Rng()
    {
        static std::mt19937 r{ std::random_device{}() };
        return r;
    }

    int RandomInt(int a, int b)
    {
        std::uniform_int_distribution<int> d(a, b);
        return d(Rng());
    }

    DWORD nextEvent = 0;
    DWORD lastEvent = 0;

    void Schedule()
    {
        const auto& c = GetConfig();
        nextEvent = GetGameTimer() + RandomInt(c.minDelayMs, c.maxDelayMs);
    }

    void AmbientAudio()
    {
        const int sound = RandomInt(0, 2);
        switch (sound)
        {
        case 0: AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", true); break;
        case 1: AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", true); break;
        default: AUDIO::PLAY_SOUND_FRONTEND(-1, "ERROR", "HUD_FRONTEND_DEFAULT_SOUNDSET", true); break;
        }
    }

    void NpcReaction()
    {
        const Ped player = PLAYER::PLAYER_PED_ID();
        const Vector3 p = ENTITY::GET_ENTITY_COORDS(player, true);
        const int seed = RandomInt(0, 7);
        if (seed < 5)
        {
            const float x = p.x + static_cast<float>(RandomInt(-10, 10));
            const float y = p.y + static_cast<float>(RandomInt(-10, 10));
            const float z = p.z;
            const Hash model = GAMEPLAY::GET_HASH_KEY("a_m_m_business_01");
            if (!STREAMING::IS_MODEL_IN_CDIMAGE(model) || !STREAMING::IS_MODEL_VALID(model))
                return;
            STREAMING::REQUEST_MODEL(model);
            const DWORD until = GetGameTimer() + 1000;
            while (!STREAMING::HAS_MODEL_LOADED(model) && GetGameTimer() < until)
                WAIT(0);
            if (!STREAMING::HAS_MODEL_LOADED(model))
                return;
            const Ped ped = PED::CREATE_PED(4, model, x, y, z, static_cast<float>(RandomInt(0, 359)), false, false);
            if (ped)
            {
                TASK::TASK_TURN_PED_TO_FACE_ENTITY(ped, player, 1200);
                ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
        }
    }

    void VehicleReaction()
    {
        const Ped player = PLAYER::PLAYER_PED_ID();
        const Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player, false);
        if (veh)
        {
            AUDIO::START_VEHICLE_HORN(veh, 250, GAMEPLAY::GET_HASH_KEY("HELDDOWN"), false);
        }
    }

    void CameraReaction()
    {
        CAM::SHAKE_GAMEPLAY_CAM("HAND_SHAKE", GetConfig().intensity == 3 ? 0.8f : 0.35f);
        WAIT(120);
        CAM::STOP_GAMEPLAY_CAM_SHAKING(true);
    }

    void WorldReaction()
    {
        const int choice = RandomInt(0, 2);
        if (choice == 0)
        {
            MISC::SET_CLOCK_TIME(RandomInt(0, 23), RandomInt(0, 59), 0);
        }
        else if (choice == 1)
        {
            MISC::SET_WEATHER_TYPE_NOW_PERSIST("CLOUDS");
        }
        else
        {
            MISC::SET_WEATHER_TYPE_NOW_PERSIST("CLEARING");
        }
    }

    void Fire(int index)
    {
        const auto& c = GetConfig();
        if (GetGameTimer() - lastEvent < static_cast<DWORD>(c.cooldownMs)) return;
        lastEvent = GetGameTimer();

        switch (index)
        {
        case 0: if (c.ambientAudio) AmbientAudio(); break;
        case 1: if (c.npcReactions) NpcReaction(); break;
        case 2: if (c.vehicleReactions) VehicleReaction(); break;
        case 3: if (c.cameraEffects) CameraReaction(); break;
        case 4: if (c.worldEffects) WorldReaction(); break;
        default: break;
        }
    }
}

void InitializeEvents()
{
    Schedule();
}

void UpdateEvents()
{
    const auto& c = GetConfig();
    if (!c.engineEnabled || !c.autoEvents) return;
    if (GetGameTimer() >= nextEvent)
    {
        const int maxEvent = std::max(0, c.intensity + 1);
        Fire(RandomInt(0, maxEvent));
        Schedule();
    }
}

void TriggerManualEvent(int index)
{
    Fire(index);
}
