#include "ChromaConfig.hpp"
#include "Chroma.hpp"
#include "hooks/SceneTransition/SceneTransitionHelper.hpp"

#include "lighting/LegacyLightHelper.hpp"
#include "ChromaController.hpp"
#include "lighting/LightIDTableManager.hpp"

#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"

#include "utils/ChromaUtils.hpp"

using namespace CustomJSONData;
using namespace Chroma;
using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace System::Collections;

void SceneTransitionHelper::Patch(SongCore::SongLoader::CustomBeatmapLevel* beatmapLevel, GlobalNamespace::BeatmapKey key, GlobalNamespace::EnvironmentInfoSO* environment) {
  if(beatmapLevel == nullptr) {
    BasicPatch(nullptr, key, nullptr);
    return;
  }

  BasicPatch(beatmapLevel, key, environment);
}

void SceneTransitionHelper::Patch(SongCore::SongLoader::CustomBeatmapLevel* beatmapLevel, GlobalNamespace::BeatmapKey key, GlobalNamespace::EnvironmentInfoSO* environment, OverrideEnvironmentSettings*& overrideEnvironmentSettings) {
  if(beatmapLevel == nullptr) {
    BasicPatch(nullptr, key, nullptr);
    return;
  }

  BasicPatch(beatmapLevel, key, environment);
}

bool SceneTransitionHelper::BasicPatch(SongCore::SongLoader::CustomBeatmapLevel* beatmapLevel, GlobalNamespace::BeatmapKey key, GlobalNamespace::EnvironmentInfoSO* environment) {
  ChromaLogger::Logger.debug("Basic Patch {}", fmt::ptr(beatmapLevel));
  ChromaController::TutorialMode = false;

  bool chromaRequirement = false;
  ChromaController::infoDatCopy = std::nullopt;

  bool legacyOverride = false;

  if(beatmapLevel == nullptr) return false;

  ChromaLogger::Logger.debug("Getting Save Data");

  auto saveData = beatmapLevel->standardLevelInfoSaveDataV2;

  if(!saveData) return false;

  auto customSaveInfo = saveData.value()->CustomSaveDataInfo;

  if (!customSaveInfo) return false;

  ChromaLogger::Logger.debug("Getting Characteristic and diff");

  auto diff = customSaveInfo.value().get().TryGetCharacteristicAndDifficulty(
      key.beatmapCharacteristic->get_serializedName(), key.difficulty);

  if(!diff) return false;

  ChromaLogger::Logger.debug("Getting Requirements & Suggestions");
  
  auto requirements = diff->get().requirements;
  auto suggestions = diff->get().suggestions;
  chromaRequirement |= std::find(requirements.begin(), requirements.end(), REQUIREMENTNAME) != requirements.end();
  chromaRequirement |= std::find(suggestions.begin(), suggestions.end(), REQUIREMENTNAME) != suggestions.end();

  ChromaLogger::Logger.debug("Setting environment. Chroma Required: {}", chromaRequirement);

  if (environment == nullptr) {
    ChromaLogger::Logger.debug("Environment is null, this is not right!", chromaRequirement);

    return false;
  }

  LightIDTableManager::SetEnvironment(static_cast<std::string>(environment->get_serializedName()));

  ChromaLogger::Logger.debug("Environment set");

  // TODO: Chromalite

  ChromaController::SetChromaLegacy(legacyOverride);
  ChromaController::setChromaRequired(chromaRequirement);

  ChromaController::randomizerThing = XoshiroCpp::Xoshiro128PlusPlus();

  ChromaLogger::Logger.debug("Scene Patch Finished");

  return ChromaController::ChromaRequired();
}