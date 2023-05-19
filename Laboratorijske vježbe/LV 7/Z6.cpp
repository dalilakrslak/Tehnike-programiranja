/* 
    TP 16/17 (LV 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <list>
template<typename Tip>
void SortirajListu(std::list<Tip> &lista){
    for(auto i=lista.begin(); i!=lista.end(); i++){
        for(auto j=i; j!=lista.end(); j++){
            if(*i>*j){
                auto pom=*i;
                *i=*j;
                *j=pom;
            }
        }
    }
}
int main ()
{
    std::cout<<"Koliko ima elemenata: ";
    int n;
    std::cin>>n;
    std::list<int> lista;
    std::cout<<"Unesite elemente: ";
    while(n!=0){
        n--;
        int pom;
        std::cin>>pom;
        lista.push_back(pom);
    }
    SortirajListu(lista);
    std::cout<<"Sortirana lista: ";
    for(auto x: lista){
        std::cout<<x<<" ";
    }
	return 0;
}