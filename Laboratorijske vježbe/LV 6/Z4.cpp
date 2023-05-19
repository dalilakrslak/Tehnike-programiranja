/* 
    TP 2018/2019: LV 6, Zadatak 4
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <stdexcept>
int **KreirajTrougao(int n){
    if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
    int **grbava=nullptr;
    try{
        grbava=new int*[n];
        try{
            grbava[0]=new int [n*n];
            for(int i=1; i<n; i++) grbava[i]=grbava[i-1]+2*(i-1)+1;
        }
        catch(...){
            delete[] grbava;
            throw;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<2*i+1; j++){
                grbava[i][j]=abs(i-j)+1;
            }
        }
    }
    catch(...){
        throw;
    }
    return grbava;
}
int main ()
{
    try{
        std::cout<<"Koliko zelite redova: ";
        int n;
        std::cin>>n;
        int **grbava=KreirajTrougao(n);
        for(int i=0; i<n; i++){
            for(int j=0; j<2*i+1; j++){
                std::cout<<grbava[i][j]<<" ";
            }
        }
        delete[] grbava[0];
        delete[] grbava;
    }
    catch(std::domain_error greska){
        std::cout<<"Izuzetak: "<<greska.what();
    }
    catch(std::bad_alloc greska){
        std::cout<<"Izuzetak: Nedovoljno memorije!";
    }
	return 0;
}