//
// Created by Daniel on 20/2/2018.
//

#ifndef INNO14_D_2017_INNO_PERIPHERALS_H
#define INNO14_D_2017_INNO_PERIPHERALS_H


#include <libsc/lcd.h>
#include <libsc/joystick.h>
#include <libsc/battery_meter.h>
#include <ui/color_schemes/color_scheme.h>

namespace ui {
    class Context {
    public:
        static libsc::Lcd* lcd_ptr;
        static libsc::Joystick* joystick_ptr;
        static libsc::BatteryMeter* batteryMeter;
        static ColorScheme color_scheme;

        static void setColorScheme(ColorScheme colorScheme);

        static const libsc::Lcd::Rect full_screen;

        static libsc::Joystick::State JOYSTICK_UP;
        static libsc::Joystick::State JOYSTICK_DOWN;
        static libsc::Joystick::State JOYSTICK_LEFT;
        static libsc::Joystick::State JOYSTICK_RIGHT;

        static void remap_joystick_directions(
                libsc::Joystick::State up,
                libsc::Joystick::State down,
                libsc::Joystick::State left,
                libsc::Joystick::State right
        );

        enum RotationalChange {
            NO_TURN,
            QUARTER_CCW,
            QUARTER_CW,
            HALF_TURN
        };

        static void set_joystick_rotation(RotationalChange rotationalChange);
    };
}



#endif //INNO14_D_2017_INNO_PERIPHERALS_H
