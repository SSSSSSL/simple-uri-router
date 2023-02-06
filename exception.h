/**
 * @file exception.h
 * @author SSSSSSL (SSSSSSL@github.com, sslee@rgblab.kr)
 * @brief 
 * @version 1.0
 * @date 2023-01-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ROUTE_EXCETPTION_H_
#define _ROUTE_EXCETPTION_H_

#include <stdexcept>


namespace Route
{
    class NotExist : public std::runtime_error
    {
    private:
        using string = std::string;
    public:
        NotExist(const string& what) : std::runtime_error(what) { }
    };

    class AlreadyExist : public std::runtime_error
    {
    private:
        using string = std::string;
    public:
        AlreadyExist(const string& what) : std::runtime_error(what) { }
    };
}

#endif