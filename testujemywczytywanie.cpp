#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "filter.h"
#include "filter_add.h"
#include "filter_median.h"
#include "filter_min.h"
#include "filter_max.h"
// <
// 1-5 (tryb)
// >
// 
// <
// if filter (0) -> wielkosc 1,3,5,7...
// >
// <
// if add (1) -> r,g,b
// > i tyle, dalej filter
//
//<
//if filter -> wczytaj wielkosc x wielkosc elementow
//>
//<
//<
//if filter specajlny (2,3,4) -> koniec (sam sie wypelnia jedynkami)
//>
namespace fs = std::filesystem;

int main()
{
    const fs::path rozszerzenia { "rozszerzenia" };
    fs::create_directories(rozszerzenia);
    //std::ofstream{ sandbox / "file1.txt" };

    std::cout << "directory_iterator:\n";
    // directory_iterator can be iterated using a range-for loop

    std::vector<filter> filtry;

    for (auto const& dir_entry : fs::directory_iterator{ rozszerzenia })
    {
        std::vector<int> wektor;
        std::cout <<std::endl<< dir_entry.path() << '\n';
        std::ifstream plik(dir_entry.path());
        std::string word;
        std::string line;
        getline(plik, line);
        while (plik >> word)
        {
           wektor.vector::push_back(std::stoi(word));
        }
        for (auto i = wektor.begin(); i != wektor.end(); ++i)
            std::cout << *i << " ";
        filter nowy(stoi(line));
        nowy.showMatrix();
    }

    return 0;
}