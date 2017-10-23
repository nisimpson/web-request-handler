#include "web_request_handler.h"

using namespace web_gui;

int main(void) {
    WebRequestHandler handler;
    int code = 0;

    handler.init();
    code = handler.run();
    handler.cleanup();
    
    return code;
}

