#include <iostream>
#include "Camera.h"
#include "Server.h"

int main() {
//    Camera c("a", "192.168.1.100:8080");
//    std::cout << c.getBase64Frame();
    Camera cinput;
    cin>>cinput;
    cout<<cinput<<endl;
    Server s;
    s.addCamera(cinput);
    for (int i = 0; i < 100; ++i) {
        Camera c("Cam", "192.168.0.100");
        s.addCamera(c);
    }
    Camera c1("Hol", "192.168.1.103");
    s.addCamera(c1);
    Camera c2("Afara1", "192.168.1.109");
    s.addCamera(c2);
    s.addSpStocare(200, 40);


    cout<<s;
    s.stergeCamera("Afara1");
    cout<<s;
    cout<<"Spatiul se va termina in(zile) "<<s.estimeazaTimpUmplere()<<endl;

    Server s2;
    cin>>s2;
    s2.stergeSpStocare(0);
    cout<<s2;

    return 0;
}
