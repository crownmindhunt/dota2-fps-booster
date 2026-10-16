# FAQ

**Does this get me VAC banned?**
No. We only touch things outside the game process: config files, a few
HKCU registry keys, process priority, and timer resolution. Nothing is
injected into `dota2.exe`.

**Why is my 1% low worse after enabling the scheduler profile?**
You probably have <4 physical cores. The profile refuses to apply below
that threshold — check `src/processors/scheduler_processor.cpp`.

**Can I revert everything?**
Yes. Every mutation is recorded in the revert map and a `.d2fb.<ts>.bak`
backup is dropped next to the original file.

**Does it work on Linux/Proton?**
Not currently. The Windows-specific drivers are the majority of the code.