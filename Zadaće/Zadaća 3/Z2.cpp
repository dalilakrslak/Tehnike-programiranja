//TP 2021/2022: Zadaća 3, Zadatak 2
#include <cctype>
#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <set>
typedef std::map<std::string, std::set<int>> IndeksPojmova;
bool DaLiJeSlovo(char c){
    return((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'));
}
IndeksPojmova KreirajIndeksPojmova(std::string tekst){
    IndeksPojmova indeks_pojmova;
    for(int i=0; i<tekst.length(); i++){
        std::string rijec="";
        while(i<tekst.length() && tekst[i]==' ') i++;
        int index=i;
        while(i<tekst.length() && DaLiJeSlovo(tekst[i])){
            rijec+=std::tolower(tekst[i]);
            i++;
        }
        if(rijec=="") continue;
        auto nalazise=indeks_pojmova.find(rijec);
        if(nalazise==indeks_pojmova.end()){
            std::set<int> pomocni;
            pomocni.insert(index);
            indeks_pojmova[rijec]=pomocni;
        }
        else nalazise->second.insert(index);
    }
    return indeks_pojmova;
}
std::set<int> PretraziIndeksPojmova (std::string rijec, IndeksPojmova indeks_pojmova){
    for(auto &pom: rijec) pom=std::tolower(pom);
    std::set<int> pozicije;
    auto pretraga=indeks_pojmova.find(rijec);
    if(pretraga==indeks_pojmova.end()) throw std::logic_error("Pojam nije nadjen");
    pozicije=pretraga->second;
    return pozicije;
}
void IspisiIndeksPojmova (IndeksPojmova indeks_pojmova){
    for(auto it=indeks_pojmova.begin(); it!=indeks_pojmova.end(); it++){
        std::cout<<it->first<<": ";
        std::set<int> pom=it->second;
        int brojac(0);
        for(auto iter=pom.begin(); iter!=pom.end(); iter++){
            brojac++;
            if(brojac==pom.size()) std::cout<<*iter;
            else std::cout<<*iter<<",";
        }
        std::cout<<std::endl;
    }
}
int main ()
{
    std::cout<<"Unesite tekst: ";
    std::string tekst;
    std::getline(std::cin, tekst);
    IndeksPojmova indeks_pojmova=KreirajIndeksPojmova(tekst);
    IspisiIndeksPojmova(indeks_pojmova);
    std::string rijec;
    do{
        std::cout<<"Unesite rijec: ";
        std::getline(std::cin,rijec);
        if(rijec==".") break;
        try{
            std::set<int> skup=PretraziIndeksPojmova(rijec, indeks_pojmova);
            for(auto it=skup.begin(); it!=skup.end(); it++) std::cout<<*it<<" ";
            std::cout<<std::endl;
        }
        catch(...){
            std::cout<<"Unesena rijec nije nadjena!"<<std::endl;
        }
    }while(rijec!=".");
	return 0;
}
