#ifndef PROIECT1_STOCARE_H
#define PROIECT1_STOCARE_H

class Stocare{

int spatiu = 0, //gb
    viteza = 0, //mb/s
    plin = 0; // %(procent)

public:
    Stocare(){}
    Stocare(int spatiu, int viteza, int plin=0) {
        this->spatiu = spatiu;
        this->viteza = viteza;
        this->plin = plin;
        if(this->plin > 100)
            this->plin = 100;
        else if(this->plin < 0)
            this->plin = 0;
    }

    Stocare(Stocare& otherStocare) {
        this->spatiu = otherStocare.spatiu;
        this->viteza = otherStocare.viteza;
        this->plin = otherStocare.plin;

        if(plin > 100)
            plin = 100;
        else if(plin < 0)
            plin = 0;
    }

    int getSpatiu();
    int getViteza();
    int getProcentPlin();

    void setSpatiu(int GB);
    void setViteza(int MBS);
    void setProcentPlin(int procentNou);

    Stocare& operator = (const Stocare& stocare);

    friend istream & operator >> (istream &in,  Stocare &s);
    friend ostream & operator << (ostream &out, const Stocare &s);
};

int Stocare::getSpatiu() {
    return spatiu;
}
int Stocare::getViteza() {
    return viteza;
}

int Stocare::getProcentPlin() {
    return plin;
}

void Stocare::setViteza(int MBS){
    viteza = MBS;
}
void Stocare::setSpatiu(int GB){
    spatiu = GB;
}

void Stocare::setProcentPlin(int procentNou){
    plin = procentNou;
    if(plin > 100)
        plin = 100;
    else if(plin < 0)
        plin = 0;
}

istream& operator>>(istream &in, Stocare &s) {
    cout<<"Ce spatiu de stocare(GB) ai?";
    in>>s.spatiu;
    cout<<"Ce viteza de WRITE/READ(MB/S) ai?";
    in>>s.viteza;
    return in;
}

ostream& operator<<(ostream &out, const Stocare &s) {
    out<<s.spatiu<<"GB";
    out<<" - ";
    out<<s.viteza<<"MB/S";
    return out;
}

Stocare &Stocare::operator=(const Stocare &otherStocare) = default;


#endif
