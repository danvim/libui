//
// Created by Daniel on 19/2/2018.
//

#ifndef INNO14_D_2017_INNO_UBUNTU_MONO_H
#define INNO14_D_2017_INNO_UBUNTU_MONO_H

#include <cstdint>
#include "ui/font.h"
#include "ui/font_repo.h"

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

        extern const UbuntuMono ubuntu_mono;
    }
}


#endif //INNO14_D_2017_INNO_UBUNTU_MONO_H
