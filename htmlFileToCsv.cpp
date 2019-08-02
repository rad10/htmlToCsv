#include <iostream>
#include <fstream>

std::string readfile(std::string filename)
{
    std::string result = "";
    ifstream src;
    src.open(filename);
    while (src.eof()) {
        src >> "\n" >> result;
    }
    return result;
}