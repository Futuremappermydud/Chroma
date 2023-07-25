

#include "lighting/environments/BigMirrorEnvironment.hpp"

using namespace Chroma;

EnvironmentLightDataT BigMirrorEnvironment::getEnvironmentLights() {
  return EnvironmentLightDataT({
      { 1,
        {
            { 1, 7 },
            { 2, 9 },
            { 3, 6 },
            { 4, 3 },
            { 5, 2 },
            { 6, 0 },
            { 7, 5 },
            { 8, 1 },
            { 9, 8 },
            { 10, 4 },
        } },
      { 2,
        {
            { 1, 6 },   { 2, 7 },   { 3, 8 },   { 4, 9 },   { 5, 10 },  { 6, 11 },  { 7, 12 },  { 8, 13 },  { 9, 14 },
            { 10, 15 }, { 11, 16 }, { 12, 17 }, { 13, 18 }, { 14, 19 }, { 15, 20 }, { 16, 21 }, { 17, 22 }, { 18, 23 },
            { 19, 24 }, { 20, 25 }, { 21, 26 }, { 22, 27 }, { 23, 28 }, { 24, 29 }, { 25, 30 }, { 26, 31 }, { 27, 32 },
            { 28, 33 }, { 29, 34 }, { 30, 35 }, { 31, 36 }, { 32, 37 }, { 33, 38 }, { 34, 39 }, { 35, 40 }, { 36, 41 },
            { 37, 42 }, { 38, 43 }, { 39, 44 }, { 40, 45 }, { 41, 46 }, { 42, 47 }, { 43, 48 }, { 44, 49 }, { 45, 50 },
            { 46, 51 }, { 47, 52 }, { 48, 53 }, { 49, 54 }, { 50, 55 }, { 51, 56 }, { 52, 57 }, { 53, 58 }, { 54, 59 },
            { 55, 60 }, { 56, 61 }, { 57, 62 }, { 58, 63 }, { 59, 64 }, { 60, 65 },
        } },
      { 3,
        {
            { 1, 7 },
            { 2, 5 },
            { 3, 4 },
            { 4, 6 },
            { 5, 9 },
            { 6, 3 },
            { 7, 0 },
            { 8, 10 },
        } },
      { 4,
        {
            { 1, 6 },
            { 2, 5 },
            { 3, 4 },
            { 4, 7 },
            { 5, 9 },
            { 6, 11 },
            { 7, 0 },
            { 8, 2 },
        } },
      { 5,
        {
            { 1, 20 },
            { 2, 18 },
            { 3, 11 },
            { 4, 15 },
            { 5, 14 },
            { 6, 16 },
            { 7, 12 },
            { 8, 17 },
            { 9, 19 },
            { 10, 13 },
            { 11, 4 },
            { 12, 2 },
            { 13, 6 },
            { 14, 8 },
            { 15, 9 },
            { 16, 10 },
        } },
  });
}

ChromaInstallEnvironment(BigMirrorEnvironment)
