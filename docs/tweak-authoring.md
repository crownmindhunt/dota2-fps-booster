# Authoring a tweak

Every tweak lives as a `[[tweak]]` block in `config/tweaks.toml` plus a
processor in `src/processors/`. The pipeline is:

    ingest-handlers -> processors -> output-drivers

1. **Ingest** — read the current value from disk, registry, or the game
   process (read-only; see `src/ingest-handlers/`).
2. **Process** — compute the recommended value and any preconditions
   (`src/processors/priority_processor.cpp` is a good template).
3. **Output** — write it, always with a backup. See `cfg_writer.cpp`.

If your tweak writes to the game process itself, it's out of scope.
See SECURITY.md.