/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#include "ddic_config.hxx"
#include "ddic_container.hxx"

#include <utility>

#ifdef DDIC_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

typedef bool(*entry_point_t)(ddic::container *);
#endif // DDIC_WINDOWS

#ifdef DDIC_LINUX
#include <dlfcn.h>
#include <iostream>

struct ddic_plugin_data
{
    bool (*entry)(ddic::container *);
};
#endif // DDIC_LINUX

namespace ddic
{
    bool container::load_types(std::string const & filename)
    {
#ifdef DDIC_WINDOWS
        // TODO: deal with the case where the filename already ends in .dll
        std::string fullname = filename + ".dll";
        auto lib = LoadLibraryA(fullname.c_str());
        if (lib)
        {
            auto entry = (entry_point_t)GetProcAddress(lib, "ddic_register_types");
            if (entry)
                return entry(this);
        }
#endif // DDIC_WINDOWS

#ifdef DDIC_LINUX
        // TODO: fix this for filenames that are more complex than "foo"...
        std::string fullname = "lib" + filename + ".so";
        auto lib = dlopen(fullname.c_str(), RTLD_LAZY | RTLD_GLOBAL);
        if (!lib)
        {
            // explicitely try current directory
            fullname = "./" + fullname;
            lib = dlopen(fullname.c_str(), RTLD_LAZY | RTLD_GLOBAL);
        }
            
        if (lib)
        {
            auto data = (ddic_plugin_data*)dlsym(lib, "ddic_plugin_data");
            if (data)
                return data->entry(this);
            else
                std::cerr << dlerror() << std::endl;
        }
        else
            std::cerr << dlerror() << std::endl;
#endif // DDIC_LINUX
        
        return false;
    }
}
