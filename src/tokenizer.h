#ifndef _ROUTE_SRC_TOKENIZER_H_
#define _ROUTE_SRC_TOKENIZER_H_

#include <string>
#include <stdexcept>
#include <vector>

namespace Route
{
    namespace Source
    {
        class OutOfRange : std::runtime_error
        {
        public:
            OutOfRange(const std::string& what) : std::runtime_error(what) {}
        };

        class Tokenizer
        {
        private:
            using string = std::string;
            using ssz_type = string::size_type;

            template <typename T>
            using vector = std::vector<T>;
            
            template <typename T>
            using vsz_type = typename vector<T>::size_type;

        public:
            struct Pos
            {
                ssz_type start;
                ssz_type len;
            };

            Tokenizer(const string& s, char delimeter);

            void tokenize();

            ssz_type        next(ssz_type pos);

            vector<string>  getAll();
            string          getToken(vsz_type<Pos> idx);
            Pos             getPos(vsz_type<Pos> idx);
            vsz_type<Pos>   getNumOfToken();

        private:
            string          origin;
            vector<Pos>     tokens;
            char            delim;
        };
    }
}

#endif