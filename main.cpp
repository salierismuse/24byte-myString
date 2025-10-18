#include "myString.cpp"
#include <iostream>
#include <cstring>
#include <utility> // For std::move

// Helper to print PASS/FAIL with color
void printTestResult(const char* test_name, bool passed) {
    if (passed) {
        std::cout << "[ \x1B[32mPASS\x1B[0m ] " << test_name << "\n";
    } else {
        std::cout << "[ \x1B[31mFAIL\x1B[0m ] " << test_name << "\n";
    }
}

// Overload for direct string comparison
void printTestResult(const char* test_name, const myString& str, const char* expected) {
    bool passed = (std::strcmp(str.c_str(), expected) == 0 && str.length() == std::strlen(expected));
    printTestResult(test_name, passed);
    if (!passed) {
        std::cout << "      Result: \"" << str << "\" (len: " << str.length() << ")\n";
        std::cout << "      Expected: \"" << expected << "\" (len: " << std::strlen(expected) << ")\n";
    }
}

int main() {
    std::cout << "--- Starting myString Test Suite ---\n\n";

    // --- Constructor & Basic Accessors ---
    myString s1 = "hello";
    printTestResult("Constructor (Small)", s1, "hello");
    printTestResult("length() (Small)", s1.length() == 5);
    printTestResult("c_str() (Small)", std::strcmp(s1.c_str(), "hello") == 0);
    printTestResult("empty() (False)", !s1.empty());

    myString s_empty;
    printTestResult("Constructor (Default)", s_empty, "");
    printTestResult("empty() (True)", s_empty.empty());

    myString s_long = "This is a string designed to be long enough for the heap.";
    printTestResult("Constructor (Large)", s_long, "This is a string designed to be long enough for the heap.");
    printTestResult("length() (Large)", s_long.length() == 57);
    std::cout<<s_long.length();
    // --- Operator[] ---
    s1[0] = 'J';
    printTestResult("operator[] (non-const)", s1, "Jello");
    const myString s_const = "const";
    printTestResult("operator[] (const)", s_const[1] == 'o');

    // --- Rule of Five ---
    std::cout << "\n--- Rule of Five Tests ---\n";
    myString copy_s = s1;
    printTestResult("Copy Constructor (Small)", copy_s, "Jello");
    myString copy_l = s_long;
    printTestResult("Copy Constructor (Large)", copy_l, "This is a string designed to be long enough for the heap.");

    myString move_s = std::move(copy_s);
    printTestResult("Move Constructor (Small)", move_s, "Jello");
    printTestResult("Move Constructor (Small source)", copy_s, "");

    myString move_l = std::move(copy_l);
    printTestResult("Move Constructor (Large)", move_l, "This is a string designed to be long enough for the heap.");
    printTestResult("Move Constructor (Large source)", copy_l, "");

    myString assign_target = "initial";
    assign_target = move_l; // Assignment (copy-and-swap)
    printTestResult("Assignment Operator (Large)", assign_target, "This is a string designed to be long enough for the heap.");
    assign_target = s1; // Assignment (copy-and-swap)
    printTestResult("Assignment Operator (Small)", assign_target, "Jello");

    // --- Modifiers ---
    std::cout << "\n--- Modifier Tests ---\n";
    myString clear_l = "This will be cleared";
    clear_l.clear();
    printTestResult("clear() (Large)", clear_l, "");
    myString clear_s = "short";
    clear_s.clear();
    printTestResult("clear() (Small)", clear_s, "");

    // --- Operator+= ---
    std::cout << "\n--- Operator+= Tests ---\n";
    myString s_s = "Small";
    s_s += " still small";
    printTestResult("operator+= (Small -> Small)", s_s, "Small still small");

    myString s_l = "This will become large";
    s_l += " by adding this extra part.";
    printTestResult("operator+= (Small -> Large)", s_l, "This will become large by adding this extra part.");

    myString l_l_fits = "A large string with plenty of initial capacity for appending.";
    l_l_fits += " Fits.";
    printTestResult("operator+= (Large -> Large, fits)", l_l_fits, "A large string with plenty of initial capacity for appending. Fits.");

    myString l_l_realloc = "A large string with just enough capacity initially.";
    l_l_realloc += " This extra long part will definitely force a reallocation to happen.";
    printTestResult("operator+= (Large -> Large, realloc)", l_l_realloc, "A large string with just enough capacity initially. This extra long part will definitely force a reallocation to happen.");

    std::cout << "\n--- Test Suite Complete ---\n";
    return 0;
}
