#include "VehicleController.h"
#include "../Player/PlayerController.h"
#include "../Native/NativeHelpers.h"
#include "../../third_party/ScriptHookV/inc/natives.h"
namespace Enchant::VehicleController {
void ReactNearby(float i){auto p=PlayerController::Local();auto c=Native::GetCoords(p);auto v=VEHICLE::GET_CLOSEST_VEHICLE(c.x,c.y,c.z,18.f,0,70);if(ENTITY::DOES_ENTITY_EXIST(v)){VEHICLE::SET_VEHICLE_HORN(v,(int)(250+500*i),GAMEPLAY::GET_HASH_KEY("HELDDOWN"),false);}}
void AlarmNearby(float i){auto p=PlayerController::Local();auto c=Native::GetCoords(p);auto v=VEHICLE::GET_CLOSEST_VEHICLE(c.x,c.y,c.z,25.f,0,70);if(ENTITY::DOES_ENTITY_EXIST(v)){VEHICLE::START_VEHICLE_ALARM(v);}}
}