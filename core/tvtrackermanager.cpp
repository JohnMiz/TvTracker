#include "tvtrackermanager.h"

TvTrackerManager::TvTrackerManager(){

}

std::vector<TvSeries> TvTrackerManager::searchSeries(const std::string& title){
    SourceGrabber grabber(title);
    std::string source = grabber.grabSearchIMDB();
    return searchResults(source);
}

std::vector<TvSeries> TvTrackerManager::searchResults(const std::string &code){

    std::smatch match,match2;
    std::vector<TvSeries> tvList;

    if (std::regex_search(code, match, std::regex("</a>Titles</h3>\\s?.*\\s?(.*)</table>")) && match.size() > 1) {

         std::string searchResult = match.str(0);

         std::regex imageQuery("<img src=\"(.{0,130})\" /></a>");
         std::sregex_iterator nextImage{ searchResult.begin(), searchResult.end(), imageQuery };
         std::sregex_iterator endImage;

         std::regex linkQuery("<td class=\"result_text\"> <a href=\"/title/(.{0,130})</td>");
         std::sregex_iterator nextLink{ searchResult.begin(), searchResult.end(), linkQuery };
         std::sregex_iterator endLink;

         while (nextImage != endImage && nextLink!=endLink && tvList.size() < 10)
         {
              match = *nextImage;
              match2 = *nextLink;
              if (match2.str(1).find("(TV Series)") != std::string::npos)
              {
                   TvSeries tv;
                   std::string title = match2.str(1);
                   auto t = title.find("\" >") + 3;
                   title = title.substr(t, title.find("</a>") - t);
                   tv.image = match.str(1);
                   tv.name = title;
                   tv.link = match2.str(1).substr(0, 9);
                   tvList.emplace_back(tv);
              }
              ++nextImage;
              ++nextLink;
         }


    }
    else
    {
         qDebug() << "Didnt find anything\n";
    }


    return tvList;
}
