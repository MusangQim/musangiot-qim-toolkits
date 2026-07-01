#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Org_01.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
const int upPin = 3;
const int downPin = 2;
const int selectPin = 1;
int selectedIndex = 0;
int scrollOffset = 0;
unsigned long lastTouchTime = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(selectPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setFont(&Org_01);
  display.display();
}

void loop() 
{
  handleTouch();
  drawMenu();
}

void drawMenu()
{
  display.clearDisplay();
  for (int i = 0; i < 3; i++)
  {
    display.setCursor(10, 14 + (i * 15));
    int actualIndex = i + scrollOffset;
    if (actualIndex >= TOTAL_ITEMS)
      break;
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

void handleTouch()
{
  int upState = digitalRead(upPin);
  int downState = digitalRead(downPin);
  int selectState = digitalRead(selectPin);
  unsigned long now = millis();
  if (now - lastTouchTime < 200)
    return;
  if (upState == HIGH && selectedIndex > 0)
  {
    selectedIndex--;
    if (selectedIndex < scrollOffset)
      scrollOffset--;
    lastTouchTime = now;
  }
  if (downState == HIGH && selectedIndex < TOTAL_ITEMS - 1)
  {
    selectedIndex++;
    if (selectedIndex > scrollOffset + 2)
      scrollOffset++;
    lastTouchTime = now;
  }
  if (selectState == HIGH)
  {
    Serial.println(menuItems[selectedIndex]);
    lastTouchTime = now;
  }
}
