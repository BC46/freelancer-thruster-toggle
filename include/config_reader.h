#pragma once

#include "common.h"
#include <string>

struct ThrusterConfig
{
    int idsName;

    ThrusterConfig();
};

class ConfigReader
{
public:
    /// @brief Retrieves the config file in the given path.
    /// @param path Path that points to the config (.ini) file.
    /// @param config Config that will be filled with the information from the config file.
    /// @return Whether or not the config could be read.
    void GetConfig(const std::string &path, ThrusterConfig &config);

private:
    /// @brief common.dll INI_Reader class.
    INI_Reader ir;
};
