#ifndef MYSTRING_H_
#define MYSTRING_H_
#include <stdint.h>
#include <stdio.h>
#include <utility>
#include <cstring>
#include <iostream>

class myString {
    public:

    myString();
    // helper
    void swap(myString& s2) noexcept;

    ~myString();

    // constructor
    myString(const char* s);

    // copy
    myString(const myString&);

    //  assign
    myString& operator=(myString);

    //move
    myString(myString&&) noexcept;


    void getBuffer();


    const char* c_str() const;
    size_t length() const noexcept;
    char& operator[] (size_t pos);
    const char& operator[] (size_t pos) const;
    bool empty() const noexcept;
    void clear() noexcept;

    //overloads
    friend std::ostream& operator<<(std::ostream& os, const myString& str);
    myString& operator+= (const myString& str);


    private:

    bool is_large() const;

    void set_flag_and_size(bool large, size_t size);

    size_t get_small_size() const;

    void destroy_data();

    void setCapacity(int cap);

    union {
        // large
        struct {
            char *longStr;
            int len;
            int capacity;
        } large_str;

        struct {
            char str[23];
            uint8_t flag_and_small_size;
        } small_str;
    } u;

};

#endif
