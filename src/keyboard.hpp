#pragma once
#include <stdint.h>
#include <string.h>
#include <map>

class Keyboard
{
private:
   
    std::map<int, bool> keys;
public:
    Keyboard(/* args */);
    ~Keyboard();
    void setKey(int index);
    void unsetKey(int index);
    bool getKey(int index);
};
