#include "web_app.h"

using namespace web_gui;

WebApp::WebApp() { }
WebApp::~WebApp() { }

bool 
WebApp::init()
{
    m_handler.add_route("^/api/(.*)$", m_api_view);
    m_handler.add_route("^/(.*)$", m_home_view);
    return true;
}

bool
WebApp::run()
{
    return m_handler.run();
}

bool 
WebApp::cleanup()
{
    return true;
}
