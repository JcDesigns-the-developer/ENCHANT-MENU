#include "WorldController.h"
#include "../../third_party/ScriptHookV/inc/natives.h"
namespace Enchant::WorldController { void WeatherPulse(float i){ if(i>1.5f)GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("FOG"); } void TimePulse(float i){ if(i>1.8f)GAMEPLAY::SET_CLOCK_TIME(3,30,0); } void AmbientDisturbance(float i){GAMEPLAY::PLAY_SOUND_FRONTEND(-1,"ATM_WINDOW","HUD_FRONTEND_DEFAULT_SOUNDSET",true);}}