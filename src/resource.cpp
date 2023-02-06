#include "resource.h"

/*************************************************************************************************/
/******************************************* Resource ********************************************/
/*************************************************************************************************/

Route::Source::Resource::Resource(sptr<Resource>& _parent) : parent(_parent)
{

}

Route::Source::Resource::Resource()
{

}

bool
Route::Source::Resource::isParamter() const
{
    return false;
}
bool
Route::Source::Resource::isConcrete() const
{
    return true;
}

bool
Route::Source::Resource::findConcrete(const string& s) const
{
    return next_concrete.find(s) != next_concrete.end();
}

std::shared_ptr<Route::Source::Resource>
Route::Source::Resource::getConcreteNext(const string& s) const
{
    if (!findConcrete(s))
        throw NotExist("Resource::getConcreteNext, not exist \"" + s + "\"");

    return next_concrete.at(s);
}

bool
Route::Source::Resource::existNextParamter() const
{
    if (!next_paramter)
        return false;
    return true;
}

std::shared_ptr<Route::Source::Resource>
Route::Source::Resource::getParamterNext() const
{
    if (!existNextParamter())
        throw NotExist("Resource::getParameterNext, not exist");

    return next_paramter;
}

void
Route::Source::Resource::addConcrete(const string& name, sptr<Resource>& next)
{
    if (findConcrete(name))
        throw AlreadyExist("Resource::addConcrete, already exist [" + name + "]");

    next_concrete.insert(std::make_pair(name, next));
}

void
Route::Source::Resource::addConcrete(string&& name, sptr<Resource>& next)
{
    if (findConcrete(name))
        throw AlreadyExist("Resource::addConcrete, already exist [" + name + "]");

    next_concrete.insert(std::make_pair(std::move(name), next));
}

void
Route::Source::Resource::addNextParamter(sptr<Resource>& next)
{
    if (existNextParamter())
        throw AlreadyExist("Resource::addNextParamter, already exist");
        
    next_paramter = next;
}

/*************************************************************************************************/
/**************************************** Parameter Resource *************************************/
/*************************************************************************************************/

/*
Route::Source::ParameterResource::ParameterResource(const string& _value) : value(_value)
{

}
*/
Route::Source::ParameterResource::ParameterResource(sptr<Resource>& _parent, const string& _parameter_name) : Resource(_parent), paramter(_parameter_name)
{

}
Route::Source::ParameterResource::ParameterResource(sptr<Resource>& _parent, string&& _parameter_name) : Resource(_parent), paramter(std::forward<string>(_parameter_name))
{

}

bool
Route::Source::ParameterResource::isParamter() const
{
    return true;
}
bool
Route::Source::ParameterResource::isConcrete() const
{
    return false;
}

std::string
Route::Source::ParameterResource::getParamterName() const
{
    return paramter;
}