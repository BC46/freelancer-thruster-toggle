# Freelancer Thruster Toggle
Plugin for the game Freelancer (2003) that allows players to toggle the Thruster activation using a single key.
Please note that this functionality isn't useful for most players as this plugin is just a proof of concept.
Also, the approach that has been taken to modify the `ids_name` value and key states in-memory is far from the greatest and is only included to demonstrate the possibility.

## Installation instructions
Download the latest `thruster_toggle.dll` from [Releases](https://github.com/BC46/freelancer-thruster-toggle/releases). Move it to the `EXE` folder of your Freelancer installation.
Next, open the `dacom.ini` file and append the `thruster_toggle.dll` entry to the `[Libraries]` section. 

## Build instructions
Build the project using the `NMAKE` tool from Visual Studio C++ 6.0 (VC98). Building the project using other compilers may require the code to be modified.
