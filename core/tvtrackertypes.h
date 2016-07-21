#ifndef TVTRACKERTYPES_H
#define TVTRACKERTYPES_H

struct Date
{
    int day;
    int month;
    int year;
};

struct Episode
{
    int number;
    Date airDate;
};

struct Season
{
    int number;
    std::vector<Episode> episodes;
};

struct TvSeries
{
    int id;
    std::string name;
    std::string image;
    std::string link;
};



#endif // TVTRACKERTYPES_H
