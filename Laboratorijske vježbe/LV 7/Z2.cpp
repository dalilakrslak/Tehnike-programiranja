/* 
    TP 16/17 (LV 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
int main ()
{
    try{
        std::cout<<"Koliko zelite recenica: ";
        int broj_recenica;
        std::cin>>broj_recenica;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite recenice:"<<std::endl;
        char **recenice=new char*[broj_recenica];
        for(int i=0; i<broj_recenica; i++){
            char radni_prostor[1000];
            std::cin.getline(radni_prostor, sizeof radni_prostor);
            try{
                recenice[i]=new char[std::strlen(radni_prostor)+1];
                std::strcpy(recenice[i], radni_prostor);
            }
            catch(std::bad_alloc){
                for(int j=0; j<i; j++) delete[] recenice[j];
                delete[] recenice;
                throw;
            }
        }
        std::sort(recenice, (recenice+broj_recenica), [](char *pom1, char *pom2){return std::strcmp(pom1,pom2)<0;});
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0; i<broj_recenica; i++) std::cout<<recenice[i]<<std::endl;
        for(int i=0; i<broj_recenica; i++) delete[] recenice[i];
        delete[] recenice;
    }
    catch(std::bad_alloc){
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}