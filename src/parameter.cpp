#include "parameter.h"

/*************************************************************************************************/
/************************************** Parameter Parse Result ***********************************/
/*************************************************************************************************/

Route::Source::Parameter::Parameter() : type(Type::UNKOWN)
{

}

Route::Source::Parameter::Parameter(const string& s)
{
    setValue(s);
}

Route::Source::Parameter::Parameter(string&& s)
{
    setValue(std::forward<string>(s));
}

Route::Source::Parameter::Parameter(intgr i)
{
    setValue(i);
}

Route::Source::Parameter::Parameter(ratio r)
{
    value.rational = r;
    type = Type::RATIONAL;
}

void
Route::Source::Parameter::setValue(const string& s)
{
    value_string = s;
    type = Type::STRING;
}
void
Route::Source::Parameter::setValue(string&& s)
{
    value_string = std::forward<string>(s);
    type = Type::STRING;
}
void
Route::Source::Parameter::setValue(intgr i)
{
    value.integer = i;
    type = Type::INTEGRAL;
}
void
Route::Source::Parameter::setValue(ratio r)
{
    value.rational = r;
    type = Type::RATIONAL;
}

Route::Source::Parameter::Type
Route::Source::Parameter::getType() const
{
    return type;
}
const long long int&
Route::Source::Parameter::asInteger() const
{
    return value.integer;
}
const long double& 
Route::Source::Parameter::asRatio() const
{
    return value.rational;
}
const std::string& 
Route::Source::Parameter::asString() const
{
    return value_string;
}
