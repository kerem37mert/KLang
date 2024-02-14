//
// Created by Kerem on 13/02/2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "lexer.h"


void run(const char* filePath)
{
    std::ifstream file(filePath);
    if (file.fail())
    {
        std::cout << "[ERROR] Unable to find file with path: " << filePath << std::endl;
        return;
    }

    std::stringstream sourceStream;
    sourceStream << file.rdbuf();
    std::string source = sourceStream.str();

    std::cout << source;    

}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "[ERROR] Invalid command line argument count." << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    size_t length = filePath.length();
    if (length < 3 || filePath.substr(length - 2) != ".k")
    {
        std::cout << "[ERROR] Invalid file extension. File must have a .k extension." << std::endl;
        return 1;
    }

    run(argv[1]);
    return 0;
}