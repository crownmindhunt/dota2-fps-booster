#include "registry_writer.hpp"
#include <windows.h>

namespace d2fb::out {

Result<void> set_dword(HKEY root, const std::string& subkey,
                       const std::string& value, DWORD data) {
    HKEY h{};
    auto rc = RegCreateKeyExA(root, subkey.c_str(), 0, nullptr,
                              REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, nullptr,
                              &h, nullptr);
    if (rc != ERROR_SUCCESS) return Result<void>::err("RegCreateKeyEx failed");

    rc = RegSetValueExA(h, value.c_str(), 0, REG_DWORD,
                        reinterpret_cast<const BYTE*>(&data), sizeof(data));
    RegCloseKey(h);
    if (rc != ERROR_SUCCESS) return Result<void>::err("RegSetValueEx failed");
    return Result<void>::ok();
}

} // namespace d2fb::out