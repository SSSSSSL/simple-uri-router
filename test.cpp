#include "route.h"
#include "src/tokenizer.h"
#include "src/resource.h"

#include <iostream>
#include <string>
#include <regex>
#include <chrono>

// g++ test.cpp event.cpp route.cpp src/method.cpp src/parser.cpp src/resource.cpp src/tokenizer.cpp -o test

inline static void test_get(const Route::Event& e) {
    std::cout << "test GET () " << std::endl;

    std::cout << e["id"].asInteger() << std::endl;

    return;
}

inline static void test_second_get(const Route::Event& e) {
    std::cout << "test second GET ()" << std::endl;

    std::cout << e["id"].asInteger() << " " << e["name"].asString() << std::endl;
}

inline static void test_camera_height_get(const Route::Event& e) {
    std::cout << "test camera height GET ()" << std::endl;

    std::cout << e["user_id"].asString() << " " << e["umv_id"].asString() << std::endl;

    std::cout << "test camera height get : 720" << std::endl;
}

inline static void test_camera_width_get(const Route::Event& e) {
    std::cout << "test camera width GET ()" << std::endl;

    std::cout << e["user_id"].asString() << " " << e["umv_id"].asString() << std::endl;

    std::cout << "test camera height get : 1280" << std::endl;
}

int main()
{
    /*
    {
        Route::Router router;

        router.regist(Route::Method::GET, "/:user_id/:umv_id/camera/width", test_camera_width_get);
        router.regist(Route::Method::GET, "/:user_id/:umv_id/camera/height", test_camera_height_get);
        router.regist(Route::Method::GET, "/path/:id/some", test_get);
        router.regist(Route::Method::GET, "/path/test/:id", test_get);
        router.regist(Route::Method::GET, "/path/:id/:name/test", test_second_get);

        router.call(Route::Method::GET, "/path/test/19242");
        router.call(Route::Method::GET, "/path/2135163/SSL/test");
        router.call(Route::Method::GET, "/rgblab/test_arion/camera/width");
        router.call(Route::Method::GET, "/rgblab/test_arion/camera/height");
        // router.call(Route::Method::GET, "/test");
    }
    */

    {
        Route::Router router;

        std::chrono::system_clock::time_point begin, end;

        std::cout << std::endl;
        std::cout << "insert, \"/:user_id/:umv_id/camera/width\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.regist(Route::Method::GET, "/:user_id/:umv_id/camera/width", test_camera_width_get);
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "insert, \"/:user_id/:umv_id/camera/height\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.regist(Route::Method::GET, "/:user_id/:umv_id/camera/height", test_camera_height_get);
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "insert, \"/path/:id/some\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.regist(Route::Method::GET, "/path/:id/some", test_get);
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "insert, \"/path/test/:id\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.regist(Route::Method::GET, "/path/test/:id", test_get);
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "insert, \"/path/:id/:name/test\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.regist(Route::Method::GET, "/path/:id/:name/test", test_second_get);
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "call, \"/path/test/19242\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.call(Route::Method::GET, "/path/test/19242");
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "call, \"/path/2135163/SSL/test\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.call(Route::Method::GET, "/path/2135163/SSL/test");
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "call, \"/rgblab/test_arion/camera/width\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.call(Route::Method::GET, "/rgblab/test_arion/camera/width");
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


        std::cout << std::endl;
        std::cout << "call, \"/rgblab/test_arion/camera/height\"" << std::endl;
        begin = std::chrono::system_clock::now();
        router.call(Route::Method::GET, "/rgblab/test_arion/camera/height");
        end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    }
        
    /*
    {
        Route::Source::Tokenizer tk("/path/to/a", '/');
        auto v = tk.getAll();

        for (auto& i : v)
            std::cout << i << std::endl;
    }

    {
        Route::Source::Tokenizer tk2("/path/to/", '/');
        auto v2 = tk2.getAll();

        for (auto& i : v2)
            std::cout << i << std::endl;
    }
    */
    
    return 1;
}