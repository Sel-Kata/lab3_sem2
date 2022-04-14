#include <iostream>
#include <vector>
#include <algorithm>
template <class T>
class Buffer{
public:
    Buffer(int size){
        if (size < 0){
            std::cout <<"невозможно поставить отрицательный размер буфера\n";
            exit(1);
        }
        this->end = nullptr;
        this->first = nullptr;
        this->delitedForPushBack = nullptr;
        this->size = size;
    }

    //push_back
    //push_front
    //pop_back
    //pop_front
    void push_front(T Data){
        Buffer<T>::Node* temp;
        temp = temp->createNode(Data);
        counterOfElements++;
        if (this->first == nullptr && counterOfElements <= size){
            this->first = temp;
            this->end = temp;
        }
        else if (this->first != nullptr && counterOfElements <= size){
            this->first->prev = temp;
            temp->next = this->first;
            this->first = temp;
        }
        else if (this->first != nullptr && counterOfElements >= size){
            this->end = this->end->prev;
            this->first->prev = temp;
            temp->next = this->first;
            this->first = temp;
        }
    }

    int Size(){
        return this->counterOfElements;
    }
    int SizeOfBuf(){
        return this->size;
    }

    void pop_front(){
        if (first == nullptr){return;}
        else{
            first = first->next;
            counterOfElements--;
        }
    }

    void resize(int size){
        if (this->size < 0){
            exit(1);
        }
        if (counterOfElements < size){
            this->size = size;
        }
        if (size < this->counterOfElements){
            int len = this->counterOfElements - size;
            for(int i = 0; i < len; i++){
                this->end = this->end->prev;
                this->counterOfElements--;
            }
            this->size = size;
        }
    }

    void push_back(T Data){
        Buffer<T>::Node* temp;
        temp = temp->createNode(Data);
        counterOfElements++;
        if (this->first == nullptr && counterOfElements <= this->size){//первый элем
            this->first = temp;
            this->end = temp;
        }
        else if (this->first != nullptr && counterOfElements <= this->size){//не первый но не заполнен
            this->end->next = temp;
            temp->prev = this->end;
            this->end = temp;
        }
        if (counterOfElements > this->size){//уже заполнен.
            //если добавляем 8. вся цепь сдвинется влево и на освободившееся встанет 8
            //1 2 3 4 5
            //2 3 4 5 8
            counterOfElements--;
            this->first = this->first->next;
            this->first->prev = nullptr;
            this->end->next = temp;
            temp->prev = this->end;
            this->end = temp;
        }
    }

    void pop_back(){
        if (end != nullptr){
            this->end = this->end->prev;
            this->counterOfElements--;
        }
    }

    T operator [](int where){
        if (where > counterOfElements){
            exit(1);
        }
        Node* temp;
        temp = this->first;
        for (int i = 0; i < where; i++){
            temp = temp->next;
        }

        return temp->GetData();
    }

    ~Buffer(){
        this->end = nullptr;
        this->first = nullptr;
        this->delitedForPushBack = nullptr;
    }
private:
    class Node{
    public:
        Node(){
            this->next = nullptr;
            this->prev = nullptr;
        }
        static Buffer<T>::Node* createNode(T Data){
            Buffer<T>::Node* temp = new Buffer<T>::Node;
            temp->data = Data;
            return temp;
        }

        T GetData(){
            return this->data;
        }

        void SetData(T data)
        { this->data = data;}

        ~Node(){
            this->next = nullptr;
            this->prev = nullptr;
        }

        Node* prev;
        Node* next;
    private:
        T data;
    };
    Node* first;
    Node* end;
    Node* delitedForPushBack;
    int size = 0;
    int counterOfElements = 0;

public:

    Buffer<T>::Node* getNodeForIter(int index){
        if (index > counterOfElements){
            exit(1);
        }

        Node* temp;
        temp = this->first;

        for (int i = 0; i < index; i++){
            temp = temp->next;
        }

        return temp;
    }
    class iter{
        friend class Buffer<T>;
    public:
        iter(){ this->data = nullptr;}
        iter(Buffer<T>::Node* temp){ this->data = temp;}

        iter& operator++(){
            if (data->next != nullptr){
                this->data = this->data->next;
            }
            return *this;
        }

        iter& operator = (const iter& other){
            this->data->prev = other.data->prev;
            this->data->next = other.data->prev;
            this->data->SetData(other.data->GetData());
            return *this;
        }

        iter& operator--(){
            if (this->data->prev != nullptr){
                this->data = this->data->prev;
            }
            return *this;
        }

        T operator * (){
            if (this->data != nullptr){
                return this->data->GetData();
            }
        }

        bool operator == (const iter& other){
            if (this->data->prev == other.data->prev && this->data->next == other.data->next && this->data->GetData() == other.data->GetData()){
                return true;
            }
            return false;
        }

        bool operator != (const iter& other){
            return (!(this->operator==(other)));
        }
    private:
        Buffer<T>::Node* data;
    };

    iter start(){
        iter temp(this->first);
        return temp;
    }
    iter finish(){
        iter temp(this->end);
        return temp;
    }

};


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

struct MyPoint{
    int x;
    int y;

    MyPoint(){
        int x, y = 0;
    }
    MyPoint(int first, int second){
        this->x = first;
        this->y = second;
    }
    MyPoint(const MyPoint & newPoint){
        this->x = newPoint.x;
        this->y = newPoint.y;
    }
    bool operator == (const MyPoint & newPoint){
        return  this->y == newPoint.y && this->x == newPoint.x;
    }
};

int main()
{
   Buffer<int> t(9);
    t.push_front(6);
    t.push_front(0);
    t.push_front(4);
    t.push_front(8);
    t.push_front(5);
    std::cout <<"кол-во элемент буфера " << t.Size()<<"\n";
    //SizeOfBuf
    std::cout <<"размер буфера " << t.SizeOfBuf()<<"\n";
    std::cout <<"push_front 6, 0, 4, 8, 5";
    std::cout << std::endl;
    for (int i = 0; i < t.Size(); i++)
    {
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < t.Size(); i++)
    {
        std::cout << t[i] << " ";
    }
    if (t.Size()<t.SizeOfBuf()){
        int temp=t.SizeOfBuf()-t.Size();
        for(int i=0;i<temp; i++){
            std::cout <<"0"<< " ";
        }
    }
    std::cout << std::endl;
    t.push_back(7);
    t.push_back(3);
    std::cout <<"push_back 7, 3";
    std::cout << std::endl;
    for (int i = 0; i < t.Size(); i++)
    {
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
    std::cout <<"далее эээксперименты!";
    std::cout << std::endl;
    t.pop_back();
    t.push_back(5);
    t.pop_front();
    t.resize(10);
    std::cout <<"кол-во элемент буфера " << t.Size()<<"\n";
    std::cout <<"размер буфера " << t.SizeOfBuf()<<"\n";
    t.resize(2);
    std::cout <<"кол-во элемент буфера " << t.Size()<<"\n";
    std::cout <<"размер буфера " << t.SizeOfBuf()<<"\n";
    for (int i = 0; i < t.Size(); i++)
    {
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
    t.resize(5);
    t.push_back(5);
    t.push_back(9);
    t.push_back(1);
    t.push_back(4);
    for (int i = 0; i < t.Size(); i++){
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
    std::cout <<"none_of по умолчанию";
    std::cout << std::endl;
    Buffer<int>::iter it_b = t.start();
    Buffer<int>::iter it_e = t.finish();
    std::cout << *it_b << std::endl;
    std::cout << std::none_of(it_b, it_e, [](int i = 0){return i == 1;});
  
  
  
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

    std::vector<MyPoint> mypoint;
    MyPoint first;
    MyPoint second;
    MyPoint third;
    mypoint.push_back(first);
    mypoint.push_back(second);
    mypoint.push_back(third);
    ty::equal_to<MyPoint> forPoint;
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
