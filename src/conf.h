#pragma once
#include <string>

struct Conf {
    static int zoomKey;
    static bool animated;

    static bool changingKey;

    static std::string getPath();
    static void load();
    static void save();
};
