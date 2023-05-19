//TP 2021/2022: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
struct Matrica{
    char ime_matrice;
    int br_redova, br_kolona;
    TipElemenata **elementi=nullptr;
};
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat){
    if(!mat.elementi) return;
    for(int i=0; i<mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi=nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime=0){
    Matrica<TipElemenata> mat;
    mat.br_redova=br_redova; mat.br_kolona=br_kolona; mat.ime_matrice=ime;
        mat.elementi=new TipElemenata*[br_redova]{};
    try{
        for(int i=0; i<br_redova; i++) mat.elementi[i]=new TipElemenata[br_kolona];
    }
    catch(...){
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata>
void UnesiMatricu(char ime, Matrica<TipElemenata> &mat){
    for(int i=0; i<mat.br_redova; i++)
        for(int j=0; j<mat.br_kolona; j++){
            std::cout<<ime<<"("<<i+1<<","<<j+1<<") = ";
            std::cin>>mat.elementi[i][j];
        }
}
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false){
    for(int i=0; i<mat.br_redova; i++){
        for(int j=0; j<mat.br_kolona; j++){
            std::cout<<std::setw(sirina_ispisa)<<std::setprecision(preciznost)<<mat.elementi[i][j];
        }
        std::cout<<std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2){
    if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i=0; i<m1.br_redova; i++)
        for(int j=0; j<m1.br_kolona; j++)
            m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
    return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2){
    if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m2.br_kolona; j++){
            TipElemenata suma{};
            for(int k=0; k<m2.br_redova; k++) suma+=m1.elementi[i][k]*m2.elementi[k][j];
            m3.elementi[i][j]=suma;
        }
    }
    return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &A, std::vector<double> p){
    if(A.br_kolona!=A.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
    Matrica<TipElemenata> polinom;
    polinom=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
    if(p.size()==0){
        for(int i=0; i<A.br_redova; i++){
            for(int j=0; j<A.br_kolona; j++){
                polinom.elementi[i][j]=0;
            }
        }
        return polinom;
    }
    for(int k=0; k<p.size(); k++){
        if(k==0){
            for(int i=0; i<A.br_redova; i++){
                for(int j=0; j<A.br_kolona; j++){
                    if(i==j) polinom.elementi[i][j]=p.at(0);
                    else polinom.elementi[i][j]=0;
                }
            }
        }
        else if(k==1){
            Matrica<TipElemenata> pom;
            try{
                pom=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
            }
            catch(...){
                throw;
            }
            for(int i=0; i<A.br_redova; i++){
                for(int j=0; j<A.br_kolona; j++){
                    pom.elementi[i][j]=A.elementi[i][j]*p.at(1);
                }
            }
            Matrica<TipElemenata> pomocna;
            pomocna=ZbirMatrica(polinom, pom);
            for(int i=0; i<A.br_redova; i++)
                for(int j=0; j<A.br_kolona; j++)
                    polinom.elementi[i][j]=pomocna.elementi[i][j];
            UnistiMatricu(pomocna);
            UnistiMatricu(pom);
        }
        else{
            Matrica<TipElemenata> mnozi;
            try{
                mnozi=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
            }
            catch(...){
                UnistiMatricu(polinom);
                throw;
            }
            for(int i=0; i<A.br_redova; i++){
                for(int j=0; j<A.br_kolona; j++) mnozi.elementi[i][j]=A.elementi[i][j];
            }
            int brojac=k-1;
            while(brojac!=0){
                Matrica<TipElemenata> pomoc;
                pomoc=ProduktMatrica(mnozi, A);
                for(int i=0; i<A.br_redova; i++)
                    for(int j=0; j<A.br_kolona; j++)
                        mnozi.elementi[i][j]=pomoc.elementi[i][j];
                brojac--;
                UnistiMatricu(pomoc);
            }
            Matrica<TipElemenata> pom;
            try{
                pom=StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
            }
            catch(...){
                UnistiMatricu(polinom);
                UnistiMatricu(mnozi);
                throw;
            }
            for(int i=0; i<A.br_redova; i++){
                for(int j=0; j<A.br_kolona; j++) pom.elementi[i][j]=mnozi.elementi[i][j]*p.at(k);
            }
            Matrica<TipElemenata> pomocna;
            pomocna=ZbirMatrica(polinom, pom);
            for(int i=0; i<A.br_redova; i++)
                for(int j=0; j<A.br_kolona; j++)
                    polinom.elementi[i][j]=pomocna.elementi[i][j];
            UnistiMatricu(pomocna);
            UnistiMatricu(mnozi);
            UnistiMatricu(pom);
        }
    }
    return polinom;
}
int main ()
{
    std::cout<<"Unesite dimenziju kvadratne matrice: ";
    int dimenzija=0;
    std::cin>>dimenzija;
    std::cout<<"Unesite elemente matrice A: "<<std::endl;
    Matrica<double> A;
    try{ 
        A=StvoriMatricu<double>(dimenzija, dimenzija,'A');
    }
    catch(...){
        std::cout<<"Greska";
    }
    UnesiMatricu('A', A);
    std::cout<<"Unesite red polinoma: ";
    int n=0;
    std::cin>>n;
    std::cout<<"Unesite koeficijente polinoma: ";
    std::vector<double> koef(n+1);
    for(auto &pom: koef) std::cin>>pom;
    Matrica<double> polinom;
    try{
        polinom=MatricniPolinom(A, koef);
    }
    catch(...){
        std::cout<<"Greska";
    }
    IspisiMatricu(polinom, 10, 6, true);
    UnistiMatricu(A);
    UnistiMatricu(polinom);
	return 0;
}
