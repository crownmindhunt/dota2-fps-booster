# Contributing to dota2-fps-booster

Thanks for helping make Dota 2 run smoother on potato rigs.

## Ground rules

- Every tweak must be **reversible**. If you write a registry or config
  mutation, ship a matching rollback entry in `src/tweaker-core/revert_map.cpp`.
- Frame-time wins must be measured with the bundled `bench/presentmon_capture`
  harness, not vibes.
- Don't touch anything that trips VAC. See SECURITY.md for the denylist of
  hooks we refuse to ship.

## Workflow

1. Fork, branch from `main`, name branches `feat/<tweak-id>` or `fix/<tweak-id>`.
2. `cmake -B build -A x64 && cmake --build build --config Release`
3. `ctest --test-dir build -C Release`
4. Open a PR. Attach a capture file and the before/after 1% low numbers.

## Code style

- C++20, `snake_case` for functions, `PascalCase` for types.
- No exceptions across the pipeline boundary; return `Result<T>` from `job-utils`.
- C# shell code follows the repo `.editorconfig`.

## Tweak proposals

Open an issue with the `tweak-proposal` template including:
- Target subsystem (convars, scheduler, GPU pipeline, driver hints)
- Expected delta
- Rollback strategy