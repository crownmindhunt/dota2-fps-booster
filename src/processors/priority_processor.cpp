#include "priority_processor.hpp"
#include <windows.h>
#include <tlhelp32.h>

namespace d2fb::proc {

// Bumps dota2.exe priority to HIGH (not REALTIME — that starves the audio thread).
Result<void> raise_dota2_priority() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return Result<void>::err("snapshot failed");

    PROCESSENTRY32W pe{}; pe.dwSize = sizeof(pe);
    if (!Process32FirstW(snap, &pe)) { CloseHandle(snap); return Result<void>::err("enum failed"); }

    do {
        if (_wcsicmp(pe.szExeFile, L"dota2.exe") == 0) {
            HANDLE p = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pe.th32ProcessID);
            if (p) {
                SetPriorityClass(p, HIGH_PRIORITY_CLASS);
                CloseHandle(p);
            }
            CloseHandle(snap);
            return Result<void>::ok();
        }
    } while (Process32NextW(snap, &pe));

    CloseHandle(snap);
    return Result<void>::err("dota2.exe not running");
}

} // namespace d2fb::proc