#include <stdlib.h>
#include "transition.h"

class Zoom {
private:
    bool zoomKeyDown;
    unsigned long zoomLevel = 5345000000;
    unsigned long lastClientZoom;

    Transition transition;

public:
    unsigned long CameraAPI_tryGetFOV(void* t);
    bool onMouseScroll(double dy);
    void onKeyboard(int keyCode, int action);
};