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
#ifndef _ROUTE_RESOURCE_H_
#define _ROUTE_RESOURCE_H_

#include "../exception.h"
#include "method.h"

#include <map>
#include <memory>
#include <string>
#include <utility>

namespace Route
{
    // Forward Declaration
    class Router;

    namespace Source
    {
        class Resource : public Method
        {
            friend class Route::Router;
        protected:
            using string = std::string;

            template <typename K, typename V>
            using map = std::map<K, V>;

            template <typename T>
            using uptr = std::unique_ptr<T>;

            template <typename T>
            using wptr = std::weak_ptr<T>;

            template <typename T>
            using sptr = std::shared_ptr<T>;

            template <typename One, typename Two>
            using pair = std::pair<One, Two>;

            Resource(sptr<Resource>& parent);
            Resource();

        public:
            // for dynamic_pointer_cast
            virtual ~Resource() {}

            virtual bool isParamter() const;
            virtual bool isConcrete() const;

            bool findConcrete(const string& s) const;
            sptr<Resource> getConcreteNext(const string& s) const;
            sptr<Resource> getParamterNext() const;

            bool existNextParamter() const;

            void addConcrete(const string& name, sptr<Resource>& next);
            void addConcrete(string&& name, sptr<Resource>& next);
            void addNextParamter(sptr<Resource>& next);
            

            inline static sptr<Resource> create(sptr<Resource>& parent);
            inline static sptr<Resource> createRoot();

            wptr<Resource>                  parent;
            map<string, sptr<Resource>>     next_concrete;

            // 그 다음에 존재하는 parameter... 즉, /path/:id에서 path가 가질 id의 주소                
            sptr<Resource>                  next_paramter;
        };

        class ParameterResource : public Resource
        {
            friend class Route::Router;
        public:
            virtual bool isParamter() const;
            virtual bool isConcrete() const;

            string getParamterName() const;

            inline static sptr<Resource> create(sptr<Resource>& parent, const string& paramter_name);
            inline static sptr<Resource> create(sptr<Resource>& parent, string&& paramter_name);

        private:
            ParameterResource(sptr<Resource>& parent, const string& parameter_name);
            ParameterResource(sptr<Resource>& parent, string&& parameter_name);

            string                          paramter;
        };
    }
}

std::shared_ptr<Route::Source::Resource>
Route::Source::Resource::create(sptr<Resource>& parent)
{
    // std::cout << "Create Resource(parent)" << std::endl;
    return sptr<Resource>(new Route::Source::Resource(parent));
}

std::shared_ptr<Route::Source::Resource>
Route::Source::Resource::createRoot()
{
    // std::cout << "Create ResourceRoot()" << std::endl;
    return sptr<Resource>(new Route::Source::Resource());
}

std::shared_ptr<Route::Source::Resource>
Route::Source::ParameterResource::create(sptr<Resource>& parent, const string& parameter_name)
{
    // std::cout << "Create ParameterResource(parent, param_name)" << std::endl;
    return sptr<Resource>(new Route::Source::ParameterResource(parent, parameter_name));
}

std::shared_ptr<Route::Source::Resource>
Route::Source::ParameterResource::create(sptr<Resource>& parent, string&& parameter_name)
{
    // std::cout << "Create ParameterResource(parent, param_name)" << std::endl;
    return sptr<Resource>(new Route::Source::ParameterResource(parent, std::forward<string>(parameter_name)));
}

#endif