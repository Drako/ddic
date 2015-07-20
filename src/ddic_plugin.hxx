#pragma once

/*************************************************************
 * Copyright © 2015, Felix Bytow <felix.bytow@googlemail.com *
 *                                                           *
 * See the file COPYING for copying permissions.             *
 *************************************************************/

#ifndef DDIC_PLUGIN_HXX
#define DDIC_PLUGIN_HXX

#include "ddic_config.hxx"

#ifdef DDIC_WINDOWS
#   ifdef DDIC_MSVC
#       define DDIC_EXPORT __declspec(dllexport)
#   else
#       define DDIC_EXPORT __attribute__((dllexport))
#   endif
#   define DDICC_REGISTER_TYPES(C) \
        extern "C" bool DDIC_EXPORT ddic_register_types(ddic::container * C)
#else
#   define DDICC_REGISTER_TYPES(C) \
        extern "C" void ddic_register_types(ddic::container *); \
        extern "C" struct \
        { \
            bool (*entry)(ddic::container *); \
        } const ddic_plugin_data = { &ddic_register_types }; \
        extern "C" void ddic_register_types(ddic::container * C)
#endif

#endif // DDIC_PLUGIN_HXX
