//
// Created by Daniel on 19/2/2018.
//

#ifndef INNO14_D_2017_INNO_HUMANIST_H
#define INNO14_D_2017_INNO_HUMANIST_H

#include <cstdint>
#include "ui/font.h"
#include "ui/font_repo.h"

namespace ui {
    namespace fonts {
        // Font data for Humanist 9pt
        extern const uint8_t humanist_9ptBitmaps[];
        extern const FONT_INFO humanist_9ptFontInfo;
        extern const FONT_CHAR_INFO humanist_9ptDescriptors[];

        class Humanist: public Font {
        public:
            Humanist();
        };

        extern const Humanist humanist;
    }
}

#endif //INNO14_D_2017_INNO_HUMANIST_H
