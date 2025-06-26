#include <cstddef>   // std::size_t
#include <cstdint>   // std::uintptr_t
#include <cstring>   // std::memcpy
#include <cassert>   // assert
#include <iostream>  // std::cout

using namespace std;


typedef int TYPE1;
typedef double TYPE2;
typedef char TYPE3;
typedef short TYPE4;
typedef long long TYPE5;


void* align_forward(void* ptr, size_t alignment)
{
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    uintptr_t aligned = (addr + alignment - 1) & ~(alignment - 1);
    return reinterpret_cast<void*>(aligned);
}


void* write(const TYPE1* p1, const TYPE2* p2, const TYPE3* p3, const TYPE4* p4, const TYPE5* p5, void* buf, size_t size) 
{
    char* base = reinterpret_cast<char*>(buf);
    char* current = base;

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE1)));
    if ((current - base + sizeof(TYPE1)) > size) return nullptr;
    memcpy(current, p1, sizeof(TYPE1));
    char* start = current;
    current += sizeof(TYPE1);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE2)));
    if ((current - base + sizeof(TYPE2)) > size) return nullptr;
    memcpy(current, p2, sizeof(TYPE2));
    current += sizeof(TYPE2);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE3)));
    if ((current - base + sizeof(TYPE3)) > size) return nullptr;
    memcpy(current, p3, sizeof(TYPE3));
    current += sizeof(TYPE3);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE4)));
    if ((current - base + sizeof(TYPE4)) > size) return nullptr;
    memcpy(current, p4, sizeof(TYPE4));
    current += sizeof(TYPE4);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE5)));
    if ((current - base + sizeof(TYPE5)) > size) return nullptr;
    memcpy(current, p5, sizeof(TYPE5));
    current += sizeof(TYPE5);

    return start; 
}


void read(TYPE1* p1, TYPE2* p2, TYPE3* p3, TYPE4* p4, TYPE5* p5, void* buf) 
{
    char* current = reinterpret_cast<char*>(buf);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE1)));
    memcpy(p1, current, sizeof(TYPE1));
    current += sizeof(TYPE1);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE2)));
    memcpy(p2, current, sizeof(TYPE2));
    current += sizeof(TYPE2);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE3)));
    memcpy(p3, current, sizeof(TYPE3));
    current += sizeof(TYPE3);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE4)));
    memcpy(p4, current, sizeof(TYPE4));
    current += sizeof(TYPE4);

    current = reinterpret_cast<char*>(align_forward(current, alignof(TYPE5)));
    memcpy(p5, current, sizeof(TYPE5));
    current += sizeof(TYPE5);
}


void run_tests() 
{
    alignas(max_align_t) char buffer[128];

    TYPE1 a1 = 402;
    TYPE2 a2 = 3.14;
    TYPE3 a3 = 'Z';
    TYPE4 a4 = 1234;
    TYPE5 a5 = 98743210LL;

    void* result = write(&a1, &a2, &a3, &a4, &a5, buffer, sizeof(buffer));
    assert(result != nullptr && "Должно хватить места в буфере");

    // Значения для чтения
    TYPE1 r1 = 0;
    TYPE2 r2 = 0.0;
    TYPE3 r3 = '\0';
    TYPE4 r4 = 0;
    TYPE5 r5 = 0;

    read(&r1, &r2, &r3, &r4, &r5, result);

    // Проверка корректности
    assert(r1 == a1);
    assert(r2 == a2);
    assert(r3 == a3);
    assert(r4 == a4);
    assert(r5 == a5);

    cout << "Все тесты пройдены успешно!" << endl;

    // Тест на нехватку памяти
    char small_buf[4];
    void* result2 = write(&a1, &a2, &a3, &a4, &a5, small_buf, sizeof(small_buf));
    assert(result2 == nullptr && "Ожидается недостаток памяти");
}

int main() 
{
    run_tests();
    return 0;
}

