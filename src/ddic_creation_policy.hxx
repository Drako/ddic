#pragma once

/*************************************************************
 * Copyright © 2015, Felix Bytow <felix.bytow@googlemail.com *
 *                                                           *
 * See the file COPYING for copying permissions.             *
 *************************************************************/

#ifndef DDIC_CREATION_POLICY_HXX
#define DDIC_CREATION_POLICY_HXX

#include <cstdint>

namespace ddic
{
    /**
     * \author Felix Bytow
     * \brief is used to declare how objects of a class shall be instantiated.
     * \since 0.1.1
     * 
     * This strongly typed enum is used to declare how objects shall be instantiated.
     * When registering a new type with a container, the user can specify the policy for that type.
     * The policy is applied during the resolution of the type.
     */
    enum class creation_policy
        : std::uint8_t
    {
        always_new = 0, ///< \e resolve always returns a new instance of the registered type
        always_same = 1, ///< \e resolve always returns the same instance of the registered type (can be used for singletons)
    };
}

#endif // DDIC_CREATION_POLICY_HXX
