#pragma once

#pragma comment(lib, "common.lib")

class __declspec(dllimport) INI_Reader
{
public:
    INI_Reader();
    ~INI_Reader();
    bool open(char const *, bool);
    bool read_header(void);
    bool is_header(char const *);
    bool read_value(void);
    bool is_value(char const *);
    int get_value_int(unsigned int);
    void close(void);

private:
    char data[0x1568];
};
