
#pragma once

#include "lighting/LightIDTableManager.hpp"

namespace Chroma {
class HalloweenEnvironment : public EnvironmentData {
public:
  EnvironmentLightDataT getEnvironmentLights() override;
};
} // namespace Chroma
