#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLEDMenu {
public:
    OLEDMenu();
    void begin();
    void update();
    

private:
    struct MenuItem {
        const char* name;
        MenuItem* subMenu;
        int subMenuSize;
        void (OLEDMenu::*function)();  // Function pointer
    };

    struct MenuState {
        MenuItem* menu;
        int selection;
        int size;
    };

    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int OLED_RESET = -1;
    static const int SCREEN_ADDRESS = 0x3C;
    static const int I2C_SDA = 18;
    static const int I2C_SCL = 19;

    static const int BUTTON_UP = 12;
    static const int BUTTON_DOWN = 13;
    static const int BUTTON_SELECT = 14;
    static const int BUTTON_BACK = 27;

    Adafruit_SSD1306 display;
    MenuItem* currentMenu;
    int currentSelection;
    int currentMenuSize;
    MenuState menuHistory[5];
    int menuHistorySize;

    // oled_menu_update.cpp
    void updateDisplay();
    void handleInput();
    
    // oled_menu_structure.cpp
    void initializeMenus();
    void nowPlayingFunction();
    void podcastsFunction();

    // oled_menu_handle_input.cpp
    void handleButtonUp(bool changed);
    void handleButtonDown(bool changed);
    void handleButtonSelect(bool changed);
    void handleButtonBack(bool changed);
};
