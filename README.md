# ENCHANT-MENU / JCTrollMod

GTA V Story Mode native-style utility menu with a configurable, intentionally unpredictable ambient-event system.

## Output

The Visual Studio project is configured to produce:

`JCTrollMod.asi`

## Scope

- GTA V Story Mode / local single-player only.
- No GTA Online support.
- No networking, telemetry, credential access, persistence outside the configured INI, or anti-cheat bypass.
- The menu uses neutral utility-style categories while the ambient event engine runs independently.

## Design references

The menu organization and configuration approach were informed by the classic GTA V trainer ecosystem, especially MenyooSP and SIMPLE-NativeTRAINER. This repository does **not** copy their source files.

- MAFINS/MenyooSP is GPL-3.0 for the majority of its source.
- SIMPLE-NativeTRAINER is referenced for its trainer/menu configuration conventions.

See `THIRD_PARTY_NOTICES.md`.

## Requirements

1. Grand Theft Auto V Story Mode.
2. ScriptHookV installed in the GTA V directory.
3. The ScriptHookV SDK headers/library available locally.
4. Visual Studio 2022 with the Desktop C++ workload.

The ScriptHookV SDK is intentionally **not redistributed** here.

## SDK setup

Put the ScriptHookV SDK in:

`third_party/ScriptHookV/`

Expected paths:

```
third_party/ScriptHookV/inc/script.h
third_party/ScriptHookV/inc/natives.h
third_party/ScriptHookV/lib/ScriptHookV.lib
```

Then open `Solution/JCTrollMod.vcxproj` and build x64 Release.

The generated file is:

`Solution/bin/Release/JCTrollMod.asi`

Copy that file into the GTA V directory beside ScriptHookV.

## Controls

- F4: open/close menu
- Arrow Up/Down: select
- Enter: activate/toggle
- Backspace: back
- Left/Right: adjust numeric settings

All keys can be changed in `Config/JCTrollMod.ini`.

## Menu

The visible menu is intentionally conventional:

- Player
- Vehicle
- World
- Camera
- Audio
- Misc
- Settings
- System Status

The event engine is controlled from Settings and can operate automatically while the menu is closed.

## License

The original code in this repository is GPL-3.0-or-later. Third-party projects and SDKs retain their own licenses.
