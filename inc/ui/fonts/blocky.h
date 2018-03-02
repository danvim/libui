//
// Created by Daniel on 19/2/2018.
//

#ifndef INNO14_D_2017_INNO_BLOCKY_H
#define INNO14_D_2017_INNO_BLOCKY_H

#include <cstdint>
#include "ui/font.h"
#include "ui/font_repo.h"

namespace ui {
    namespace fonts {
        // Font data for Blocky 5pt
        extern const uint8_t blocky_5ptBitmaps[];
        extern const FONT_INFO blocky_5ptFontInfo;
        extern const FONT_CHAR_INFO blocky_5ptDescriptors[];

        class Blocky: public Font {
        public:
            Blocky();
        };

        extern const Blocky blocky;
    }
}

#endif //INNO14_D_2017_INNO_BLOCKY_H
