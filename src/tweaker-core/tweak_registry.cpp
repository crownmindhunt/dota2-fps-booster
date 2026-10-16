#include "tweak_registry.hpp"
#include "revert_map.hpp"
#include "vac_denylist.hpp"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace d2fb::core {

void TweakRegistry::load_from_disk(const std::string& config_root) {
    tweaks_.clear();
    auto manifest = fs::path(config_root) / "tweaks.toml";
    if (!fs::exists(manifest)) return;

    // Minimal TOML-ish reader; full parser lives in job-utils.
    std::ifstream in(manifest);
    std::string line;
    Tweak current{};
    while (std::getline(in, line)) {
        if (line.rfind("[[tweak]]", 0) == 0) {
            if (!current.id.empty()) tweaks_.push_back(current);
            current = Tweak{};
        } else if (line.rfind("id =", 0) == 0) {
            current.id = line.substr(5);
        } else if (line.rfind("name =", 0) == 0) {
            current.display_name = line.substr(7);
        } else if (line.rfind("recommended =", 0) == 0) {
            current.recommended_value = line.substr(14);
        }
    }
    if (!current.id.empty()) tweaks_.push_back(current);
}

std::vector<Tweak> TweakRegistry::all() const { return tweaks_; }

std::optional<Tweak> TweakRegistry::find(const std::string& id) const {
    for (const auto& t : tweaks_) if (t.id == id) return t;
    return std::nullopt;
}

Result<void> TweakRegistry::apply(const std::string& id) {
    if (is_denied_by_vac(id)) return Result<void>::err("denied by VAC denylist");
    auto t = find(id);
    if (!t) return Result<void>::err("unknown tweak id");
    return RevertMap::instance().record_and_apply(*t);
}

Result<void> TweakRegistry::revert(const std::string& id) {
    return RevertMap::instance().revert(id);
}

} // namespace d2fb::core