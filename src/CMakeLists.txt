SET(SOURCES screens/ui_Speed.c
    ui_theme_manager.c
    ui_themes.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    fonts/ui_font_FontAwesomeSolid.c
    fonts/ui_font_MontserratSemiBoldLarge.c)

add_library(ui ${SOURCES})
