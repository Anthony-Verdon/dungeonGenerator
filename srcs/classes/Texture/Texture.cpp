#include "Texture.hpp"
#include "../Utils/Utils.hpp"
#include <sstream>
#include <stdexcept>
#include <vector>

Texture::Texture(const std::string &texturePath)
{
    path = texturePath;
    std::stringstream textureStream;
    std::string line;
    std::vector<std::string> words;
    unsigned int nbLine;
    unsigned int pixel;

    if (!Utils::checkExtension(path, ".ppm"))
        throw(std::runtime_error(path + ": invalid extension file"));

    nbLine = 0;
    pixel = 0;
    textureStream = Utils::readFile(path);
    while (std::getline(textureStream, line))
    {
        line = line.substr(0, line.find("#"));
        if (line.length() == 0)
            continue;
        else if (nbLine < 3)
            checkHeader(path, line, nbLine);
        else
        {
            words = Utils::splitLine(line);
            for (size_t i = 0; i < words.size(); i++)
            {
                data.push_back(std::stoi(words[i]));
                pixel++;
            }
        }
        nbLine++;
    }
}

Texture::~Texture()
{
}

Texture::Texture(const Texture &copy)
{
    *this = copy;
}

Texture &Texture::operator=(const Texture &copy)
{
    if (&copy != this)
    {
        width = copy.getWidth();
        height = copy.getHeight();
        valueMax = copy.getValueMax();
        data = copy.getData();
    }
    return (*this);
}

void Texture::checkHeader(const std::string &path, const std::string &line, unsigned int nbLine)
{
    std::vector<std::string> words;

    if (nbLine == 0 && line != "P3")
        throw(std::runtime_error(path + ": invalid magic number"));
    else if (nbLine == 1)
    {
        words = Utils::splitLine(line);
        if (words.size() != 2)
            throw(std::runtime_error(path + ": invalid declaration of width and height"));
        width = std::stoi(words[0]);
        height = std::stoi(words[1]);
    }
    else if (nbLine == 2)
    {
        words = Utils::splitLine(line);
        if (words.size() != 1)
            throw(std::runtime_error(path + ": invalid maximum value"));
        valueMax = std::stoi(words[0]);
    }
}

int Texture::getWidth() const
{
    return width;
}

int Texture::getHeight() const
{
    return height;
}

unsigned int Texture::getValueMax() const
{
    return valueMax;
}

std::vector<int> Texture::getData() const
{
    return data;
}

std::string Texture::getPath() const
{
    return path;
}