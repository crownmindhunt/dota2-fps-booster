# Changelog

## [0.9.4] - 2026-02-11
### Added
- `scheduler_processor` now bails out on battery power.
- Report writer emits 1% low in addition to average FPS.

### Changed
- VAC denylist expanded to cover `convars.sv_cheats` prefix.

## [0.9.3] - 2026-01-22
### Fixed
- `cfg_writer` no longer clobbers user binds when rewriting autoexec.
- Registry writer correctly creates the key if missing.

## [0.9.2] - 2025-12-30
### Added
- Initial worker pool in `src/job-utils/queue.cpp`.
- WPF shell scaffold under `shell/`.