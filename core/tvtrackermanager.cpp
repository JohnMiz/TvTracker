#include "tvtrackermanager.h"

TvTrackerManager::TvTrackerManager()
{

}

std::vector<TvSeries> TvTrackerManager::searchSeries(const std::string& title){
    SourceGrabber grabber;
    std::string source = grabber.grabSearchIMDB(title);
    return searchResults(source);
}

int TvTrackerManager::getNumberOfSeasons(const std::string &linkId)
{
    std::string url = "http://www.imdb.com/title/"+ linkId + "/episodes?season=999";

    SourceGrabber grabber;
    std::string source = grabber.grabURL(url);

    if(source != "")
    {

        std::string start = "itemprop=\"name\">Season&nbsp;";
        std::string end = "</h3>\n  <div class=\"list detail eplist\">";

        return std::stoi(source.substr(source.find(start)+start.length(),source.find(end) - source.find(start)-start.length()));
    }
    return 0;
}

Season TvTrackerManager::getSeasonEpisodes(const std::string& linkId, const int& seasonNumber)
{
    Season s;
    s.number = seasonNumber;
    SourceGrabber grabber;
    std::string source = grabber.grabURL("http://www.imdb.com/title/"+ linkId + "/episodes?season=" + std::to_string(seasonNumber));
    qDebug() << seasonNumber;
    std::smatch match;

    std::regex episodeQuery("<div class=\"info\" itemprop=\"episodes\" itemscope itemtype=\"http://schema.org/TVEpisode\">\\s(.*)\\s.*\\s.*\\s.*");
    std::sregex_iterator nextEpisode{ source.begin(), source.end(), episodeQuery };
    std::sregex_iterator endEpisode;


     while (nextEpisode != endEpisode)
     {
         match = *nextEpisode;

        std::string searchResult = match.str(0);

        std::string startQueryEpNum = "<meta itemprop=\"episodeNumber\" content=\"";
        std::string endQueryEpNum = "\"/>";

        std::string epNum = searchResult.substr(searchResult.find(startQueryEpNum) + startQueryEpNum.length(),searchResult.find(endQueryEpNum) -(searchResult.find(startQueryEpNum) + startQueryEpNum.length()));

        std::string startQueryAirDate = "<div class=\"airdate\">\n            ";
        std::string endQueryAirDate = "\n    </div>";

        std::string airDate = searchResult.substr(searchResult.find(startQueryAirDate) + startQueryAirDate.length(),searchResult.find(endQueryAirDate) -(searchResult.find(startQueryAirDate) + startQueryAirDate.length()));

        s.episodes.push_back(Episode{std::stoi(epNum),airDate});

        ++nextEpisode;

    }

    return s;
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

         while (nextImage != endImage && nextLink!=endLink && tvList.size() < 20)
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
         QMessageBox::warning(0,"Message","Did not find anything!");
         qDebug() << "Didnt find anything\n";
    }


    return tvList;
}
