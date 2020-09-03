#include <iostream>
#include <string>
#include <exception>
#include "CacheManager.hpp"

int main(int argc, char** argv) {
    try {
        CacheManager cm(2);
        cm.insert("hi1", "hi1.txt", "opposite of bye1");
        cm.insert("hi2", "hi2.txt", "opposite of bye2");
        cm.insert("hi3", "hi3.txt", "opposite of bye3");
        if (cm.search("hi3")) {
            std::cout << cm.get("hi3") << std::endl;
        }
    }
    catch (std::exception e) {
        std::cout << "theres exception" << std::endl;
        std::cout << e.what() << std::endl;
    }
    std::cout << "this works again" << std::endl;
}