#pragma once

/*************************************************************
 * Copyright © 2015, Felix Bytow <felix.bytow@googlemail.com *
 *                                                           *
 * See the file COPYING for copying permissions.             *
 *************************************************************/

#ifndef DDIC_REGISTER_PROXY_HXX
#define DDIC_REGISTER_PROXY_HXX

namespace ddic
{
    struct abstract_factory;
    class container;
    
    class register_proxy
    {
    public:
        register_proxy(std::shared_ptr<abstract_factory> const & p, container & c);
        register_proxy(register_proxy && src);

        register_proxy & as(std::string const & what);

        template <typename Type>
        register_proxy & as()
        {
            return as(typeid(Type).name());
        }

    private:
        std::shared_ptr<abstract_factory> p_;
        container & c_;
    };
}

#endif // DDIC_REGISTER_PROXY_HXX
