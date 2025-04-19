#include "conf.h"
#include "key_mapping.h"
#include <properties/property_list.h>
#include <properties/property.h>
#include <string>
#include <fstream>

int Conf::zoomKey = 'C';
bool Conf::animated = true;

bool Conf::changingKey = false;

static properties::property_list conf('=');
static properties::property<int> zoomKey(conf, "zoomKey", 'C');
static properties::property<bool> animated(conf, "animated", true);

std::string Conf::getPath() {
    return "/data/data/com.mojang.minecraftpe/zoom.conf";
}

void Conf::load() {
    std::ifstream propertiesFile(getPath());
    if(propertiesFile) {
        conf.load(propertiesFile);
    }
    Conf::zoomKey = ::zoomKey.get();
    Conf::animated = ::animated.get();
}

void Conf::save() {
    ::zoomKey.set(Conf::zoomKey);
    ::animated.set(Conf::animated);

    std::ofstream propertiesFile(getPath());
    if(propertiesFile) {
        conf.save(propertiesFile);
    }
}
