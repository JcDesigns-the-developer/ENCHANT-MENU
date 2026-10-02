#pragma once
#include <string>
#include <vector>
#include <functional>
namespace Enchant { struct MenuItem {std::string label;std::function<void()> action;}; class Menu {public:void Init();void Tick();private:bool open_=false;int index_=0;std::vector<MenuItem> items_;void Draw();}; }