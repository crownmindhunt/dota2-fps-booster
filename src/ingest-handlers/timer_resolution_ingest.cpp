#include "timer_resolution_ingest.hpp"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace d2fb::ingest {

// 0.5ms timer resolution trick — narrow win on old CPUs, harmless otherwise.
TimerResolutionSnapshot probe() {
    TIMECAPS caps{};
    if (timeGetDevCaps(&caps, sizeof(caps)) != TIMERR_NOERROR)
        return { 0, 0, false };
    return { caps.wPeriodMin, caps.wPeriodMax, true };
}

} // namespace d2fb::ingest