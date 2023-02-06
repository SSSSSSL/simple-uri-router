/**
 * @file parser.h
 * @author SSSSSSL (SSSSSSL@github.com, sslee@rgblab.kr)
 * @brief parser class for route
 * @version 1.0
 * @date 2023-02-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ROUTE_PARSER_H_
#define _ROUTE_PARSER_H_

#include "parameter.h"
#include "tokenizer.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Route
{
    namespace Source
    {
        // forward declaration
        class QueryParamParser;

        class KeyValueParser
        {
            friend class QueryParamParser;

        protected:
            template <typename T>
            using vector = std::vector<T>;
            
            using string = std::string;

            using ssz_type = string::size_type;

            struct Pos
            {
                ssz_type start;
                ssz_type len;
            };

            struct KeyValue
            {
                Pos key;
                Pos val;
            };

        public:
            KeyValueParser(string&& s);

        private:
            void parse();
            string data;
            vector<KeyValue> key_value_s;
        };

        class QueryParamParser
        {
        protected:
            template <typename T>
            using vector = std::vector<T>;

            template <typename One, typename Two>
            using pair = std::pair<One, Two>;

            template <typename T>
            using uptr = std::unique_ptr<T>;

            using string = std::string;

            using ssz_type = string::size_type;

            using key_value = pair<string, string>;

            using result = vector<key_value>;

        public:
            QueryParamParser(string& s);

            result getAll();

            inline static bool existQueryParameter(const string& s);
            inline static void addQueryParameter(string& uri, const string& key, const string& val);

        private:
            void parse(string& s);

            uptr<KeyValueParser> kp;
        };

        class ParameterParser
        {
        protected:
            using string = std::string;
            using regex = std::regex;

        public:
            static Parameter parse(const string& s);
            static Parameter parse(string&& s);

        private:
            static bool isIntegral(const string& s);
            static bool isRational(const string& s);
        };
    }
}

bool
Route::Source::QueryParamParser::existQueryParameter(const string& s)
{
    return s.find('?') != string::npos;
}

void
Route::Source::QueryParamParser::addQueryParameter(string& uri, const string& key, const string& val)
{
    if (existQueryParameter(uri))
        uri.push_back('?');
    else 
        uri.push_back(',');

    uri.append(key);
    uri.push_back('=');
    uri.append(val);
}

#endif