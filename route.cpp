#include "route.h"

Route::Router::Router() : root(Source::Resource::createRoot())
{

}

void
Route::Router::call(Method type, const string& uri)
{
    // 이벤트 생성
    Event e;

    // QueryParam이 존재하면, path를 자르고, QueryParam으로 바꾸는 작업이 선행되야함.
    // 그래야 QueryParameter로 '/'같은 문자가 포함될 수 있음.
    auto path = uri;
    Source::QueryParamParser qp(path);

    for (auto &key_value : qp.getAll())
    {
        // add Query Parameter
        e.insertQueryParam(key_value.first, Source::ParameterParser::parse(key_value.second));
    }

    Source::Tokenizer tk(path, '/');

    // root부터 시작함.
    sptr<Source::Resource> rp = root;

    auto tokens = tk.getAll();

    // 토큰을 자르고
    for (size_t i=0; i<tokens.size(); i++)
    {
        string& token = tokens[i];

        // 일단 concrete에서 먼저 탐색함.        
        if (rp->findConcrete(token))
        {
            // 존재하면 넘어감.
            rp = rp->getConcreteNext(token);
            continue;
        }

        // token이 concrete하지 않다면, parameter로 간주함.
        // parameter로 접근할 수 있다면,
        if (rp->existNextParamter())
        {
            auto param_resource = rp->getParamterNext();

            auto sp = std::static_pointer_cast<Source::ParameterResource>(param_resource);
            
            // add Path Parameter
            e.insertPathParam(sp->getParamterName(), Source::ParameterParser::parse(token));

            // rp = rp->getParamterNext();
            rp = param_resource;

            continue;
        }

        throw NotExist("Router::call, " + path + " is invalid path");
    }

    // call method
    (*rp) (type, e);
}