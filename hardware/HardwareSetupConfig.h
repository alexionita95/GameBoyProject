// This header file contains a list of user setup files and defines which one the
// compiler uses when the IDE performs a Verify/Compile or Upload.
//
// Users can create configurations for different Espressif boards and TFT displays.
// This makes selecting between hardware setups easy by "uncommenting" one line.

// The advantage of this hardware configuration method is that the examples provided
// with the library should work with different setups immediately without any other
// changes being needed. It also improves the portability of users sketches to other
// hardware configurations and compatible libraries.
//
// Create a shortcut to this file on your desktop to permit quick access for editing.
// Re-compile and upload after making and saving any changes to this file.

// Customised User_Setup files are stored in the "User_Setups" folder.

#ifndef HW_SETUP_LOADED //  Lets PlatformIO users define settings in
                          //  platformio.ini, see notes in "Tools" folder.

// Only ONE line below should be uncommented.  Add extra lines and files as needed.
#include <hardware/HardwarePins.h>
#include <hardware/HardwareSetup.h>           // Default setup is root library folder



#endif // USER_SETUP_LOADED



/////////////////////////////////////////////////////////////////////////////////////
//                                                                                 //
//     DON'T TINKER WITH ANY OF THE FOLLOWING LINES, THESE ADD THE TFT DRIVERS     //
//       AND ESP8266 PIN DEFINITONS THEY ARE HERE FOR BODMER'S CONVENIENCE!        //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////


// Identical looking TFT displays may have a different colour ordering in the 16 bit colour
#define TFT_BGR 0   // Colour order Blue-Green-Red
#define TFT_RGB 1   // Colour order Red-Green-Blue


// Load the right driver definition - do not tinker here !
#if   defined (ILI9341_DRIVER)
     #include <hardware/ILI9341_Defines.h>
     #define  TFT_DRIVER 0x9341
#endif



