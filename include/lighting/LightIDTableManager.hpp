#pragma once

#include "main.hpp"

#include <unordered_map>
#include <optional>
#include <string>
#include <functional>

namespace Chroma {

    using EnvironmentLightDataT = std::unordered_map<int, std::unordered_map<int, int>>;

    class EnvironmentData {
        public:
            virtual constexpr EnvironmentLightDataT getEnvironmentLights() = 0;
    };

    using InstallEnvironmentFunc = std::pair<std::string, const EnvironmentLightDataT&>;

    class LightIDTableManager {
    private:
        inline static bool installed = false;
        inline static std::unordered_map<std::string, EnvironmentLightDataT> environmentsToInstall;

        inline static std::unordered_map<std::string, EnvironmentLightDataT> lightIdTable;

        inline static std::optional<EnvironmentLightDataT> activeTable = std::nullopt;

    public:
        LightIDTableManager() = delete;

        static std::optional<int> GetActiveTableValue(int type, int id) {
            if (activeTable) {
                auto &table = activeTable.value();

                auto typeTableIt = table.find(type);

                if (typeTableIt == table.end()) {
                    getLogger().warning("Unable to find value for type %d", type);
                    return std::nullopt;
                }

                const auto &typeTable = typeTableIt->second;
                auto it = typeTable.find(id);

                if (it != typeTable.end()) {
                    return it->second;
                } else {
                    getLogger().warning("Unable to find value for type %d and id %d.", type, id);
                }
            }

            getLogger().warning("Return not found");
            return std::nullopt;
        }

        static void SetEnvironment(const std::string& environmentName);

        static void InitTable();

        static void RegisterIndex(int type, int index, std::optional<int> requestedKey);

        static void AddEnvironment(InstallEnvironmentFunc environmentData);
    };
}

#define ChromaInstallEnvironment(environment) \
struct __ChromaRegisterEnvironment##environment { \
    __ChromaRegisterEnvironment##environment() { \
        Chroma::LightIDTableManager::AddEnvironment({#environment, environment().getEnvironmentLights()}); \
    } \
}; \
static __ChromaRegisterEnvironment##environment __ChromaRegisterEnvironmentInstance##environment;