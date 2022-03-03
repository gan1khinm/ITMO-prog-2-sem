#include <iostream>
#include <math.h>
#include <cmath>
#include <locale>

using namespace std;


class tochka{
private:
    float x, y;
public:
    tochka (float x2, float y2){
        x = x2;
        y = y2;
    }

    tochka (const tochka &t){
        this -> x = t.x;
        this -> y = t.y;
    }

    tochka (){

    }

    float get_x(){
        return x;
    }

    float get_y(){
        return y;
    }

    tochka operator = (const tochka &t){
        this -> x = t.x;
        this -> y = t.y;
    }

    void coord(){
        cout << "Координаты точки: " << '(' << x << ';' << y << ')' << endl;
    }
};


float get_lenth(tochka t1, tochka t2){             //Нахождение длины отрезка
    return sqrt(pow((t2.get_x() - t1.get_x()),2) + pow((t2.get_y() - t1.get_y()),2));
}


class lom{
private:
    tochka *mas;
public:
    lom (tochka *mas2){
        mas = mas2;
    }

    float lengh(){
        int l = 0;
        for(int i = 0; i < (sizeof(mas) / 2) - 1;i++){
            l+= sqrt(pow((mas[i + 1].get_x() - mas[i].get_x()),2) + pow((mas[i + 1].get_y() - mas[i].get_y()),2));
        }
        cout << "Длина кривой: " << l << endl;
        return l;
    }
};


class ZamkLom{
private:
    tochka *mas;

public:
    ZamkLom (tochka *mas2){
        mas = mas2;
    }

    ZamkLom (int size){
        mas =  new tochka[size];
    }

    ZamkLom (){
        mas = new tochka[5];
    }

    void set_value(int n, tochka value){
        mas[n] = value;
    }

    void set_mas(tochka *mas2){
        mas = mas2;
    }

    tochka *get(){
        return mas;
    }

    float perim(){
        float per = 0;
        for(int i = 0; i < (sizeof(mas) / 2) - 1; i++){
            float l;
            l = sqrt(pow((mas[i+1].get_x() - mas[i].get_x()),2) + pow((mas[i+1].get_y() - mas[i].get_y()),2));
            per += l;
        }
        cout << "Периметр фигуры равен: " << per << endl;
        return per;
    }

    float s(){
        double t = 0;
        int n = ((sizeof(get()) - 1) / 2);
        for(int i = 0; i < n - 1; ++i){
            t += get()[i].get_x() * get()[i + 1].get_y();
            t -= get()[i].get_y() * get()[i + 1].get_x();
        }
        t = t + get()[n - 1].get_x() * get()[0].get_y() - get()[n - 1].get_y() * get()[0].get_x();
        if(t < 0) t = -t; //можно функцию из cmath или math.h использовать fabs()
        return t / 2;
    }
};


class mnogoug: public ZamkLom{
public:
    mnogoug (tochka *mas2) : ZamkLom(mas2)
    {

    }
};


class treug{
private:
    tochka first, second, therd;

public:
    treug (tochka t1, tochka t2, tochka t3){
        first = t1;
        second = t2;
        therd = t3;
    }

    treug (){

    }

    float s(){            //Нахождение площади 
        float p = perimetr()/2;
        float S = sqrt(p*(p-get_lenth(first, second)) * (p -  get_lenth(second, therd)) * (p - get_lenth(therd, first)));
        cout << "Площадь треугольника: " << S << endl;
        return S;
    }

    float perimetr(){     //Нахождение периметра
        float perim;
        perim = get_lenth(first, second) + get_lenth(second, therd) + get_lenth(therd, first);
        cout << "Периметр треугольника: " << perim << endl;
        return perim;
    }
};


class trapec{
private:
    tochka first, second, therd, fourth;
public:
    trapec (tochka t1, tochka t2, tochka t3, tochka t4){
        first = t1;
        second = t2;
        therd = t3;
        fourth = t4;
    }

    float s(){                
        if((first.get_x() == second.get_x() && therd.get_x() == fourth.get_x() && first.get_x() != therd.get_x()) || 
        (second.get_y() == therd.get_y() && first.get_y() == fourth.get_y() && second.get_y() != first.get_y())){
            float S;
            S = ((get_lenth(second, therd) + get_lenth(fourth, first)) / 2) * sqrt(pow(get_lenth(first, second), 2) -
            pow((pow(get_lenth(fourth, first) - get_lenth(second, therd), 2) + pow(get_lenth(first, second), 2) -
            pow(get_lenth(therd, fourth), 2)) / 2*(get_lenth(fourth, first) - get_lenth(second, therd)), 2) );
            cout << "Площадь трапеции: " << S << endl;
            return S;
        }
        else{
            cout << "Фигура не является трапецией" << endl;
        }
    }

    float perimetr(){
        if((first.get_x() == second.get_x() && therd.get_x() == fourth.get_x() && first.get_x() != therd.get_x()) || 
        (second.get_y() == therd.get_y() && first.get_y() == fourth.get_y() && second.get_y() != first.get_y())){
            float perim;
            perim = get_lenth(first, second) + get_lenth(second, therd) + get_lenth(therd, fourth) + get_lenth(fourth, first);
            cout << "Периметр трапеции: " << perim << endl;
            return perim;
        }
        else{
            cout << "Фигура не является трапецией" << endl;
        }
    }
};


class PravTreug: public treug{
public:
    PravTreug(tochka t1, tochka t2, tochka t3): treug(t1, t2 , t3){

    }
};


int main(){

    setlocale(LC_ALL, "RUS");
    tochka mas[3] = {tochka(1,2), tochka(8,3), tochka(3,2)};
    /*
    lom l(mas);
    l.lengh();
    */

    /*ZamkLom lom(mas);
    lom.perim();*/

    /*
    mnogoug l(mas);
    l.s();
    cout << l.s(); 
    */
    /*
    tochka t1(1,2);
    tochka t2(3,4);
    tochka t3(1,3);
    treug tre(t1, t2, t3);
    tre.s();*/

    
    tochka t1(0,0);
    tochka t2(4,7);
    tochka t3(0,8);
    PravTreug tre(t1, t2, t3);
    if(get_lenth(t1, t2) == get_lenth(t2,t3) == get_lenth(t3, t1)){
        tre.s();
    }
    else{
        cout << "Не является правильным треугольиком" << endl;
    }
    
    /*
    tochka t1(1,0);
    tochka t2(2,4);
    tochka t3(5,4);
    tochka t4(3,0);
    trapec t(t1, t2, t3, t4);
    t.s();
    */
    return 0;
}
