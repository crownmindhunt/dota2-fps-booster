#include "shader_cache_processor.hpp"
#include <filesystem>

namespace fs = std::filesystem;

namespace d2fb::proc {

// Dota 2 shader cache lives under steamapps/shadercache/570.
// Nuking it forces a recompile — sometimes fixes 1% stutter, always
// causes a 3-minute load on first launch. Ask the user first.
Result<uint64_t> measure_shader_cache(const std::string& shadercache_dir) {
    if (!fs::exists(shadercache_dir))
        return Result<uint64_t>::err("shadercache path not found");

    uint64_t total = 0;
    for (auto& e : fs::recursive_directory_iterator(shadercache_dir)) {
        if (e.is_regular_file()) total += e.file_size();
    }
    return Result<uint64_t>::ok(total);
}

} // namespace d2fb::proc