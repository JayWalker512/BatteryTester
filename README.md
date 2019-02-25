Battery Tester
--------------

Quick dump of code and schematic for a battery tester I made with an Arduino Micro. Intended for testing 18650 type Lithium Ion battery cells. You could configure it to test other types of batteries as well.

This should be enough to get up and running for someone who's familiar with Arduino, I'll add more details and clean up the code at a later time. See 'schematic.jpg' (below) for constructing the circuit, and the definitions at the top of the Arduino code if you wish to configure this for another type of battery.

![Battery Tester Schematic](https://github.com/JayWalker512/BatteryTester/blob/master/schematic.jpg?raw=true "Battery Tester Schematic")

Perhaps there should be a low-pass filter on the input to the FET, but this circuit works well enough in practice.
