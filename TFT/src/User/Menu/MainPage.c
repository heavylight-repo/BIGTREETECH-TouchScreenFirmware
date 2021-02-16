#include "MainPage.h"
#include "includes.h"

void menuMain(void)
{
  // 1 title, ITEM_PER_PAGE items(icon+label)
  MENUITEMS mainPageItems = {
    // title
    LABEL_MAINMENU,
    // icon                         label
    {{ICON_HOME,                    LABEL_HOME},   //Tobbe
     {ICON_HOME_MOVE,               LABEL_UNIFIEDMOVE},   //Tobbe
     {ICON_CONNECTION_SETTINGS,     LABEL_CONNECTION_SETTINGS}, //Tobbe
    //#ifdef LOAD_UNLOAD_M701_M702                              //Tobbe
    //  {ICON_EXTRUDE,                 LABEL_LOAD_UNLOAD_SHORT},//Tobbe
    //#else                                                     //Tobbe
    //  {ICON_EXTRUDE,                 LABEL_EXTRUDE},          //Tobbe
    //#endif
     {ICON_STOP,                    LABEL_EMERGENCYSTOP},
     {ICON_SCREEN_SETTINGS,         LABEL_SCREEN_SETTINGS},
     {ICON_RGB_SETTINGS,            LABEL_RGB_SETTINGS},
     {ICON_SCREEN_INFO,             LABEL_SCREEN_INFO},
     {ICON_BACK,                    LABEL_BACK},}
  };

  KEY_VALUES key_num = KEY_IDLE;

  if (infoSettings.status_screen != 1)
  {
    mainPageItems.items[7].icon = ICON_PRINT;
    mainPageItems.items[7].label.index = LABEL_PRINT;
  }

  menuDrawPage(&mainPageItems);

  while (infoMenu.menu[infoMenu.cur] == menuMain)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        //infoMenu.menu[++infoMenu.cur] = menuUnifiedHeat; //Tobbe
        infoMenu.menu[++infoMenu.cur] = menuHome; //Tobbe
        break;

      case KEY_ICON_1:
        infoMenu.menu[++infoMenu.cur] = menuUnifiedMove; //Tobbe
        break;

      case KEY_ICON_2:
        #ifdef LOAD_UNLOAD_M701_M702
          infoMenu.menu[++infoMenu.cur] = menuConnectionSettings; //Tobbe
        #else
          infoMenu.menu[++infoMenu.cur] = menuExtrude; //Tobbe
        #endif
        break;

      case KEY_ICON_3:
        // Emergency Stop : Used for emergency stopping, a reset is required to return to operational mode.
        // it may need to wait for a space to open up in the command queue.
        // Enable EMERGENCY_PARSER in Marlin Firmware for an instantaneous M112 command.
        Serial_Puts(SERIAL_PORT, "M112\n");
        break;

      case KEY_ICON_4:
        infoMenu.menu[++infoMenu.cur] = menuScreenSettings;
        break;

      case KEY_ICON_5:
        infoMenu.menu[++infoMenu.cur] = menuRGBSettings;
        break;

      case KEY_ICON_6:
        infoMenu.menu[++infoMenu.cur] = menuInfo;
        break;

      case KEY_ICON_7:
        if (infoSettings.status_screen != 1)
          infoMenu.menu[++infoMenu.cur] = menuPrint;
        else
          infoMenu.cur--;
        break;

      default:
        break;
    }

    loopProcess();
  }
}

