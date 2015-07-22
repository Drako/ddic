#pragma once

/*************************************************************
 * Copyright © 2015, Felix Bytow <felix.bytow@googlemail.com *
 *                                                           *
 * See the file COPYING for copying permissions.             *
 *************************************************************/

/**
 * \file ddic_container.hxx
 * \author Felix Bytow
 * \since 0.1.1
 * \brief The DI container.
 * 
 * This file contains the core component of DDIC, the ddic::container.
 */

#ifndef DDIC_CONTAINER_HXX
#define DDIC_CONTAINER_HXX

#include "ddic_factory.hxx"
#include "ddic_register_proxy.hxx"

#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace ddic
{
    /**
     * \brief Little helper used for autowiring.
     * 
     * This is a little helper used for autowiring.
     * Inside classes you can do:
     * \code
     *  // if your constructor were MyClass(std::shared_ptr<IFoo> && foo, std::shared_ptr<IBar> && bar);
     *  // the following would be the approprite autowire typedef.
     *  typedef ddic::inject<IFoo, IBar> autowire;
     * \endcode
     */
    template <typename... Types>
    struct inject {};

    class container
    {
    public:
        container() {}

        container(std::weak_ptr<container> && parent)
            : parent_(std::move(parent))
        {}

        // non copyable and non movable
        container(container const &) = delete;
        container(container &&) = delete;
        container & operator = (container const &) = delete;
        container & operator = (container &&) = delete;

        // default constructible types
        template <typename Type, creation_policy Policy = creation_policy::always_new>
        auto register_type()
            -> typename std::enable_if<std::is_default_constructible<Type>::value, register_proxy>::type
        {
            auto factory = std::make_shared<default_factory<Type, Policy>>();
            factories_[typeid(Type).name()] = factory;
            return register_proxy(factory, *this);
        }

        // copyable prototypes
        template <typename Type, creation_policy Policy = creation_policy::always_new>
        auto register_type(Type const & proto)
            -> typename std::enable_if<std::is_copy_constructible<Type>::value, register_proxy>::type
        {
            auto factory = std::make_shared<prototype_factory<Type, Policy>>(proto);
            factories_[typeid(Type).name()] = factory;
            return register_proxy(factory, *this);
        }

        // custom types we'd like to construct with a functor
        template <typename Type, creation_policy Policy = creation_policy::always_new>
        register_proxy register_type(std::function<Type* (container &)> const & fn)
        {
            auto factory = std::make_shared<functor_factory<container, Type, Policy>>(fn, *this);
            factories_[typeid(Type).name()] = factory;
            return register_proxy(factory, *this);
        }

        // types with injection friendly constructors
        template <typename Type, creation_policy Policy = creation_policy::always_new, typename... Types>
        register_proxy register_type(inject<Types...> const &)
        {
            return register_type<Type, Policy>([](container & c) {
                return new Type(c.resolve<Types>()...);
            });
        }

        // types with injection AND a autowire type
        template <typename Type, creation_policy Policy = creation_policy::always_new>
        register_proxy autowire_type()
        {
            return register_type<Type, Policy>(typename Type::autowire());
        }

        template <typename Type>
        std::shared_ptr<Type> resolve(std::string const & name = typeid(Type).name())
        {
            // try resolving it here
            auto it = factories_.find(name);
            if (it != factories_.end())
                return std::static_pointer_cast<Type>(it->second->create());

            // maybe the parent can
            auto parent = parent_.lock();
            if (parent)
                return parent->resolve<Type>();

            // nope, cannot resolve the requested thing
            return std::shared_ptr<Type>();
        }

        virtual bool load_types(std::string const & filename);

    private:
        std::weak_ptr<container> parent_;
        std::unordered_map<std::string, std::shared_ptr<abstract_factory>> factories_;
        friend class register_proxy;
    };
}

#endif // DDIC_CONTAINER_HXX
