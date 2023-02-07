# simple-uri-router
Simple URI router


# Usage


```c++
// call back
inline static void test_get(const Route::Event& e)
{
    std::cout << "test GET () " << std::endl;

    std::cout << e["id"].asInteger() << std::endl;

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
