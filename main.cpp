#include <iostream>
#include <memory>
#include "Camera.h"
#include "Server.h"
#include "Istoric.h"
#include "Utilizator.h"
#include "Event.h"

int main() {
//    Camera c("a", "192.168.1.100:8080");
//    std::cout << c.getBase64Frame();

//    cout<<cinput<<endl;
//
//    Camera cam2;
//    cam2 = std::move(cinput);
//

//    for (int i = 0; i < 100; ++i) {
//        Camera c("Cam", "192.168.0.100");
//        s.addCamera(c);
//    }
//    Camera c1("Hol", "192.168.1.103");
//    s.addCamera(c1);
//    Camera c2("Afara1", "192.168.1.109");
//    s.addCamera(c2);
//    s.addSpStocare(200, 40);
//
//
//    cout<<s;
//    s.stergeCamera("Afara1");
//    cout<<s;
//    cout<<"Spatiul se va termina in(zile) "<<s.estimeazaTimpUmplere()<<endl;
//
//    Server s2;
//    cin>>s2;
//    s2.stergeSpStocare(0);
//    s = s2;
//    cout<<s;



    bool pornit = true;
    int rasp = 5;
    while(pornit){
        cout<<"Selecteaza ce vrei sa faci"<<endl;
        cout<<"1 - Adauga utilizator"<<endl;
        cout<<"2 - Adauga staff"<<endl;
        cout<<"3 - Adauga camera"<<endl;
        cout<<"4 - Inhide"<<endl;

        cin>>rasp;
        switch (rasp) {
            case 1: {
                string nume, parola;
                cout << "Numele noului utilizator?" << endl;
                cin >> nume;
                cout << "Parola noului utilizator?" << endl;
                cin >> parola;
                auto u = std::make_shared<Utilizator>(nume, parola);
                EventHandler::getInstance()->propaga(EventType::ADD_UTILIZATOR, u.get());

                cout << "Introdu numele" << endl;
                cin >> nume;
                cout << "Introdu parola:" << endl;
                cin >> parola;
                shared_ptr<Utilizator> u2 = Utilizator::getUtilizator(nume);
                if(u2 != nullptr){
                    bool logat = u2->log(parola);
                    if(logat){
                        EventHandler::getInstance()->propaga(EventType::LOGIN, u2.get());
                        cout<<"Utilizator logat"<<endl;
                    }else{
                        cout<<"Parola gresita"<<endl;
                    }
                }else{
                    cout<<"Utilizatorul nu a fost gasit"<<endl;
                }
                break;
            }
            case 2:
                {
                    string nume, parola;
                    int perm;
                    cout << "Numele noului staff?" << endl;
                    cin >> nume;
                    cout << "Parola noului staff?" << endl;
                    cin >> parola;
                    cout << "Permisiunea noului staff?" << endl;
                    cin >> perm;

                    auto a = std::make_shared<Staff>(nume, parola, perm);
                    auto e = std::make_unique<Event<Utilizator*>>(a.get(), EventType::ADD_UTILIZATOR, 1, [a](EventTarget* t){
                        auto staff = dynamic_cast<Staff*>(t);
                        if(staff != nullptr)
                            cout<<"Nou staff adaugat"<<endl;
                        cout<<"Lambda: "<<t->getInfo()<<endl;

                    });
                    EventHandler::getInstance()->addEvent(e.get());

                    cout << "Numele noului utilizator?" << endl;
                    cin >> nume;
                    cout << "Parola noului utilizator?" << endl;
                    cin >> parola;
                    auto u = std::make_shared<Utilizator>(nume, parola);
                    EventHandler::getInstance()->propaga(EventType::ADD_UTILIZATOR, u.get());

                    cout << "Introdu numele" << endl;
                    cin >> nume;
                    cout << "Introdu parola:" << endl;
                    cin >> parola;
                    shared_ptr<Utilizator> u2 = Utilizator::getUtilizator(nume);
                    if(u2 != nullptr){
                        bool logat = u2->log(parola);
                        if(logat){
                            EventHandler::getInstance()->propaga(EventType::LOGIN, u2.get());
                            cout<<"Utilizator logat"<<endl;
                        }else{
                            cout<<"Parola gresita"<<endl;
                        }
                    }else{
                        cout<<"Utilizatorul nu a fost gasit"<<endl;
                    }
                }
                break;
            case 3:
                {
                    Server s;

                    Camera cinput;
                    try{
                        cin>>cinput;
                    }catch (exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout<<"Camera a fost adaugata!"<<endl;
                    s.addCamera(cinput);
                    try{
                        s.stergeCamera(0);
                        s.stergeCamera(0);
                    }catch (out_of_range& e){
                        cout<<e.what()<<endl;
                        throw logic_error("A aparut o eroare de logica la sters");
                    }

                }
                break;
            default:
                pornit = false;
        }
    }
    cout<<"Program inchis"<<endl;

//    while(true){}
    return 0;
}
