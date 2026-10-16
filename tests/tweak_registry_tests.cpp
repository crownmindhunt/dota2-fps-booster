#include "tweak_registry.hpp"
#include <cassert>
#include <iostream>

using namespace d2fb::core;

int main() {
    TweakRegistry reg;
    reg.load_from_disk("../../config");

    auto all = reg.all();
    std::cout << "loaded " << all.size() << " tweaks\n";
    assert(all.size() >= 4);

    auto t = reg.find("cpu.priority_high");
    assert(t.has_value());

    // Denied ids must fail to apply.
    auto bad = reg.apply("hook.present_swapchain");
    assert(!bad.has_value());

    std::cout << "ok\n";
    return 0;
}