//TP 2021/2022: Zadaća 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>
#include <set>
#include <list>
int mod(int n, int k){
    return n%k;
}
int DuzinaImena(std::string ime){
    int duz=0;
    for(auto x: ime){
        if(x>='A' && x<='Z') duz++;
        else if(x>='a' && x<='z') duz++;
        else if(x>='0' && x<='9') duz++;
    }
    return duz;
}
std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> imena_djece, int broj_timova){
    if(broj_timova<1 || broj_timova>imena_djece.size()) throw std::logic_error("Razvrstavanje nemoguce");
    std::vector<std::set<std::string>> formirani(broj_timova);
    int viseclanova=mod(imena_djece.size(), broj_timova);
    int br_clanova1=imena_djece.size()/broj_timova;
    int br_clanova2=br_clanova1;
    if(viseclanova!=0) br_clanova2++;
    std::list<std::string> pomocna;
    for(auto pom: imena_djece) pomocna.push_back(pom);
    auto pomoc=pomocna.begin();
    for(int i=0; i<viseclanova; i++){
        for(int j=0; j<br_clanova2; j++){
            formirani.at(i).insert(*pomoc);
            int duzina=DuzinaImena(*pomoc);
            auto provjera=pomoc; provjera++;
            pomoc=pomocna.erase(pomoc);
            if(provjera==pomocna.end()) pomoc++;
            while(duzina!=1){
                pomoc++;
                if(pomoc==pomocna.end()) pomoc=pomocna.begin();
                duzina--;
            }
        }
    }
    for(int i=viseclanova; i<broj_timova; i++){
        for(int j=0; j<br_clanova1; j++){
            formirani.at(i).insert(*pomoc);
            int duzina=DuzinaImena(*pomoc);
            auto provjera=pomoc; provjera++;
            pomoc=pomocna.erase(pomoc);
            if(provjera==pomocna.end()) pomoc++;
            while(duzina!=1){
                pomoc++;
                if(pomoc==pomocna.end()) pomoc=pomocna.begin();
                duzina--;
            }
        }
    }
    return formirani;
}
int main ()
{
    std::cout<<"Unesite broj djece: ";
    int broj_djece;
    std::cin>>broj_djece;
    std::cout<<"Unesite imena djece: ";
    std::vector<std::string> imena_djece(broj_djece);
    std::cin.ignore(10000,'\n');
    for(auto &pom : imena_djece) std::getline(std::cin, pom);
    std::cout<<"Unesite broj timova: ";
    int broj_timova;
    std::cin>>broj_timova;
    try{
        std::vector<std::set<std::string>> formirani=Razvrstavanje(imena_djece, broj_timova);
        for(int i=0; i<formirani.size(); i++){
            std::cout<<"Tim "<<i+1<<": ";
            int j=0;
            for(auto pom: formirani.at(i)){
                if(j<formirani.at(i).size()-1) std::cout<<pom<<", ";
                else std::cout<<pom;
                j++;
            }
            std::cout<<std::endl;
        }
    }
    catch(std::logic_error er){
        std::cout<<"Izuzetak: "<<er.what();
    }
	return 0;
}
