# include "display-helpers.h"


// --- Globals ---
GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(/*CS=*/ DISP_CS_PIN, /*DC=*/ DISP_DC_PIN, /*RST=*/ DISP_RES_PIN, /*BUSY=*/ DISPLAY_BUSY_PIN));


// --- Display Related Functions ---

/// @brief Starts a new page to draw on.
/// @param fast If true, does a partial refresh of the full window insted of a full refresh.
/// @param full If true, a full windows refresh is selected. If false, the refresh style has to be manually set after this.
void displayStartDraw(bool fast, bool full) {
    
    display.firstPage();
    display.setTextColor(GxEPD_BLACK);
    if (!full) return;
    if (fast) {
        display.setPartialWindow(0, 0, display.width(), display.height());
    } else {
        display.setFullWindow();
    }

}

/// @brief Refreshes the display.
void displayEndDraw() {

    display.nextPage();

}

/// @brief Set the cursor, and print text to the display, such that the text is centered at the coordinates.
/// @param text The text to print, or set the cursor for.
/// @param x The X coordinate.
/// @param y The Y coordinate.
/// @param onlyCursor If true, the text will not be rendered, but the cursor will be positioned.
void displayCenterText(char* text, uint16_t x = (display.width() / 2), uint16_t y = (display.height() / 2), bool onlyCursor) {

    // Get bounding box of text.
    int16_t tbx, tby; uint16_t tbw, tbh;
    display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);

    // Move cursor to the correct location.
    display.setCursor(x - (tbw / 2) - tbx, y - (tbh / 2) - tby);
    if (onlyCursor) return; // Skip printing text if only cursor is set.
    display.print(text);

}

/// @brief Renders the visual borders of the screen.
void displayRenderBorders() {

    /*
    display.drawRect(0, 12, display.width(), display.height() - 12, GxEPD_BLACK);
    display.drawRect(1, 13, display.width() - 2, display.height() - 14, GxEPD_BLACK);
    */

}

/// @brief Renders the status bar on the top of the display.
// TODO
void displayRenderStatusBar(char* battery_voltage_buf, char* last_sync_hour_buf, char* last_sync_minute_buf) {

    display.setFont(&FreeMonoBold9pt7b);
    displayCenterText(battery_voltage_buf, 32, 6);

    displayCenterText(last_sync_hour_buf, 260, 6);
    displayCenterText((char*)":", 273, 6);
    displayCenterText(last_sync_minute_buf, 286, 6);

}

/// @brief Renders the time to the center of the display.
// TODO
void displayRenderTime(char* hour_buf, char* minute_buf) {

    display.setFont(&FreeMonoBold48pt7b);
    displayCenterText(hour_buf, 74, 62);
    displayCenterText((char*)":", 148, 62);
    displayCenterText(minute_buf, 222, 62);

}

/// @brief Render the date to the bottom of the display.
// TODO
void displayRenderDate(char* date_buf) {

    display.setFont(&FreeMonoBold12pt7b);
    displayCenterText(date_buf, 148, 114);

}

/// @brief Render the seconds to the display over the large colon.
// TODO
void displayRenderSecond(uint8_t seconds) {

    display.setFont(&FreeMonoBold12pt7b);
    displayCenterText((char*)"00", 148, 28, true);
    display.printf("%02d", seconds);

}

/// @brief Renders text to the status bar area.
/// @param text Text to reder. Recommended to be fully capitalised.
void displayRenderFlag(char* text) {

    display.setFont(&FreeMonoBold9pt7b);
    displayCenterText(text, 148, 6);

}

/// @brief Renders large text to the center of the display.
/// @param text Text to reder. Recommended to be fully capitalised.
void displayRenderClaim(char* text) {

    display.setFont(&FreeMonoBold24pt7b);
    displayCenterText(text);

}


void displayInit(bool wipe) {

    display.init(115200, wipe, 2, false);
    display.setRotation(3); // Landscape with the connector on the left

}

void displayOff() {

    display.powerOff();

}