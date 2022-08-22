#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

// <
// 1-5 (tryb)
// >
// 
// <
// if filter -> wielkosc 1,3,5,7...
// >
// <
// if add -> r,g,b
// > i tyle, dalej filter
//
//<
//if filter -> wczytaj wielkosc x wielkosc elementow
//>
//<
//<
//if filter specajlny -> koniec (sam sie wypelnia jedynkami)
//>
namespace fs = std::filesystem;
int main()
{
    const fs::path sandbox{ "sandbox" };
    fs::create_directories(sandbox / "dir1" / "dir2");
    std::ofstream{ sandbox / "file1.txt" };
    std::ofstream{ sandbox / "file2.txt" };

    std::cout << "directory_iterator:\n";
    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : fs::directory_iterator{ sandbox })
    {
        std::cout << dir_entry.path() << '\n';
    }
    return 0;
}