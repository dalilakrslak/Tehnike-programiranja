/* 
    TP 16/17 (LV 7, Zadatak 3)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
int main ()
{
    try{
        std::cout<<"Koliko zelite recenica: ";
        int broj_recenica;
        std::cin>>broj_recenica;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite recenice:"<<std::endl;
        std::string **recenice=new std::string *[broj_recenica];
        for(int i=0; i<broj_recenica; i++){
            recenice[i]=nullptr;
            try{
                recenice[i]=new std::string;
                std::getline(std::cin, *(recenice[i]));
            }
            catch(std::bad_alloc){
                for(int j=0; j<i; j++) delete recenice[j];
                delete[] recenice;
                throw;
            }
        }
        std::sort(recenice, (recenice+broj_recenica), [](std::string *pom1, std::string *pom2){return *pom1<*pom2;});
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0; i<broj_recenica; i++) std::cout<<*recenice[i]<<std::endl;
        for(int i=0; i<broj_recenica; i++) delete recenice[i];
        delete[] recenice;
    }
    catch(std::bad_alloc){
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}