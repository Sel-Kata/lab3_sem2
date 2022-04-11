#include <iostream>
template<typename T>
class Buffer{
private:
    T begin_;
    T end_;
    int size_of_array_;
    int data_size_;
    T array_[10000];//max=1000

public:
    ///сеттеры
    void setBuf(const T& place, const T& meaning){//поставить значение в опред.место в буфере
        array_[place] = meaning;
    }
    void setStart(const T& start){
        begin_ = start;
    }

    void setFinish(const T& finish){
        end_ = finish;
    }

    void setSize(int dataSize){
        data_size_ = dataSize;
    }

    void set_array_size(int new_size){/// закончить потом
        if (new_size > get_array_size()){//если хотим задать больше чем у нас было
            if (getSize() < get_array_size()){
                size_of_array_ = new_size;
            }
            else{
                size_of_array_ = new_size;
                if (getSize() + getFinish() < new_size){
                    int temp=0;
                    while(temp < getFinish()){
                        setBuf(getSize(), getBuf(temp));
                        setSize(getSize() + 1);
                        temp++;
                    }
                }
            }
        }
        else if (new_size < get_array_size()){
            std::cout << "Точно хотим уменьшить буффер??"<<"\n";

        }
        else if(new_size == get_array_size()){
            std::cout << "Установленный размер уже такой"<<"\n";
        }
    }
    ////геттеры
    T getSize() const {
        return data_size_;
    }

    T getStart() const {
        return begin_;
    }

    T getFinish() const {
        return end_;
    }
    T getBuf(const int& place) const {
        return array_[place];
    }
    T get_array_size() const {
        return size_of_array_;
    }

    T getBegin() const{
        return array_[getStart()];
    }

    T getEnd() const {
        return array_[getFinish()];
    }

    Buffer(){//создание
        this->setStart(0);
        this->setSize(0);
        this->setFinish(-1);
        this->set_array_size(5);
    }

    Buffer(T array[], const int& size){
        this->set_array_size(size);
        for (int cur = 0; cur < size; ++cur){
            this->setBuf(cur, array[cur]);
        }
        this->setSize(size);
        this->setFinish(size - 1);
        this->setStart(0);
    }

    void insert_end(const T& value){
        if (getSize() + 1 <= get_array_size()){//если есть место свободное
            setFinish(getFinish() + 1);
            setBuf(getFinish(), value);
            setSize(getSize() + 1);
        }
        else{//если место нет,берём начало
            setFinish(getStart());
            setBuf(getFinish(), value);
            setStart(getStart() + 1);
        }
    }

    void delete_end(){
        setFinish(getFinish() - 1);
        setSize(getSize() - 1);
    }

    void insert_begin(const int & value){ ///что-то не так!!!!
        if (getStart() + 1 <= get_array_size()){//если он ещё не образует кольцо
            for (int i = getFinish() ; i >= getStart(); --i){
                setBuf(i + 1, getBuf(i));
            }
            setFinish(getFinish() + 1);
            setBuf(getStart(), value);
            setSize(getSize() + 1);
        }
        else {//когда замкнутая цепь,то...
            for (int i  = getFinish(); i > getStart(); --i){//сдвигаем
                setBuf(i + 1, getBuf(i));
            }
            setStart(getStart() - 1);
            setBuf(getStart(), value);
        }
    }

    void delete_begin(){
        setStart(getStart() + 1);
        setSize(getSize() - 1);
    }
    friend std::ostream& operator<< (std::ostream& stream, const Buffer<T, T, int, int, T>& buff);
};

std::ostream& operator<< (std::ostream& stream, const Buffer<T, T, int, int, T>& buff){
    if(buff.getSize() == 1){
        stream << buff.getBuf(buff.getFinish());
    }
    else if (buff.getSize() == 0){
        return stream;
    }
    else if (buff.getStart() < buff.getFinish()){
        if(buff.getSize() <= buff.get_array_size()){
            for (int i = buff.getStart(); i <= buff.getFinish(); ++ i){
                stream << buff.getBuf(i) << ", ";
            }
        }
    }
    else {
        for (int i = buff.getStart(); i < buff.get_array_size(); ++i){
            stream << buff.getBuf(i) << ", ";
        }
        for (int i = 0; i <= buff.getFinish(); ++i){
            stream << buff.getBuf(i) << ", ";
        }
    }
    return stream;
};


int main(){
    Buffer bufer;
    std::cout << bufer << "size: " << bufer.getSize() << std::endl;
    bufer.insert_end(5);
    std::cout <<"buf.insert_end(5)\t" << bufer << "\tразмер: " << bufer.getSize() << std::endl;
    bufer.insert_begin(3);
    std::cout <<"buf.insert_begin(3)\t" << bufer << "\tразмер: " << bufer.getSize() << std::endl;
    bufer.insert_end(6);
    std::cout << "buf.insert_end(6)\t" << bufer << "\tразмер: " << bufer.getSize() << std::endl;
    bufer.insert_end(7);
    std::cout << "buf.insert_end(7)\t" << bufer << "\tразмер: " << bufer.getSize() << std::endl;
    bufer.insert_end(2);
    std::cout << "buf.insert_end(2)\t" << bufer << "\tразмер: " << bufer.getSize() << std::endl;
    //bufer.delete_end();
    //std::cout << "buf.delete_end();\t" << bufer << "\размер: " << bufer.getSize() << std::endl;
    bufer.insert_end(1);
    std::cout << "buf.insert_end(1)\t" << bufer << "\tразмер: " << bufer.getSize() << std::endl;
    //bufer.delete_begin();
    //std::cout << "buf.delete_begin();\t" << bufer << "\размер: " << bufer.getSize() << std::endl;
    //bufer.insert_begin(7);
    //std::cout << "buf.insert_begin(7)\t" << bufer << "\размер: " << bufer.getSize() << std::endl;
}
