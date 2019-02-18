# HeliosLightcontrol
## Filetree
```
|-- HLC_Base
    |-- src
|-- HLC_Lamp
    |-- src
|-- HLC_LED_Matrix
    |-- src
        |-- WirelessConnection.cpp
        |-- WirelessConnection.h
    |-- HLC_LED_Matrix.ino
|-- HLC_Sensor
    |-- src
        |-- Sensoring.cpp
        |-- Sensoring.h
    |-- HLC_Sensor.ino
|-- HLC_Web
|-- tmp
|-- .gitignore
|-- README.md
```

## Dependencies
| Tables            |      Name of Lib              |  Website                                                              | Folder |
|-------------------|:-------------                 |------                                                                 | ------|
| HLC_Base          |                               |                                                                       |  |
| HLC_Lamp          |                               |                                                                       |  | 
| HLC_LED_Matrix    |                               |  https://github.com/adafruit/Adafruit-GFX-Library/archive/master.zip  | Arduino/libraries |
|                   |                               |  https://github.com/adafruit/Adafruit_NeoMatrix/archive/master.zip    | Arduino/libraries |
|                   |                               |  https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip     | Arduino/libraries |
| HLC_Sensor        | Adafruit DHT-sensor-library   |  https://github.com/adafruit/DHT-sensor-library                       | Arduino/libraries |
|                   | Adafruit sensor library       |  https://github.com/adafruit/Adafruit_Sensor                          | Arduino/libraries |
|                   | Adafruit_TCS34725.h           |  https://github.com/adafruit/Adafruit_TCS34725                        | ../src/Adafruit_TCS34725.h |