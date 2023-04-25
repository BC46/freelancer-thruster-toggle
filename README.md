# Freelancer Thruster Toggle
Plugin for the game Freelancer (2003) that allows players to toggle the Thruster activation using a single key.
Please note that this functionality isn't useful for most players as this plugin is just a proof of concept.
Also, the approach that has been taken to modify the `ids_name` value and key states in-memory is far from the greatest and is only included to demonstrate the possibility.

## Installation instructions
Download the latest `thruster_toggle.dll` from [Releases](https://github.com/BC46/freelancer-thruster-toggle/releases) and move it to the `EXE` folder of your Freelancer installation.
Next, open the `dacom.ini` file and append the `thruster_toggle.dll` entry to the `[Libraries]` section.

## Usage instructions
In-game the "ACTIVATE AFTERBURNER" control (TAB key) now functions as a toggle on/off key.
When flying in space, pressing TAB activates the Thruster continuously until the key is pressed a second time.

In the `thruster_toggle.ini` config file, some additional settings are available to edit the control strings from the options menu.

## Build instructions
Build the project using the `NMAKE` tool from Microsoft Visual C++ 6.0 (VC6 or Visual Studio 98) with the included makefile.
This will output the `thruster_toggle.dll` file in the `bin` folder.
Building the project using other compilers may require the code to be modified.

If you're wondering what my experience with VC6 has been like, the following compiler output pretty much summarizes it:
```
src\utils.cpp(3) : fatal error C1001: INTERNAL COMPILER ERROR
        (compiler file 'msc1.cpp', line 1786)
         Please choose the Technical Support command on the Visual C++
         Help menu, or open the Technical Support help file for more information
```
