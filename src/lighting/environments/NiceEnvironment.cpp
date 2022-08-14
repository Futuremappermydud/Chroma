

#include "lighting/environments/NiceEnvironment.hpp"

using namespace Chroma;

EnvironmentLightDataT NiceEnvironment::getEnvironmentLights() {
    return EnvironmentLightDataT(
        {
    {1, {
        {1, 6 },
        {2, 5 },
        {3, 8 },
        {4, 7 },
        {5, 2 },
        {6, 4 },
        {7, 3 },
        {8, 9 },
    }},
    {2, {
        {1, 3 },
        {2, 4 },
        {3, 5 },
        {4, 6 },
        {5, 7 },
        {6, 8 },
        {7, 9 },
        {8, 10 },
        {9, 11 },
        {10, 12 },
        {11, 13 },
        {12, 14 },
        {13, 15 },
        {14, 16 },
        {15, 17 },
        {16, 18 },
        {17, 19 },
        {18, 20 },
        {19, 21 },
        {20, 22 },
        {21, 23 },
        {22, 24 },
        {23, 25 },
        {24, 26 },
        {25, 27 },
        {26, 28 },
        {27, 29 },
        {28, 30 },
        {29, 31 },
        {30, 32 },
        {31, 33 },
        {32, 34 },
        {33, 35 },
        {34, 36 },
        {35, 37 },
        {36, 38 },
        {37, 39 },
        {38, 40 },
        {39, 41 },
        {40, 42 },
    }},
    {3, {
        {1, 1 },
        {2, 2 },
        {3, 3 },
        {4, 4 },
        {5, 15 },
        {6, 10 },
        {7, 5 },
        {8, 9 },
        {9, 7 },
        {10, 0 },
        {11, 11 },
    }},
    {4, {
        {1, 2 },
        {2, 3 },
        {3, 4 },
        {4, 5 },
        {5, 13 },
        {6, 0 },
        {7, 8 },
        {8, 10 },
        {9, 12 },
        {10, 1 },
        {11, 7 },
    }},
    {5, {
        {1, 11 },
        {2, 12 },
        {3, 9 },
        {4, 10 },
        {5, 6 },
        {6, 8 },
        {7, 0 },
        {8, 7 },
        {9, 18 },
        {10, 17 },
        {11, 5 },
        {12, 3 },
        {13, 13 },
        {14, 15 },
    }},
}
    );
}

ChromaInstallEnvironment(NiceEnvironment)
