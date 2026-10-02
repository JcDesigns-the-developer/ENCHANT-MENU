#pragma once
#include "../Core/Types.h"
#include "../../../third_party/ScriptHookV/inc/natives.h"
namespace Enchant::Native { bool IsStoryMode(); Vec3 GetCoords(Entity e); float Distance(const Vec3&a,const Vec3&b); void Notify(const char* text); }