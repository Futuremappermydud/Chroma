#include "lighting/LegacyLightHelper.hpp"
#include "main.hpp"
#include "Chroma.hpp"
#include "utils/ChromaUtils.hpp"

using namespace Chroma;
using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace System::Collections;

LegacyLightHelper::ColorMap LegacyLightHelper::LegacyColorEvents = LegacyLightHelper::ColorMap();

void LegacyLightHelper::Activate(const std::vector<GlobalNamespace::BeatmapEventData*>& eventData) {
    static auto contextLogger = getLogger().WithContext(ChromaLogger::LegacyLightColor);

    getLogger().debug("Legacy starting now!");
    LegacyColorEvents = LegacyLightHelper::ColorMap();
    getLogger().debug("Legacy going now!");
    debugSpamLog(contextLogger, "Got the events, checking for legacy %d", eventData.size());
    for (auto& d : eventData)
    {
        // TODO: Should we do this or find the root of the nullptr and fix that instead?
        if (d == nullptr) {
            continue;
        }

        if (!ASSIGNMENT_CHECK(classof(BeatmapEventData*), d->klass)) {
            getLogger().debug("Beatmap data: %s not what expected", il2cpp_utils::ClassStandardName(d->klass).c_str());
            continue;
        }


        debugSpamLog(contextLogger, "Checking d %d %s", d->value, d->value >= RGB_INT_OFFSET ? "true" : "false");
        if (d->value >= RGB_INT_OFFSET)
        {
            auto it = LegacyColorEvents.find(d->type);
            auto list = it != LegacyColorEvents.end() ? it->second : std::vector<pair<float, UnityEngine::Color>>();

            list.emplace_back(d->time, ColorFromInt(d->value));
            LegacyColorEvents[d->type] = list;
        }
    }
}

std::optional<UnityEngine::Color> LegacyLightHelper::GetLegacyColor(GlobalNamespace::BeatmapEventData *beatmapEventData) {
    auto it = LegacyColorEvents.find(beatmapEventData->type);
    if (it != LegacyColorEvents.end()) {
        auto dictionaryID = it->second;
        std::vector<pair<float, UnityEngine::Color>> colors;

        for (pair<float, UnityEngine::Color>& n : dictionaryID) {
            if (n.first <= beatmapEventData->time)
                colors.push_back(n);
        }


        if (!colors.empty())
        {
            return std::make_optional(colors.back().second);
        }
    }

    return std::nullopt;
}

UnityEngine::Color LegacyLightHelper::ColorFromInt(int rgb) {
    rgb -= RGB_INT_OFFSET;
    auto red = (float) ((rgb >> 16) & 0x0ff);
    auto green = (float) ((rgb >> 8) & 0x0ff);
    auto blue = (float ) (rgb & 0x0ff);
    return UnityEngine::Color(red / 255.0f, green / 255.0f, blue / 255.0f, 1);
}