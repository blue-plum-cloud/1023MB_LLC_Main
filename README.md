# 1023MB_LLC_Main
<a href=".github/workflows/main.yml" ><img src="https://img.shields.io/github/workflow/status/blue-plum-cloud/1023MB_LLC_Main/Arduino-CI?label=Build&logo=arduino&style=flat-square"/></a>

good stuff

# Prerequisites

## Install Libraries

1. Go to "Manage Libraries" in the Arduino IDE, and download the following libraries:
- [iBusBM](https://github.com/bmellink/IBusBM)
- [Arduino_APDS9960](https://github.com/1487quantum/Arduino_APDS9960/), `ESP32` branch

> **Note:** There is a slight modification that is required for the ESP32 to compile the APDS9960 library, comment out the `wire.end();` of `void APDS9960::end()` inside `src/Arduino_APDS9960.cpp`. Alternatively, refer [here](https://github.com/1487quantum/Arduino_APDS9960/blob/esp32/src/Arduino_APDS9960.cpp#L80).

## Set Up ESP32

1. To set up the ESP32, go to File -> Preferences and paste (https://dl.espressif.com/dl/package_esp32_index.json) in "Additional Board Managers URLs".

2. Go to Tools -> Board -> Boards Manager and search for ESP32. Install the package titled "ESP32".

3. For Windows systems, you need to go to this link and download the CP2120x Universal Windows Driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers.
4. Install the driver.


## Compile Sketch

1. Open `LLCMain.ino` (the main sketch) in Arduino IDE. It will open the main sketch and the other libraries used.

2. Compile and upload <code>LLCMain.ino</code> onto the ESP32. Ensure that pre-setup has already been completed before you start this step.
