#include "keyboard.hpp"

Keyboard::Keyboard(){
}

Keyboard::~Keyboard(){}

void Keyboard::setKey(int index){
    keys[index]=1;
}

void Keyboard::unsetKey(int index){
    keys[index]=0;
}

bool Keyboard::getKey(int index){
    return keys[index];
}