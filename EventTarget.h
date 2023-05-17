//
// Created by chiru on 16.05.2023.
//

#ifndef PROIECT1_EVENTTARGET_H
#define PROIECT1_EVENTTARGET_H

#include <iostream>
#include <functional>
#include "Istoric.h"

using namespace std;

enum EventType {
    LOGIN,
    ADD_UTILIZATOR,
    ADD_STAFF,
    ADD_CAMERA,

};

string eventToStr(EventType v)
{
    switch (v)
    {
        case ADD_CAMERA:    return "Camera adaugata";
        case ADD_UTILIZATOR: return "Utilizator adugat";
        case ADD_STAFF: return "Staff adugat";
        case LOGIN:         return "Login";

        default:      return "[Eveniment necunoscut]";
    }
}

class EventTarget{
public:
    virtual string getInfo() = 0;
};



#endif //PROIECT1_EVENTTARGET_H
