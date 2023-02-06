#include "tokenizer.h"

#include <iostream>

Route::Source::Tokenizer::Tokenizer(const string& s, char delimeter) : origin(s), delim(delimeter)
{
    tokenize();
}

void
Route::Source::Tokenizer::tokenize()
{
    ssz_type pos = origin[0] == delim ? 1 : 0;
    ssz_type nxt = pos;

    while (pos < origin.length())
    {
        nxt = next(pos);

        tokens.push_back({pos, nxt - pos});       

        pos = nxt + 1;
    }
}
/*
void
Route::Source::Tokenizer::tokenize()
{
    ssz_type pos = origin[0] == delim ? 1 : 0;
    ssz_type nxt = pos;

    while (pos <= origin.length())
    {
        nxt = next(pos);

        tokens.push_back({pos, nxt - pos});       

        pos = nxt + 1;
    }

    if (tokens.back().len == 0)
        tokens.erase(--tokens.end());
}
*/

std::string::size_type
Route::Source::Tokenizer::next(ssz_type pos)
{
    auto ans = pos;
    for (; ans < origin.length() && origin[ans] != delim; ans++) { }
    return ans;
}

std::vector<std::string> 
Route::Source::Tokenizer::getAll()
{
    vector<string> ans;

    for (auto t : tokens)
        ans.push_back(origin.substr(t.start, t.len));

    return ans;
}

std::string
Route::Source::Tokenizer::getToken(vsz_type<Pos> idx)
{
    if (idx >= tokens.size())
        throw OutOfRange("Tokenizer getToken, index " + std::to_string(idx) + " out of range. " + std::to_string(tokens.size()));

    return origin.substr(tokens[idx].start, tokens[idx].len);

}

Route::Source::Tokenizer::Pos
Route::Source::Tokenizer::getPos(vsz_type<Pos> idx)
{
    if (idx >= tokens.size())
        throw OutOfRange("Tokenizer getPos, index " + std::to_string(idx) + " out of range. " + std::to_string(tokens.size()));

    return tokens[idx];
}

std::vector<Route::Source::Tokenizer::Pos>::size_type
Route::Source::Tokenizer::getNumOfToken()
{
    return tokens.size();
}