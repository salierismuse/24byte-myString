#include "myString.hpp"

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

myString::myString() {
    set_flag_and_size(false, 0);
    u.small_str.str[0] = '\0';
}

//constructor
myString::myString(const char* s) {
    int x = strlen(s);
    if (strlen(s) > 22){
        // add check here that *2 is okay
        u.large_str.capacity = (x)*2;
        set_flag_and_size(true, x);

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



const char* myString::c_str() const {
    if (is_large()) {
        return u.large_str.longStr;
    }
    else {
        return u.small_str.str;
    }
}

size_t myString::length() const noexcept {
    if (is_large()) {
        return u.large_str.len;
    }
    else {
        return u.small_str.flag_and_small_size>>1;
    }
}

char& myString::operator[] (size_t pos) {
    if (is_large()) {
        return u.large_str.longStr[pos];
    }
    else {
        return u.small_str.str[pos];
    }
}

const char& myString::operator[] (size_t pos) const {
    if (is_large()) {
        return u.large_str.longStr[pos];
    }
    else {
        return u.small_str.str[pos];
    }
}


//overloads
std::ostream& operator<<(std::ostream& os, const myString& str) {
    os << str.c_str();
    return os;
}

myString& myString::operator+=(const myString& str) {
    int x = str.length();
    if (is_large()){
        while (length() + str.length() >= u.large_str.capacity) {
            // rebuild
            char *temp = new char[((u.large_str.capacity*2))+1];
            strcpy(temp, u.large_str.longStr);
            u.large_str.capacity = (((u.large_str.capacity)*2));

            delete[] u.large_str.longStr;
            u.large_str.longStr = temp;
        }
        strcat(u.large_str.longStr, str.c_str());
        u.large_str.len += str.length();
        return *this;
    }
    else {
        if (length() + str.length() > 22) {
            char temp[length()];
            strcpy(temp, c_str());
            set_flag_and_size(true, length()+str.length());
            u.large_str.capacity = u.large_str.len*2;
            u.large_str.longStr = new char[u.large_str.capacity+1];
            strcpy(u.large_str.longStr, temp);
            strcat(u.large_str.longStr, str.c_str());
            return * this;
        }
        else {
            strcat(u.small_str.str, str.c_str());
            (u.small_str.flag_and_small_size = (x + length()) << 1);
            return *this;
        }
    }
}


bool myString::empty() const noexcept{
    if (length() == 0){
        return true;
    }
    return false;
}

void myString::clear() noexcept {
    if (is_large()){
        u.large_str.capacity = 0;
        delete[] u.large_str.longStr;
        set_flag_and_size(false, 0);
    }
    else {
        u.small_str.flag_and_small_size = 0;
        u.small_str.str[0] = '\0';
    }
}
