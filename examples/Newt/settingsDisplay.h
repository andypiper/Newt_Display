void renderSettingsDisplay(int msg = 0)
{

  currentDisplay = SETTINGS;

  display.fillScreen(BGCOLOR);
  display.setTextColor(TEXTCOLOR);

  if (msg == 1)
  {

    display.setFont(&FreeSansBold12pt7b);
    display.getTextBounds("Clearing Habit Calendar....DONE", 0, 0, &xP, &yP, &w, &h);
    display.setCursor(displayWidth / 2 - w / 2, displayHeight / 2 - h / 2);
    display.print("Clearing Habit Calendar....");
    display.refresh();
    clearChecks();
    delay(2000);
    display.print("DONE");
    display.refresh();
    delay(3000);
  }

  if (msg == 2)
  {

    display.setFont(&FreeSansBold12pt7b);
    display.getTextBounds("Clearing WIFI SETTINGS....DONE", 0, 0, &xP, &yP, &w, &h);
    display.setCursor(displayWidth / 2 - w / 2, displayHeight / 2 - h / 2);
    display.print("Clearing WIFI SETTINGS....");
    display.refresh();

    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    wm.resetSettings();

    delay(2000);
    display.print("DONE");
    display.refresh();
    delay(3000);
    display.fillScreen(BGCOLOR);
    display.setTextColor(TEXTCOLOR);
    display.getTextBounds("RESTARTING DEVICE", 0, 0, &xP, &yP, &w, &h);
    display.setCursor(displayWidth / 2 - w / 2, displayHeight / 2 - h / 2);
    display.print("RESTARTING DEVICE");
    display.refresh();
    delay(2000);
    ESP.restart();
  }

  display.fillScreen(BGCOLOR);
  display.setTextColor(TEXTCOLOR);
  int startX = displayMarginW / 2;
  int startY = displayMarginH * 2 + 10;

  display.setCursor(startX, startY);
  display.setFont(&FreeSansBold12pt7b);
  display.print("DEVICE DETAILS");

  int spacer = 20;
  int majorSpacer = 30;
  int tab = 180;

  startY += majorSpacer;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Device ID");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(uniqId);

  startY = startY + spacer;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Current Version");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(SWVERSION_MAJOR);
  display.print(".");
  display.print(SWVERSION_MINOR);
  display.print(".");
  display.print(SWVERSION_PATCH);

  startY = startY + spacer;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Latest Version");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(latest_ver_major);
  display.print(".");
  display.print(latest_ver_minor);
  display.print(".");
  display.print(latest_ver_patch);

  startY = startY + spacer;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Location (Major)");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(city);

  startY = startY + spacer;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Location (Minor)");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(locale);

  startY = startY + spacer;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Units");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(units);

  startY = startY + 20;

  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(startX, startY);
  display.print("Timezone");
  display.print(": ");
  display.setCursor(startX + tab, startY);
  display.setFont(&FreeSans9pt7b);
  display.print(timezone);

  startY = startY + 20;

  int minorSpacer = 4;
  display.setTextSize(1);
  display.setFont(&FreeSansBold9pt7b);

  display.getTextBounds("CLEAR", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_C_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y - h - minorSpacer);
  display.print("CLEAR");

  display.getTextBounds("HABITS", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_C_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
  display.print("HABITS");

  display.getTextBounds("RESET", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_D_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y - h - minorSpacer);
  display.print("RESET");

  display.getTextBounds("WIFI", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_D_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
  display.print("WIFI");

  if (versionUpdateAvailable)
  {
    display.getTextBounds("UPGRADE", 0, 0, &xP, &yP, &w, &h);
    display.setCursor(BUTTON_E_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
    display.print("UPGRADE");
  }

  display.getTextBounds("EXIT", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_F_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
  display.print("EXIT");

  display.refresh();
}

void handleSettingsDetails(int button)
{

  switch (button)
  {
  case BUTTON_C:
    renderSettingsDisplay(1);
    break;
  case BUTTON_D:
    renderSettingsDisplay(2);
    break;
  case BUTTON_E:
    if (versionUpdateAvailable)
    {
      updateVersion();
    }
    break;
  case BUTTON_F:
    exitScreensRoutine();
    break;
  }
  return;
}
