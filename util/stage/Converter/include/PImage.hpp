#pragma once

#include <vector>
#include <string>
#include "DataCompress.hpp"

class PImage
{
public:
    u_int getHeigh() {return heigh;};
    u_int getWidth() {return width;};
    void saveToFile(std::string filename, char format);
    void loadFromFile(std::string filename);
protected:
    void readProperties(std::ifstream &file);
    void writeProperties(std::ofstream &file, char format);
    bool format;
    u_int width;
    u_int heigh;
    u_int length;
    u_short nbColor;
    DataCompress datas;
};
