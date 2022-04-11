#include <iostream>
using namespace std;

template<typename T>
bool all_of(T begin, T end, bool(*func)(T)){//все элементы удовлетворяют
    while(begin!=end){
        if(func(*begin)==false){
            return false;
        }
        ++begin;
    }
    return true;
}
template<typename T>
bool any_of(T begin, T end, bool(*func)(T)){//хотяб 1 эл удовлетворяет
    while(begin!=end){
        if(func(*begin)==true){
            return true;
        }
        ++begin;
    }
    return false;
}
template<typename T>
bool none_of(T begin, T end, bool(*func)(T)){//
    while(begin!=end){
        if(func(*begin)==true){
            return false;
        }
        ++begin;
    }
    return true;
}
template<typename T>
bool one_of(T begin, T end, bool(*func)(T)){//ровно 1 удовлетворяет
    int count=0;
    while(begin!=end){
        if(func(*begin)==true){
            count++;
        }
        ++begin;
    }
    if (count==1){
        return true;
    }
    else{
        return false;
    }

}
template<typename T>
bool func(T value){
    if (sizeof(value)>sizeof(int)){
        return true;
    }
    else{
        return false;
    }
}
template<typename T>
bool is_sorted(T begin, size_t size, bool(*bubbleSort)(T, size_t)){//отсортировано ли?
    if(bubbleSort(*begin, size)==false){
       return false; 
    }
    else{
        return true;
    }

}
template < typename T >
bool bubbleSort(T arr, size_t arrSize){
    for(size_t i = 0; i < arrSize - 1; ++i)
        for(size_t j = 0; j < arrSize - 1; ++j)
            if (arr[j + 1] < arr[j])
                return false;
                //my_swap ( arr[j] , arr[j+1] ) ;
}

int main(){
    int array[]={8,7,6,5};
    one_of(array, array+4, func);

}
