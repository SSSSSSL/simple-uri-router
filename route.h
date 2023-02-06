/**
 * @file route.h
 * @author SSSSSSL (SSSSSSL@github.com, sslee@rgblab.kr)
 * @brief Simple URI Router
 * @version 1.0
 * @date 2023-02-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ROUTE_H_
#define _ROUTE_H_

#include "event.h"
#include "exception.h"
#include "src/method.h"
#include "src/parser.h"
#include "src/resource.h"
#include "src/tokenizer.h"

#include <memory>
#include <string>

namespace Route
{
    using Method = Source::Method::Type;

    class Router
    {
    private:
        using func = Source::Method::func;

        using string = std::string;

        template <typename T>
        using sptr = std::shared_ptr<T>;

    public:
        Router();

        // void regist(Method type, const string& path, func&& f);

        template <typename F>
        void regist(Method type, const string& path, F&& f);

        void call(Method type, const string& uri);

    private:
        sptr<Source::Resource>  root;
    };
}

template <typename F>
void
Route::Router::regist(Method type, const string& path, F&& f)
{
    Source::Tokenizer tk(path, '/');

    // root부터 시작함
    sptr<Source::Resource> rp = root;

    // std::cout << "[ROOT POINT] " << root.get() << std::endl;

    // 토큰을 자르고
    for (auto& token : tk.getAll())
    {
        // std::cout << std::endl;
        // std::cout << "token : [" << token << "] " << std::endl;

        // Parameter Resource일 때
        if (token[0] == ':')
        {
            string param_key = token.substr(1, token.size() - 1);

            // 내가 paramter를 가진 resource라면
            if (rp->existNextParamter())
            {
                // 다음 위치의 paramter resource로 가서
                auto next = rp->getParamterNext();

                auto sp = std::static_pointer_cast<Source::ParameterResource>(next);

                // 만약 새로 삽입하고자하는 key와 다르다면 throw 
                if (sp->getParamterName() != param_key)
                    throw AlreadyExist("Router::regist, parameter already exist");
                
                // 기존 기와 같다면 거기로 간다.
                rp = next;
                continue;
            }

            // 부모를 rp로 가지는 Parameter Resource를 생성. 
            // param_key는 더 이상 쓸 필요 없으니 넘겨준다.
            auto next = Source::ParameterResource::create(rp, std::move(param_key));
            // std::cout << "[created] " << (next->isParamter() ? "Parameter" : "Concrete") << std::endl;
            // std::cout << "[POINT] " << next.get() << std::endl;

            rp->addNextParamter(next);

            // move next
            rp = rp->getParamterNext();
        }
        // Resource일 때
        else
        {
            // 현재 위치에 다음 path가 존재하지 않을 때
            if (!rp->findConcrete(token)) {
                // std::cout << token << " not found...! will be inserted" << std::endl;

                try {
                    // 부모를 rp로 가지는 Concrete Resource를 샐성
                    auto next = Source::Resource::create(rp);

                    // std::cout << "[created] " << (next->isParamter() ? "Parameter" : "Concrete") << std::endl;
                    // std::cout << "[POINT] " << next.get() << std::endl;

                    // 토큰을 콘트리트로 등록
                    rp->addConcrete(token, next);
                }
                catch (AlreadyExist& e)
                {
                    // 이미 존재하지 않는다는 것을 확인한 이후기에, 절대로 여기로 접근 안함.
                    // std::cout << "?????????????????????????" << std::endl;
                }
            }

            // move next
            rp = rp->getConcreteNext(token);
        }
    }

    // regist method
    // rp->regist(type, std::forward<func>(f));
    rp->regist(type, std::bind(std::forward<F>(f), std::placeholders::_1));
}

#endif