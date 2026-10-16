#include "convar_ingest.hpp"
#include <fstream>
#include <sstream>

namespace d2fb::ingest {

// Reads the user's existing Dota 2 autoexec.cfg and returns the lines
// we can safely overwrite without nuking their personal binds.
std::vector<ConvarLine> parse_autoexec(const std::string& path) {
    std::vector<ConvarLine> out;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '/' || line.rfind("bind", 0) == 0) continue;
        auto eq = line.find(' ');
        if (eq == std::string::npos) continue;
        ConvarLine c;
        c.name = line.substr(0, eq);
        c.value = line.substr(eq + 1);
        c.origin_line = line;
        out.push_back(std::move(c));
    }
    return out;
}

bool is_perf_convar(const std::string& name) {
    static const char* kPrefixes[] = {
        "r_", "mat_", "fps_", "engine_", "cl_", "dota_"
    };
    for (auto p : kPrefixes) if (name.rfind(p, 0) == 0) return true;
    return false;
}

} // namespace d2fb::ingest