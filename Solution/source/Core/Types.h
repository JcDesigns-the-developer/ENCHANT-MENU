#pragma once
#include <string>
#include <vector>
#include <cstdint>
namespace Enchant {
using Hash=std::uint32_t;
using Entity=std::int32_t;
using Ped=Entity;
using Vehicle=Entity;
struct Vec3 { float x{},y{},z{}; };
enum class EventType { AmbientAudio, PedReaction, VehicleReaction, CameraEffect, WorldEffect };
struct EventRequest { EventType type{}; float intensity{1.f}; std::uint32_t delayMs{}; };
}