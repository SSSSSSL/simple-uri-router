/**
 * @file event.h
 * @author SSSSSSL (SSSSSSL@github.com, sslee@rgblab.kr)
 * @brief event class for router
 * @version 1.0
 * @date 2023-02-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ROUTE_EVENT_H_
#define _ROUTE_EVENT_H_

#include "exception.h"
#include "src/method.h"
#include "src/parameter.h"

#include <map>
#include <memory>
#include <string>

namespace Route
{
    class Router;
        
    class Event
    {
        friend class Route::Router;

        using string = std::string;

        using Parameter = Source::Parameter;

        template <typename T>
        using uptr = std::unique_ptr<T>;

        template <typename K, typename V>
        using map = std::map<K, V>;

    public:
        inline const Parameter& operator[] (const string& key) const;
        inline const map<string, Parameter>& path() const;
        inline const map<string, Parameter>& query() const;
            
    private:
        Event();

        inline void insertPathParam(const string& key, const Parameter& param);
        inline void insertQueryParam(const string& key, const Parameter& param);

        map<string, Parameter> m_path_param;
        map<string, Parameter> m_query_param;
    };
}

const Route::Source::Parameter&
Route::Event::operator[] (const string& s) const
{
    // path param이 먼저 처리 됨
    try {
        return m_path_param.at(s);
    }
    catch (...) {
        // 그 다음에 query param이 처리 됨.
        return m_query_param.at(s);
    }
}

const std::map<std::string, Route::Source::Parameter>&
Route::Event::path() const
{
    return m_path_param;
}

const std::map<std::string, Route::Source::Parameter>&
Route::Event::query() const
{
    return m_query_param;
}

void
Route::Event::insertPathParam(const string& key, const Parameter& param)
{
    m_path_param.insert(std::make_pair(key, param));
}

void
Route::Event::insertQueryParam(const string& key, const Parameter& param)
{
    m_query_param.insert(std::make_pair(key, param));
}

#endif