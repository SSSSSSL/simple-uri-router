#include "route.h"
#include "src/tokenizer.h"
#include "src/resource.h"

#include <iostream>
#include <string>
#include <regex>
#include <chrono>

// g++ test.cpp event.cpp route.cpp src/method.cpp src/parameter.cpp src/parser.cpp src/resource.cpp src/tokenizer.cpp -o test

inline static void test_get(const Route::Event& e) {
    std::cout << "test GET () " << std::endl;

    std::cout << e.path().at("id").asInteger() << std::endl;

    return;
}

int main()
{
    Route::Router router;

    router.regist(Route::Method::GET, "/path/:id/some", test_get);

    router.call(Route::Method::GET, "/path/1236123/some");
   
    return 1;
}