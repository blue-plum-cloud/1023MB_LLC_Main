# 1023MB_LLC_Main
 good stuff

<h1>Pre-Setup</h1>
<h3>
<h2>Install Libraries</h2>
1. Go to "Manage Libraries" in the Arduino IDE, and download <strong>iBusBM and ESP32 AnalogWrite</strong>.

<h2>Set Up ESP32</h2>
1. To set up the ESP32, go to File -> Preferences and paste (https://dl.espressif.com/dl/package_esp32_index.json) in "Additional Board Managers URLs".

2. Go to Tools -> Board -> Boards Manager and search for ESP32. Install the package titled "ESP32".

3. For Windows systems, you need to go to this link and download the CP2120x Universal Windows Driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers.

4. Install the driver.


<h2>Compile Sketch</h2>
1. Open <code>LLCMain.ino</code> (the main sketch) in Arduino IDE. It will open the main sketch and the other libraries used.

2. Compile and upload <code>LLCMain.ino</code> onto the ESP32. Ensure that pre-setup has already been completed before you start this step.