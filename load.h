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

struct filters
{
    string filter_name;
    filter *filter;
    filter_add *filter_add;
    filter_min *filter_min;
    filter_median *filter_median;
    filter_max *filter_max;
};

namespace fs = std::filesystem;

vector<filters*> load()
{
    const fs::path rozszerzenia { "rozszerzenia" };
    fs::create_directories(rozszerzenia);
    //std::ofstream{ sandbox / "file1.txt" };

    std::cout << "directory_iterator:\n";
    // directory_iterator can be iterated using a range-for loop

    vector<filters*> filtry;
    int aktualny = 0;
    for (auto const& dir_entry : fs::directory_iterator{ rozszerzenia })
    {
        
        std::vector<int> wektor;
        std::cout <<std::endl<< dir_entry.path() << '\n';
        std::ifstream plik(dir_entry.path());
        std::string word;
        while (plik >> word)
        {
           wektor.vector::push_back(std::stoi(word));
        }
        if (wektor[0] == 0)
        {
            filtry.emplace_back(new filters{fs::path(dir_entry.path()).stem().string(), new filter(wektor[1]), nullptr, nullptr, nullptr, nullptr});
            //  cout << *i << " ";
            for (int i = 0; i < wektor[1]; i++)
            {
                for (int j = 0; j < wektor[1]; j++)
                {
                    int co = wektor[1] * i + j + 2;
                    filtry[aktualny]->filter->setMatrixCo(wektor[co], i, j);
                }
            }
        }
        else if (wektor[0] == 1)
        {
            filtry.emplace_back(new filters{ fs::path(dir_entry.path()).stem().string(), nullptr, new filter_add(wektor[1], wektor[2], wektor[3]), nullptr, nullptr, nullptr });
        }
        else if (wektor[0] == 2)
        {
            filtry.emplace_back(new filters{ fs::path(dir_entry.path()).stem().string(), nullptr, nullptr, new filter_min(wektor[1]), nullptr, nullptr });
        }
        else if (wektor[0] == 3)
        {
            filtry.emplace_back(new filters{ fs::path(dir_entry.path()).stem().string(),  nullptr, nullptr, nullptr, new filter_median(wektor[1]), nullptr });
        }
        else if (wektor[0] == 4)
        {
            filtry.emplace_back(new filters{ fs::path(dir_entry.path()).stem().string(),  nullptr, nullptr, nullptr, nullptr, new filter_max(wektor[1])});
        }

        aktualny++;
    }
    return filtry;
}