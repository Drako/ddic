/*********************************************************************
 * Copyright © 2015 - 2016, Felix Bytow <felix.bytow@googlemail.com> *
 *                                                                   *
 * See the file COPYING for copying permissions.                     *
 *********************************************************************/

#include "ddic_config.hxx"
#include "ddic_container.hxx"

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <regex>
#include <utility>

#ifdef DDIC_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

typedef bool(*entry_point_t)(ddic::container *);
#endif // DDIC_WINDOWS

#if defined(DDIC_LINUX) || defined(DDIC_MACOS)

#include <dlfcn.h>
#include <iostream>

struct ddic_plugin_data {
  bool (* entry)(ddic::container*);
};

#endif // DDIC_LINUX || DDIC_MACOS

namespace {
  std::regex const re_begin{"^(lib)?", std::regex_constants::ECMAScript | std::regex_constants::optimize};
  std::regex const re_end{R"((\.dll|\.so|\.dylib)?$)",
                          std::regex_constants::ECMAScript | std::regex_constants::optimize};

  std::string normalize_name(std::string const& name)
  {
    return std::regex_replace(
        std::regex_replace(name, ::re_begin, "", std::regex_constants::format_first_only),
        ::re_end, "", std::regex_constants::format_first_only
    );
  }
}

namespace ddic {
  bool container::load_types(std::string const& name)
  {
    auto const filename = ::normalize_name(name);

#ifdef DDIC_WINDOWS
    static std::array<std::function<HMODULE(std::string const&)>, 2> const loaders{
        // normal dll naming (foo.dll)
        [](std::string const& fn) {
          return LoadLibraryA((fn+".dll").c_str());
        },
        // GCC style dll naming (libfoo.dll)
        [](std::string const& fn) {
          return LoadLibraryA(("lib"+fn+".dll").c_str());
        },
    };

    HMODULE lib = nullptr;
    for (auto const& loader : loaders) {
      lib = loader(filename);
      if (lib) {
        auto entry = (entry_point_t) GetProcAddress(lib, "ddic_register_types");
        if (entry)
          return entry(this);
        break;
      }
    }
#endif // DDIC_WINDOWS

#ifdef DDIC_LINUX
    static std::array<std::function<void*(std::string const&)>, 2> const loaders{
        // general .so
        [](std::string const& fn) {
          return dlopen(("lib"+fn+".so").c_str(), RTLD_LAZY | RTLD_GLOBAL);
        },
        // .so in application directory
        [](std::string const& fn) {
          return dlopen(("./lib"+fn+".so").c_str(), RTLD_LAZY | RTLD_GLOBAL);
        },
    };
#endif // DDIC_LINUX

#ifdef DDIC_MACOS
    static std::array<std::function<void*(std::string const&)>, 4> const loaders{
        // general .so
        [](std::string const& fn) {
          return dlopen(("lib"+fn+".so").c_str(), RTLD_LAZY | RTLD_GLOBAL);
        },
        // general .dylib
        [](std::string const& fn) {
          return dlopen(("lib"+fn+".dylib").c_str(), RTLD_LAZY | RTLD_GLOBAL);
        },
        // .so in application directory
        [](std::string const& fn) {
          return dlopen(("./lib"+fn+".so").c_str(), RTLD_LAZY | RTLD_GLOBAL);
        },
        // .dylib in application directory
        [](std::string const& fn) {
          return dlopen(("./lib"+fn+".so").c_str(), RTLD_LAZY | RTLD_GLOBAL);
        },
    };
#endif // DDIC_MACOS

#if defined(DDIC_LINUX) || defined(DDIC_MACOS)

    void* lib = nullptr;
    for (auto const& loader : loaders) {
      lib = loader(filename);
      if (lib) {
        auto data = (ddic_plugin_data*) dlsym(lib, "ddic_plugin_data");
        if (data)
          return data->entry(this);
        break;
      }
    }
    std::cerr << dlerror() << std::endl;

#endif // DDIC_LINUX || DDIC_MACOS

    return false;
  }
}
