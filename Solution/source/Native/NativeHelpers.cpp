#include "NativeHelpers.h"
#include "../../../third_party/ScriptHookV/inc/natives.h"
#include <cmath>
namespace Enchant::Native {
bool IsStoryMode(){ return !NETWORK::NETWORK_IS_SESSION_STARTED(); }
Vec3 GetCoords(Entity e){ auto v=ENTITY::GET_ENTITY_COORDS(e,true); return {v.x,v.y,v.z}; }
float Distance(const Vec3&a,const Vec3&b){float x=a.x-b.x,y=a.y-b.y,z=a.z-b.z;return std::sqrt(x*x+y*y+z*z);}
void Notify(const char*text){ UI::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(false,false); }
}