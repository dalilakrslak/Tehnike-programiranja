//TP 2021/2022: Zadaća 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include <memory>
struct Dijete{
    std::string ime;
    std::shared_ptr<Dijete> sljedeci;
};
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
    std::vector<std::set<std::string>> formirani;
    int viseclanova=mod(imena_djece.size(), broj_timova);
    int br_clanova1=imena_djece.size()/broj_timova;
    int br_clanova2=br_clanova1;
    if(viseclanova!=0) br_clanova2++;
    std::shared_ptr<Dijete> pocetak=nullptr, prethodni=nullptr;
    int i=0;
    for(;;){
        if(i==imena_djece.size()) break;
        std::shared_ptr<Dijete> novi=std::make_shared<Dijete>();
        novi->ime=imena_djece.at(i);
        novi->sljedeci=nullptr;
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
        if(i==imena_djece.size()-1) prethodni->sljedeci=pocetak;
        i++;
    }
    std::shared_ptr<Dijete> temp=pocetak;
    int brisi=imena_djece.size();
    int duzina=0;
    for(int i=0; i<viseclanova; i++){
        std::set<std::string> pomoc;
        for(int j=0; j<br_clanova2; j++){
            if(brisi==1){
                pomoc.insert(temp->ime);
                temp->sljedeci=nullptr;
                break;
            }
            while(duzina>1){
                temp=temp->sljedeci;
                prethodni=prethodni->sljedeci;
                duzina--;
            }
            pomoc.insert(temp->ime);
            duzina=DuzinaImena(temp->ime);
            prethodni->sljedeci=temp->sljedeci;
            temp=prethodni->sljedeci;
            brisi--;
        }
        formirani.push_back(pomoc);
    }    
    for(int i=viseclanova; i<broj_timova; i++){
        std::set<std::string> pomoc;
        for(int j=0; j<br_clanova1; j++){
            if(brisi==1){
                pomoc.insert(temp->ime);
                temp->sljedeci=nullptr;
                break;
            }
            while(duzina>1){
                temp=temp->sljedeci;
                prethodni=prethodni->sljedeci;
                duzina--;
            }
            pomoc.insert(temp->ime);
            duzina=DuzinaImena(temp->ime);
            prethodni->sljedeci=temp->sljedeci;
            temp=prethodni->sljedeci;
            brisi--;
        }
        formirani.push_back(pomoc);
    }
    return formirani;
}
int main ()
{
    std::cout<<"Unesite broj djece: ";
    int broj_djece=0;
    std::cin>>broj_djece;
    std::cout<<"Unesite imena djece: ";
    std::vector<std::string> imena_djece(broj_djece);
    std::cin.ignore(10000,'\n');
    for(auto &pom: imena_djece) std::getline(std::cin, pom);
    std::cout<<"Unesite broj timova: ";
    int broj_timova=0;
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
