#include "ChromaController.hpp"
#include "main.hpp"
#include "Chroma.hpp"
#include "GlobalNamespace/TrackLaneRingsRotationEffect.hpp"

using namespace Chroma;

MAKE_HOOK_OFFSETLESS(TrackLaneRingsRotationEffect_AddRingRotationEffect, void, GlobalNamespace::TrackLaneRingsRotationEffect* self, float angle, float step, int propagationSpeed, float flexySpeed) {
    // Essentially, here we cancel the original method. DO NOT call it IF it's a Chroma map
    if (!ChromaController::DoChromaHooks() && self->klass == classof(GlobalNamespace::TrackLaneRingsRotationEffect*)) {
        TrackLaneRingsRotationEffect_AddRingRotationEffect(self, angle, step, propagationSpeed, flexySpeed);
        return;
    }

}

void Hooks::TrackLaneRingsRotationEffect() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), TrackLaneRingsRotationEffect_AddRingRotationEffect, il2cpp_utils::FindMethodUnsafe("", "TrackLaneRingsRotationEffect", "AddRingRotationEffect", 4));
//    INSTALL_HOOK_OFFSETLESS(getLogger(), SaberManager_Finalize, il2cpp_utils::FindMethodUnsafe("System", "Object", "Finalize", 0));
}