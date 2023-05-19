/* 
    TP 16/17 (LV 12, Zadatak 6)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>
template <typename TipEl>
class Matrica {
    char ime_matrice;
    int br_redova, br_kolona;
    TipEl **elementi;
    static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(TipEl **elementi, int br_redova);
    void KopirajElemente(TipEl **elementi);
public:
    Matrica(int br_redova, int br_kolona, char ime = 0);
    Matrica(const Matrica &m);
    Matrica(Matrica &&m);
    ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
    Matrica &operator =(const Matrica &m);
    Matrica &operator =(Matrica &&m);
    template <typename NekiTip>
    friend std::istream &operator >>(std::istream &is, const Matrica<NekiTip> &m);
    template <typename NekiTip>
    friend std::ostream &operator <<(std::ostream &os, const Matrica<NekiTip> &m);
    template <typename NekiTip>
    friend Matrica<NekiTip> operator +(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2);
    template <typename NekiTip>
    friend Matrica<NekiTip> operator -(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2);
    template <typename NekiTip>
    friend Matrica<NekiTip> operator *(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2);
    template <typename NekiTip>
    friend Matrica<NekiTip> operator *(const Matrica<NekiTip> &m1, double broj);
    template <typename NekiTip>
    friend Matrica<NekiTip> operator *(double broj, const Matrica<NekiTip> &m2);
    Matrica<TipEl> &operator += (const Matrica<TipEl> &m){
        if(m.br_redova!=br_redova || m.br_kolona!=br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> zbir(m.br_redova, m.br_kolona);
        for(int i=0; i<m.br_redova; i++){
            for(int j=0; j<m.br_kolona; j++){
                zbir.elementi[i][j]=m.elementi[i][j]+elementi[i][j];
            }
        }
        *this=zbir;
        return *this;
    }
    Matrica<TipEl> &operator -= (const Matrica<TipEl> &m){
        if(m.br_redova!=br_redova || m.br_kolona!=br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> razlika(m.br_redova, m.br_kolona);
        for(int i=0; i<m.br_redova; i++){
            for(int j=0; j<m.br_kolona; j++){
                razlika.elementi[i][j]=elementi[i][j]-m.elementi[i][j];
            }
        }
        *this=razlika;
        return *this;
    }
    Matrica<TipEl> &operator *= (const Matrica<TipEl> &m){
        if(br_kolona!=m.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        Matrica<TipEl> rezultantna(br_redova, m.br_kolona);
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<m.br_kolona; j++){
                TipEl suma={};
                for(int k=0; k<br_kolona; k++){
                    suma+=(elementi[i][k]*m.elementi[k][j]);
            	}
            rezultantna.elementi[i][j]=suma;
            }
        }
        *this=rezultantna;
        return *this;
    }
    Matrica<TipEl> &operator *= (TipEl broj){
        Matrica<TipEl> rezultantna(br_redova, br_kolona);
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<br_kolona; j++){
                rezultantna.elementi[i][j]=elementi[i][j]*broj;
            }
        }
        *this=rezultantna;
        return *this;
    }
    TipEl &operator()(int i, int j){
        if(i<=0 || i>br_redova || j<=0 || j>br_kolona) throw std::range_error("Neispravan indeks");
        return elementi[i-1][j-1];
    }
    TipEl operator()(int i, int j) const{
        if(i<=0 || i>br_redova || j<=0 || j>br_kolona) throw std::range_error("Neispravan indeks");
        return elementi[i-1][j-1];
    }
    TipEl* &operator[](int i){return elementi[i];}
    TipEl* operator[](int i) const{return elementi[i];}
    operator std::string() const{
        std::string string;
        string.push_back('{');
        for(int i=0; i<br_redova; i++){
            string.push_back('{');
            for(int j=0; j<br_kolona; j++){
                if(j==br_kolona-1){
                    string+=std::to_string(int(elementi[i][j]));
                    string.push_back('}');
                    break;
                }
                string+=std::to_string(int(elementi[i][j]));
                string.push_back(',');
            }
            if(i==br_redova-1){
                string.push_back('}');
                break;
            }
            string.push_back(',');
        }
        return string;
    }
};
template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
    TipEl **elementi = new TipEl*[br_redova]{};
    try {
        for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
    }
    catch(...) {
        DealocirajMemoriju(elementi, br_redova); throw;
    }
    return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
    for(int i = 0; i < br_redova; i++) delete[] elementi[i];
    delete[] elementi;
}
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime), elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
    for(int i = 0; i < br_redova; i++)
        for(int j = 0; j < br_kolona; j++)
            Matrica::elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova), br_kolona(m.br_kolona), ime_matrice(m.ime_matrice), elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
    KopirajElemente(m.elementi);
}
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice) {
    m.br_redova = 0; m.elementi = nullptr;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) {
    if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
        TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
        DealocirajMemoriju(elementi, br_redova);
        elementi = novi_prostor;
    }
    else if(br_redova > m.br_redova)
        for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
    br_redova = m.br_redova; br_kolona = m.br_kolona;
    ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);
    return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) {
    std::swap(br_redova, m.br_redova); std::swap(br_kolona, m.br_kolona);
    std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);
    return *this;
}
template <typename NekiTip>
std::istream &operator >>(std::istream &is, const Matrica<NekiTip> &m){
    for(int i=0; i<m.br_redova; i++){
        for(int j=0; j<m.br_kolona; j++){
            std::cout<<m.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
            std::cin>>m.elementi[i][j];
        }
    }
    return is;
}
template <typename NekiTip>
std::ostream &operator <<(std::ostream &os, const Matrica<NekiTip> &m){
    int pom=os.width();
    for(int i=0; i<m.br_redova; i++){
        for(int j=0; j<m.br_kolona; j++){
            os<<std::setw(pom)<<m.elementi[i][j];
        }
        std::cout<<std::endl;
    }
    return os;
}
template <typename NekiTip>
Matrica<NekiTip> operator +(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2){
    if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<NekiTip> zbir(m1.br_redova, m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m2.br_kolona; j++){
            zbir.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
        }
    }
    return zbir;
}
template <typename NekiTip>
Matrica<NekiTip> operator -(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2){
    if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<NekiTip> razlika(m1.br_redova, m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m2.br_kolona; j++){
            razlika.elementi[i][j]=m1.elementi[i][j]-m2.elementi[i][j];
        }
    }
    return razlika;
}
template <typename NekiTip>
Matrica<NekiTip> operator *(const Matrica<NekiTip> &m1, const Matrica<NekiTip> &m2){
    if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<NekiTip> rezultantna(m1.br_redova, m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m2.br_kolona; j++){
            NekiTip suma={};
            for(int k=0; k<m1.br_kolona; k++){
                suma+=(m1.elementi[i][k]*m2.elementi[k][j]);
            }
            rezultantna.elementi[i][j]=suma;
        }
    }
    return rezultantna;
}
template <typename NekiTip>
Matrica<NekiTip> operator *(const Matrica<NekiTip> &m1, double broj){
    Matrica<NekiTip> rezultantna(m1.br_redova, m1.br_kolona);
    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m1.br_kolona; j++){
            rezultantna.elementi[i][j]=m1.elementi[i][j]*broj;
        }
    }
    return rezultantna;
}
template <typename NekiTip>
Matrica<NekiTip> operator *(double broj, const Matrica<NekiTip> &m2){
    return m2*broj;
}
/*template <typename NekiTip>
Matrica<NekiTip>&Matrica<NekiTip>::operator*=(const Matrica<Tip> &m);*/
int main() {
    int m, n;
    std::cout << "Unesi broj redova i kolona za matrice:\n";
    std::cin >> m >> n;
    try {
        Matrica<double> a(m, n, 'A'), b(m, n, 'B');
        std::cout << "Unesi matricu A:\n";
        std::cin>>a;
        std::cout << "Unesi matricu B:\n";
        std::cin>>b;
        std::cout << "Zbir ove dvije matrice je:\n";
        std::cout<<std::setw(7)<<a+b;
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
    }
    return 0;
}