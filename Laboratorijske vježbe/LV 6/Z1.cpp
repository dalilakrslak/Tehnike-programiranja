/* 
    TP 2018/2019: LV 6, Zadatak 1
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <exception>
#include <iostream>
#include <stdexcept>
#include <limits>
template <typename Tip>
Tip *GenerirajStepeneDvojke (int n){
    if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    Tip *niz=nullptr;
    try{
        niz=new Tip[n];
    }
    catch(...){
        throw std::runtime_error("Alokacija nije uspjela");
    }
    Tip pom=1;
    for(int i=0; i<n;i++){
        niz[i]=pom;
        if(pom>=std::numeric_limits<Tip>::max()/2 && i<n-1){
            delete[] niz;
            throw std::overflow_error("Prekoracen dozvoljeni opseg");
        }
        pom*=2;
    }
    return niz;
}
int main ()
{
    try{
        std::cout<<"Koliko zelite elemenata: ";
        int n;
        std::cin>>n;
        int *niz=GenerirajStepeneDvojke<int>(n);
        for(int i=0; i<n; i++) std::cout<<niz[i]<<" ";
        delete[] niz;
    }
    catch(std::domain_error greska){
        std::cout<<"Izuzetak: "<<greska.what();
    }
    catch(std::runtime_error greska){
        std::cout<<"Izuzetak: "<<greska.what();
    }
    catch(std::overflow_error greska){
        std::cout<<"Izuzetak: "<<greska.what();
    }
	return 0;
}