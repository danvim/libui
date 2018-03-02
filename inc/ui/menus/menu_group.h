//
// Created by Daniel on 17/2/2018.
//

#ifndef INNO14_D_2017_INNO_MENU_H
#define INNO14_D_2017_INNO_MENU_H


#include <utility>
#include <string>
#include <libsc/lcd.h>
#include <ui/context.h>
#include <ui/color_util.h>
#include <ui/text_block.h>
#include <ui/fonts/humanist.h>
#include <ui/icons.h>
#include <ui/fonts/blocky.h>
#include <ui/menus/menu_action.h>

namespace ui {
    class MenuGroup: public virtual MenuAction {
    public:
        explicit MenuGroup(std::string menu_name = "Untitled");

        int run() override;

        void setHasBackArrow(bool has_back_arrow);

        void addMenuAction(MenuAction* menu_action);

        void render() override;

    private:
        static const uint8_t TITLE_BAR_HEIGHT = 18;
        static const uint16_t BATTERY_METER_WIDTH = 20;
        static const uint16_t SCROLLBAR_WIDTH = 2;
        static const uint16_t CARET_OFFSET = TEXT_OFFSET + 1;

        bool has_back_arrow = false;

        TextBlock textBlockTitle;
        TextBlock textBlockBatteryVoltage;

        std::vector<MenuAction*> menu_actions;
        uint8_t selected_index = 0;

        uint8_t getItemsPerPage();
        uint8_t getTotalPages();
        uint8_t getCurrentPageIndex();
        uint8_t getPageIndexByItemIndex(uint8_t item_index);

        void drawBatteryMeter();

        void drawBaseUI();

        void drawPage();

        void selectPrevAction();

        void selectNextAction();

        bool isIndexInPage(uint8_t i);

        void selectNewActionByIndex(uint8_t i);

        void drawScrollBar();
    };
}


#endif //INNO14_D_2017_INNO_MENU_H
