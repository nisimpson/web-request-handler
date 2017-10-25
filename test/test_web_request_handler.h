#include "common/web_request_handler.h"
#include "common/web_view.h"
#include "common/web_request.h"
#include "gtest/gtest.h"
#include <string>
#include <sstream>

namespace
{

class MockWebView : public web_gui::WebView
{
public:
    MockWebView(const std::string & tag)
        : web_gui::WebView()
        , m_tag(tag) { }

    ~MockWebView() { }
    
    std::string handle_request(web_gui::WebRequest & request)
    {
        std::stringstream response;
        response << "<html>"
            << "<body>"
            << "<h1>Hello, " << m_tag << "</h1>"
            << "</body>"
            << "</html>";

        return response.str();
    }

    std::string tag() const
    {
        return m_tag;
    }

    std::string to_string() const
    {
        return tag();
    }

private:
    std::string m_tag;
};

// The fixture for testing class WebRequestHandler.
class WebRequestHandlerTest : public ::testing::Test
{
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    WebRequestHandlerTest()
    {
        // You can do set-up work for each test here.
        view_one = new MockWebView("one");
        view_two = new MockWebView("two");
    }

    virtual ~WebRequestHandlerTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
        delete view_one;
        delete view_two;
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    web_gui::WebRequestHandler handler;
    MockWebView * view_one;
    MockWebView * view_two;
};

TEST_F(WebRequestHandlerTest, WebRequestHandlerPicks404)
{
    // should match only uris prefixed with 'api'
    const std::string pattern_one = "^/api(.*)$";

    // should match only root uri
    const std::string pattern_two = "^/$";
    
    // otherwise, error
    MockWebView view_error("error");

    handler.add_route(pattern_one, *view_one);
    handler.add_route(pattern_two, *view_two);
    handler.add_404_view(view_error);

    web_gui::WebView * expected = &view_error;
    web_gui::WebView * actual = handler.route("/home.html");
    EXPECT_EQ(expected->to_string(), actual->to_string()); 
}

TEST_F(WebRequestHandlerTest, MethodRoutePicksOne)
{
    const std::string pattern_one = "/number";
    const std::string pattern_two = "/smile";

    handler.add_route(pattern_one, *view_one);
    handler.add_route(pattern_two, *view_two);

    web_gui::WebView * expected = view_one;
    web_gui::WebView * actual = handler.route("/number");
    EXPECT_EQ(expected->to_string(), actual->to_string());

    handler.clear_routes();

    // demonstrate that order doesn't matter in this case;
    // the two patterns are dramatically different
    handler.add_route(pattern_two, *view_two);
    handler.add_route(pattern_one, *view_one);
    EXPECT_EQ(expected->to_string(), actual->to_string());
}

TEST_F(WebRequestHandlerTest, MethodRoutePicksBestMatch)
{
    const std::string pattern_one = "/number/(\\d+)";
    const std::string pattern_two = "/number";

    handler.add_route(pattern_one, *view_one);
    handler.add_route(pattern_two, *view_two);

    web_gui::WebView * expected = view_two;
    web_gui::WebView * actual = handler.route("/number");
    EXPECT_EQ(expected->to_string(), actual->to_string());

    expected = view_one;
    actual = handler.route("/number/5");
    EXPECT_EQ(expected->to_string(), actual->to_string());
}

} // namespace
