#include <iostream>
#include <fstream>
#include <iomanip>
#include "SaveService.h"
#include "../../externals/json/json.hpp"

SaveService::SaveService(): fileName("save.json"), j(std::make_unique<nlohmann::json>())
{}

void SaveService::init()
{

}

void SaveService::clean()
{

}

void SaveService::flush() const
{
    std::ofstream ofS;
    ofS.open(fileName);
    ofS << std::setw(4) << *j << std::endl;
}

void SaveService::load()
{
    std::ifstream ifS;
    ifS.open(fileName);
    ifS >> *j;

    std::cout << "Loaded save: " << std::endl << std::setw(4) << *j << std::endl;
}
