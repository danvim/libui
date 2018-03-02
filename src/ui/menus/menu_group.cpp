//
// Created by Daniel on 17/2/2018.
//

#include <sstream>
#include <utility>
#include <libsc/system.h>
#include "ui/menus/menu_group.h"

namespace ui {

    MenuGroup::MenuGroup(std::string menu_name) {
        this->setName(std::move(menu_name));
        this->setRegion(Context::full_screen);

        //Style setup
        textBlockTitle.setFont(&fonts::humanist);
        textBlockTitle.setTextWrap(text::ELLIPSIS);
        textBlockTitle.setColor(Context::color_scheme.BODY);
        textBlockTitle.setRegion(PADDING, TEXT_OFFSET, Context::full_screen.w - PADDING - BATTERY_METER_WIDTH, 120);
        textBlockTitle.setText(this->name);

        textBlockBatteryVoltage.setFont(&fonts::blocky);
        textBlockBatteryVoltage.setTextWrap(text::NO_WRAP);
        textBlockBatteryVoltage.setRegion(112, 6, 20, 5);
        textBlockBatteryVoltage.setText("Err");
    }

    int MenuGroup::run() {
        drawBaseUI();

        //Draw items
        drawPage();

        //Rendering loop
        bool is_exit = false;
        libsc::Timer::TimerInt time;

        while (!is_exit) {
            if ((time = libsc::System::Time()) % 300 == 1) {
                libsc::Joystick::State state = Context::joystick_ptr->GetState();
                if (state == Context::JOYSTICK_UP) {
                    //Select prev item
                    selectPrevAction();
                } else if (state == Context::JOYSTICK_DOWN) {
                    //Select next item
                    selectNextAction();
                }
            }

            if (time % 1000 == 1) {
                drawBatteryMeter();
            }
        }

        //Exit preparation

        return 0;
    }

    void MenuGroup::setHasBackArrow(bool has_back_arrow) {
        this->has_back_arrow = has_back_arrow;
    }

    void MenuGroup::drawBatteryMeter() {
        float voltage = Context::batteryMeter->GetVoltage();
        uint16_t &battery_color = voltage > 7.4 ?
                                  Context::color_scheme.SUCCESS :
                                  Context::color_scheme.DANGER;

        Icons::drawBatteryGauge(Context::full_screen.w - 19, 4, battery_color, 16, 9);
        Context::lcd_ptr->SetRegion(libsc::Lcd::Rect(Context::full_screen.w - 18, 5, 13, 7));
        Context::lcd_ptr->FillColor(Context::color_scheme.BACKGROUND_LIGHTER);
        std::ostringstream os;
        os << (roundf(voltage * 10) / 10);
        if (os.str().back() == '.')
            os << '0';
        textBlockBatteryVoltage.setText(os.str());
        textBlockBatteryVoltage.setColor(battery_color);
        textBlockBatteryVoltage.render();
    }

    void MenuGroup::addMenuAction(MenuAction* menu_action) {
        menu_actions.push_back(menu_action);
    }

    void MenuGroup::render() {
        MenuAction::render();

        //Draw arrow
        Icons::drawCaret(
                Context::full_screen.w - PADDING,
                CARET_OFFSET,
                is_selected ? Context::color_scheme.PRIMARY : Context::color_scheme.GRAY,
                graphics::RIGHT, 5
        );

    }

    void MenuGroup::drawBaseUI() {
        //Draw title bar
        for (uint8_t i = 0; i < TITLE_BAR_HEIGHT; i++) {
            Context::lcd_ptr->SetRegion(libsc::Lcd::Rect(0, i, Context::full_screen.w, 1));
            Context::lcd_ptr->FillColor(ColorUtil::rgb565Mix(
                    Context::color_scheme.BACKGROUND_LIGHTER,
                    Context::color_scheme.GRAY_LIGHTER,
                    (double) i / TITLE_BAR_HEIGHT
            ));
        }
        Context::lcd_ptr->SetRegion(libsc::Lcd::Rect(0, TITLE_BAR_HEIGHT - 1, Context::full_screen.w, 1));
        Context::lcd_ptr->FillColor(Context::color_scheme.GRAY);
        textBlockTitle.render();

        //Draw back icon
        if (has_back_arrow)
            Icons::drawCaret(4, CARET_OFFSET, Context::color_scheme.BLACK, graphics::LEFT, 5);

        //Draw battery meter
        drawBatteryMeter();

        //Draw scrollbar
        Context::lcd_ptr->SetRegion(libsc::Lcd::Rect(
                Context::full_screen.w - 2,
                TITLE_BAR_HEIGHT + 1,
                SCROLLBAR_WIDTH,
                Context::full_screen.h - TITLE_BAR_HEIGHT
        ));
        Context::lcd_ptr->FillColor(Context::color_scheme.BACKGROUND_LIGHTER);
    }

    void MenuGroup::drawPage() {
        //Draw background
        Context::lcd_ptr->SetRegion(libsc::Lcd::Rect(0, TITLE_BAR_HEIGHT, Context::full_screen.w, Context::full_screen.h));
        Context::lcd_ptr->FillColor(Context::color_scheme.BACKGROUND_LIGHT);

        std::deque<MenuAction*> current_page_actions;

        uint8_t i = 0;
        auto menu_actions_it = menu_actions.begin() + (getCurrentPageIndex() * getItemsPerPage());
        //show one more item
        auto menu_actions_stop = std::min(menu_actions_it + getItemsPerPage(), menu_actions.end());

        while (menu_actions_it < menu_actions_stop) {
            MenuAction* menu_action = *menu_actions_it;

            menu_action->setRegion(
                    this->ui_region.x,
                    this->ui_region.y + TITLE_BAR_HEIGHT + ITEM_HEIGHT * i,
                    this->ui_region.w - SCROLLBAR_WIDTH,
                    ITEM_HEIGHT
            );

            current_page_actions.push_back(menu_action);

            if (i == selected_index % getItemsPerPage()) {
                menu_action->select();
            } else {
                menu_action->deselect();
            }

            menu_action->render();
            i++;
            menu_actions_it++;
        }

        drawScrollBar();
    }

    uint8_t MenuGroup::getItemsPerPage() {
        return uint8_t ((Context::full_screen.h - TITLE_BAR_HEIGHT) / ITEM_HEIGHT);
    }

    uint8_t MenuGroup::getTotalPages() {
        return (uint8_t) (menu_actions.size() / getItemsPerPage() + 1);
    }

    uint8_t MenuGroup::getCurrentPageIndex() {
        return selected_index / getItemsPerPage();
    }

    uint8_t MenuGroup::getPageIndexByItemIndex(uint8_t item_index) {
        return item_index / getItemsPerPage();
    }

    void MenuGroup::selectNewActionByIndex(uint8_t new_index) {
        new_index = (uint8_t) std::min(std::max((int) new_index, 0), (int) (menu_actions.size() - 1));

        if (new_index == selected_index)
            return;

        MenuAction* current_action_ptr = menu_actions[selected_index];
        MenuAction* new_action_ptr = menu_actions[new_index];
        current_action_ptr->deselect();
        new_action_ptr->select();
        if (isIndexInPage(new_index)) {
            //New index is in the same page. Alter current and last item
            current_action_ptr->render();
            new_action_ptr->render();
            selected_index = new_index;
        } else {
            //New index is on a new page. Need to re-render entire page
            selected_index = new_index;
            drawPage();
        }
    }

    void MenuGroup::selectPrevAction() {
        selectNewActionByIndex((uint8_t) std::max(selected_index -  1, 0));
    }

    void MenuGroup::selectNextAction() {
        selectNewActionByIndex(selected_index + (uint8_t) 1);
    }

    bool MenuGroup::isIndexInPage(uint8_t i) {
        uint8_t start_of_current_page_index = getCurrentPageIndex() * getItemsPerPage();
        return i >= start_of_current_page_index && i < start_of_current_page_index + getItemsPerPage();
    }

    void MenuGroup::drawScrollBar() {
        if (getTotalPages() > 1) {
            //draw scroll bar
            uint8_t scroll_bar_height = (uint8_t) (ui_region.h - TITLE_BAR_HEIGHT) / getTotalPages();
            uint8_t scroll_bar_offset = (getCurrentPageIndex() / (getTotalPages() - (uint8_t) 1)) * scroll_bar_height;

            Context::lcd_ptr->SetRegion(libsc::Lcd::Rect(
                    ui_region.x + ui_region.w - SCROLLBAR_WIDTH,
                    TITLE_BAR_HEIGHT + scroll_bar_offset,
                    SCROLLBAR_WIDTH,
                    scroll_bar_height)
            );

            Context::lcd_ptr->FillColor(Context::color_scheme.PRIMARY);

        }
    }
}
