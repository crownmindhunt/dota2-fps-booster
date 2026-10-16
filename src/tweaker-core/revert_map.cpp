#include "revert_map.hpp"
#include <unordered_map>
#include <mutex>

namespace d2fb::core {

struct Entry { Tweak tweak; std::string prior_value; };

static std::unordered_map<std::string, Entry> g_entries;
static std::mutex g_mu;

RevertMap& RevertMap::instance() {
    static RevertMap r;
    return r;
}

Result<void> RevertMap::record_and_apply(const Tweak& t) {
    std::lock_guard lk(g_mu);
    Entry e{ t, t.current_value };
    g_entries[t.id] = e;
    // Actual write happens in the ingest-handlers layer via a queued job.
    return Result<void>::ok();
}

Result<void> RevertMap::revert(const std::string& id) {
    std::lock_guard lk(g_mu);
    auto it = g_entries.find(id);
    if (it == g_entries.end()) return Result<void>::err("nothing to revert");
    g_entries.erase(it);
    return Result<void>::ok();
}

} // namespace d2fb::core