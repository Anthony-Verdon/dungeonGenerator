#pragma once

#include <string>
#include <vector>
class Texture
{
  private:
    Texture() = delete;
    void checkHeader(const std::string &path, const std::string &line, unsigned int nbLine);

    int width;
    int height;
    unsigned int valueMax;
    std::vector<int> data;

  public:
    Texture(const std::string &path);
    Texture(const Texture &copy);
    Texture &operator=(const Texture &copy);
    ~Texture();

    int getWidth() const;
    int getHeight() const;
    unsigned int getValueMax() const;
    std::vector<int> getData() const;
};