#include "config_reader.h"

bool ConfigReader::GetConfig(const std::string &path, ThrusterConfig& config)
{
    bool foundValue = false;

    ir.open(path.c_str(), false);

    while (ir.read_header())
    {
        if (ir.is_header("Options"))
        {
            while (ir.read_value())
            {
                if (ir.is_value("ids_name"))
                {
                    config.idsName = ir.get_value_int(0);
                    foundValue = true;
                }
            }
        }
    }

    ir.close();

    return foundValue;
}
