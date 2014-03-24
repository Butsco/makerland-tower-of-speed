Tower of Speed
==============

Project for the hackathon at Makerland in Warsaw on the 19th of March 2014 (http://www.makerland.org/)

The game
--------

The game is very simple, we have a light and when this starts to flicker the players need to push their button as fast as possible. The player who was first gets a point. When a player presses the button when the light is not flickering, he loses a point.
The first to 7 points is the winner.

Our setup
---------

* a laptop running a nodeJS server
* 2 3D printed and soldered buttons, conected to an arduino
* a 4x4 LED matrix as the main light, connected to an arduino
* 2 LED strips with 2x7 LEDs each, each connected to an arduino
* a tower to attach the LED strips on for enhanced visibility

All the arduinos are connected to the laptop by the USB cable, and use Serial communication to communicate to a nodeJS server on the laptop. This server contains the full game logic and controls all the attached elements: the LED cube to indicate when players need to press the buttons, the LED strips to serve as a scoreboard for each player, and the buttons as an input for each player.

A picture can be found here:
https://twitter.com/StevenRKM/status/446311110485233664
