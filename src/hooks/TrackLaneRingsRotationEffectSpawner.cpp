#include "main.hpp"
#include "Chroma.hpp"
#include "utils/ChromaUtils.hpp"
#include "GlobalNamespace/TrackLaneRingsRotationEffectSpawner.hpp"
#include "GlobalNamespace/TrackLaneRingsRotationEffect.hpp"
#include "ChromaRingsRotationEffect.hpp"
#include "UnityEngine/Random.hpp"
#include "UnityEngine/GameObject.hpp"
#include "custom-json-data/shared/CustomBeatmapData.h"
#include <cstring>
#include "ChromaController.hpp"

using namespace Chroma;
using namespace CustomJSONData;
using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace ChromaUtils;



MAKE_HOOK_OFFSETLESS(TrackLaneRingsRotationEffectSpawner_Start, void, GlobalNamespace::TrackLaneRingsRotationEffectSpawner* self) {
    static auto contextLogger = getLogger().WithContext(Chroma::ChromaLogger::TrackLaneRings);
    if (!ChromaController::DoChromaHooks()) {
        TrackLaneRingsRotationEffectSpawner_Start(self);
        return;
    }

    auto* oldRotationEffect = self->trackLaneRingsRotationEffect;
    contextLogger.debug("Adding component");
    auto newRotationEffect = oldRotationEffect->get_gameObject()->AddComponent<ChromaRingsRotationEffect*>();
    contextLogger.debug("Copyying values now");
    newRotationEffect->CopyValues(oldRotationEffect);

    self->trackLaneRingsRotationEffect = reinterpret_cast<TrackLaneRingsRotationEffect*>(newRotationEffect);
    TrackLaneRingsRotationEffectSpawner_Start(self);
}


template<typename T>
T getValueOrDefault(rapidjson::Value* val, const std::string& s, T def) {
    auto v = val->FindMember(s);
    return v != val->MemberEnd() ? v->value.Get<T>() : def;
}

void TriggerRotation(
        TrackLaneRingsRotationEffect* trackLaneRingsRotationEffect,
        bool rotRight,
        float rotation,
        float rotationStep,
        float rotationPropagationSpeed,
        float rotationFlexySpeed)
{
    static auto contextLogger = getLogger().WithContext(Chroma::ChromaLogger::TrackLaneRings);
    contextLogger.debug("DOING TRIGGER ROTATION %s", trackLaneRingsRotationEffect->klass->name);

    auto chromaRingRotation = reinterpret_cast<ChromaRingsRotationEffect*>(trackLaneRingsRotationEffect);

    chromaRingRotation->AddRingRotationEffectF(chromaRingRotation->GetFirstRingDestinationRotationAngle() + (rotation * (rotRight ? -1.0f : 1.0f)), rotationStep, rotationPropagationSpeed, rotationFlexySpeed);
}



// TODO:
// This method is directly ported from TrackLaneRingsRotationEffectSpawner. It is required to be ported since for some inexplicable reason
// using the original method causes CJD or something else to stop loading the map and it
// just stays as limbo. Hopefully with time we can fix that and use that instead
void origHandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger(GlobalNamespace::TrackLaneRingsRotationEffectSpawner* self, BeatmapEventData* beatmapEventData) {
    static auto contextLogger = getLogger().WithContext(Chroma::ChromaLogger::TrackLaneRings);
    if (beatmapEventData->type != self->beatmapEventType)
    {
        return;
    }
    float step = 0.0f;

    int originalRotationStepType = (int) self->rotationStepType;

    if (originalRotationStepType == TrackLaneRingsRotationEffectSpawner::RotationStepType::Range0ToMax) {
        step = UnityEngine::Random::Range(0.0f, self->rotationStep);
    } else if (originalRotationStepType == TrackLaneRingsRotationEffectSpawner::RotationStepType::Range) {
        step = UnityEngine::Random::Range(-self->rotationStep, self->rotationStep);
    } else if (originalRotationStepType == TrackLaneRingsRotationEffectSpawner::RotationStepType::MaxOr0) {
        step = (UnityEngine::Random::get_value() < 0.5f) ? self->rotationStep : 0.0f;
    }
    contextLogger.debug("Track lane klass %s", self->trackLaneRingsRotationEffect->klass->name);

    self->trackLaneRingsRotationEffect->AddRingRotationEffect(self->trackLaneRingsRotationEffect->GetFirstRingRotationAngle() + self->rotation * (float)((UnityEngine::Random::get_value() < 0.5f) ? 1 : -1), step, self->rotationPropagationSpeed, self->rotationFlexySpeed);
}

MAKE_HOOK_OFFSETLESS(TrackLaneRingsRotationEffectSpawner_HandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger, void, GlobalNamespace::TrackLaneRingsRotationEffectSpawner* self,
                     CustomJSONData::CustomBeatmapEventData* beatmapEventData) {
    if (!ChromaController::DoChromaHooks()) {
        TrackLaneRingsRotationEffectSpawner_HandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger(self,
                                                                                                        beatmapEventData);
        return;
    }


//    contextLogger.debug("Track lane rotation effect self %d beat %d and customData %d", self->beatmapEventType.value,
//                      beatmapEventData->type.value,
//                      beatmapEventData->customData != nullptr && beatmapEventData->customData->value != nullptr ? 0 : 1);

//    if (il2cpp_functions::class_is_assignable_from(beatmapEventData->klass, classof(CustomJSONData::CustomBeatmapEventData*))) {
    auto *customBeatmapEvent = reinterpret_cast<CustomBeatmapEventData *>(beatmapEventData);

    static auto contextLogger = getLogger().WithContext(Chroma::ChromaLogger::TrackLaneRings);
    if (self->beatmapEventType.value == beatmapEventData->type.value && customBeatmapEvent->customData &&
        customBeatmapEvent->customData->value) {
        contextLogger.debug("Doing stuff with custom Data");
        float rotationStep = 0.0f;
        float originalRotationStep = self->rotationStep;
        float originalRotation = self->rotation;
        float originalRotationPropagationSpeed = (float) self->rotationPropagationSpeed;
        float originalRotationFlexySpeed = self->rotationFlexySpeed;
        int originalRotationStepType = (int) self->rotationStepType;

        if (originalRotationStepType == TrackLaneRingsRotationEffectSpawner::RotationStepType::Range0ToMax) {
            rotationStep = UnityEngine::Random::Range(0.0f, rotationStep);
        } else if (originalRotationStepType == TrackLaneRingsRotationEffectSpawner::RotationStepType::Range) {
            rotationStep = UnityEngine::Random::Range(-originalRotationStep, originalRotationStep);
        } else if (originalRotationStepType == TrackLaneRingsRotationEffectSpawner::RotationStepType::MaxOr0) {
            rotationStep = (UnityEngine::Random::get_value() < 0.5f) ? originalRotationStep : 0.0f;
        }

        auto dynData = customBeatmapEvent->customData->value;
        contextLogger.debug("Got the data");
        auto selfName = to_utf8(csstrtostr(self->get_name()));

        auto nameFilter = dynData->FindMember(NAMEFILTER);
        if (nameFilter != dynData->MemberEnd() &&
            stringCompare(selfName, nameFilter->value.GetString()) == 0) {
            contextLogger.debug("Name filter ignored");
            return;
        }

        int dir;

        auto dirV = dynData->FindMember(DIRECTION);

        if (dirV == dynData->MemberEnd()) {
            dir = -1;
        } else dir = dirV->value.GetInt();

        bool rotRight;
        if (dir == -1) {
            rotRight = UnityEngine::Random::get_value() < 0.5f;
        } else {
            rotRight = dir == 1;
        }

        auto counterSpinV = dynData->FindMember(COUNTERSPIN);
        if (counterSpinV != dynData->MemberEnd() && counterSpinV->value.GetBool()) {
            if (selfName.find("Big") == std::string::npos) {
                rotRight = !rotRight;
            }
        }

        auto reset = dynData->FindMember(RESET);
        if (reset != dynData->MemberEnd() && reset->value.GetBool()) {
            contextLogger.debug("Reset spawn, returning");
            TriggerRotation(self->trackLaneRingsRotationEffect, rotRight, originalRotation, 0, 50, 50);
            return;
        }

        contextLogger.debug("Getting the last values");

        float step = getValueOrDefault(dynData, STEP, rotationStep);
        float prop = getValueOrDefault(dynData, PROP, originalRotationPropagationSpeed);
        float speed = getValueOrDefault(dynData, SPEED, originalRotationFlexySpeed);
        float rotation = getValueOrDefault(dynData, ROTATION, originalRotation);

        float stepMult = getValueOrDefault(dynData, STEPMULT, 1.0f);
        float propMult = getValueOrDefault(dynData, PROPMULT, 1.0f);
        float speedMult = getValueOrDefault(dynData, SPEEDMULT, 1.0f);

        TriggerRotation(self->trackLaneRingsRotationEffect, rotRight, rotation, step * stepMult, prop * propMult,
                        speed * speedMult);
        contextLogger.debug("Finished spawn, returning");
        return;
    }

//    }

    contextLogger.debug("Not a custom beat map");
    origHandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger(self, beatmapEventData);//        TrackLaneRingsRotationEffectSpawner_HandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger(self, beatmapEventData);

}




void Hooks::TrackLaneRingsRotationEffectSpawner() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), TrackLaneRingsRotationEffectSpawner_Start, il2cpp_utils::FindMethodUnsafe("", "TrackLaneRingsRotationEffectSpawner", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), TrackLaneRingsRotationEffectSpawner_HandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger, il2cpp_utils::FindMethodUnsafe("", "TrackLaneRingsRotationEffectSpawner", "HandleBeatmapObjectCallbackControllerBeatmapEventDidTrigger", 1));
    //    INSTALL_HOOK_OFFSETLESS(getLogger(), SaberManager_Finalize, il2cpp_utils::FindMethodUnsafe("System", "Object", "Finalize", 0));
}