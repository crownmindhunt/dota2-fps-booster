#pragma once
#include <string>
#include <vector>
#include <optional>
#include "job-utils/result.hpp"

namespace d2fb::core {

enum class TweakCategory {
    Convar,
    Scheduler,
    GpuPipeline,
    DriverHint,
    Filesystem,
};

struct Tweak {
    std::string id;                 // e.g. "gpu.shader_cache_size"
    std::string display_name;
    TweakCategory category;
    std::string current_value;
    std::string recommended_value;
    bool requires_restart{false};
};

class TweakRegistry {
public:
    void load_from_disk(const std::string& config_root);
    std::vector<Tweak> all() const;
    std::optional<Tweak> find(const std::string& id) const;

    Result<void> apply(const std::string& id);
    Result<void> revert(const std::string& id);

private:
    std::vector<Tweak> tweaks_;
};

} // namespace d2fb::core