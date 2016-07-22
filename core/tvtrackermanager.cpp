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

        s.episodes.push_back(Episode{std::stoi(epNum),stringToDate(airDate)});

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

Date TvTrackerManager::stringToDate(std::string strDate)
{
    std::string months[] = {"Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.", "Jul.", "Aug.", "Sep.", "Oct.","Nov.","Dec."};
    Date d;

    std::vector<std::string> words;

    size_t spaceLoc = 0,temp = 0;
    while((spaceLoc = strDate.find(" ",temp)) != -1)
    {
        words.push_back(strDate.substr(temp,spaceLoc-temp));
        temp = spaceLoc + 1;
    }
    words.push_back(strDate.substr(temp));

    if(words.size() == 1)
    {
        d.day = 0;
        d.month = 0;
        d.year = std::stoi(words[0]);
    }
    else
    {
        if(words[words.size() - 2] == months[0])
            d.month = 1;
        else if(words[words.size() - 2] == months[1])
            d.month = 2;
        else if(words[words.size()-2] == months[2])
            d.month = 3;
        else if(words[words.size()-2] == months[3])
            d.month = 4;
        else if(words[words.size()-2] == months[4])
            d.month = 5;
        else if(words[words.size()-2] == months[5])
            d.month = 6;
        else if(words[words.size()-2] == months[6])
            d.month = 7;
        else if(words[words.size()-2] == months[7])
            d.month = 8;
        else if(words[words.size()-2] == months[8])
            d.month = 9;
        else if(words[words.size()-2] == months[9])
            d.month = 10;
        else if(words[words.size()-2] == months[10])
            d.month = 11;
        else if(words[words.size()-2] == months[11])
            d.month = 12;

        if(words.size()==2)
        {
            d.year = std::stoi(words[1]);
            d.day = 0;
        }
        else{
            d.day = std::stoi(words[0]);
            d.year = std::stoi(words[2]);
        }
    }
    return d;
}
