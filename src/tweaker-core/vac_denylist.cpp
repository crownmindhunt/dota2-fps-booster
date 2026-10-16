#include "vac_denylist.hpp"
#include <unordered_set>
#include <algorithm>

namespace d2fb::core {

// Never ship anything that touches these. See SECURITY.md.
static const std::unordered_set<std::string> kDeniedPrefixes = {
    "engine.dll.",
    "client.dll.",
    "hook.",
    "inject.",
    "memory.patch.",
    "convars.sv_cheats",
    "convars.r_draw*",
};

bool is_denied_by_vac(const std::string& tweak_id) {
    return std::any_of(kDeniedPrefixes.begin(), kDeniedPrefixes.end(),
        [&](const std::string& p) { return tweak_id.rfind(p, 0) == 0; });
}

} // namespace d2fb::core