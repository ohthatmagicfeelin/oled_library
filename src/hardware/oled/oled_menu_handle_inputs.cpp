#include "oled_menu.h"

void OLEDMenu::handleButtonUp(bool changed) {
    if (digitalRead(BUTTON_UP) == LOW) {
        if (currentSelection > 0) {
            currentSelection--;
            changed = true;
        }
        delay(200);
    }
}

void OLEDMenu::handleButtonDown(bool changed) {
    if (digitalRead(BUTTON_DOWN) == LOW) {
        if (currentSelection < currentMenuSize - 1) {
            currentSelection++;
            changed = true;
        }
        delay(200);
    }
}

void OLEDMenu::handleButtonSelect(bool changed) {
    if (digitalRead(BUTTON_SELECT) == LOW) {
        MenuItem selectedItem = currentMenu[currentSelection];
        if (selectedItem.subMenu != nullptr) {
            menuHistory[menuHistorySize] = {currentMenu, currentSelection, currentMenuSize};
            menuHistorySize++;
            currentMenu = selectedItem.subMenu;
            currentMenuSize = selectedItem.subMenuSize;
            currentSelection = 0;
            changed = true;
        } else if (selectedItem.function != nullptr) {
            (this->*selectedItem.function)();  
        } else {
            // Handle leaf menu item selection
            Serial.print("Selected: ");
            Serial.println(selectedItem.name);
        }
        delay(200);
    }
}

void OLEDMenu::handleButtonBack(bool changed) {
    if (digitalRead(BUTTON_BACK) == LOW) {
        if (menuHistorySize > 0) {
            menuHistorySize--;
            MenuState previousMenu = menuHistory[menuHistorySize];
            currentMenu = previousMenu.menu;
            currentSelection = previousMenu.selection;
            currentMenuSize = previousMenu.size;
            changed = true;
        }
        delay(200);
    }
}

void OLEDMenu::handleInput() {
    bool changed = false;

    handleButtonUp(changed);
    handleButtonDown(changed);
    handleButtonSelect(changed);
    handleButtonBack(changed);
    
    if (changed) {
        updateDisplay();
    }
}
