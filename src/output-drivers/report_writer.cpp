#include "report_writer.hpp"
#include <fstream>
#include <sstream>

namespace d2fb::out {

std::string render_report(const BenchmarkReport& r) {
    std::ostringstream ss;
    ss << "# dota2-fps-booster report\n";
    ss << "generated_at: " << r.timestamp_iso8601 << "\n";
    ss << "avg_fps: " << r.avg_fps << "\n";
    ss << "one_percent_low: " << r.p1_low << "\n";
    ss << "applied_tweaks:\n";
    for (const auto& id : r.applied_tweaks) ss << "  - " << id << "\n";
    return ss.str();
}

Result<void> write_report(const std::string& path, const BenchmarkReport& r) {
    std::ofstream out(path, std::ios::trunc);
    if (!out) return Result<void>::err("cannot write report");
    out << render_report(r);
    return Result<void>::ok();
}

} // namespace d2fb::out