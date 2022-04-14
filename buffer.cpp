#include <iostream>
#include <algorithm>

template <class T>
class Buffer{
public:
    Buffer(int size){
        if (size < 0){
            exit(1);
        }
        this->end = nullptr;
        this->first = nullptr;
        this->delitedForPushBack = nullptr;
        this->size = size;
    }

    void push_first(T Data){
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

    void pop_first(){
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
        if (counterOfElements > this->size){//уже заполнен
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

    T operator [](int index){
        if (index > counterOfElements){
            exit(1);
        }
        Node* temp;
        temp = this->first;
        for (int i = 0; i < index; i++){
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

int main()
{
    Buffer<int> t(9);
    t.push_first(6);
    t.push_first(0);
    t.push_first(4);
    t.push_back(7);
    t.pop_back();
    t.push_back(5);
    t.pop_first();
    t.resize(10);
    t.resize(2);
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
    Buffer<int>::iter it_b = t.start();
    Buffer<int>::iter it_e = t.finish();
    std::cout << *it_b << std::endl;
    std::cout << std::none_of(it_b, it_e, [](int i = 0){return i == 1;});
    return 0;

}

