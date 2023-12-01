#pragma once
#include <string>
#include <iostream>
#include "Config.hpp"
#include <map>
#include <vector>
#include <set>

typedef std::vector<std::string> vec;
typedef std::map<std::string, std::string> mp;
typedef std::map<std::string, mp > map_last;

class ServConf
{
    public:
        ServConf();
        std::string host;
        std::set<std::string> ports;
        mp errorPages;
        std::string name;
        long long clientBodyLimit;
        mp routes; 
        mp rout2;
        map_last rout;
        std::vector<std::string> my_data;
};