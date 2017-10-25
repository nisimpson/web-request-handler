#include <sstream>
#include "common/web_request.h"

using namespace std;
using namespace web_gui;

map<string, string>
WebRequest::parse_query_string(const string & qs)
{
    map<string, string> queries;
    if (qs.size() > 0)
    {
        string query;
        stringstream tokenizer(qs);
        while(getline(tokenizer, query, '&'))
        {
            string key;
            string value;
            stringstream queryTokenizer(query);
            getline(queryTokenizer, key, '=');
            getline(queryTokenizer, value, '=');
            queries.insert(make_pair(key, value));
        }
    }
    return queries;
}