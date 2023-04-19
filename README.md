# Freelancer Thruster Toggle
Plugin for the game Freelancer (2003) that allows players to toggle the Thruster activation using a single key.
Please note that this functionality isn't useful for most players as this plugin is just a proof of concept.
Also, the approach that has been taken to modify the `ids_name` value and key states in-memory is far from the greatest and is only included to demonstrate the possibility.

## Installation instructions
Download the latest `thruster_toggle.dll` from [Releases](https://github.com/BC46/freelancer-thruster-toggle/releases). Move it to the `EXE` folder of your Freelancer installation.
Next, open the `dacom.ini` file and append the `thruster_toggle.dll` entry to the `[Libraries]` section.

## Build instructions
Build the project using the `NMAKE` tool from Microsoft Visual C++ 6.0 (VC6). Building the project using other compilers may require the code to be modified.

If you're wondering what my experience with VC6 has been like, the following compiler output pretty much summarizes it:
```
src\utils.cpp(3) : fatal error C1001: INTERNAL COMPILER ERROR
        (compiler file 'msc1.cpp', line 1786)
         Please choose the Technical Support command on the Visual C++
         Help menu, or open the Technical Support help file for more information
```
