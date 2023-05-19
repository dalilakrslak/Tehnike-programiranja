//TP 2021/2022: LV 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
std::string VelikaSlova(std::string s){
    for(char &c: s){
        if(c>='a' && c<='z') c+='A'-'a';
    }
    return s;
}
void IzdvojiKrajnjeRijeci(std::vector<std::string> spisak, std::string &prva, std::string &posljednja){
    prva="";
    posljednja="";
    if(spisak.size()>0){
        prva=spisak[0];
        posljednja=spisak[0];
    }
    for(int i=0; i<spisak.size(); i++){
        if(VelikaSlova(spisak[i])<VelikaSlova(prva)) prva=spisak[i];
        if(VelikaSlova(spisak[i])>VelikaSlova(posljednja)) posljednja=spisak[i];
    }
}
void ZadrziDuplikate(std::vector<std::string> &spisak){
    std::vector<std::string> bez_duplih;
    for(int i=0; i<spisak.size(); i++){
        bool jednaki=0;
        for(int j=i+1; j<spisak.size(); j++){
            if(spisak[i]==spisak[j]) jednaki=1;
        }
        if(jednaki){
            bool ponavljanje=0;
            for(int j=0; j<bez_duplih.size(); j++){
                if(spisak[i]==bez_duplih[j]) ponavljanje=1;
            }
            if(!ponavljanje) bez_duplih.push_back(spisak[i]);
        }
    }
    spisak=bez_duplih;
}
int main ()
{
    std::cout<<"Koliko zelite unijeti rijeci: ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite rijeci: ";
    std::vector<std::string> spisak;
    for(int i=0; i<n; i++){
        std::string pom;
        std::cin>>pom;
        spisak.push_back(pom);
    }
    std::string prva,posljednja;
    IzdvojiKrajnjeRijeci(spisak,prva,posljednja);
    std::cout<<"Prva rijec po abecednom poretku je: "<<prva<<std::endl;
    std::cout<<"Posljednja rijec po abecednom poretku je: "<<posljednja<<std::endl;
    ZadrziDuplikate(spisak);
    std::cout<<"Rijeci koje se ponavljaju su: ";
    for(std::string pom: spisak) std::cout<<pom<<" ";
	return 0;
}
