// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include "hardware/io/io.h"

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET    -1
// #define SCREEN_ADDRESS 0x3C
// const int I2C_SDA = 18;
// const int I2C_SCL = 19;

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// const int BUTTON_UP = 12;
// const int BUTTON_DOWN = 13;
// const int BUTTON_SELECT = 14;
// const int BUTTON_BACK = 27;

// const int ITEMS_PER_SCREEN = 4;
// const int ITEM_HEIGHT = 16;

// bool needsUpdate = true;

// struct MenuItem {
//     const char* name;
//     MenuItem* subMenu;
//     int subMenuSize;
// };

// MenuItem musicSubMenu[] = {
//     {"Playlists", nullptr, 0},
//     {"Artists", nullptr, 0},
//     {"Albums", nullptr, 0},
//     {"Songs", nullptr, 0},
//     {"Genres", nullptr, 0}
// };

// MenuItem settingsSubMenu[] = {
//     {"Sound", nullptr, 0},
//     {"Display", nullptr, 0},
//     {"Date & Time", nullptr, 0},
//     {"Language", nullptr, 0},
//     {"Reset", nullptr, 0}
// };

// MenuItem mainMenu[] = {
//     {"Now Playing", nullptr, 0},
//     {"Music", musicSubMenu, 5},
//     {"Podcasts", nullptr, 0},
//     {"Photos", nullptr, 0},
//     {"Videos", nullptr, 0},
//     {"Extras", nullptr, 0},
//     {"Settings", settingsSubMenu, 5},
//     {"Shuffle Songs", nullptr, 0},
//     {"Backlight", nullptr, 0},
//     {"About", nullptr, 0}
// };

// int currentSelection = 0;
// MenuItem* currentMenu = mainMenu;
// int currentMenuSize = 10;

// struct MenuState {
//     MenuItem* menu;
//     int selection;
//     int size;
// };

// MenuState menuHistory[5];
// int menuHistorySize = 0;




// void updateDisplay() {
//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(SSD1306_WHITE);

//     // Calculate the maximum number of items that can fit on the screen
//     int maxItems = 4; // Assuming 4 items can fit comfortably
//     int startIndex = max(0, min(currentSelection - 1, currentMenuSize - maxItems));

//     // Calculate vertical spacing
//     int totalHeight = maxItems * 16; // 16 pixels per item (including spacing)
//     int topMargin = (display.height() - totalHeight) / 2; // Center vertically on screen

//     for (int i = 0; i < maxItems && (startIndex + i) < currentMenuSize; i++) {
//         int y = topMargin + i * 16; // 16 pixels per line for better spacing
        
//         if (startIndex + i == currentSelection) {
//             // Draw a filled rectangle for the selected item
//             display.fillRect(0, y, display.width(), 15, SSD1306_WHITE);
//             display.setTextColor(SSD1306_BLACK);
//         } else {
//             display.setTextColor(SSD1306_WHITE);
//         }

//         display.setCursor(4, y + 4); // 4 pixels left margin, 4 pixels for vertical centering within the line
//         display.println(currentMenu[startIndex + i].name);

//         // Reset text color for the next item
//         display.setTextColor(SSD1306_WHITE);
//     }

//     display.display();
// }


// void setup() {
//     Serial.begin(9600);

//       // Set up I2C communication
//       Wire.begin(I2C_SDA, I2C_SCL);

//     if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//         Serial.println(F("SSD1306 allocation failed"));
//         for(;;);
//     }

//     pinMode(BUTTON_UP, INPUT_PULLUP);
//     pinMode(BUTTON_DOWN, INPUT_PULLUP);
//     pinMode(BUTTON_SELECT, INPUT_PULLUP);
//     pinMode(BUTTON_BACK, INPUT_PULLUP);

//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(SSD1306_WHITE);
//     updateDisplay();
// }


// void loop() {
//     bool changed = false;

//     if (digitalRead(BUTTON_UP) == LOW) {
//         if (currentSelection > 0) {
//             currentSelection--;
//             changed = true;
//         }
//         delay(200);
//     }

//     if (digitalRead(BUTTON_DOWN) == LOW) {
//         if (currentSelection < currentMenuSize - 1) {
//             currentSelection++;
//             changed = true;
//         }
//         delay(200);
//     }

//     if (digitalRead(BUTTON_SELECT) == LOW) {
//         MenuItem selectedItem = currentMenu[currentSelection];
//         if (selectedItem.subMenu != nullptr) {
//             menuHistory[menuHistorySize] = {currentMenu, currentSelection, currentMenuSize};
//             menuHistorySize++;
//             currentMenu = selectedItem.subMenu;
//             currentMenuSize = selectedItem.subMenuSize;
//             currentSelection = 0;
//             changed = true;
//         } else {
//             // Handle leaf menu item selection
//             Serial.print("Selected: ");
//             Serial.println(selectedItem.name);
//         }
//         delay(200);
//     }

//     if (digitalRead(BUTTON_BACK) == LOW) {
//         if (menuHistorySize > 0) {
//             menuHistorySize--;
//             MenuState previousMenu = menuHistory[menuHistorySize];
//             currentMenu = previousMenu.menu;
//             currentSelection = previousMenu.selection;
//             currentMenuSize = previousMenu.size;
//             changed = true;
//         }
//         delay(200);
//     }

//     if (changed) {
//         updateDisplay();
//     }
// }



// // #include <Wire.h>
// // #include <Adafruit_GFX.h>
// // #include <Adafruit_SSD1306.h>

// // #define SCREEN_WIDTH 128
// // #define SCREEN_HEIGHT 64
// // #define OLED_RESET    -1
// // #define SCREEN_ADDRESS 0x3C

// // // Define I2C pins
// // #define I2C_SDA 18
// // #define I2C_SCL 19

// // Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // void setup() {
// //   Serial.begin(115200);
// //   Serial.println("OLED test");

// //   // Initialize I2C
// //   Wire.begin(I2C_SDA, I2C_SCL);

// //   // Initialize OLED display
// //   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
// //     Serial.println(F("SSD1306 allocation failed"));
// //     for(;;); // Don't proceed, loop forever
// //   }

// //   // Clear the buffer
// //   display.clearDisplay();

// //   // Set text size and color
// //   display.setTextSize(2);
// //   display.setTextColor(SSD1306_WHITE);

// //   // Position cursor at top-left corner
// //   display.setCursor(0,0);

// //   // Print "Hello"
// //   display.println(F("Hello"));

// //   // Show the display buffer on the screen
// //   display.display();

// //   Serial.println("Setup complete");
// // }

// // void loop() {
// //   // Nothing to do here
// // }



// main.cpp
#include "hardware/oled/oled.h"

OLEDMenu menu;

void setup() {
    Serial.begin(9600);
    menu.begin();
}

void loop() {
    menu.update();
}
