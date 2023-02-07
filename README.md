# simple-uri-router
Simple URI router


# Usage


```c++
// call back
inline static void test_get(const Route::Event& e)
{
    std::cout << "test GET () " << std::endl;

    std::cout << e.path().at("id").asInteger() << std::endl;
    
    // if exist query parameter
    // std::cout << e.query().at("some_key").asString() << std::endl;

    return;
}

// main
int main()
{
    Route::Router router;

    router.regist(Route::Method::GET, "/path/:id/some", test_get);
    
    router.call(Route::Method::GET, "/path/1236123/some");
}
```
