//
// Created by Daniel on 19/2/2018.
//

#ifndef INNO14_D_2017_INNO_FONT_REPO_H
#define INNO14_D_2017_INNO_FONT_REPO_H

#include <string>
#include "ui/font.h"

namespace ui {
    class FontRepo {
    public:
        static std::map<std::string, Font*> fonts;

        static void addFont(const std::string &name, Font* font);

        static Font* getFontByName(const std::string &name);
    };
}


#endif //INNO14_D_2017_INNO_FONT_REPO_H
