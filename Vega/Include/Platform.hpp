#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#pragma once

#ifdef _M_X64

#if defined _WIN32 && defined _MSC_VER

#endif

#if defined __linux__ && defined __GNUC__
extern "C" {
#include <dlfcn.h>
}
#endif

#else
#error "Architecture not supported"
#endif

#endif