/* 
    TP 2018/2019: LV 6, Zadatak 6
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>
template <typename Tip>
auto KreirajDinamickuKopiju2D(Tip kontejner){
    std::remove_reference_t<decltype(kontejner.at(0).at(0))> **dvade=nullptr;
    int n(0);
    for(int i=0; i<kontejner.size(); i++){
        for(int j=0; j<kontejner.at(i).size(); j++){
            n++;
        }
    }
    try{
        dvade=new std::remove_reference_t<decltype(kontejner.at(0).at(0))> *[kontejner.size()];
        try{
            dvade[0]= new std::remove_reference_t<decltype(kontejner.at(0).at(0))> [n];
            for(int i=1; i<kontejner.size(); i++) dvade[i]=dvade[i-1]+kontejner.at(i-1).size();
        }
        catch(...){
            delete[] dvade;
            throw;
        }
        for(int i=0; i<kontejner.size(); i++){
            for(int j=0; j<kontejner.at(i).size(); j++){
                dvade[i][j]=kontejner.at(i).at(j);
            }
        }
    }catch(...){
        throw;
    }
    return dvade;
}
int main ()
{
    try{
        std::cout<<"Unesite broj redova kvadratne matrice: ";
        int n;
        std::cin>>n;
        std::vector<std::deque<int>> nesto(n);
        for(auto &red: nesto) red.resize(n);
        std::cout<<"Unesite elemente matrice: ";
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                std::cin>>nesto.at(i).at(j);
            }
        }
        auto kopija=KreirajDinamickuKopiju2D(nesto);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                std::cout<<kopija[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        delete[] kopija[0];
        delete[] kopija;
    }
    catch(...){
        std::cout<<"Nedovoljno memorije";
    }
	return 0;
}