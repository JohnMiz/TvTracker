#include "tvtrackermanager.h"

TvTrackerManager::TvTrackerManager(){

}

void TvTrackerManager::searchSeries(const std::string& title){
    SourceGrabber grabber(title);
    std::string source = grabber.grabSearchIMDB();
    auto results = searchResults(source);

    for(auto tv : results){
        qDebug() << "Link: " << tv.link.c_str();
        qDebug() << "Name: " << tv.title.c_str();
        qDebug() << "Image: " << tv.image.c_str();
    }
}

std::vector<TvSeries> TvTrackerManager::searchResults(const std::string &code){
    std::regex re("</a>Titles</h3>\\s?.*\\s?(.*)</table>");
    std::smatch match,match2;
    std::string searchResult;
    std::vector<TvSeries> tvList;
    if (std::regex_search(code, match, re) && match.size() > 1) {

         searchResult = match.str(0);
         re.assign("<img src=\"(.{0,130})\" /></a>");
         std::sregex_iterator next{ searchResult.begin(), searchResult.end(), re };
         std::sregex_iterator end;

         std::regex re2("<td class=\"result_text\"> <a href=\"/title/(.{0,130})</td>");
         std::sregex_iterator next2{ searchResult.begin(), searchResult.end(), re2 };
         std::sregex_iterator end2;

         while (next != end && next2!=end2 && tvList.size() < 10) {
              match = *next;
              match2 = *next2;
              if (match2.str(1).find("(TV Series)") != std::string::npos) {
                   TvSeries tv;
                   std::string title = match2.str(1);
                   auto t = title.find("\" >") + 3;
                   title = title.substr(t, title.find("</a>") - t);
                   tv.image = match.str(1);
                   tv.title = title;
                   tv.link = match2.str(1).substr(0, 9);
                   tvList.emplace_back(tv);
              }
              next++;
              next2++;
         }


    }
    else {
         qDebug() << "Didnt find anything\n";
    }


    return tvList;
}
