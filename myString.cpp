#include "myString.hpp"
#include <cstring>

//helper
void myString::swap(myString& s2) noexcept {
    auto temp = this->u;
    this->u = s2.u;
    s2.u = temp;
}


bool myString::is_large() const {
    if ((u.small_str.flag_and_small_size & 00000001) == 1){
        return true;
    }
    return false;
}

void myString::set_flag_and_size(bool large, size_t size) {
    if (large == true) {
        u.small_str.flag_and_small_size = 00000001;
        u.large_str.len = size;
    }
    else {
        u.small_str.flag_and_small_size = size << 1;
    }
}

//constructor
myString::myString(const char* s) {
    int x = strlen(s);
    if (strlen(s) > 22){
        // add check here that *2 is okay
        set_flag_and_size(true, x);
        u.large_str.capacity = (x)*2;
        u.large_str.longStr = new char[u.large_str.capacity + 1];
        strcpy(u.large_str.longStr, s);
    }
    else {
        set_flag_and_size(false, x);
        strcpy(u.small_str.str, s);
    }
}

myString::~myString() {
    if (is_large()) {
        delete[] u.large_str.longStr;
    }
}



//copy
myString::myString(const myString& s2) {
    if (s2.is_large()) {
        set_flag_and_size(true, s2.u.large_str.len);
        u.large_str.capacity = s2.u.large_str.capacity;
        u.large_str.len = s2.u.large_str.len;
        u.large_str.longStr = new char[u.large_str.capacity + 1];
        strcpy(u.large_str.longStr, s2.u.large_str.longStr);
    }
    else {
        u.small_str.flag_and_small_size = s2.u.small_str.flag_and_small_size;
        strcpy(u.small_str.str, s2.u.small_str.str);
    }
}

// assignment
myString& myString::operator=(myString s2) {
    swap(s2);
    return *this;
}

//move constructor
myString::myString(myString&& s2) noexcept {
    u = s2.u;
    s2.set_flag_and_size(false, 0);
    strcpy(s2.u.small_str.str, "\0");
}



