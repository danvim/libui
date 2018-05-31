# ![LibUI](libui_logo_trim.png)

This is my personal GUI toolkit targeted for small LCD screens on micro-controllers.  This library is built originally for the HKUST Robotics Team Smart Car sub team `libsccc`.

libsccc repo: https://github.com/hkust-smartcar/libsccc

`libui` is an OOP-centric library, and it is definitely going to slow down and eat your memory running it. Therefore, you do not want it running in the background when doing you "main" task. The API of the library takes inspiration from jQuery(CSS accessors),  and Android GUI API.

## Using Lib UI in a `libsccc` project

The easiest way is to link the `ui/` directory in `inc/` and `src/` to your own ones inside your project, using soft links (shortcuts on Windows) or symbolic links. The compiler will scan within them and compile them as well. This is the easiest way because there is no need to change the somewhat inconvenient make file.  The other way is to use the statically linked `libui.a` library.

## Adapters

`libui` does not depend on any libraries. The way to connect peripheral classes such as an LCD screen to `libui` is by using deriving the provided adapter interfaces: `ui::adapters::*` to enable API calls to access various peripherals, and the context adapter interface: `ui::adapters::ContextAdapterInterface`  to store static pointers to peripheral interfaces. The context adapter created from the interface is then attached to `ui::Context` via `ui::Context::attachContextAdapter(context_adapter_ptr)`.  The effect is that the entire library will now be able to draw images to the screen with no knowledge of the implementation of lower level logics.

The user of `libui` is so effectively required to manage the resources in the derived adapter interfaces by themselves and are required to complete the logic within the implemented`ContextAdapterInterface` to be able to run the library.

## Convention

(Anonymous) derivation of classes is a recommended approach to initialize and use the provided features. For example, below lists how to apply a `MenuAction`. Note that if you do not extend the class, the element will not provide any interactivity in this case.

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

Fonts are to be rendered in `ui::text::TextEngine` and are basically useless on their own. By including a font` .h` header file, the font data members are globally accessible, together with a global `Font`-based instance of that font. You can retrieve a font by the global variables directly, or by its name with the `FontRepo`, e.g.:

```c++
//The font pointer will be added to the font repo once the font is included once.
Font* blocky_ptr = ui::FontRepo::getFontByName("Blocky");
```

##### Font Families

Font families provides an easy way to change the font style when rendering text.

## Theme

Colors used by the library to paint on the screen is stored in an instance of the class `ui::ColorScheme`. By changing the public static data member of the Context: `ui::Context::color_scheme`, one can change the colors used to draw the UI in a somewhat constricted way.