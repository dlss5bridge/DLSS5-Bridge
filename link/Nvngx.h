// rev-a7e10c-20260910 Nvngx.h
#pragma once
#include <string>
namespace dlss5 {
struct BridgeConfig {
    bool allow30Series = true;
    bool allow40Series = true;
    bool allow50Series = true;
    bool refuseAmd = true;
    std::string nvngxName = "nvngx_dlss.dll";
    bool load(const std::string& path);
};
class Bridge {
public:
    bool probeGpu(const BridgeConfig& cfg) const;
    bool installNvngx(const std::string& gameDir, const BridgeConfig& cfg);
    void writePreset(const std::string& gameDir) const;
private:
    std::string detectGameExe(const std::string& gameDir) const;
};
}
