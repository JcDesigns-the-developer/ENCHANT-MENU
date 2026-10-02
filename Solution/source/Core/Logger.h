#pragma once
#include <string>
namespace Enchant { class Logger { public: static void Init(); static void Info(const std::string&); static void Warn(const std::string&); static void Error(const std::string&); }; }