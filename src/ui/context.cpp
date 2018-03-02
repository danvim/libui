//
// Created by Daniel on 20/2/2018.
//

#include "ui/context.h"


const libsc::Lcd::Rect ui::Context::full_screen(0, 0, 128, 160);
libsc::Lcd* ui::Context::lcd_ptr = nullptr;
libsc::Joystick* ui::Context::joystick_ptr = nullptr;
libsc::BatteryMeter* ui::Context::batteryMeter = nullptr;
ui::ColorScheme ui::Context::color_scheme;
libsc::Joystick::State ui::Context::JOYSTICK_UP = libsc::Joystick::State::kUp;
libsc::Joystick::State ui::Context::JOYSTICK_DOWN = libsc::Joystick::State::kDown;
libsc::Joystick::State ui::Context::JOYSTICK_LEFT = libsc::Joystick::State::kLeft;
libsc::Joystick::State ui::Context::JOYSTICK_RIGHT = libsc::Joystick::State::kRight;

void ui::Context::setColorScheme(ui::ColorScheme colorScheme) {
    Context::color_scheme = colorScheme;
}

void ui::Context::remap_joystick_directions(libsc::Joystick::State up, libsc::Joystick::State down,
                                            libsc::Joystick::State left, libsc::Joystick::State right) {
    JOYSTICK_UP = up;
    JOYSTICK_DOWN = down;
    JOYSTICK_LEFT = left;
    JOYSTICK_RIGHT = right;
}

void ui::Context::set_joystick_rotation(ui::Context::RotationalChange rotationalChange) {
    if (rotationalChange == QUARTER_CCW) {
        remap_joystick_directions(
                libsc::Joystick::State::kLeft,
                libsc::Joystick::State::kRight,
                libsc::Joystick::State::kDown,
                libsc::Joystick::State::kUp
        );
    } else if (rotationalChange == QUARTER_CW) {
        remap_joystick_directions(
                libsc::Joystick::State::kRight,
                libsc::Joystick::State::kLeft,
                libsc::Joystick::State::kUp,
                libsc::Joystick::State::kDown
        );
    } else if (rotationalChange == HALF_TURN) {
        remap_joystick_directions(
                libsc::Joystick::State::kDown,
                libsc::Joystick::State::kUp,
                libsc::Joystick::State::kRight,
                libsc::Joystick::State::kLeft
        );
    }
}
