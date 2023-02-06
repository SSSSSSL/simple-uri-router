/**
 * @file resource.h
 * @author SSSSSSL (SSSSSSL@github.com, sslee@rgblab.kr)
 * @brief 
 * @version 1.0
 * @date 2023-01-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ROUTE_PARAMETER_H_
#define _ROUTE_PARAMETER_H_

#include "../exception.h"

#include <regex>
#include <string>

namespace Route
{
    // forward declaration
    class Event;

    namespace Source
    {
        class Parameter
        {
            friend class ParameterParser;
            friend class Route::Event;

        protected:
            using string = std::string;
            using intgr = long long int;
            using ratio = long double;

        public:
            enum class Type
            {
                UNKOWN,
                RATIONAL,
                INTEGRAL,
                STRING
            };

            Type getType() const;
            const intgr& asInteger() const;
            const ratio& asRatio() const;
            const string& asString() const;

        private:
            Parameter();
            Parameter(const string& s);
            Parameter(string&& s);
            Parameter(intgr i);
            Parameter(ratio r);

            void setValue(const string& s);
            void setValue(string&& s);
            void setValue(intgr i);
            void setValue(ratio r);

            union Data
            {
                ratio rational;
                intgr integer;
            };

            Data    value;
            string  value_string;
            Type    type;
        };
    }
}

#endif