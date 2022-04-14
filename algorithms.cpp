#include <iostream>
#include <vector>
#include <algorithm>


namespace ty{
    template<class T>
    class equal_to{
    public:
        bool operator()(T valueOne, T valueTwo){
            if (valueOne == valueTwo){
                return true;
            }
            return false;
        }
    };
    template <class T, class T2>
    class comparison{
    public:
        bool operator ()(T valueOne, T2 valueTwo){
            return valueOne > valueTwo;
        }
    };
}

namespace rp{
    template<class T1, class T2, class T3>
    bool all_of(T1 r, T2 func, T3 tr){
        for (auto value : r){
            if (func(value, tr)==false){
                return false;
            }
        }
        return true;
    }
    template<class T1, class T2, class T3>
    bool any_of(T1 r, T2 func, T3 tr){
        for (auto value : r){
            if (func(value, tr)==true){
                return true;
            }
        }
        return false;
    }
    template<class T1, class T2, class T3>
    bool none_of(T1 r, T2 func, T3 tr){
        for (auto value : r){
            if (func(value, tr)==true){
                return false;
            }
        }
        return true;
    }
    template<class T1, class T2, class T3>
    bool one_of(T1 r, T2 func, T3 tr){
        int check=0;
        for (auto value : r){
            if (func(value, tr)==true){
                check++;
            }
        }
        if (check==1){
            return true;
        }
        return false;
    }
    template <class T1, class T2, class T4>
    bool is_sorted (T1 data, T2 func, T4 first, T4 end){
        bool signal = false;
        auto temp=*(++first);
        for (auto value : data){
            if (signal==true){
                if (!func(temp, value)){//если первое больше другого
                    return false;
                }
            }
            if (signal==true){
                temp = value;
            }
            signal = true;
        }
        return true;
    }
    template <class T1, class T2, class element, class T3>
    element find_not (T1 data, T2 func, T3 first, T3 end, element elem){
        for (auto value : data){
            if (func(value, elem)==false){
                return value;
            }
        }
        return *end;
    }
    template <class T1, class T2, class T3, class T4>
    bool is_palindrome(T1 data, T2 func, T4 middle, T4 first, T3 end){
        if (first == middle){return true;}
        else{
            int check = 0;
            bool signal = true;
            for (auto value : data){
                if (check != 0){
                    break;
                }
                for (auto value2 : data){
                    (func(value, value2)==false)?signal = false:signal = true;
                }
                ++check;
            }
            if (signal==true){
                if (middle!=first ){
                    is_palindrome(data, func, ++first, --end, middle);
                }
                return true;
            }
            return false;
        }
    }
    template <class T1, class T2, class element, class T3>
    element find_backward (T1 data, T2 func, T3 first, T3 end, element elem){
        for (auto res : data){
            if (func(res, elem)==true){return res;}
        }
        return *first;
    }
    template <class T1, class T2, class T3>
    bool is_partitioned (T1 data, T2 func, T3 first, T3 end){
        auto temp = *(++first);
        bool signal1 = false;
        bool signal2 = false;
        for (auto value : data){
            if (!signal2){
                if(signal1){
                    if (!func(temp, value)){
                        signal2 = true;
                    }
                }
            }
            else if (signal2){
                if(signal1){
                    if (func(temp, value)){
                        return false;
                    }
                }
            }

            if (signal1==true){
                temp = value;
            }
            signal1 = true;
        }
        if (signal2) {
            if (signal1) {return true;}
        }
        return false;
    }
}

struct mydot{
    int x_;
    int y_;
};

class point{
private:
    mydot dot_;

public:
    //конструктор
    point (int x = 0, int y = 0){
        this->set_x(x);
        this->set_y(y);
    }
    //оператор присваивания
    point& operator=(const point &point_New2){
        this->set_x(point_New2.getx());
        this->set_y(point_New2.gety());
        return *this;
    }
    //конструктор копирования
    point (const point &point_New){
        this->set_x(point_New.getx());
        this->set_y(point_New.gety());
    }
    void set_y(const int& y){
        this->dot_.y_ = y;
    }
    void set_x(const int& x){
        this->dot_.x_ = x;
    }

    int gety() const{
        return this->dot_.y_;
    }
    int getx() const{
        return this->dot_.x_;
    }

    mydot getPoint(){
        return this->dot_;
    }
    //деструктор
    ~point()
    {}
};

int main()
{
    ty::equal_to<int> t;
    if (t(2,2)){
        std::cout << "true";
    }
    ty::comparison<int, int> comp;
    std::vector<int> r;
    r.push_back(5);
    r.push_back(3);
    r.push_back(2);
    r.push_back(6);
    std::vector<int>::iterator it_b = r.begin();
    std::vector<int>::iterator it_e = r.end();
    std::cout <<"all_of?\n";
    std::cout <<rp::all_of(r, t, 5)<<"\n";
    std::cout <<"any_of?\n";
    std::cout <<rp::any_of(r, t, 5)<<"\n";
    std::cout <<"none_of?\n";
    std::cout <<rp::none_of(r, t, 5)<<"\n";
    std::cout <<"is_sorted?\n";
    std::cout <<rp::is_sorted(r, comp, r.begin(), r.end())<<"\n";
    std::cout <<"is_partitioned?\n";
    std::cout <<rp::is_partitioned(r, comp, r.begin(), r.end())<<"\n";
    std::cout <<"find_not?\n";
    std::cout <<rp::find_not(r, t, r.begin(), r.end(), 3)<<"\n";
    std::cout <<"is_palindrome?\n";
    std::cout <<rp::is_palindrome(r, t, r.begin()+r.size()/2, r.begin(), r.end())<<"\n";
    std::cout <<"find_backward?\n";
    std::cout <<rp::find_backward(r, t, r.rbegin(), r.rbegin(), 7)<<"\n";//rbegin-обратный


    point first(2, 1);
    point second(3, 2);
    point third(4, 3);
    std::vector<point> mypoint;
    mypoint.push_back(first);
    mypoint.push_back(second);
    mypoint.push_back(third);
    ty::equal_to<point> forPoint;
    if (forPoint(first,second)){
        std::cout << "true";
    }
    std::cout <<"\n-------теперь для точек?--------\n";
    std::cout <<"all_of?\n";
    std::cout <<rp::all_of(mypoint, forPoint, second)<<"\n";
    std::cout <<"any_of?\n";
    std::cout <<rp::any_of(mypoint, forPoint, third)<<"\n";
    std::cout <<"none_of?\n";
    std::cout <<rp::none_of(mypoint, forPoint, third)<<"\n";
    return 0;
}

