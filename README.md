# Assetto Corsa Arduino LC-Display Dashboard

This piece of software provides the ability to connect an Arduino attached with a LC-Display-Shield to display some game relevant informations in real time. This project is currently in it's very beginning. The software needs refactoring that will probably happen within the next months. 

## Arduino 

Part of this repository is the Arduino source. It uses the LiquidChrystal library that ships with the Arduino IDE. To get this working, you probably have to tweak the pins set for the usage of the library. They differ from shield to shield. As far as I know, different suppliers of these shields handle them differently. If you find the right pin configuration, you should see some "Gear: Rev:" texts in your display, even though it's not connected to the phyton app.

## Python

This library already comes with an pySerial version which is required to communicate with the Arduino. To run the Assetto Corsa phyton app you just have to add the whole **ArduinoDash** folder to your Assetto Corsa installation which can be found in your Steam installation under */Steam/SteamApps/common/assettocorsa/apps/python*

You have to configure the right COM-port on your PC. Otherwise the app will crash until it tries to connect again on the next start of a race. 

To set a new value for the rev limiter, you have to edit the part:

```python
ser.write("3:17000;".encode())
```

17000 is the current limit. Feel free to edit.