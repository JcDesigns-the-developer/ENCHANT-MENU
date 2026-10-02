#include "EventManager.h"
#include "EventTypes.h"
#include "EventActions.h"
#include "../Config/Config.h"
#include "../Core/Logger.h"
#include <windows.h>
#include <random>
#include <algorithm>
namespace Enchant {
static std::mt19937 rng{std::random_device{}()};
void EventManager::Init(){nextTick_=GetTickCount64()+ConfigManager::Get().minDelayMs;}
void EventManager::Trigger(EventType t,float i){Logger::Info(std::string("Event: ")+EventName(t));ExecuteEvent(t,i);}
void EventManager::Tick(){auto&c=ConfigManager::Get();if(!c.enabled||!c.autoEvents)return;auto now=GetTickCount64();if(now<nextTick_||now-lastEvent_<static_cast<unsigned long long>(c.cooldownMs))return;std::uniform_int_distribution<int>d(c.minDelayMs,std::max(c.minDelayMs,c.maxDelayMs));nextTick_=now+d(rng);lastEvent_=now;std::uniform_int_distribution<int>e(0,4);Trigger(static_cast<EventType>(e(rng)),static_cast<float>(c.intensity));}
}