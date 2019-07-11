                                 W O R K   S T I L L   I N   P R O C E S S . . .

Hey there! Here is my project called SmarTClouD. 

Project includes:
  - Schemes of magneto-levitating system
  - Source code of levitron
  - And README file, that i hope will help you to understand what's going on
  
  A
  
This repository combines two different projects: the megneto levitating system and the colormusic for the cloud. 
I’ve tride to make such cloud as Richard Clarkson’s studio produces. 
 *link : https://www.rclarkson.com/collections/clouds/products/floating-cloud

The main idea of the project was the levitating cloud above some sort of platform.
I used the crealev company magnet levitation system patent to create the base of project (platform), but whith my own coil-control system. 
 *link : https://www.crealev.com/levitation-modules
!ACHTUNG! You better watch to the schemes if you wanna understand all case
 Or skip this part and just download project. 

  
Imho magnet-levitation project are divided into 3 cases:

First one is quite simple. The solenoid, that positioned above magnet, turns off or on depending on Hall sensor’s testimony. There are examples 1 in folder schemes btw.

Second type used to be composed from round permanent magnet and about 4 (or more) solenoid coils, which are equidistant from center of platform, also they have some sort of control stuff (as usual Hall sensor) right in center of platform.

Third type used to be pretty much stronger than the second one. Also they have different control system of above-thing (levitating body); for example, Crealev uses magneto-optical control system, based on magnet Kerr effect and light polarization. Personally I used ultrasonic sensors to find out distance between sensor and the levitating body, then to figure out deviation of each axis (x and y) from “perfect” axis z (witch is positioned right in the middle of the levitating body and in the middle of the platform), I used differences between cos from each distance. After all manipulations, if deviation of axis is positive, that means that incline of levitating body is on the right side, so resistance of potentiometer that is paralleled to the coil of the right side is decreasing, at the same time, resistance of potentiometer that is paralleled to the coil of the left side of the axis that we are looking at, is increasing until deviation of the axis will be negative or equals 0 (all the opposite for the negative way and delay for zero).

  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Technical shift: probably you'll need 

maybe change const_alpha 

change default_resistance


GL
