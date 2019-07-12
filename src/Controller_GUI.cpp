/*++++++++++++++++++++++++++++++++++++++++++| INFOMATION |++++++++++++++++++++++++++++++++++++++++++++
Welcome to the TISSAN_OS. Here, you can configure settings for your VEX V5 Controller and display text on the
controller!
Functions that are very useful:

(Main/Partner)_ControlGUI_print(string text, int row, int col) --> Replacement for Screen.print and Screen.setCursor
(Main/Partner)_ControlGUI_printMSG(string text) --> Prints text on the first line
(Main/Partner)_ControlGUI_clearLine(int row) --> Replacement for Screen.clearLine without clearing the selector
(Main/Partner)_ControlGUI_clearScreen() --> Replacement for Screen.clearScreen without clearing the selector
(Main/Partner)_ControlGUI_selector(int row) --> Shows cursor on passed row
(Main/Partner)_ControlGUI_displayMenu(int currRow, int configuration[]) --> Display the menu options for selected row

------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------
[GLOBAL] Includes > Include needed external libraries and files
------------------------------------------------------------------------------------------------------*/
#include "main.h" //Put in your robot config in order to make the gui to work

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Variables for GUI > Constant vars that won't change during program run
------------------------------------------------------------------------------------------------------*/
//Define buttons
#define btnNONE			0
#define btnUP			1
#define btnDOWN			2
#define btnLEFT			3
#define btnRIGHT		4
#define btnA			5
#define btnB			6
#define btnX			7
#define btnY			8
#define btnR1			9
#define btnR2			10
#define btnL1			11
#define btnL2			12

//Define delays
#define bounceDelay		20 //Time to wait between reads to check for key bounce
#define refreshDelay	200 //Time to wait between refreshing screens

//Define usable screen space
#define screenTextWidth		16 //Max characters you can print on one line
#define screenTextHeight	3 //Max lines of text that can show on the controller

//Array
#define maxMenus		3 //Make this the same # as items in maxMenusIndex
#define maxOptions		3 //Make this the same # as items in 2D of menuDisplayIndex

//Robot status
#define modeDisabled	0
#define modeDriver		1
#define modeAuton		2
#define modeError		3

/*------------------------------------------------------------------------------------------------------
[GLOBAL] Default Strings and Arrays for GUI > GUI needed stuff
------------------------------------------------------------------------------------------------------*/
//This is a string void to tell the user the status of the robot
std::string robotStatus[4] =
{
	"!Robot Disabled!",
	"Driver Control",
	"Auton Control",
	"!!!MODE ERROR!!!"
};

//Array for max options in menu
int maxMenusIndex[maxMenus] =
{
	2,
	2,
	2
};

//Array for selected options
int configuration[maxMenus] =
{
	0,
	0,
	0
};

//Array for displaying the menu types (Proto, Dont use unless testing)
std::string menuTypes[maxMenus] =
{
	"Color: ",
	"Row: ",
	"Mode: "
};

//Array for displaying the menu options (Proto, Dont use unless testing)
std::string menuOptions[maxMenus][maxOptions] =
{
	{ "Blue", "Red", "" },
	{ "Front", "Back", "" },
	{ "RC", "TANK", "" }
};

/*------------------------------------------------------------------------------------------------------
[SYSTEM] rumble > User feedback through controller's rumble motors
------------------------------------------------------------------------------------------------------*/
// This will rumble both partner and main controller
void rumble()
{
	master.rumble("_____");
  partner.rumble("_____");
}

// This will rumble only the main controller
void Main_Control_rumble()
{
  master.rumble("_____");
}

// This will rumble only the partner controller
void Partner_Control_rumble()
{
  partner.rumble(".");
}
