//
// Created by Daniel on 19/2/2018.
//

#include "ui/font_repo.h"

std::map<std::string, ui::Font*> ui::FontRepo::fonts;

void ui::FontRepo::addFont(const std::string &name, ui::Font *font) {
    fonts.insert({name, font});
}

ui::Font *ui::FontRepo::getFontByName(const std::string &name) {
    return fonts[name];
}
