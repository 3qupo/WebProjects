#include <iostream>
#include "complex.h"
#include <cassert>

using namespace std;

int main()
{
    long int value = 10;
    long int* ptr = &value;

    assert(post_inc(ptr) == 10); 
    assert(value == 11);      
    cout << *ptr << endl;   

    assert(pref_inc(ptr) == 12); 
    assert(value == 12);   
    cout << *ptr << endl;      

    cout << "Все тесты пройдены\n" << endl;

    return 0;
}