#include <cstring>
#include <iostream>

#ifndef LABORATORPOO_CUSTOMSTR_H
#define LABORATORPOO_CUSTOMSTR_H


using namespace std;

class CustomString{
private:
    char* data = nullptr;
    int size = 0;
public:
    CustomString(){
        this->data = nullptr;
    }

    CustomString(const char str[]) {
        this->size = strlen(str)+1;
        this->data = new char[this->size];
        for (int i = 0; i < size; ++i) {
            data[i] = str[i];
        }
    }

    CustomString(const CustomString& customString){
        this->size = customString.size;
        this->data = new char[this->size];
        for (int i = 0; i < size; ++i) {
            data[i] = customString.data[i];
        }
    }

    CustomString(CustomString&& other){
        this->size = other.size;
        this->data = other.data;

        other.data = nullptr;
        other.size = 0;
    }

    CustomString& operator=(CustomString&& other){
        if(&other == this) return *this;

        this->size = other.size;
        this->data = other.data;
        other.data = nullptr;
        other.size = 0;

        return *this;
    }

    CustomString& operator = (const CustomString& customString){
        if(&customString == this) return *this;
        if(data != nullptr)
            delete[] data;
        this->size = customString.size;
        this->data = new char[this->size];

        for (int i = 0; i < size; ++i) {
            data[i] = customString.data[i];
        }
        return *this;
    }

    //facilitam convertirea automata din char;
    CustomString& operator = (const char str[]){
        if(data != nullptr)
            delete[] data;
        this->size = strlen(str)+1;
        this->data = new char[this->size];
        for (int i = 0; i < size; ++i) {
            data[i] = str[i];
        }
        return *this;
    }

    CustomString operator + (const CustomString& customString){

        int nou_size = size + customString.size - 1;
        char* nou = new char[nou_size];

        for (int i = 0; i < size-1; ++i) {
            nou[i] = data[i];
        }
        for (int i = 0; i < customString.size; ++i) {
            nou[size-1+i] = customString.data[i];
        }


        return {nou};
    }



    void insert(char caracter, int poz){
        char* nou = new char[this->size+1];
        for (int i = 0; i < poz; ++i) {
            nou[i] = this->data[i];
        }
        nou[poz] = caracter;
        for (int i = poz+1; i < this->size+1; ++i) {
            nou[i] = this->data[i-1];
        }
        if(data != nullptr)
            delete[] data;
        this->size++;
        this->data = nou;
    }

    char * strstr(const CustomString customString){
        return ::strstr(customString.data, data);
    }

    friend bool operator == (const CustomString &c1, const CustomString &c2);
    friend bool operator != (const CustomString &c1, const CustomString &c2);
    friend ostream & operator << (ostream &out, const CustomString &c);

    ~CustomString(){
        if(data != nullptr)
            delete[] data;
    }
};

ostream & operator << (ostream &out, const CustomString &c){
    out<<c.data;
    return out;
}

bool operator==(const CustomString &c1, const CustomString &c2) {
    if(c1.size == c2.size){
        for (int i = 0; i < c1.size-1; ++i)
            if(c1.data[i] != c2.data[i]) return false;
        return true;
    }
    return false;
}

bool operator != (const CustomString &c1, const CustomString &c2) {
    return !(c1 == c2);
}


#endif