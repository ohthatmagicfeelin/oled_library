#include "oled_menu.h"

void OLEDMenu::nowPlayingFunction() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Now Playing");
    display.println("Song: My Favorite Song");
    display.println("Artist: Popular Artist");
    display.display();

    while (digitalRead(BUTTON_BACK) == HIGH) {
        // Wait for back button press
        delay(50);
    }
    updateDisplay(); // Return to menu
}

void OLEDMenu::podcastsFunction() {
    Serial.println("Podcasts");
    // do some stuff here
}

void OLEDMenu::initializeMenus() {
    static MenuItem musicSubMenu[] = {
        {"Playlists", nullptr, 0, nullptr},
        {"Artists", nullptr, 0, nullptr},
        {"Albums", nullptr, 0, nullptr},
        {"Songs", nullptr, 0, nullptr},
        {"Genres", nullptr, 0, nullptr}
    };

    static MenuItem settingsSubMenu[] = {
        {"Sound", nullptr, 0, nullptr},
        {"Display", nullptr, 0, nullptr},
        {"Date & Time", nullptr, 0, nullptr},
        {"Language", nullptr, 0, nullptr},
        {"Reset", nullptr, 0, nullptr}
    };

    static MenuItem mainMenu[] = {
        {"Now Playing", nullptr, 0, &OLEDMenu::nowPlayingFunction},
        {"Music", musicSubMenu, 5, nullptr},
        {"Podcasts", nullptr, 0, &OLEDMenu::podcastsFunction},
        {"Photos", nullptr, 0, nullptr},
        {"Videos", nullptr, 0, nullptr},
        {"Extras", nullptr, 0, nullptr},
        {"Settings", settingsSubMenu, 5, nullptr},
        {"Shuffle Songs", nullptr, 0, nullptr},
        {"Backlight", nullptr, 0, nullptr},
        {"About", nullptr, 0, nullptr}
    };

    currentMenu = mainMenu;
    currentMenuSize = 10;
}
