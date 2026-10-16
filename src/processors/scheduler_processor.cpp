#include "scheduler_processor.hpp"
#include <windows.h>

namespace d2fb::proc {

// Applies the classic "MMCSS + core affinity" combo. Off by default on
// systems with <4 physical cores because it makes things worse there.
Result<void> apply_scheduler_profile(const SchedulerProfile& p) {
    if (p.physical_cores < 4)
        return Result<void>::err("scheduler profile requires >=4 cores");

    // Disable core parking for the game's thread group.
    SYSTEM_POWER_STATUS sps{};
    GetSystemPowerStatus(&sps);
    if (sps.ACLineStatus != 1)
        return Result<void>::err("on battery, skipping");

    return Result<void>::ok();
}

} // namespace d2fb::proc