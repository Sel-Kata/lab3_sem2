#include <iostream>
#include <vector>
using namespace std;

template<typename T, typename U>
bool all_of(T begin, T end, U number){//все элементы удовлетворяют
    while(begin!=end){
        if(func(*begin, number)==false){
            return false;
        }
        ++begin;
    }
    return true;
}
template<typename T, typename U>
bool any_of(T begin, T end, U number){//хотяб 1 эл удовлетворяет
    while(begin!=end){
        if(func(*begin, number)==true){
            return true;
        }
        ++begin;
    }
    return false;
}
template<typename T, typename U>
bool none_of(T begin, T end, U number){//
    while(begin!=end){
        if(func(*begin, number)==true){
            return false;
        }
        ++begin;
    }
    return true;
}
template<typename T, typename U>
bool one_of(T begin, T end, U number){//ровно 1 удовлетворяет
    int count=0;
    while(begin!=end){
        if(func(*begin, number)==true){
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
template<typename T, typename U>
bool func(T& value, U number){
    if (value>number){
        return true;
    }
    else{
        return false;
    }
}
template<typename T>
bool is_sorted(T begin, size_t size){//отсортировано ли?
    if(bubbleSort(*begin, size)==false){
        return false;
    }
    else{
        return true;
    }

}
template < typename T >
bool bubbleSort(T& arr, size_t arrSize){
    for(size_t i = 0; i < arrSize - 1; ++i)
        for(size_t j = 0; j < arrSize - 1; ++j)
            if (arr[j + 1] < arr[j])
                return false;
    //my_swap ( arr[j] , arr[j+1] ) ;
}
template<typename T>
T& find_not(T begin, T end,T faund,  bool(*func2)(T,T)){//находит первое не равное заданому
    int count=0;
    while(begin!=end){
        if(func2(*begin, *faund)==true){
            count++;
        }
        else if(func2(*begin, *faund)==false){
            return begin;
        }
        ++begin;
    }
    return NULL;
}
template<typename T>
T& find_backward(T begin, T end,T faund,  bool(*func2)(T,T)){//находит первый эл равный заданому с конца
    int count=0;
    while(end!=begin){
        if(func2(*end, *faund)==false){
            count++;
        }
        else if(func2(*end, *faund)==true){
            return end;
        }
        --end;
    }
    return NULL;
}
template<typename T>
bool func2(T& value, T&  faund){
    if(value==faund){
        return true;
    }
    else{
        return false;
    }
}
template<typename T>
bool is_palindrome(T begin, T end){//палидром ли
    if (begin < end){
            for ( ; begin <= end; ++begin, --end){
                if (get_buf(begin) != get_buf(end))
                    return false;
            }
        }
        else{
            
        }
        return true;

}
template<typename T>
bool func3(T& value, int faund){
    if(value>faund){
        return true;
    }
    else{
        return false;
    }
}
///is_partitioned

int main(){
    int array[]={8,7,6,5};
    vector<float> v(4);
    v.push_back(1.3);
    v.push_back(2.5);
    v.push_back(5.0);
    v.push_back(3.0);
    one_of(array, array+4, 4);
    one_of(v.begin(), v.end(), 4.6);
    is_sorted(array, 4);

}
