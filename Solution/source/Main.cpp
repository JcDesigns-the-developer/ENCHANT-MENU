#include <windows.h>
#include "../../third_party/ScriptHookV/inc/script.h"
#include "Core/Logger.h"
#include "Config/Config.h"
#include "Menu/Menu.h"
#include "Events/EventManager.h"
#include "Native/NativeHelpers.h"
namespace { Enchant::EventManager g_events; Enchant::Menu g_menu; }
void Main(){Enchant::ConfigManager::Load("JCTrollMod.ini");Enchant::Logger::Init();g_menu.Init();g_events.Init();for(;;){if(Enchant::ConfigManager::Get().storyModeOnly&&!Enchant::Native::IsStoryMode()){WAIT(1000);continue;}g_events.Tick();g_menu.Tick();WAIT(0);}}
BOOL APIENTRY DllMain(HMODULE h,DWORD r,LPVOID){if(r==DLL_PROCESS_ATTACH){DisableThreadLibraryCalls(h);scriptRegister(h,Main);}else if(r==DLL_PROCESS_DETACH){scriptUnregister(h);}return TRUE;}