# Security Policy

`dota2-fps-booster` deliberately stays outside the cheat/injection space.
The scope is **client-side performance tuning only**.

## What this tool does NOT do

- No DLL injection into `dota2.exe`
- No memory patching of the game process
- No hooking of D3D11/D3D12 present chains
- No convar writes flagged by VAC (see `src/tweaker-core/vac_denylist.cpp`)
- No skin changers, no ESP overlays, no input automation

If a PR adds any of the above it will be closed without review.

## Reporting a vulnerability

If you find a tweak that writes outside our sandbox (for example a config
path that could be abused to load arbitrary code), email the maintainers at
`security@dota2-fps-booster.dev` or open a private security advisory.

We aim to triage within 72 hours. Please do not open public issues for
privilege-escalation bugs — Windows token duplication in `output-drivers`
is a known sensitive area.

## Supported versions

Only the latest tagged release and `main` receive security fixes.