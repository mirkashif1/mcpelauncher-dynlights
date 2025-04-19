#include "util.h"
#include "imgui.h"
#include "conf.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initImgui() {
    void* libmenu = dlopen("libmcpelauncher_menu.so", 0);
    if(libmenu) {
        mcpelauncher_show_window = (decltype(mcpelauncher_show_window))dlsym(libmenu, "mcpelauncher_show_window");
        mcpelauncher_close_window = (decltype(mcpelauncher_close_window))dlsym(libmenu, "mcpelauncher_close_window");
        mcpelauncher_addmenu = (decltype(mcpelauncher_addmenu))dlsym(libmenu, "mcpelauncher_addmenu");

        struct MenuEntryABI changeZoomKey;
        changeZoomKey.name = "Change zoom key";
        changeZoomKey.click = [](void* user) {
            showKeyWindow();
            Conf::changingKey = true;
        };
        changeZoomKey.selected = [](void* user) -> bool { return false; };
        changeZoomKey.length = 0;

        struct MenuEntryABI animated;
        animated.name = "Animated";
        animated.click = [](void* user) {
            Conf::animated = !Conf::animated;
            Conf::save();
        };
        animated.selected = [](void* user) {
            return Conf::animated;
        };
        animated.length = 0;

        struct MenuEntryABI entry;
        struct MenuEntryABI entries[] = {changeZoomKey, animated};
        entry.subentries = entries;
        entry.length = sizeof(entries) / sizeof(struct MenuEntryABI);
        entry.name = "Zoom";
        mcpelauncher_addmenu(1, &entry);
    }
}

void showKeyWindow() {
    std::string msg = std::string("Push new key (Current key: " + keyToString(Conf::zoomKey) + ")");
    struct control zoomKeyWindow;
    zoomKeyWindow.type = 3;
    zoomKeyWindow.data.text.label = (char*)msg.c_str();
    zoomKeyWindow.data.text.size = 0;

    mcpelauncher_show_window("Zoom key", 1, NULL, [](void* user) { Conf::save(); Conf::changingKey = false; }, 1, &zoomKeyWindow);
}