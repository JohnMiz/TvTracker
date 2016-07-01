#ifndef TVSHOW_H
#define TVSHOW_H

#include <string>

class tvshow
{
public:
    tvshow();
    tvshow(int id,std::string name);
    tvshow(int id,std::string name,std::string image);

    int getId() const;
    void setId(int value);

    std::string getName() const;
    void setName(const std::string &value);

    std::string getImage() const;
    void setImage(const std::string &value);

private:
    int id;
    std::string name;
    std::string image;
};

#endif // TVSHOW_H
