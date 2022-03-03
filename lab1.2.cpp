#include<iomanip>
#include<fstream>
#include<iostream>

using namespace std;

class polynom
{
public:
    double *koef_mas;
    int n; //степень полинома
     
    polynom(){
        koef_mas = NULL;
    }
    
    int getn(){     //получение степени полинома
        return n;
    } 
    
    polynom(int obj){        
        n = obj;
        koef_mas = new double[n + 1];
        for (int i = 0; i <= n; i++){
            koef_mas[i] = 0;
        }
    }
    
    polynom(const polynom &obj){      //копированиe
        n = obj.n;
        koef_mas = new double[n + 1];
        for (int i = 0; i <= n; i++){
            koef_mas[i] = obj.koef_mas[i];
        }
    }
    
    double getkoef(int);    //получение коэффициента при i-й степени
    
    polynom operator*(const polynom &);
    
    polynom operator/(const float &);
    
    polynom operator+(const polynom &);  
    
    polynom operator-(const polynom &);   
    
    polynom operator=(const polynom &);   
   
    void operator+=(const polynom &);

    void operator-=(const polynom &);
    
    void operator*=(const polynom &);
    
    void operator/=(const float &);
    
    friend ostream &operator<< (ostream &s, const polynom &c);
    
    friend istream &operator>> (istream &s, polynom &c); 
    
    bool operator==(const polynom &other){ 
        if(this->n != other.n){
            return false;
        }
        for(int i = 0; i < n; i++){
            if(this->koef_mas[i] != other.koef_mas[i])
                return false;
        }
        return true;
    }

    bool operator!=(const polynom &other){ 
        if(this->n != other.n){
            return true;
        }
        for(int i = 0; i < n; i++){
            if(this->koef_mas[i] != other.koef_mas[i])
                return true;
        }
        return false;
    }
    
    double &operator()(int i){
        return koef_mas[i];
    }

    ~polynom(){       
        delete[]koef_mas;
    }
};


double polynom::getkoef(int i){
    if(i <= n)
        return koef_mas[i];
    else
        return 0.0;
}

polynom polynom::operator+(const polynom &b){
    int i;
    if (n >= b.n){   //A>B
        polynom Z=*this;
        for (i = 0; i <= n; i++)
            Z.koef_mas[i] = koef_mas[i] + b.koef_mas[i];
        return Z;
    }
    else{    //A<B
        polynom Z=b;
        for (i = 0; i <= n; i++)
            Z.koef_mas[i] = b.koef_mas[i] + koef_mas[i];
        return Z;
    }
}

void polynom::operator+=(const polynom &b){
    int i;
    if (n >= b.n){   //A>B
        for (i = 0; i <= n; i++)
            koef_mas[i] += b.koef_mas[i];
    }
    else{    //A<B
        polynom M=b;
        for (i = 0; i <= n; i++)
            M.koef_mas[i] = b.koef_mas[i] + koef_mas[i];
        *this = M;
    }
}

polynom polynom::operator-(const polynom &b){
    int i;
    if (n >= b.n){   //А>B
        polynom Z = *this;
        for (i = 0; i <= b.n; i++)
            Z.koef_mas[i] = koef_mas[i] - b.koef_mas[i];
        return Z;
    }
    else{    //B>A
        polynom Z(b.n);
        for (i = 0; i <= n; i++)
            Z.koef_mas[i] = -b.koef_mas[i] + koef_mas[i];
        for (i = n + 1; i <= b.n; i++)
            Z.koef_mas[i] = -b.koef_mas[i];
        return Z;
    }
}

void polynom::operator-=(const polynom &b){
    int i;
    if (n >= b.n){   //А>B
        for (i = 0; i <= b.n; i++)
            koef_mas[i] -= b.koef_mas[i];
    }
    else{    //B>A
        polynom Z(b.n);
        for (i = 0; i <= n; i++)
            Z.koef_mas[i] = -b.koef_mas[i] + koef_mas[i];
        for (i = n + 1; i <= b.n; i++)
            Z.koef_mas[i] = -b.koef_mas[i];
        *this = Z;
    }
}

polynom polynom::operator*(const polynom &b){
    polynom Z(n+b.n);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= b.n; j++)
            Z.koef_mas[i + j] += koef_mas[i]*b.koef_mas[j];
    return Z;
}

void polynom::operator*=(const polynom &b){
    polynom Z(n+b.n);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= b.n; j++)
            Z.koef_mas[i + j] += koef_mas[i]*b.koef_mas[j];
    *this = Z;
}

polynom polynom::operator/(const float &b){ 
    polynom Z(n);
    for (int i = 0; i <= n; i++)
        Z.koef_mas[i] = koef_mas[i]/b;
    return Z;
}

void polynom::operator/=(const float &b){ 
    for (int i = 0; i <= n; i++)
        koef_mas[i] /= b;
}

polynom polynom::operator=(const polynom &b){
    if(this!=&b){
        delete[] koef_mas;
        n = b.n;
        koef_mas = new double[n + 1];
        for (int i = 0; i <= n; i++)
            koef_mas[i] = b.koef_mas[i];
    }
    return *this;
}

istream &operator>>(istream &s, polynom &b){
    for (int i = 0; i <= b.n; i++){
        s >> b.koef_mas[i];
    }
    return s;
}

ostream &operator<<(ostream &s, const polynom &b){
    int i, n=0;
    for (i = 0; i <= b.n; i++){
        if (b.koef_mas[i] != 0)
            n++;
    }

    if (n != 0){
        if (b.koef_mas[0] != 0){
            s << b.koef_mas[0];
        }
        for (i = 1; i <= b.n; i++){
            if (b.koef_mas[i] == 0){
                continue;
            }
            if (b.koef_mas[i] < 0){ 
                s << b.koef_mas[i] << "X^" << i; 
            }
            else{
                s << "+" << b.koef_mas[i] << "X^" << i;
            }
        }
    s << endl;
    }
    else{
        s << 0;
    }
    return s;
}


int main()
{
    setlocale(LC_ALL, "ru");
    bool result;
    int n, m, d;
    cout << "Введите степень полинома A и степень полинома B:" << endl;
    cin >> n >> m;
    polynom A(n), B(m), D, K, Y, Z, M(n), S(n), W(n), R(n);
    M(n) = S(n) = R(n) = W(n) = A(n);

    cout << "Введите коэфициенты полинома A:" << endl;
    cin >> A;
    cout << "Введите коэфициенты полинома B:" << endl;
    cin >> B;
    cout << "Многочлен А:  " << A << endl;
    cout << "Многочлен B:  " << B << endl;
    cout << "Многочлен D=A+B:  " << (D = A + B) << endl;
    cout << "Многочлен K=A-B:  " << (K = A - B) << endl;
    cout << "Многочлен Y=A*B:  " << (Y = A*B)<< endl;
    cout << "Введите делитель d:  " << endl;
    cin >> d;
    cout << "Многочлен Z=A/" << d << ":  " << (Z = A/d)<< endl;
    
    M += B;
    cout << "Многочлен A+=B:  " << M << endl;
    S -= B;
    cout << "Многочлен A-=B:  " << S << endl;
    A *= B;
    cout << "Многочлен A*=B:  " << A << endl;
    A(n) = W(n);
    A /= d;
    cout << "Многочлен A/=" << d << ":  " << A << endl;
    A(n) = W(n);
    
    result = A==B;
    if(result == 0){
        cout << "A не равно B" << endl;
    }
    else{
        cout << "A равно В" << endl;
    }
    
    result = A!=B;
    if(result == 1){
        cout << "A не равно В" << endl;
    }
    else{
        cout << "А равно В" << endl;
    }
    
    return 0;
}