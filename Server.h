#ifndef PROIECT1_SERVER_H
#define PROIECT1_SERVER_H

#include "Camera.h"
#include "Stocare.h"

class Server{
    int numarCamere = 0;
    Camera* camere;

    int numarSpStocare = 0;
    Stocare* spStocare;

public:
    Server(){
        camere = nullptr;
        spStocare = nullptr;
    }

    Server(Server& server){
        this->numarCamere = server.numarCamere;
        this->camere = new Camera[numarCamere];
        for (int i = 0; i < numarCamere; ++i) {
            camere[i] = server.camere[i];
        }
        this->numarSpStocare = server.numarSpStocare;
        for (int i = 0; i < numarSpStocare; ++i) {
            spStocare[i] = server.spStocare[i];
        }

    }

    Server(Server&& server){
        this->numarCamere = server.numarCamere;
        this->camere = server.camere;
        this->numarSpStocare = server.numarSpStocare;
        this->spStocare = server.spStocare;

        server.numarCamere = 0;
        server.camere = nullptr;
        server.numarSpStocare = 0;
        server.spStocare = nullptr;
    }

    Server& operator = (const Server& server);
    Server& operator = (Server&& server);

    ~Server(){
        if(camere != nullptr)
            delete[] camere;
        if(spStocare != nullptr)
            delete[] spStocare;
    }

    int getNumarCamere();
    Camera getCamera(int i);
    Camera getCamera(const char numeSauAdresa[]);

    int getNumarSpStocare();
    Stocare getSpStocare(int i);

    void addCamera(Camera camera);
    void stergeCamera(int index);
    void stergeCamera(const char numeSauAdresa[]);

    void addSpStocare(int GB, int MBS);
    void addSpStocare(Stocare& spStoc);
    void stergeSpStocare(int index);

    int estimeazaTimpUmplere();

    friend istream & operator >> (istream &in,  Server &s);
    friend ostream & operator << (ostream &out, Server &s);
};

void Server::addCamera(Camera camera) {
    int numarCamereNoi = numarCamere + 1;
    Camera* camereNoi = new Camera[numarCamereNoi];
    for (int i = 0; i < numarCamere; ++i) {
        camereNoi[i] = camere[i];
    }
    camereNoi[numarCamere] = camera;
    numarCamere = numarCamereNoi;
    if(camere != nullptr)
        delete[] camere;
    camere = camereNoi;
}

void Server::addSpStocare(int GB, int MBS) {
    Stocare spStoc(GB, MBS);
    addSpStocare(spStoc);
}

void Server::addSpStocare(Stocare& spStoc) {
    int numarSpatiiNoi = numarSpStocare + 1;
    Stocare* spatiiNoi = new Stocare[numarSpatiiNoi];
    for (int i = 0; i < numarSpStocare; ++i) {
        spatiiNoi[i] = spStocare[i];
    }
    spatiiNoi[numarSpStocare] = spStoc;
    numarSpStocare = numarSpatiiNoi;
    if(spStocare != nullptr)
        delete[] spStocare;
    spStocare = spatiiNoi;
}

void Server::stergeCamera(int index) {
    int numarCamereNoi = numarCamere - 1;
    Camera* camereNoi = new Camera[numarCamereNoi];

    for (int i = 0; i < index; ++i) {
        camereNoi[i] = camere[i];
    }
    for (int i = index+1; i < numarCamere; ++i) {
        camereNoi[i-1] = camere[i];
    }
    if(camere != nullptr)
        delete[] camere;
    camere = camereNoi;
    numarCamere = numarCamereNoi;
}

void Server::stergeSpStocare(int index) {
    int numarSpStocNoi = numarSpStocare - 1;
    Stocare* spStocNoi = new Stocare[numarSpStocNoi];

    for (int i = 0; i < index; ++i) {
        spStocNoi[i] = spStocare[i];
    }
    for (int i = index+1; i < numarSpStocare; ++i) {
        spStocNoi[i-1] = spStocare[i];
    }
    if(spStocare != nullptr)
        delete[] spStocare;
    spStocare = spStocNoi;
    numarSpStocare = numarSpStocNoi;
}

void Server::stergeCamera(const char* numeSauAdresa) {
    CustomString test(numeSauAdresa);
    for (int i = 0; i < numarCamere; ++i) {
        if(camere[i].getNume() == test || camere[i].getAdresa() == test){
            stergeCamera(i);
            return;
        }
    }
}

int Server::getNumarCamere() {
    return numarCamere;
}
Camera Server::getCamera(int i) {
    return camere[i];
}


int Server::getNumarSpStocare() {
    return numarSpStocare;
}
Stocare Server::getSpStocare(int i) {
    return spStocare[i];
}


Camera Server::getCamera(const char str[]) {
    CustomString numeSauAdresa(str);
    for (int i = 0; i < numarCamere; ++i) {
        if(camere[i].getNume() == numeSauAdresa || camere[i].getAdresa() == numeSauAdresa){
            return camere[i];
        }
    }
}

int Server::estimeazaTimpUmplere() {

    int bytesPerSecond = 0;

    for (int i = 0; i < numarCamere; ++i) {
        int bytesPerFrame = sizeof(camere[i].getBase64Frame());
        int framesPerSecond = 60;
        bytesPerSecond += bytesPerFrame * framesPerSecond;
    }

    double gbPerSecond = (double) bytesPerSecond / (1024 * 1024 * 1024);

    double gbTotali = 0;
    for (int i = 0; i < numarSpStocare; ++i) {
        Stocare spStoc = spStocare[i];
        double gbSpatiu = (double) spStoc.getSpatiu();
        double gbProcentPlin = (double) spStoc.getProcentPlin() / 100;
        gbTotali += gbSpatiu - (gbProcentPlin * gbSpatiu);
    }

    return (int) (gbTotali / gbPerSecond)/60/60/24;
}


istream& operator>>(istream &in, Server &s) {
    cout<<"Cate camere vrei sa adaugi?";
    int camereDeAdaugat;
    in>>camereDeAdaugat;
    for (int i = 0; i < camereDeAdaugat; ++i) {
        Camera c;
        in>>c;
        s.addCamera(c);
    }

    cout<<"Cate spatii de stocare vrei sa adaugi?";
    int spatiiDeAdaugat;
    in>>spatiiDeAdaugat;
    for (int i = 0; i < spatiiDeAdaugat; ++i) {
        Stocare stoc;
        in>>stoc;
        s.addSpStocare(stoc);
    }
    return in;
}

ostream& operator<<(ostream &out, Server &s) {
    out<<"-----------["<<s.numarCamere<<" Camere]-----------"<<endl;
    for (int i = 0; i < s.numarCamere; ++i) {
        out<<"- ["<<i+1<<"] "<<s.camere[i]<<endl;
    }
    out<<"-----------["<<s.numarCamere<<" Camere]-----------"<<endl;
    out<<"-----------["<<s.numarSpStocare<<" Spatii de stocare]-----------"<<endl;
    for (int i = 0; i < s.numarSpStocare; ++i) {
        out<<"- ["<<i+1<<"] "<<s.spStocare[i]<<endl;
    }
    out<<"Spatiul se va termina in(zile) "<<s.estimeazaTimpUmplere()<<endl;
    out<<"-----------["<<s.numarSpStocare<<" Spatii de stocare]-----------"<<endl;
    return out;
}

Server &Server::operator=(const Server& server) {
    if(&server == this) return *this;

    if(camere != nullptr)
    delete[] camere;
    if(spStocare != nullptr)
    delete[] spStocare;

    this->numarCamere = server.numarCamere;
    this->camere = new Camera[numarCamere];
    for (int i = 0; i < numarCamere; ++i) {
        this->camere[i] = server.camere[i];
    }

    this->numarSpStocare = server.numarSpStocare;
    this->spStocare = new Stocare[numarSpStocare];
    for (int i = 0; i < numarSpStocare; ++i) {
        this->spStocare[i] = server.spStocare[i];
    }

    return *this;
}

Server &Server::operator=(Server&& server) {
    if(&server == this) return *this;

    if(camere != nullptr)
        delete[] camere;
    if(spStocare != nullptr)
        delete[] spStocare;

    this->numarCamere = server.numarCamere;
    this->camere = server.camere;
    this->numarSpStocare = server.numarSpStocare;
    this->spStocare = server.spStocare;

    server.camere = nullptr;
    server.numarCamere = 0;
    server.spStocare = nullptr;
    server.numarSpStocare = 0;

    return *this;
}

#endif