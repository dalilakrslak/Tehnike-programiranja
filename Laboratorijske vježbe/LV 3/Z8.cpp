//TP 2021/2022: LV 3, Zadatak 8
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
std::string IzdvojiRijec(std::string s, int x){
    if(x<1) throw std::range_error("Pogresan redni broj rijeci!");
    int broj_rijeci=0;
    for(int i=0; i<s.length(); i++){
        while(s[i]==' ' && i!=s.length()) i++;
        if(i==s.length()) break;
        broj_rijeci++;
        while(s[i]!=' ' && i<s.length()) i++;
    }
    if(x>broj_rijeci) throw std::range_error("Pogresan redni broj rijeci!");
    std::string rijec;
    int redni_broj=0;
    for(int i=0; i<s.length(); i++){
        while(s[i]==' ' && i!=s.length()) i++;
        if(i==s.length()) break;
        if(s[i]!=' '){
            redni_broj++;
            if(redni_broj==x){
                while(s[i]!=' ' && i<s.length()){
                    rijec.push_back(s[i]);
                    i++;
                }
                break;
            }
            else while(s[i]!=' ') i++;
        }
    }
    return rijec;
}
int main ()
{
    try{
        int n;
        std::cout<<"Unesite redni broj rijeci: ";
        std::cin>>n;
        std::cin.ignore(1000,'\n');
        std::string recenica;
        std::cout<<"Unesite recenicu: ";
        std::getline(std::cin,recenica);
        std::string rijec=IzdvojiRijec(recenica, n);
        std::cout<<"Rijec na poziciji "<<n<<" je "<<rijec;
    }
    catch(std::range_error izuzetak){
        std::cout<<"IZUZETAK: "<<izuzetak.what()<<std::endl;
    }
	return 0;
}
