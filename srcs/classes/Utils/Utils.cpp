#include "Utils.hpp"
#include <fstream>

std::vector<std::string> Utils::splitLine(std::string line)
{
    size_t index;
    std::string word;
    std::vector<std::string> words;

    index = 0;
    while (index != std::string::npos)
    {
        index = line.find(" ");
        word = line.substr(0, index);
        words.push_back(word);
        line = line.substr(index + 1, std::string::npos);
    }
    return words;
}

std::stringstream Utils::readFile(const std::string &path)
{
    std::ifstream file;
    std::stringstream stream;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(path);
    stream << file.rdbuf();
    file.close();
    return (stream);
}

unsigned int Utils::convertRGBtoNum(unsigned char R, unsigned char G, unsigned char B)
{
    return ((R << 16) | (G << 8) | B);
}

bool Utils::checkExtension(const std::string &path, const std::string &extension)
{
    unsigned int extensionLength;
    unsigned int pathLength;

    extensionLength = extension.length();
    pathLength = path.length();
    if (pathLength > extensionLength && path.compare(pathLength - extensionLength, extensionLength, extension) == 0)
        return (true);
    else
        return (false);
}