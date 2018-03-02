//
// Created by Daniel on 17/2/2018.
//

#ifndef INNO14_D_2017_INNO_MENU_NUMBER_H
#define INNO14_D_2017_INNO_MENU_NUMBER_H


#include <ui/menus/menu_action.h>

namespace ui {
    template <class T>
    class MenuNumber: public virtual MenuAction {
    public:

        void setValue(T value) {
            this->value = value;
        }

        T getValue() {
            return value;
        }

    protected:
        T value;
    };
}

#endif //INNO14_D_2017_INNO_MENU_NUMBER_H
