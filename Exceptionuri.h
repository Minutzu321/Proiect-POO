//
// Created by chiru on 17.05.2023.
//

#ifndef PROIECT1_EXCEPTIONURI_H
#define PROIECT1_EXCEPTIONURI_H

#include <exception>
#include <iostream>
using namespace std;

class IpException : std::exception{
public:
    const char *what() const noexcept override {
        return "Ip-ul camerei nu este corect!";
    }
};

#endif //PROIECT1_EXCEPTIONURI_H
