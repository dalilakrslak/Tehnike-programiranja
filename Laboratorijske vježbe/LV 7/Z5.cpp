/* 
    TP 16/17 (LV 7, Zadatak 5)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <memory>
int main ()
{
    try{
        std::cout<<"Koliko zelite recenica: ";
        int broj_recenica;
        std::cin>>broj_recenica;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite recenice:"<<std::endl;
        std::shared_ptr<std::shared_ptr<std::string>> recenice(new std::shared_ptr<std::string>[broj_recenica], [](auto *recenice){delete[] recenice;});
        for(int i=0; i<broj_recenica; i++){
            recenice.get()[i]=std::make_shared<std::string>();
            std::getline(std::cin, *(recenice.get()[i]));
        }
        std::sort(&recenice.get()[0], &recenice.get()[broj_recenica-1]+1, [](auto pom1, auto pom2){return *pom1<*pom2;});
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0; i<broj_recenica; i++) std::cout<<*recenice.get()[i]<<std::endl;
    }
    catch(std::bad_alloc){
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}