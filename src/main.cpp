#include <lvgl.h>
#include <LV_Helper.h>
#include <LilyGo_AMOLED.h>
#include <ui.h>
#include <gps.h>

// Define display and touch hardware specifics
LilyGo_Class amoled;

void setup(void)
{
    Serial.begin(115200);

    // Initialize AMOLED Display
    if (!amoled.begin())
    {
        Serial.println("AMOLED init failed");
        while (1)
            delay(1000);
    }

    // Set the orientation of the AMOLED display
    //   0: Landscape mode. USB port on the left bottom.
    //   1:
    //   2:
    //   3: Portrait mode. USB port on the right bottom.
    Serial.println("Set the orientation of the AMOLED display to landscape mode.");
    amoled.setRotation(0);

    // Initialize LVGL
    beginLvglHelper(amoled);

    // Initialize UI from LVGL helper
    ui_init();

    // Initialize GPS
    gps_init();

    // Set up a 1sec timer
    lv_timer_create(display, 1000, NULL);
}

void loop()
{
    // Handle LVGL tasks
    lv_task_handler();
    delay(5);
}
