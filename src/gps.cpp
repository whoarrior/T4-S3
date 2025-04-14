#include <LilyGo_AMOLED.h>
#include <ui.h>
#include <TinyGPSPlus.h>

#define GPS_TX_PIN (43)
#define GPS_RX_PIN (44)
// #define GPS_BAUD 38400
#define GPS_BAUD 9600
#define SerialGPS Serial1

const char nosat[14] = "no satellites";
const char three[4] = "...";
const char two[3] = "..";
const char one[2] = ".";
const char zero[1] = "";

int try2connect = 0;

// The TinyGPSPlus object
TinyGPSPlus gps;

void gps_init()
{
    SerialGPS.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
}

void light()
{
    ui_object_set_themeable_style_property(ui_Speed_DirectionText, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, _ui_theme_color_DigitalBg);
    ui_object_set_themeable_style_property(ui_Speed_DirectionText, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA, _ui_theme_alpha_DigitalBg);
}

void dark()
{
    ui_object_set_themeable_style_property(ui_Speed_DirectionText, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR, _ui_theme_color_Grey);
    ui_object_set_themeable_style_property(ui_Speed_DirectionText, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA, _ui_theme_alpha_Grey);
}

void display(lv_timer_t *timer)
{
    uint32_t satellites = gps.satellites.isValid() ? gps.satellites.value() : 0;
    // double hdop = gps.hdop.isValid() ? gps.hdop.hdop() : 0;
    // double lat = gps.location.isValid() ? gps.location.lat() : 0;
    // double lng = gps.location.isValid() ? gps.location.lng() : 0;
    // uint32_t age = gps.location.isValid() ? gps.location.age() : 0;
    // uint16_t year = gps.date.isValid() ? gps.date.year() : 0;
    // uint8_t month = gps.date.isValid() ? gps.date.month() : 0;
    // uint8_t day = gps.date.isValid() ? gps.date.day() : 0;
    // uint8_t hour = gps.time.isValid() ? gps.time.hour() : 0;
    // uint8_t minute = gps.time.isValid() ? gps.time.minute() : 0;
    // uint8_t second = gps.time.isValid() ? gps.time.second() : 0;
    // double meters = gps.altitude.isValid() ? gps.altitude.meters() : 0;

    if (!gps.satellites.isValid())
    {
        switch (try2connect)
        {
        case 2:
            lv_label_set_text(ui_Speed_SatelliteConnections, three);
            dark();
            try2connect++;
            break;
        case 1:
            lv_label_set_text(ui_Speed_SatelliteConnections, two);
            light();
            try2connect++;
            break;
        case 0:
            lv_label_set_text(ui_Speed_SatelliteConnections, one);
            dark();
            try2connect++;
            break;
        default:
            lv_label_set_text(ui_Speed_SatelliteConnections, zero);
            lv_label_set_text(ui_Speed_DirectionText, nosat);
            light();
            try2connect = 0;
            break;
        }
    }
    else
    {
        lv_label_set_text_fmt(ui_Speed_SatelliteConnections, "%d", satellites);
        dark();
        try2connect = 0;
    }
}
