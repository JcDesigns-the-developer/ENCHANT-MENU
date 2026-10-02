#include "PlayerController.h"
#include "../Native/NativeHelpers.h"
#include "../../third_party/ScriptHookV/inc/natives.h"
namespace Enchant::PlayerController { Ped Local(){return PLAYER::PLAYER_PED_ID();} void CameraJolt(float i){GAMEPLAY::SHAKE_GAMEPLAY_CAM("SMALL_EXPLOSION_SHAKE",i);} void SmallMovementEffect(float i){auto p=Local();if(!ENTITY::DOES_ENTITY_EXIST(p))return;AI::TASK_PLAY_ANIM(p,"move_m@brave","idle",8.f,-8.f,350,(int)(i*2),0.f,false,false,false);}}