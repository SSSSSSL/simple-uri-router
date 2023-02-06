#include "parser.h"

/*************************************************************************************************/
/**************************************** KeyValue Parser ****************************************/
/*************************************************************************************************/
Route::Source::KeyValueParser::KeyValueParser(string&& s) : data(std::forward<string>(s))
{
    parse();
}

void
Route::Source::KeyValueParser::parse()
{
    Tokenizer tk(data, ',');

    size_t offset = 0;
    for (auto& token : tk.getAll())
    {
        auto it = token.find('=');

        if (it == string::npos)
        {
            offset += (token.size() + 1);
            continue;
        }

        key_value_s.push_back({{offset, it}, {offset+it+1, token.size()-it-1}});
        offset += (token.size() + 1);
    }
}

/*************************************************************************************************/
/*************************************** QueryParam Parser ***************************************/
/*************************************************************************************************/

Route::Source::QueryParamParser::QueryParamParser(string& s)
{
    parse(s);
}

void
Route::Source::QueryParamParser::parse(string& s)
{
    ssz_type it = s.find('?');

    // '?' not found
    if (it == string::npos)
        return;

    // ? 이후부터 KeyValueParser에게 넘기고
    kp = std::make_unique<KeyValueParser>(s.substr(it+1, s.size()-it-1));

    // ? 이전까지를 parsing한다.
    s.erase(s.begin()+it, s.end());
}

std::vector<std::pair<std::string, std::string>>
Route::Source::QueryParamParser::getAll()
{
    result ans;

    for (auto& k_v : kp->key_value_s)
        ans.push_back(std::make_pair(kp->data.substr(k_v.key.start, k_v.key.len), kp->data.substr(k_v.val.start, k_v.val.len)));

    return ans;
}

/*************************************************************************************************/
/***************************************** Parameter Parser **************************************/
/*************************************************************************************************/
Route::Source::Parameter
Route::Source::ParameterParser::parse(const string& s)
{
    if (isIntegral(s)) {
        try {
            return Parameter{std::stoll(s)};
        }
        catch (...) {
            return Parameter{s};
        }
    }
    else if (isRational(s)) {
        try {
            return Parameter{std::stold(s)};
        }
        catch (...) {
            return Parameter{s};
        }
    }
    else {
        return Parameter{s};
    }
}
Route::Source::Parameter
Route::Source::ParameterParser::parse(string&& s)
{
    if (isIntegral(s)) {
        try {
            return Parameter{std::stoll(s)};
        }
        catch (...) {
            return Parameter{std::forward<string>(s)};
        }
    }
    else if (isRational(s)) {
        try {
            return Parameter{std::stold(s)};
        }
        catch (...) {
            return Parameter{std::forward<string>(s)};
        }
    }
    else {
        return Parameter{std::forward<string>(s)};
    }
}

bool
Route::Source::ParameterParser::isIntegral(const string& s)
{
    // static regex integral("^[-+]?[1-9]\\d*$");
    // return std::regex_match(s, integral);

    if (s.empty())
        return false;

    auto it = s.begin();

    // skip sign
    if (*it == '+' || *it == '-') {
        it++;

        if (it == s.end())
            return false;
    }

    while (it != s.end() && std::isdigit(*it)) { ++it; }

    return it == s.end();
}
bool
Route::Source::ParameterParser::isRational(const string& s)
{
    // static regex rational("^-?[0-9]+.[0-9]+$");
    // return std::regex_match(s, rational);

    if (s.empty())
        return false;

    auto it = s.begin();

    // skip sign
    if (*it == '+' || *it == '-') {
        it++;

        if (it == s.end())
            return false;
    }

    bool point_find = false;
    while (it != s.end() && (std::isdigit(*it) || *it == '.'))
    {
        ++it;

        if (*it == '.')
        {
            // 중복
            if (point_find)
                return false;

            point_find = true;
        }
    }

    return it == s.end() && point_find;
}