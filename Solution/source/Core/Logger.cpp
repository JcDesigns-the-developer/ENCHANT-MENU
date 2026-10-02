#include "Logger.h"
#include <fstream>
#include <windows.h>
namespace { std::ofstream g_log; void write(const char* level,const std::string& s){ if(!g_log.is_open()) return; SYSTEMTIME t{}; GetLocalTime(&t); g_log<<"["<<t.wHour<<":"<<t.wMinute<<":"<<t.wSecond<<"] ["<<level<<"] "<<s<<"\n"; g_log.flush(); } }
namespace Enchant { void Logger::Init(){ g_log.open("JCTrollMod.log",std::ios::app); Info("JCTrollMod initialized."); } void Logger::Info(const std::string&s){write("INFO",s);} void Logger::Warn(const std::string&s){write("WARN",s);} void Logger::Error(const std::string&s){write("ERROR",s);} }