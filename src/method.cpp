#include "method.h"

void
Route::Source::Method::regist(Type type, func&& f)
{
    switch (type)
    {
    case Type::GET:
        f_get = std::forward<func>(f);
        break;

    case Type::POST:
        f_post = std::forward<func>(f);
        break;

    case Type::PUT:
        f_put = std::forward<func>(f);
        break;

    case Type::DELETE:
        f_delete = std::forward<func>(f);
        break;
    }
}

void
Route::Source::Method::operator() (Type type, const Event& e)
{
    switch (type)
    {
    case Type::GET:
        if (f_get)
            f_get(e);
        else
            throw NotExist("Method::operator(), GET method not exist");
        break;

    case Type::POST:
        if (f_post)
            f_post(e);
        else
            throw NotExist("Method::operator(), POST method not exist");
        break;

    case Type::PUT:
        if (f_put)
            f_put(e);
        else
            throw NotExist("Method::operator(), PUT method not exist");
        break;

    case Type::DELETE:
        if (f_delete)
            f_delete(e);
        else
            throw NotExist("Method::operator(), DELETE method not exist");
        break;
    }
}