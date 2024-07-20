#include "oled_menu.h"

OLEDMenu::OLEDMenu() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
    currentSelection = 0;
    menuHistorySize = 0;
}

void OLEDMenu::begin() {
    Wire.begin(I2C_SDA, I2C_SCL);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_SELECT, INPUT_PULLUP);
    pinMode(BUTTON_BACK, INPUT_PULLUP);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    initializeMenus();
    updateDisplay();
}

void OLEDMenu::update() {
    handleInput();
}

void OLEDMenu::updateDisplay() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Calculate the maximum number of items that can fit on the screen
    int maxItems = 4; // Assuming 4 items can fit comfortably
    int startIndex = max(0, min(currentSelection - 1, currentMenuSize - maxItems));

    // Calculate vertical spacing
    int totalHeight = maxItems * 16; // 16 pixels per item (including spacing)
    int topMargin = (display.height() - totalHeight) / 2; // Center vertically on screen

    for (int i = 0; i < maxItems && (startIndex + i) < currentMenuSize; i++) {
        int y = topMargin + i * 16; // 16 pixels per line for better spacing
        
        if (startIndex + i == currentSelection) {
            // Draw a filled rectangle for the selected item
            display.fillRect(0, y, display.width(), 15, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }

        display.setCursor(4, y + 4); // 4 pixels left margin, 4 pixels for vertical centering within the line
        display.println(currentMenu[startIndex + i].name);

        // Reset text color for the next item
        display.setTextColor(SSD1306_WHITE);
    }

    display.display();
}
