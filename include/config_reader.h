#include "common.h"
#include <string>

struct ThrusterConfig
{
    int idsName;
};

class ConfigReader
{
public:
    /// @brief Retrieves the config file in the given path.
    /// @param path Path that points to the config (.ini) file.
    /// @param ThrusterConfig Config that will be filled with the information from the config file.
    /// @return Whether or not the config could be read.
    bool GetConfig(const std::string &path, ThrusterConfig &ThrusterConfig);

private:
    /// @brief common.dll INI_Reader class.
    INI_Reader _iniReader;
};
