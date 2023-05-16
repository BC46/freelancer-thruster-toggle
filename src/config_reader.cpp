#include "config_reader.h"

ThrusterConfig::ThrusterConfig()
{
    idsName = 1465;
}

void ConfigReader::GetConfig(const std::string &path, ThrusterConfig& config)
{
    if (!ir.open(path.c_str(), false))
        return;

    while (ir.read_header())
    {
        if (!ir.is_header("Options"))
            continue;

        while (ir.read_value())
        {
            if (ir.is_value("ids_name"))
                config.idsName = ir.get_value_int(0);
        }
    }

    ir.close();
}
