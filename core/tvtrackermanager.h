#ifndef TVTRACKERMANAGER_H
#define TVTRACKERMANAGER_H

#include <string>
#include <vector>
#include <regex>

#include <QMessageBox>

#include "http/sourcegrabber.h"

// TEMP
#include <QDebug>

class TvTrackerManager
{
public:
    TvTrackerManager();
    std::vector<TvSeries> searchSeries(const std::string& title);
    int getNumberOfSeasons(const std::string& linkId);
    Season getSeasonEpisodes(const std::string &linkId, const int &seasonNumber);

private:
    std::vector<TvSeries> searchResults(const std::string& code);
    Date stringToDate(std::string strDate);
};

#endif // TVTRACKERMANAGER_H
