#include "Menu.h"
#include "../Config/Config.h"
#include "../Native/NativeHelpers.h"
#include "../World/WorldController.h"
#include "../../third_party/ScriptHookV/inc/script.h"
#include "../../third_party/ScriptHookV/inc/natives.h"
namespace Enchant {
void Menu::Init(){items_={{"Player",[]{}},{"Vehicle",[]{}},{"World",[]{}},{"Camera",[]{}},{"Audio",[]{}},{"Misc",[]{}},{"Settings",[]{}},{"System Status",[]{}},{"Run Ambient Test",[]{WorldController::AmbientDisturbance(1.f);}}};}
void Menu::Draw(){UI::SET_TEXT_FONT(0);UI::SET_TEXT_SCALE(.32f,.32f);UI::SET_TEXT_COLOUR(255,255,255,255);UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~b~ENCHANT~s~");UI::END_TEXT_COMMAND_DISPLAY_TEXT(.06f,.12f);float y=.16f;for(size_t n=0;n<items_.size();++n){UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((n==static_cast<size_t>(index_)?"~b~> ":"~s~  ")+items_[n].label);UI::END_TEXT_COMMAND_DISPLAY_TEXT(.06f,y);y+=.028f;}}
void Menu::Tick(){auto&c=ConfigManager::Get();if(PAD::IS_CONTROL_JUST_PRESSED(0,c.toggleKey))open_=!open_;if(!open_)return;if(PAD::IS_CONTROL_JUST_PRESSED(0,172))index_=(index_+items_.size()-1)%items_.size();if(PAD::IS_CONTROL_JUST_PRESSED(0,173))index_=(index_+1)%items_.size();if(PAD::IS_CONTROL_JUST_PRESSED(0,191))items_[index_].action();Draw();}
}