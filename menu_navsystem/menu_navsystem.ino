#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* menuItems[] = {
  "MP3 Player",
  "Voltage Tester",
  "Stopwatch",
  "Directory",
  "Wifi Tester",
  "Osint",
  "Navigation"
};
const int TOTAL_ITEMS = sizeof(menuItems) / sizeof(menuItems[0]);
const int upPin = 5;
const int downPin = 6;
const int selectPin = 7;

int selectedIndex = 0;
int scrollOffset = 0;

void drawMenu()
{
  display.clearDisplay();
  for (int i = 0; i < 3; i++)
  {
    display.setCursor(10, i * 15);
    int actualIndex = i + scrollOffset;
    if (actualIndex == selectedIndex)
    {
      display.print("> ");
      display.print(menuItems[actualIndex]);
    }
    else
    {
      display.print(" ");
      display.print(menuItems[actualIndex]);
    }
  }
  display.display();
}

void 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
