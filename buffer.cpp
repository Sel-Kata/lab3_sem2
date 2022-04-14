#include <iostream>
#include <algorithm>

template <class T>
class Buffer{
public:
    Buffer(int size){
        if (size < 0){exit(1);}
        this->end = nullptr;
        this->first = nullptr;
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
        if (this->size < 0){exit(1);}
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
        if (this->first == nullptr && counterOfElements <= this->size){
            this->first = temp;
            this->end = temp;
        }
        else if (this->first != nullptr){
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
        if (index > counterOfElements){exit(1);}
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

        void SetData(T data){ this->data = data;}

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
    int size = 0;
    int counterOfElements = 0;

public:
    T* Begin(){
        T temp = this->first->GetData();
        T* t = &temp;
        return t;
    }
    T* End(){
        T temp = this->end->GetData();
        T* t = &temp;
        return t;
    }
};

int main(){
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
    for (int i = 0; i < t.Size(); i++){
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
    std::cout << *t.Begin() << " " << *t.End();
    //std::none_of(t.Begin(), t.End(), 8);
    return 0;

}
