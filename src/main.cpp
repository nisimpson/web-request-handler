#include "web_app.h"

using namespace web_gui;

#ifndef BUILD_TEST

int main(void) {
    WebApp app;
    int code = -1;

    if (app.init() &&
        app.run() &&
        app.cleanup())
    {
        code = 0;
    }

    return code;
}

#endif // BUILD_TEST
