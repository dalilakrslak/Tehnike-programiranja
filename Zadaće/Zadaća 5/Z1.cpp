//TP 2021/2022: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <limits>
void ProvjeriSabiranjeIOduzimanje(long long int x, long long int y){
    long long int najmanja=std::numeric_limits<long long int>::max();
    long long int najveca=std::numeric_limits<long long int>::min();
    if((y>=0 && x>najveca-y) || (y<0 && x<najmanja-y)) throw std::overflow_error("Nemoguce dobiti tacan rezultat"); 
}
void ProvjeriMnozenje(long long int x, long long int y){
    long long int najmanja=std::numeric_limits<long long int>::max();
    long long int najveca=std::numeric_limits<long long int>::min();
    if((y>=0 && (x<najmanja || x>najveca/y)) || (y<0 && (x==najmanja || -x>najveca/(-y)))) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
}
class Razlomak{
    long long int brojnik, nazivnik;
    static long long int NZD(long long int p, long long int q){
        if(p<0) p=-p;
        if(q<0) q=-q;
        if(q==0) return p;
        p=p%q;
        return NZD(q,p);
    }
public:
    Razlomak(long long int b=0, long long int n=1){
        if(n==0) throw std::logic_error("Nekorektan razlomak");
        if(n<0) {
            b=-b; n=-n;
        }
        long long int nzd=NZD(b,n);
        brojnik=b/nzd; nazivnik=n/nzd;
    }
    long long int DajBrojnik() const{
        return brojnik;
    }
    long long int DajNazivnik() const{
        return nazivnik;
    }
    friend Razlomak operator +(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator -(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator *(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator /(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak operator +(Razlomak r);
    friend Razlomak operator -(Razlomak r);
    friend Razlomak &operator +=(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak &operator -=(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak &operator *=(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak &operator /=(const Razlomak &r1, const Razlomak &r2);
    friend Razlomak &operator ++(Razlomak &r);
    friend Razlomak operator ++(Razlomak &r, int);
    friend Razlomak &operator --(Razlomak &r);
    friend Razlomak operator --(Razlomak &r, int);
    friend bool operator <(Razlomak r1, Razlomak r2);
    friend bool operator >(Razlomak r1, Razlomak r2);
    friend bool operator <=(Razlomak r1, Razlomak r2);
    friend bool operator >=(Razlomak r1, Razlomak r2);
    friend bool operator ==(const Razlomak &r1, const Razlomak &r2);
    friend bool operator !=(const Razlomak &r1, const Razlomak &r2);
    friend std::ostream &operator <<(std::ostream &tok, const Razlomak &r);
    friend std::istream &operator >>(std::istream &tok, const Razlomak &r);
    operator long double() const{
        return (long double)brojnik/nazivnik;
    }
};
    Razlomak operator +(const Razlomak &r1, const Razlomak &r2){
        long long int r=r1.NZD(r1.nazivnik, r2.nazivnik);
        Razlomak zbir;
        zbir.brojnik=r1.brojnik*(r2.nazivnik/r)+r2.brojnik*(r1.nazivnik/r);
        zbir.nazivnik=r1.nazivnik*(r2.nazivnik/r);
        zbir=Razlomak(zbir.brojnik, zbir.nazivnik);
        return zbir;
    }
    Razlomak operator -(const Razlomak &r1, const Razlomak &r2){
        long long int r=r1.NZD(r1.nazivnik, r2.nazivnik);
        Razlomak razlika;
        razlika.brojnik=r1.brojnik*(r2.nazivnik/r)-r2.brojnik*(r1.nazivnik/r);
        razlika.nazivnik=r1.nazivnik*(r2.nazivnik/r);
        razlika=Razlomak(razlika.brojnik, razlika.nazivnik);
        return razlika;
    }
    Razlomak operator *(const Razlomak &r1, const Razlomak &r2){
        long long int s=r1.NZD(r1.brojnik, r2.nazivnik);
        long long int t=r1.NZD(r2.brojnik, r1.nazivnik);
        Razlomak proizvod;
        proizvod.brojnik=(r1.brojnik/s)*(r2.brojnik/t);
        proizvod.nazivnik=(r1.nazivnik/t)*(r2.nazivnik/s);
        proizvod=Razlomak(proizvod.brojnik, proizvod.nazivnik);
        return proizvod;
    }
    Razlomak operator /(const Razlomak &r1, const Razlomak &r2){
        long long int u=r1.NZD(r1.brojnik, r2.brojnik);
        long long int r=r1.NZD(r1.nazivnik, r2.nazivnik);
        Razlomak kolicnik;
        kolicnik.brojnik=(r1.brojnik/u)*(r2.nazivnik/r);
        kolicnik.nazivnik=(r1.nazivnik/r)*(r2.brojnik/u);
        kolicnik=Razlomak(kolicnik.brojnik, kolicnik.nazivnik);
        return kolicnik;
    }
    Razlomak operator +(Razlomak r){
        return r;
    }
    Razlomak operator -(Razlomak r){
        r.brojnik=-r.brojnik;
        return r;
    }
    Razlomak &operator +=(Razlomak &r1, const Razlomak &r2){
        return r1=r1+r2;
    }
    Razlomak &operator -=(Razlomak &r1, const Razlomak &r2){
        return r1=r1-r2;
    }
    Razlomak &operator *=(Razlomak &r1, const Razlomak &r2){
        return r1=r1*r2;
    }
    Razlomak &operator /=(Razlomak &r1, const Razlomak &r2){
        return r1=r1/r2;
    }
    Razlomak &operator ++(Razlomak &r){
        return r=r+Razlomak(1,1);
    }
    Razlomak operator ++(Razlomak &r, int){
        Razlomak pom=r;
        ++r;
        return pom;
    }
    Razlomak &operator --(Razlomak &r){
        return r=r-Razlomak(1,1);
    }
    Razlomak operator --(Razlomak &r, int){
        Razlomak pom=r;
        --r;
        return pom;
    }
    bool operator <(Razlomak r1, Razlomak r2){
        long double prvi=(long double)r1.brojnik/r1.nazivnik;
        long double drugi=(long double)r2.brojnik/r2.nazivnik;
        return prvi<drugi;
    }
    bool operator >(Razlomak r1, Razlomak r2){
        long double prvi=(long double)r1.brojnik/r1.nazivnik;
        long double drugi=(long double)r2.brojnik/r2.nazivnik;
        return prvi>drugi;
    }
    bool operator <=(Razlomak r1, Razlomak r2){
        long double prvi=(long double)r1.brojnik/r1.nazivnik;
        long double drugi=(long double)r2.brojnik/r2.nazivnik;
        return prvi<=drugi;
    }
    bool operator >=(Razlomak r1, Razlomak r2){
        long double prvi=(long double)r1.brojnik/r1.nazivnik;
        long double drugi=(long double)r2.brojnik/r2.nazivnik;
        return prvi>=drugi;
    }
    bool operator ==(const Razlomak &r1, const Razlomak &r2){
        return r1.brojnik==r2.brojnik && r1.nazivnik==r2.nazivnik;
    }
    bool operator !=(const Razlomak &r1, const Razlomak &r2){
        return !(r1==r2);
    }
    std::ostream &operator <<(std::ostream &tok, const Razlomak &r){
        if(r.nazivnik==1) tok<<r.brojnik;
        else tok<<r.brojnik<<"/"<<r.nazivnik;
        return tok;
    }
    std::istream &operator >>(std::istream &tok, Razlomak &r){
        long long int b,n;
        tok>>b;
        if(tok.peek()==' ' || tok.peek()=='\n' || tok.peek()==EOF){
            n=1;
        }
        else{
            char znak;
            tok>>znak>>n;
            if(tok.peek()!=' ' || znak!='/') tok.setstate(std::ios::failbit);
        }
        r=Razlomak(b,n);
        return tok;
    }
int main ()
{
	return 0;
}
