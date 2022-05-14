boolean isHourlyDisplay = true;
int weatherDisplayPage = 1;

void renderWeatherDisplay() {

  currentDisplay = WEATHER;
  display.fillScreen(BGCOLOR);

  int xStart = 10;
  int yStart = 40;
  int displayValues;  //= 5;
  int xTab;
  int x = xStart;
  int y = yStart;

  display.setTextColor(TEXTCOLOR);
  display.setFont(&FreeSansBold12pt7b);
  display.getTextBounds("FORECAST", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(x, displayMarginH + h);


  if (isHourlyDisplay) {
    display.print("HOURLY FORECAST");
    displayValues = 5;
  }
  else {
    display.print("DAILY FORECAST");
    displayValues = 4;
  }

  xTab = ((displayWidth - xStart * 2) / (displayValues));
  x = xStart;
  yStart += 35;

  File forecastJSON = SPIFFS.open("/forecast.json", FILE_READ);

  if (!forecastJSON) {
    Serial.println("The file does not exist");
    return;
  } else {

    size_t capacity = forecastJSON.size() * 4;
    if ( capacity == 0 ) {
      Serial.println("The file is empty");
      return;
    } else {
      Serial.println("Getting data");
      DynamicJsonDocument doc(capacity);
      DeserializationError err = deserializeJson(doc, forecastJSON);

      forecastJSON.close();
      //serializeJson(doc, Serial);

      if (err) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(err.c_str());
        return;
      }

      JsonArray hourly = doc["hourly"];
      JsonArray daily = doc["daily"];
      int startCounter = 0;

      if (weatherDisplayPage == 2 && isHourlyDisplay) {
        startCounter = 5;
        displayValues = 10;
      }

      for (int i = startCounter; i < displayValues; i++) {

        JsonObject hourlyObj = hourly[i];
        const char* hr = hourlyObj["h"]; // "11"
        const char* am = hourlyObj["am"]; // "PM"
        int temp = hourlyObj["t"]; // 46
        int precip = hourlyObj["p"]; // 0
        const char* icon = hourlyObj["i"]; // "C"

        JsonObject dailyObj = daily[i];
        const char* wd = dailyObj["d"]; // "FRI"
        int tMin = dailyObj["tmin"]; // 40
        int tMax = dailyObj["tmax"]; // 56
        int dPrec = dailyObj["p"]; // 0
        const char* dIcon = dailyObj["i"]; // "c"

        y = yStart;

        if (isHourlyDisplay) {

          //hour --------
          char hramChr[5];
          strcpy(hramChr, hr);
          strcat(hramChr, am);

          display.setFont(&FreeSansBold12pt7b);
          display.getTextBounds(hramChr, 0, 0, &xP, &yP, &w, &h);
          display.setCursor(x + xTab / 2 - w / 2, y);
          display.print(hr);

          display.setFont(&FreeSansBold9pt7b);
          display.print(am);

          y += 30;

          //precipitation chance--------

          if (precip > 0) {

            char precipPercChar[5];
            char precipChar[3];
            itoa(precip, precipChar, 10);
            strcpy(precipPercChar, precipChar);
            strcat(precipPercChar, "%");

            display.setFont(&FreeSans9pt7b);

            display.getTextBounds(precipPercChar, 0, 0, &xP, &yP, &w, &h);
            display.setCursor(x + xTab / 2 - w / 2, y);
            display.print(precipPercChar);

          }

          //icon--------

          display.setFont(&slateWeather30pt7b);
          display.getTextBounds(icon, 0, 0, &xP, &yP, &w, &h);
          int iconCenter = x + (xTab / 2) - (w / 2);

          y += 58 + 10; //58 is the approx height of the icon

          display.setCursor(iconCenter, y);
          display.print(icon);

          //temperature--------
          char tempChar[4];
          itoa(temp, tempChar, 10);

          display.setFont(&FreeSansBold12pt7b);
          display.getTextBounds(tempChar, 0, 0, &xP, &yP, &w, &h);

          y += h + 9;//changed from 5 to 9

          int tempX = x + (xTab / 2) - (w / 2);
          display.setCursor(tempX, y);
          display.print(tempChar);
          display.fillCircle(tempX + w + 6, y - (h * .8), 4, TEXTCOLOR);
          display.fillCircle(tempX + w + 6, y - (h * .8), 1, BGCOLOR);

        } else { // DAILY FORECAST

          display.setFont(&FreeSansBold12pt7b);
          display.getTextBounds(wd, 0, 0, &xP, &yP, &w, &h);
          display.setCursor(x + xTab / 2 - w / 2, y);
          display.print(wd);

          y += 20;

          if (dPrec > 0) {

            char precipPercChar[5];
            char precipChar[3];
            itoa(dPrec, precipChar, 10);
            strcpy(precipPercChar, precipChar);
            strcat(precipPercChar, "%");

            display.setFont(&FreeSans9pt7b);

            display.getTextBounds(precipPercChar, 0, 0, &xP, &yP, &w, &h);
            display.setCursor(x + xTab / 2 - w / 2, y);
            display.print(precipPercChar);

          }

          //icon------

          display.setFont(&slateWeather30pt7b);
          display.getTextBounds(dIcon, 0, 0, &xP, &yP, &w, &h);
          int iconCenter = x + (xTab / 2) - (w / 2);

          y += 58 + 5; //58 is the approx height of the icon

          display.setCursor(iconCenter, y);
          display.print(dIcon);

          //temperature--------
          char tempMaxChar[4];
          itoa(tMax, tempMaxChar, 10);
          char tempMinChar[4];
          itoa(tMin, tempMinChar, 10);

          //Max temp
          display.setFont(&FreeSansBold12pt7b);
          display.getTextBounds(tempMaxChar, 0, 0, &xP, &yP, &w, &h);

          y += h + 5;

          int tempX = x + (xTab / 2) - (w / 2);
          display.setCursor(tempX, y);
          display.print(tempMaxChar);
          display.fillCircle(tempX + w + 6, y - (h * .8), 4, TEXTCOLOR);
          display.fillCircle(tempX + w + 6, y - (h * .8), 1, BGCOLOR);

          //Min temp
          display.setFont(&FreeSans12pt7b);
          display.getTextBounds(tempMinChar, 0, 0, &xP, &yP, &w, &h);

          y += h + 8;

          tempX = x + (xTab / 2) - (w / 2);
          display.setCursor(tempX, y);
          display.print(tempMinChar);
          display.fillCircle(tempX + w + 6, y - (h * .8), 4, TEXTCOLOR);
          display.fillCircle(tempX + w + 6, y - (h * .8), 2, BGCOLOR);

        }

        x += xTab;

      }

      display.setTextColor(TEXTCOLOR);
      display.setFont(&FreeSansBold9pt7b);

      if (isHourlyDisplay) {
        display.getTextBounds("DAILY", 0, 0, &xP, &yP, &w, &h);
        display.setCursor(BUTTON_C_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
        display.print("DAILY");
      } else {
        display.getTextBounds("HOURLY", 0, 0, &xP, &yP, &w, &h);
        display.setCursor(BUTTON_C_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
        display.print("HOURLY");
      }

      if (isHourlyDisplay) {
        if (weatherDisplayPage == 1) {
          display.getTextBounds("NEXT", 0, 0, &xP, &yP, &w, &h);
          display.setCursor(BUTTON_D_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
          display.print("NEXT");
        } else {
          display.getTextBounds("PREVIOUS", 0, 0, &xP, &yP, &w, &h);
          display.setCursor(BUTTON_D_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
          display.print("PREVIOUS");
        }
      }

      display.getTextBounds("EXIT", 0, 0, &xP, &yP, &w, &h);
      display.setCursor(BUTTON_F_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
      display.print("EXIT");

      display.refresh();
    }
  }


}

void toggleWeatherDisplay(int button) {

  switch (button)
  {
    case BUTTON_C :
      isHourlyDisplay = !isHourlyDisplay;
      weatherDisplayPage = 1;
      renderWeatherDisplay();
      break;
    case BUTTON_D :
      if (isHourlyDisplay) {
        weatherDisplayPage++;
        if (weatherDisplayPage == 3) {
          weatherDisplayPage = 1;
        }
        renderWeatherDisplay();
      }
      break;
    case BUTTON_E :
      break;
    case BUTTON_F :
      exitScreensRoutine();
      break;
  }
  return;
}

boolean showReadings = true;
void renderAQDisplay() {

  currentDisplay = AIRQUALITY;
  display.fillScreen(BGCOLOR);

  int xStart = 10;
  int yStart = 40;
  int displayValues;  //= 5;
  int xTab;
  int x = xStart;
  int y = yStart;

  display.setTextColor(TEXTCOLOR);
  display.setFont(&FreeSansBold12pt7b);
  display.getTextBounds("AIR QUALITY", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(x, displayMarginH + h);
  display.print("AIR QUALITY");

  File aqJSON = SPIFFS.open("/airquality.json", FILE_READ);

  if (!aqJSON) {
    Serial.println("The file does not exist");
    // return;
  } else {

    StaticJsonDocument<1200> doc;
    DeserializationError err = deserializeJson(doc, aqJSON);

    if (err) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(err.c_str());
    } else {
      Serial.println("Getting data");
      aqJSON.close();

      if (showReadings) {
        //Display currrent

        int current_aqi = doc["current"]["aqi"];
        const char* current_icon = doc["current"]["icon"];
        const char* current_desc = doc["current"]["desc"];

        x = 45;

        display.setFont(&slateIcons30pt7b);
        display.getTextBounds(current_icon, 0, 0, &xP, &yP, &w, &h);
        int iconX = x + (xTab / 2) - (w / 2);

        y += h + 5;
        int textX = iconX + w;

        display.setCursor(iconX, y);
        display.print(current_icon);

        int textY = y - h;

        //Currently
        display.setFont(&FreeSansBold9pt7b);
        display.getTextBounds("NOW", 0, 0, &xP, &yP, &w, &h);

        textX += 10;
        textY += h;
        display.setCursor(textX, textY);
        display.print("NOW");

        textY += h + 10;

        //Current AQI--------
        char currAQI[4];
        itoa(current_aqi, currAQI, 10);
        display.setFont(&FreeSansBold9pt7b);
        display.getTextBounds(currAQI, 0, 0, &xP, &yP, &w, &h);

        display.setCursor(textX, textY);
        display.print("AQI: ");
        display.print(currAQI);

        textY += h + 10;


        //Current STATUS--------
        display.setCursor(textX, textY);
        display.print("STATUS: ");
        display.print(current_desc);


        //Display Forecast
        int displayValues = 5;
        xTab = ((displayWidth - xStart * 2) / (displayValues));
        x = xStart;

        yStart += 110;

        for (JsonObject forecast_item : doc["forecast"].as<JsonArray>()) {

          y = yStart;

          int forecast_item_avg = forecast_item["avg"]; // 75, 51, 50, 52, 33
          int forecast_item_max = forecast_item["max"]; // 104, 59, 55, 64, 40
          int forecast_item_min = forecast_item["min"]; // 35, 35, 34, 36, 25
          const char* forecast_item_icon = forecast_item["icon"]; // "y", "y", "g", "y", "g"
          const char* forecast_item_d = forecast_item["d"]; // "FRI", "SAT", "SUN", "MON", "TUE"

          display.setFont(&FreeSansBold9pt7b);
          display.getTextBounds(forecast_item_d, 0, 0, &xP, &yP, &w, &h);
          display.setCursor(x + xTab / 2 - w / 2, y);
          display.print(forecast_item_d);

          display.setFont(&slateIcons14pt7b);
          display.getTextBounds(forecast_item_icon, 0, 0, &xP, &yP, &w, &h);
          int iconCenter = x + (xTab / 2) - (w / 2);

          y += h + 5;

          display.setCursor(iconCenter, y);
          display.print(forecast_item_icon);

          //Avg AQI--------
          char avgAQI[4];
          itoa(forecast_item_avg, avgAQI, 10);
          display.setFont(&FreeSans9pt7b);
          display.getTextBounds(avgAQI, 0, 0, &xP, &yP, &w, &h);

          y += h + 10;

          int valueX = x + (xTab / 2) - (w / 2);
          display.setCursor(valueX, y);
          display.print(avgAQI);

          x += xTab;

        }
      } else {
        
        int y = 60;

        display.setFont(&FreeSansBold9pt7b);


        display.setCursor(x, y);
        display.print("Attribution");

        display.setFont(&FreeSans9pt7b);
        JsonArray attributions = doc["attributions"];
        for (JsonVariant credit : attributions) {
          y += 20;
          display.setCursor(x, y);
          display.print(credit.as<const char*>());
        }
      }
    }
  }

  display.setTextColor(TEXTCOLOR);
  display.setFont(&FreeSansBold9pt7b);

  display.getTextBounds("INFO", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_E_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);

  if (showReadings){
    display.print("INFO");
  }else{
    display.print("BACK");
  }

  display.getTextBounds("EXIT", 0, 0, &xP, &yP, &w, &h);
  display.setCursor(BUTTON_F_PIN_X - (w / 2), BUTTON_CDEF_PIN_Y);
  display.print("EXIT");

  display.refresh();


}

void handleAQDisplay(int button) {

  switch (button)
  {
    case BUTTON_C :
      break;
    case BUTTON_D :
      break;
    case BUTTON_E :
      showReadings = !showReadings;
      renderAQDisplay();
      break;
    case BUTTON_F :
      showReadings = true;
      exitScreensRoutine();
      break;
  }
  return;
}
