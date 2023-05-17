#ifndef PROIECT1_UTILIZATOR_H
#define PROIECT1_UTILIZATOR_H

#include <string>
#include <list>
#include <random>
#include <iostream>
#include "Istoric.h"
#include "EventTarget.h"
#include <cmath>
#include <algorithm>

using namespace std;

class Staff;

class Utilizator: public EventTarget, protected Istoric{

    static list<int> utilizatoriIds;
    static list<Utilizator*> utilizatori;

protected:
    int id;
    string nume;

    string parola;
    bool logat = true;

    bool parolaValida(string& checkPass){
        return checkPass == parola;
    }
public:
    Utilizator(const string& nume, const string& parola): Istoric("Utilizator "+nume){
        id=getRandomUniqueId();
        this->nume = nume;
        this->parola = parola;
        utilizatori.push_back(this);
        utilizatoriIds.push_back(id);
    }

    Utilizator(Utilizator& utilizator): Istoric("Utilizator "+utilizator.nume){
        id = utilizator.id;
        nume = utilizator.nume;
        utilizatori.push_back(this);
        utilizatoriIds.push_back(id);
    }

    ~Utilizator(){
        utilizatori.remove(this);
        utilizatoriIds.remove(id);
    }

    void sendNotificare(string& titlu, string& mesaj){
        //DUMMY
    }

    static int genRandomId(){
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(0, 1000000);
        return floor(dist(mt));
    }

    static int getRandomUniqueId(){
        int id = genRandomId();
        while(find(utilizatoriIds.begin(), utilizatoriIds.end(), id) != utilizatoriIds.end())
            id = genRandomId();
        return id;
    }

    static list<shared_ptr<Utilizator>> getUtilizatori();
    static list<shared_ptr<Staff>> getStaff();
    static shared_ptr<Utilizator> getUtilizator(const string& numeCautat);

    virtual int getId() const{
        return id;
    }

    virtual string getNume(){
        return nume;
    }

    virtual bool log(string& pass){
        if(logat) return logat;
        if(parolaValida(pass))
            logat = true;
        return logat;
    }

    string getInfo() override;
};

string Utilizator::getInfo() {
    return "Nume: "+getNume()+", Id: "+std::to_string(getId());
}
list<int> Utilizator::utilizatoriIds;
list<Utilizator*> Utilizator::utilizatori;

class Staff: public Utilizator{
    int perm;
public:
    Staff(const string& nume, const string& parola, int perm): Utilizator(nume, parola), perm(perm) {
        setNumeIstoric("Staff "+nume);
    }

    Staff(Staff& otherStaff): Utilizator(otherStaff.nume, otherStaff.parola), perm(otherStaff.perm){
        setNumeIstoric("Staff "+nume);
    }

    int getPerm() const{
        return perm;
    }

    static bool eStaff(Utilizator* utiliz);
};

bool Staff::eStaff(Utilizator* utiliz) {
    auto* staff = dynamic_cast<Staff*>(utiliz);
    return staff != nullptr;
}


list<shared_ptr<Utilizator>> Utilizator::getUtilizatori() {
    list<shared_ptr<Utilizator>> final;
    list<int> ids;
    for (auto utiliz: utilizatori) {
        bool deja = find(ids.begin(), ids.end(), utiliz->id) != ids.end();
        if(!deja){
            ids.push_back(utiliz->id);
            final.push_back(std::make_shared<Utilizator>(*utiliz));
        }
    }
    return final;
}

list<shared_ptr<Staff>> Utilizator::getStaff() {
    list<shared_ptr<Staff>> final;
    for (const auto& utiliz: getUtilizatori()) {
        auto* staff = dynamic_cast<Staff*>(utiliz.get());
        if(staff != nullptr){
            final.push_back(std::make_shared<Staff>(*staff));
        }
    }
    return final;
}

shared_ptr<Utilizator> Utilizator::getUtilizator(const string& numeCautat) {
    for(const auto& utiliz : getUtilizatori()){
        if(utiliz->getNume() == numeCautat){
            return utiliz;
        }
    }
    return nullptr;
}


#endif //PROIECT1_UTILIZATOR_H
