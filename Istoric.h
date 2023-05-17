#ifndef PROIECT1_ISTORIC_H
#define PROIECT1_ISTORIC_H

#include <string>
#include <list>
#include <ostream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

class Istoric{
    list<string> itemeIstoric;

    string numeIstoric;

public:
    Istoric(string numeIstoric){
        this->numeIstoric = numeIstoric;
    }

    Istoric(Istoric& istoric){
        this->numeIstoric = istoric.numeIstoric;
        this->itemeIstoric = istoric.itemeIstoric;
    }

    Istoric(Istoric&& istoric){
        this->numeIstoric = istoric.numeIstoric;
        this->itemeIstoric = istoric.itemeIstoric;

        istoric.itemeIstoric.clear();
        istoric.numeIstoric = "";
    }

    ~Istoric() {

    }
    void setNumeIstoric(const string &numeIstoric) {
        Istoric::numeIstoric = numeIstoric;
    }

    void addIstoric(const char* ist){
        string s = ist;
        itemeIstoric.push_back(getTime()+" >> "+s);
    }

    void addIstoric(string ist){
        itemeIstoric.push_back(getTime()+" >> "+ist);
    }

    const string &getNumeIstoric() const {
        return numeIstoric;
    }

    const list<string> &getItemeIstoric() const {
        return itemeIstoric;
    }

    static string getTime(){
        auto timp = std::chrono::system_clock::now();
        std::time_t timp_t = std::chrono::system_clock::to_time_t(timp);
        std::tm* timp_tm = std::localtime(&timp_t);

        std::ostringstream oss;
        oss << std::put_time(timp_tm, "%Y-%m-%d,%H:%M");
        std::string formattedTime = oss.str();
        return formattedTime;
    }

    ostream& printIstoric(ostream& os){
        os << "Istoric " << numeIstoric << ":" << endl;
        int nr = 1;
        for (auto &item : itemeIstoric) {
            os << " " << nr << ": " << item<<endl;
            nr++;
        }
        return os;
    }


};

#endif //PROIECT1_ISTORIC_H
