//TP 2021/2022: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
bool DaLiSeDameNapadaju(std::vector<std::vector<bool>> ploca){
    int m=ploca.size();
    for(int i=0; i<m; i++){
        int n=ploca.at(i).size();
        for(int j=0; j<n; j++){
            if(ploca.at(i).at(j)){
                if(j-1>=0){
                    for(int k=0; k<j; k++){
                        if(ploca.at(i).at(k)) return true;
                    }
                }
                if(j+1<n){
                    for(int k=j+1; k<n; k++){
                        if(ploca.at(i).at(k)) return true;
                    }
                }
                if(i-1>=0){
                    for(int k=0; k<i; k++){
                        if(j<ploca.at(k).size() && ploca.at(k).at(j)) return true;
                    }
                }
                if(i+1<m){
                    for(int k=i+1; k<m; k++){
                        if(j<ploca.at(k).size() && ploca.at(k).at(j)) return true;
                    }
                }
                for(int k=0; k<m; k++){
                    for(int l=0; l<ploca.at(k).size(); l++){
                        if(k+l==i+j && ploca.at(k).at(l) && (k!=i || l!=j)) return true;
                    }
                }
                for(int k=0; k<m; k++){
                    for(int l=0; l<ploca.at(k).size(); l++){
                        if(l-k==j-i && ploca.at(k).at(l) && (k!=i || l!=j)) return true;
                    }
                }
            }
        }
    }
    return false;
}
int main ()
{
    std::vector<std::vector<bool>> ploca;
    std::cout<<"Unesite opis sahovske ploce:"<<std::endl<<"(Q za kraljicu, bilo sta drugo za prazno polje, ENTER naprazno za kraj unosa):";
    for(int i=0; ;i++){
        bool stop=0;
        for(int j=0; ;j++){
            char c;
            std::cin.get(c);
            if(j==0 && c=='\n'){
                stop=1;
                break;
            }
            if(c=='\n') break;
            ploca.resize(i+1);
            ploca.at(i).resize(j+1);
            if(c=='Q') ploca.at(i).at(j)=true;
            else ploca.at(i).at(j)=false;
        }
        if(stop) break;
    }
    bool napad=DaLiSeDameNapadaju(ploca);
    if(napad) std::cout<<std::endl<<"Dame se medjusobno napadaju.";
    else std::cout<<std::endl<<"Dame se medjusobno ne napadaju.";
	return 0;
}
