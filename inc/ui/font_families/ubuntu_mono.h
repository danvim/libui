//
// Created by Daniel on 21/2/2018.
//

#ifndef INNO14_D_2017_INNO_UBUNTU_MONO_FAMILY_H
#define INNO14_D_2017_INNO_UBUNTU_MONO_FAMILY_H


#include <ui/font_family.h>
#include <ui/fonts/ubuntu_mono.h>
#include <ui/fonts/ubuntu_mono_italic.h>

namespace ui {
    namespace font_families {
        class UbuntuMono: public FontFamily {
        public:
            UbuntuMono(): FontFamily(Config {
                    &ui::fonts::ubuntu_mono,
                    &ui::fonts::ubuntu_mono_italic,
                    nullptr,
                    nullptr,
                    nullptr,
                    nullptr
            }) {}
        };

        extern const UbuntuMono ubuntu_mono;
    }
}


#endif //INNO14_D_2017_INNO_UBUNTU_MONO_FAMILY_H
