#include "vac_denylist.hpp"
#include <cassert>
#include <iostream>

using namespace d2fb::core;

int main() {
    assert(is_denied_by_vac("engine.dll.patch"));
    assert(is_denied_by_vac("hook.d3d11_present"));
    assert(is_denied_by_vac("inject.manual_map"));
    assert(!is_denied_by_vac("gpu.shader_cache_size"));
    assert(!is_denied_by_vac("cpu.priority_high"));
    std::cout << "denylist ok\n";
    return 0;
}