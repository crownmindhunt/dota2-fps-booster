#include "cfg_writer.hpp"
#include <fstream>
#include <chrono>

namespace d2fb::out {

// Writes a timestamped backup before touching autoexec.cfg.
Result<void> write_cfg_with_backup(const std::string& path,
                                   const std::string& contents) {
    auto ts = std::chrono::system_clock::now().time_since_epoch().count();
    std::string backup = path + ".d2fb." + std::to_string(ts) + ".bak";

    if (std::filesystem::exists(path)) {
        std::filesystem::copy_file(path, backup,
            std::filesystem::copy_options::overwrite_existing);
    }

    std::ofstream out(path, std::ios::trunc);
    if (!out) return Result<void>::err("cannot open cfg for write");
    out << contents;
    return Result<void>::ok();
}

} // namespace d2fb::out