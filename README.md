# scsim
Simple DOS spacecraft simulator

Copyright (c) 2022, Michael Robinson

## Synopsis

This is the source code for a physics-mostly-accurate spacecraft simulator I wrote, circa 1995.  It is written in Microsoft QuickC for DOS, and is unlikely to build on any modern system.  However, the `.exe` files do appear to work on DOSBox.

## Source code

There are two versions of the program, with similar but distinct controls:

* `sc2sima` : Keyboard controls the thrusters
* `scsimj` : Game port connected joystick controls the thrusters

There are numerous differences as well.  This was a program that I spend considerable time adjusting. These are two development snapshots at the time I left for college.

## Space Craft Controls:

At least for `sc2sima`, the keyboard controls the thrusters.  Some of these are disabled in `scsimj`, since the joystick controls the thrusters.

| Key | Action |
| --- | ------ |
|`8` | Fire forward thrusters|
|`2` | Fire reverse Thrusters|
|`5` | center heading on direction of movement|
|`4` | Rotate left|
|`6` | Rotate right|
|`7` | Translate Up|
|`3` | translate down|
|`w` | increase thruster power|
|`x` | decrease thruster power|
|`a` | decrease main engines|
|`g` | increase main engines|
|`f` | translate right|
|`s` | translate left|
|`e` | pitch up|
|`c` | pitch down|
|shift+`f` | fine control mode toggle|

## Computer & simulation Controls:

The ship's computer and the simulation itself also is under keyboard control

| Key | Action |
| --- | ------ |
|`t` | select track object|
|shift+`e` | toggle Auto track Directing (points ship at object)|
|shift+`s` | track coordinates|
|`b` | toggle fill|
|`d` | redraw screen|
|`v` | toggle view window|
|`o` | toggle inside/outside view|
|shift+`r` | reset program|
|`q` | quit|
|`p` | pause simulation|
|shift + `c` | toggle crosshairs on/off|

## Special Purpose Commands:

| Key | Action |
| --- | ------ |
|`]` | arm/disarm weapon systems|
|`[` | initiate weapon pulse (fire)|
|shift+`v` | open editing menus|

## Control Panel:

### Numbers:

* second from bottom: your velocity
* bottom (three numbers): your x,y,z location
* top: tracking status, x,y,z: size, V:velocity, D:distance

### Dials:

* top dial (compass):
  - x,y vector (heading)
  - white needle: way your ship is pointing
  - green needle: way your ship is moving
  - white nicks: angle to object being tracked
* Bottom Dial (pitch meter):
  - pitch

### Meters:

* Horizontal:
  - graphic velocity representation
* Vertical at left:
  - thruster power
* Vertical at right:
  - Main engine power

### Lights:

* most right:
  - crash type:
    . green: crash off
    . Red: crash restarts program
    . blue: crash bounces spacecraft off course
* between dials:
  - compass alignment (doesn't always work)
* under horizontal meter
  - Auto track:
    . red: off
    . green: on
* Left of horizontal meter:
  - direction     

### Other Objects on panel:

* right, just below crash type indicator
  - Weapons status indicator unit
    . Red: weapon systems armed
    . Green: weapon systems disarmed
    . Plus sign (+) in unit: object tracked is in weapon range
    . Small vector: absolute direction of motion of track object