#ifndef TVTRACKERMANAGER_H
#define TVTRACKERMANAGER_H

#include <string>
#include <vector>
#include <regex>
#include "sourcegrabber.h"

// TEMP
#include <QDebug>

class TvTrackerManager
{
public:
    TvTrackerManager();

public:
    std::vector<TvSeries> searchSeries(const std::string& title);

private:
    std::vector<TvSeries> searchResults(const std::string& code);
};

#endif // TVTRACKERMANAGER_H