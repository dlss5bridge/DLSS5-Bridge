// rev-a7e10c-20260910 main.cpp
#include "Nvngx.h"
#include <iostream>
int main(int argc, char** argv) {
    dlss5::Bridge bridge;
    dlss5::BridgeConfig cfg;
    cfg.load("gpu/Supported.json");
    std::cout << "DLSS 5 Bridge v1.0.0\n";
    if (!bridge.probeGpu(cfg)) return 1;
    const char* gameDir = (argc > 1) ? argv[1] : ".";
    if (!bridge.installNvngx(gameDir, cfg)) return 2;
    bridge.writePreset(gameDir);
    return 0;
}
