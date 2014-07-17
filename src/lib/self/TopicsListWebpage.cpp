// last modified 

#include "TopicsListWebpage.h"
#include <iostream>


using namespace std;


TopicsListWebpage::TopicsListWebpage ( const string& url,
                                       TopicsListWebpage::ParseTitlesAndUrls parseTitlesAndUrls,
                                       TopicsListWebpage::ParseNextpageUrl parseNextpageUrl,
                                       const string& proxy_addr,
                                       const string& src_charset,
                                       const string& dest_charset )
    : Webpage(url, "", proxy_addr)
{
    if (!isLoaded()) {
        return;
    }

    // charset convert
    if (!src_charset.empty() && !dest_charset.empty()) {
        convertCharset(src_charset, dest_charset);
    }

    // parse the URLs and titles of all topics on topicslist webpage
    const string& webpage_txt = getTxt();
    parseTitlesAndUrls(webpage_txt, titles_and_urls_list_);

    // unescape html for title
    for (auto& e : titles_and_urls_list_) {
        string& title = e.first;
        title = unescapeHtml(title);
    }

    // parse the next topicslist webpage URL
    parseNextpageUrl(webpage_txt, nextpage_url_);
}

TopicsListWebpage::~TopicsListWebpage ()
{
    ;
}

// if there is no more topicslist page, return empty string
const string&
TopicsListWebpage::getNextpageUrl (void) const
{
    return(nextpage_url_);
}

// first title, second url
const vector<pair<string, string>>&
TopicsListWebpage::getTitlesAndUrlsList (void) const
{
    return(titles_and_urls_list_);
}
