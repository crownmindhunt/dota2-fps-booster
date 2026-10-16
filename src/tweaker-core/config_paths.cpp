#include "config_paths.hpp"
#include <windows.h>
#include <shlobj.h>

namespace d2fb::core {

std::string steam_userdata_root() {
    char buf[MAX_PATH]{};
    if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_PROGRAM_FILESX86, nullptr, 0, buf))) {
        return std::string(buf) + "\\Steam\\userdata";
    }
    return {};
}

std::string dota2_cfg_dir(const std::string& steamid3) {
    return steam_userdata_root() + "\\" + steamid3 + "\\570\\local\\cfg";
}

} // namespace d2fb::core