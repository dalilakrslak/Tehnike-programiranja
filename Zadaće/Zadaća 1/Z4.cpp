//TP 2021/2022: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <array>
#include <stdexcept>
#include <vector>
#include <string>
std::array<std::vector<std::string>, 100> RazvrstajRijeciPoDuzini(std::string recenica){
    for(int i=0; i<recenica.length(); i++){
        if(recenica.at(i)>='a' && recenica.at(i)<='z') recenica.at(i)+='A'-'a';
    }
    std::array<std::vector<std::string>, 100> vrati;
    for(int i=0; i<recenica.length(); i++){
        if((recenica.at(i)>='A' && recenica.at(i)<='Z')||(recenica.at(i)>='0' && recenica.at(i)<='9')){
            int duzina_rijeci=0;
            std::string izdvojena_rijec="";
            while(i<recenica.length() && ((recenica.at(i)>='A' && recenica.at(i)<='Z')||(recenica.at(i)>='0' && recenica.at(i)<='9'))){
                izdvojena_rijec.push_back(recenica.at(i));
                duzina_rijeci++;
                i++;
            }
            if(duzina_rijeci>99) throw std::range_error ("Predugacka rijec!");
            vrati.at(duzina_rijeci).push_back(izdvojena_rijec);
        }
    }
    return vrati;
}
int main ()
{
    try{
        std::string recenica;
        std::cout<<"Unesite recenicu: ";
        getline(std::cin, recenica);
        std::array<std::vector<std::string>, 100> rijeci=RazvrstajRijeciPoDuzini(recenica);
        for(int i=0; i<=99; i++){
            if(rijeci.at(i).size()>0){
                std::cout<<std::endl<<"Duzina "<<i<<": ";
                for(int j=0; j<rijeci.at(i).size(); j++){
                    std::cout<<rijeci.at(i).at(j)<<" ";
                }
            }
        }
    }
    catch(std::range_error greska){
        std::cout<<"Greska: Recenica sadrzi predugacku rijec!";
    }
	return 0;
}
