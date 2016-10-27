#pragma once

/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

/**
 * \file ddic_plugin.hxx
 * \author Felix Bytow
 * \since 0.1.1
 * \brief Helper macros for ddic plugins.
 * 
 * This file contains some macros used to create ddic plugins
 * (i.e. plugins that can be loaded using the ddic::container)
 */

#ifndef DDIC_PLUGIN_HXX
#define DDIC_PLUGIN_HXX

#include "ddic_config.hxx"
#include "ddic_container.hxx"

/**
 * \macro DDIC_REGISTER_TYPES
 * \brief Register the types the plugin provides with the given container.
 * \param C The name of the pointer to the DI container inside the registration function.
 * 
 * This macro is to be used once in each plugin module.
 * Every plugin must use it to register the types it provides with the DI container,
 * so the main application can make use of these types.
 * 
 * \code
 *  DDIC_REGISTER_TYPES(c)
 *  {
 *      c->register_type<Foo>().as<IFoo>();
 *      return true; // the registration function shall return a boolean indicating success or failure.
 *  }
 * \endcode
 */

#ifdef DDIC_WINDOWS
#   ifdef DDIC_MSVC
#       define DDIC_EXPORT __declspec(dllexport)
#   else
#       define DDIC_EXPORT __attribute__((dllexport))
#   endif
#   define DDIC_REGISTER_TYPES(C) \
        extern "C" bool DDIC_EXPORT ddic_register_types(ddic::container * C)
#else
#   define DDIC_REGISTER_TYPES(C) \
        extern "C" bool ddic_register_types(ddic::container *); \
        extern "C" struct \
        { \
            bool (*entry)(ddic::container *); \
        } const ddic_plugin_data = { &ddic_register_types }; \
        extern "C" bool ddic_register_types(ddic::container * C)
#endif

#endif // DDIC_PLUGIN_HXX
