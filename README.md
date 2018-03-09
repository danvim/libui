# Lib UI

This is my personal GUI toolkit targeted for small LCD screens (that is width or height approximately below 500px) on microcontrollers.  This library is built for the HKUST Robotics Team Smart Car sub team `libsccc`.

libsccc repo: https://github.com/hkust-smartcar/libsccc

The dependency on `libsccc` is the usage of the various peripherals including LCD, 5-way-switches, etc. In the future however, it is planned to make itself independent from `libsccc` and instead provide a set of adapters to bridge `libsccc` and `libui`, to make easily compatible with other microcontrollers other than NXP K60.

`libui` is an OOP-centric library, and it is definitely going to slow down and eat your memory running it. Therefore, you do not want it running in the background when doing you "main" task. The API of the library takes inspiration from jQuery(CSS accessors),  and Android GUI API.

## Using Lib UI in a `libsccc` project

The easiest way is to link the `ui/` directory in `inc/` and `src/` to your own ones inside your project, using soft links (shortcuts on Windows) or symbolic links. The compiler will scan within them and compile them as well. This is the easiest way because there is no need to change the somewhat inconvenient make file. 

## Convention

(Anonymous) extension of classes is a recommended approach to initialize and use the provided features. For example, below lists how to apply a `MenuAction`. Note that if you do not extend the class, the element will not provide any interactivity in this case.

```c++
class: public ui::MenuAction {
public:
    int onEnter() override {
        //Do its thing when the action is selected.
        return SUCCESS;
    }
} my_menu_action;
```

However, when pointers are necessary:

```c++
class MyMenuAction: public ui::MenuAction {
public:
    int onEnter() override {
        //Do its thing when the action is selected.
        return SUCCESS;
    }
};

MyMenuAction* my_menu_action_ptr = new MyMenuAction;
```

Furthermore, if you need to pass variables from a broader scope into the instance, use pointers like so, or use data members in static classes:

```c++
float important_number = 3.14f;

class MyMenuAction: public ui::MenuAction {
public:
    MyMenuAction(float* my_number_ptr): my_number_ptr(my_number_ptr) {}
    int onEnter() override {
        //Do its thing when the action is selected.
        return SUCCESS;
    }
private:
    float* my_number_ptr;
} my_menu_action(&important_number);
```

## Understanding the library structure

### UI-Wise

#### `UIElement`

Most of the UI elements has `UIElement` as one of its base classes. This class is used by UI elements that is affected by layout. This class provides general accessors and mutators.

#### `UIBase`

The rest of the UI elements, if not dependent on `UIElement` will depend directly on `UIBase`. This class provides basic accessors and mutators.

### Text

##### Fonts

The library provides some proportional and monospaced fonts and some incomplete font-families. The fonts have fixed sizes and are raster-based. Sadly, there is no kerning. The current fonts provided:

-   Blocky
    6px tall proportional font
-   Ubuntu
    11px tall monospaced font
-   Ubuntu Italic
    11px tall monospaced font
-   Humanist
    12px tall proportional font
-   Noto
    50px tall proportional font

Fonts are used to be rendered in `ui::text::TextEngine` and are basically useless on their own. By including a font header, the font data members are globally accessible, together with a global `Font`-based instance of that font. You can retrieve a font by the global variables directly, or by its name with the `FontRepo`, e.g.:

```c++
//The font pointer will be added to the font repo once the font is included once.
Font* blocky_ptr = ui::FontRepo::getFontByName("Blocky");
```

##### Font Families

Font families provide an easy way to change the font style when rendering text.

### Theming

