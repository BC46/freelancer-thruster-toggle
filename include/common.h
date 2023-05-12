#pragma once

#pragma comment(lib, "common.lib")

unsigned int __declspec(dllimport) CreateID(char const *);

class __declspec(dllimport) INI_Reader
{
public:
    bool open(char const *, bool);
    bool read_header(void);
    bool read_value(void);
    int get_value_int(unsigned int);
    void close(void);
};
