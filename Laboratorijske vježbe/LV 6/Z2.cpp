/* 
    TP 2018/2019: LV 6, Zadatak 2
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <type_traits>
#include <new>
#include <vector>
template <typename Tip>
auto KreirajIzvrnutiNiz(Tip pocetak, Tip kraj){
    typename std::remove_reference<decltype(*pocetak)>::type *niz=nullptr;
    Tip pom=pocetak;
    int n=0;
    while(pom!=kraj){
        n++;
        pom++;
    }
    try{
        niz=new typename std::remove_reference<decltype(*pocetak)>::type [n];
    }
    catch(std::bad_alloc){
        delete [] niz;
        throw;
    }
    for(int i=n-1; i>=0; i--) niz[i]=*pocetak++;
    return niz;
}
int main ()
{
    try{
        int n;
        std::cout<<"Koliko zelite elemenata: ";
        std::cin>>n;
        std::vector<double> v(n);
        std::cout<<"Unesite elemente: ";
        for(int i=0; i<n; i++){
            double pom;
            std::cin>>pom;
            v.push_back(pom);
        }
        double *niz=KreirajIzvrnutiNiz(v.begin(), v.end());
        std::cout<<"Kreirani niz: ";
        for(int i=0; i<n; i++) std::cout<<niz[i]<<" ";
        delete[] niz;
    }
    catch(std::bad_alloc){
        std::cout<<"Nedovoljno memorije!";
    }
	return 0;
}