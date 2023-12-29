/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   tools.h
 * Author: smorodin
 *
 * Created on May 8, 2023, 1:54 PM
 */

#ifndef TOOLS_H
#define TOOLS_H

#        if defined(_MSC_VER)
 /*           __pragma() is specified starting from Visual Studio 2008*/
#            if (_MSC_VER < 1500)
#                error "Unsupport Visual C compiler version. Minimum version is Visual Studio 2008."
#            endif
#            define ATTRIBUTE_PACKED
/*           Enable packing and supress warning C4103: Packing was changed after the inclusion of the header, probably missing #pragma pop */
#            define BEGIN_ATTRIBUTE_PACKED __pragma(pack(push,1)) \
                                           __pragma(warning(disable : 4103))
/*           Disable packing and enable warning C4103 back */
#            define END_ATTRIBUTE_PACKED   __pragma(pack(pop)) \
                                          __pragma(warning(default : 4103))
#            define ATTRIBUTE_SECTION_GCC(x)
#        elif defined (__GNUC__)
#            define BEGIN_ATTRIBUTE_PACKED
#            define END_ATTRIBUTE_PACKED
#            if defined(__clang__)
#                define ATTRIBUTE_PACKED __attribute__ ((packed))
#            else
#                define ATTRIBUTE_PACKED __attribute__ ((gcc_struct,packed))
#            endif
#        endif /* defined(_MSC_VER) */


#include <string>

void sleep_();
void wtf(std::string str);
void fatal_error(std::string str);
uint32_t transparent_color(uint32_t old_color, uint32_t new_color, int percent);
int wchar_to_ascii(int p);

#endif /* TOOLS_H */

