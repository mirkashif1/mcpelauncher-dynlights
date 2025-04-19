#include <dlfcn.h>
#include <link.h>
#include <link.h>
#include <span>
#include <string>
#include "zoom.h"
#include "main.h"
#include "conf.h"
#include "imgui.h"
#include <libhat.hpp>
#include <span>
#include <cstddef>

Zoom zoom;

unsigned long CameraApi_tryGetFOV(void* t) {
    return zoom.CameraAPI_tryGetFOV(t);
}

extern "C" [[gnu::visibility("default")]] void mod_preinit() {}

extern "C" [[gnu::visibility("default")]] void mod_init() {
    Conf::load();

    auto gw = dlopen("libmcpelauncher_gamewindow.so", 0);
    game_window_is_mouse_locked = (decltype(game_window_is_mouse_locked))dlsym(gw, "game_window_is_mouse_locked");
    game_window_get_primary_window = (decltype(game_window_get_primary_window))dlsym(gw, "game_window_get_primary_window");
    game_window_add_window_creation_callback = (decltype(game_window_add_window_creation_callback))dlsym(gw, "game_window_add_window_creation_callback");
    game_window_add_keyboard_callback = (decltype(game_window_add_keyboard_callback))dlsym(gw, "game_window_add_keyboard_callback");
    game_window_add_mouse_scroll_callback = (decltype(game_window_add_mouse_scroll_callback))dlsym(gw, "game_window_add_mouse_scroll_callback");

    auto mcLib = dlopen("libminecraftpe.so", 0);

    std::span<std::byte> range1, range2;

    auto callback = [&](const dl_phdr_info& info) {
        if(auto h = dlopen(info.dlpi_name, RTLD_NOLOAD); dlclose(h), h != mcLib)
            return 0;
        range1 = {reinterpret_cast<std::byte*>(info.dlpi_addr + info.dlpi_phdr[1].p_vaddr), info.dlpi_phdr[1].p_memsz};
        range2 = {reinterpret_cast<std::byte*>(info.dlpi_addr + info.dlpi_phdr[2].p_vaddr), info.dlpi_phdr[2].p_memsz};
        return 1;
    };

    dl_iterate_phdr(
        [](dl_phdr_info* info, size_t, void* data) {
            return (*static_cast<decltype(callback)*>(data))(*info);
        },
        &callback);

    auto CameraAPI_typeinfo_name = hat::find_pattern(range1, hat::object_to_signature("9CameraAPI")).get();
    auto CameraAPI_typeinfo = hat::find_pattern(range2, hat::object_to_signature(CameraAPI_typeinfo_name)).get() - sizeof(void*);
    auto CameraAPI_vtable = hat::find_pattern(range2, hat::object_to_signature(CameraAPI_typeinfo)).get() + sizeof(void*);
    auto CameraAPI_tryGetFOV = reinterpret_cast<unsigned long (**)(void*)>(CameraAPI_vtable) + 6;

    CameraAPI_tryGetFOV_orig = *CameraAPI_tryGetFOV;

    *CameraAPI_tryGetFOV = [](void* t) -> unsigned long {
        return zoom.CameraAPI_tryGetFOV(t);
    };

    initImgui();
    game_window_add_window_creation_callback(NULL, [](void* user) {
        game_window_add_keyboard_callback(game_window_get_primary_window(), NULL, [](void* user, int keyCode, int action) -> bool {
            if(Conf::changingKey) {
                if(action == 0) {
                    Conf::zoomKey = keyCode;
                    showKeyWindow();
                }
                return true;
            }
            if(action != 1) {
                zoom.onKeyboard(keyCode, action);
            }
            return false;
        });
        game_window_add_mouse_scroll_callback(game_window_get_primary_window(), NULL, [](void* user, double x, double y, double dx, double dy) -> bool {
            return zoom.onMouseScroll(dy);
        });
    });
}
