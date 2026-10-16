#include "registry_ingest.hpp"
#include <windows.h>

namespace d2fb::ingest {

// Read a DWORD from HKCU\Software\...\Dota 2 style keys.
std::optional<DWORD> read_dword(HKEY root, const std::string& subkey,
                                const std::string& value) {
    HKEY h{};
    if (RegOpenKeyExA(root, subkey.c_str(), 0, KEY_READ, &h) != ERROR_SUCCESS)
        return std::nullopt;
    DWORD data{}, size = sizeof(data), type{};
    auto rc = RegQueryValueExA(h, value.c_str(), nullptr, &type,
                               reinterpret_cast<LPBYTE>(&data), &size);
    RegCloseKey(h);
    if (rc != ERROR_SUCCESS || type != REG_DWORD) return std::nullopt;
    return data;
}

} // namespace d2fb::ingest