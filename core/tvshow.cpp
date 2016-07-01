#include "tvshow.h"

tvshow::tvshow():id(0),name(""),image("")
{

}

tvshow::tvshow(int id, std::string name):id(id),name(name),image("")
{

}

tvshow::tvshow(int id, std::string name, std::string image):id(id),name(name),image(image)
{

}

int tvshow::getId() const
{
    return id;
}

void tvshow::setId(int value)
{
    id = value;
}

std::string tvshow::getName() const
{
    return name;
}

void tvshow::setName(const std::string &value)
{
    name = value;
}

std::string tvshow::getImage() const
{
    return image;
}

void tvshow::setImage(const std::string &value)
{
    image = value;
}
