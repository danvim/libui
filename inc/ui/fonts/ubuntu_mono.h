//
// Created by Daniel on 19/2/2018.
//

#ifndef LIBUI_UBUNTU_MONO_H
#define LIBUI_UBUNTU_MONO_H

#include <cstdint>
#include "ui/font.h"

namespace ui {
    namespace fonts {
        // Font data for Ubuntu Mono 10pt
        extern const uint8_t ubuntuMono_10ptBitmaps[];
        extern const FONT_INFO ubuntuMono_10ptFontInfo;
        extern const FONT_CHAR_INFO ubuntuMono_10ptDescriptors[];

        class UbuntuMono: public Font {
        public:
            UbuntuMono();
        };
    }
}


#endif //LIBUI_UBUNTU_MONO_H
