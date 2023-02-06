#ifndef _RGBLAB_ROUTE_METHOD_H_
#define _RGBLAB_ROUTE_METHOD_H_

#include "../exception.h"

#include <functional>
#include <string>

namespace Route
{
    class Event;
    
    namespace Source
    {
        class Method
        {
        protected:
            using func = std::function<void(const Event& e)>;
            using string = std::string;

        public:
            enum class Type : unsigned int
            {
                GET,
                POST,
                PUT,
                DELETE
            };

            void regist(Type type, func&& f);

            void operator() (Type type, const Event& e);

            inline static Type parse(const string& s);

        private:
            func    f_get;
            func    f_put;
            func    f_delete;
            func    f_post;
        };
    }
}

Route::Source::Method::Type
Route::Source::Method::parse(const string& s)
{
    if (s.size() == 3)
    {
        if (s[0] == 'G' && s[1] == 'E' && s[2] == 'T')
            return Type::GET;

        if (s[0] == 'P' && s[1] == 'U' && s[2] == 'T')
            return Type::PUT;
    }
    else if (s.size() == 4)
    {
        if (s[0] == 'P' && s[1] == 'O' && s[2] == 'S' && s[3] == 'T')
            return Type::POST;
    }
    else if (s.size() == 6)
    {
        if (s[0] == 'D' && s[1] == 'E' && s[2] == 'L' && s[3] == 'E' && s[4] == 'T' && s[5] == 'E')
            return Type::DELETE;
    }
    
    throw NotExist("Method::parse, [" + s + "] not exist.");
}

#endif