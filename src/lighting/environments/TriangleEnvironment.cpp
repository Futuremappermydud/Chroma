

#include "lighting/environments/TriangleEnvironment.hpp"

using namespace Chroma;

EnvironmentLightDataT TriangleEnvironment::getEnvironmentLights() {
  return EnvironmentLightDataT({
      { 1,
        {
            { 1, 3 },
            { 2, 8 },
            { 3, 5 },
            { 4, 2 },
            { 5, 7 },
            { 6, 4 },
            { 7, 1 },
            { 8, 6 },
            { 9, 0 },
            { 10, 12 },
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
            { 1, 10 },
            { 2, 3 },
            { 3, 2 },
            { 4, 6 },
            { 5, 7 },
            { 6, 4 },
            { 7, 5 },
            { 8, 12 },
            { 9, 9 },
            { 10, 0 },
            { 11, 13 },
        } },
      { 4,
        {
            { 1, 10 },
            { 2, 4 },
            { 3, 3 },
            { 4, 7 },
            { 5, 8 },
            { 6, 5 },
            { 7, 6 },
            { 8, 12 },
            { 9, 14 },
            { 10, 0 },
            { 11, 2 },
        } },
      { 5,
        {
            { 1, 6 },
            { 2, 10 },
            { 3, 13 },
            { 4, 5 },
            { 5, 9 },
            { 6, 12 },
            { 7, 7 },
            { 8, 11 },
            { 9, 8 },
            { 10, 0 },
            { 11, 14 },
            { 12, 16 },
        } },
  });
}

ChromaInstallEnvironment(TriangleEnvironment)
