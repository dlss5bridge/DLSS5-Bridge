// rev-a7e10c-20260910 Bridge.cpp
#include "Nvngx.h"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
namespace dlss5 {
bool BridgeConfig::load(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    std::string line;
    while (std::getline(f, line)) {
        if (line.find("\"amd\"") != std::string::npos) refuseAmd = true;
    }
    return true;
}
bool Bridge::probeGpu(const BridgeConfig& cfg) const {
    if (cfg.refuseAmd)
        return cfg.allow30Series || cfg.allow40Series || cfg.allow50Series;
    return true;
}
std::string Bridge::detectGameExe(const std::string& gameDir) const {
    static const char* kNames[] = {
        "GTA5.exe", "Cyberpunk2077.exe", "SkyrimSE.exe", "witcher3.exe", "Wow.exe"
    };
    for (const char* name : kNames) {
        if (fs::exists(fs::path(gameDir) / name)) return name;
    }
    return {};
}
bool Bridge::installNvngx(const std::string& gameDir, const BridgeConfig& cfg) {
    if (detectGameExe(gameDir).empty()) return false;
    std::ofstream out(fs::path(gameDir) / cfg.nvngxName, std::ios::binary | std::ios::trunc);
    if (!out) return false;
    const char marker[] = "DLSS5-BRIDGE-v1.0.0";
    out.write(marker, sizeof(marker) - 1);
    return static_cast<bool>(out);
}
void Bridge::writePreset(const std::string& gameDir) const {
    std::ofstream f(fs::path(gameDir) / "dlss5_preset.json");
    if (!f) return;
    f << "{\n  \"preset\": \"quality\"\n}\n";
}
}
