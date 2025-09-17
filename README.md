# pio_esp32s3_devkit_ap_webserver

An example project that shows how to setup a webserver on a ESP32 DevKit in Access Point mode.

## Getting Started

After getting started you can find further instructions about the [usage](#usage) down below.

### Install the PlatformIO IDE VSCode Extension

Install the PlatformIO IDE extension from the VSCode extension marketplace (see workspace recommendations). You may be asked to install Python. You may follow the instructions [here](https://docs.platformio.org/en/latest/faq/install-python.html).

### Initialize the Project

In this example a PlatformIO project has already been created. The project configuration can be inspected in the [platformio.ini](./platformio.ini) file.

The `platformio` (or `pio`) command-line interface should be installed along the the extension. For the local development purposes you need to intialize the command-line interface. Execute the following commands in the command-line:

```bash
pio project init
```

Note: The command-line has to be a PlatformIO terminal. You can create a new PlatformIO termincal by pressing the `PlatformIO: New Terminal` buttom in the bottom left of your VSCode window.

Run the `pio check` command to do a static code analysis to check if everything is setup correctly.

### Set up Configuration and Secrets

You can find sections below on how to handle [configuration](#configuration) and [secrets](#secrets) down below. Make to follow the instructions and you should be good to go.

### Build and Upload the Code to the [ESP32-S3-DevKitC-1]

After installation and initialization you may build and upload the code to your device. Connect the Ardunino Nano ESP32 via USB. Then run the following commands (in a PlatformIO terminal):

```bash
# Check if your device can be detected
pio device list
# Build the code
pio run -e esp32-s3-devkitm-1 -t build
# Upload the build
pio run -e esp32-s3-devkitm-1 -t upload
```

As an alternative to the command you can also use the PlatformIO buttons in VSCode. You can find the buttons below. Make sure to select the correct (`esp32-s3-devkitm-1`) environment for the upload.

The next setup step is the [upload of files for the static website](#upload-the-files-for-the-static-website).

### Upload the Files for the Static Website

Use the following steps to upload the files for the static website:

1. Create a data Folder: In the root directory of your PlatformIO project, create a new folder and name it data. This folder should be at the same level as the src and lib folders. All the files you want to upload (e.g., HTML, CSS, JavaScript, images) must be placed inside this data folder.
2. Access the Project Tasks: Open the PlatformIO Home or Project Tasks view in VS Code (usually the "ant" icon on the left sidebar).
3. Build the File System Image: Under the project tasks for your specific board (e.g., env:esp32dev), expand the Platform menu. You will see an option to Build Filesystem Image. Click this to compile the files in your data folder into a single binary image file that the ESP32 can understand.
4. Upload the File System Image: After the image is built, the same menu will have an option to Upload Filesystem Image. Click this to flash the binary image to your ESP32's SPIFFS partition. Ensure your ESP32 is connected and the correct port is selected.

Use the following [tutorial](https://microcontrollerslab.com/upload-files-esp32-spiffs-vs-code-platformio-ide/#:~:text=After%20you%20have%20created%20your,that%20click%20Upload%20Filesystem%20Image.) if you get stuck at the steps above.

### Run Tests

```bash
# Run test locally on your desktop
pio test -e desktop
# Run test on the device
pio test -e esp32-s3-devkitm-1
```

#### Debug Tests

If you are using VSCode (which is recommended), use the following steps to debug your test runs:

1. Select the `desktop` environment to select your local machine as the build target
2. Open the testing module [test_desktop_main.cpp](test/test_desktop/test_desktop_main.cpp) in your editor
3. Go to the debug tab in VSCode
4. Launch the code with the `PIO Debug` configuration

This will automatically attach a gdb debugger and enable VSCode debugging.

## Documentation

### Configuration

Set the configuration in the [config.h](lib/Config/config.h) header file. Use the provided constants as they are used in the code.

### Secrets

Provide the secrets in the [secrets.h](lib/Config/secrets.h) header file. This file provides constants which are used in the code. As part of the setup you have to create the [secrets.h](lib/Config/secrets.h) file at the `lib/Config/secrets.h` path. Use the following template to create the file

```cpp
/**
 * @brief The WIFI SSID for a Wifi client.
 *
 * This Wifi SSID is used together with the `WIFI_PASSWORD` to create a Wifi access point (AP).
 */
const char *WIFI_SSID = "INSERT_YOUR_WIFI_SSID_HERE";

/**
 * @brief The Wifi password a Wifi client.
 *
 * This Wifi password is used together with the `WIFI_SSID` to create a Wifi access point (AP).
 */
const char *WIFI_PASSWORD = "INSERT_YOUR_WIFI_PASSWORD_HERE";
```

### Wifi Connection QR-Code

You can use the [QR Code Generator](https://www.qrcode-generator.de/solutions/wifi-qr-code/) website to create a QR-code to make access to the wifi AP easiert.

Insert the Wifi SSID and password from the [lib/Config/secrets.h](lib/Config/secrets.h) (see [secret configuration](#secrets)) into the website. Make sure to select the `WPA/WPA2` encription.

*Note:* You can store the QR-code in the hidden [private/](private/) directory.

## Usage

This is a simple demo on how to create a Wifi access point (AP) and a webserver on your [ESP32-S3-DevKitC-1]. After completing the [getting started](#getting-started) instructions you can power the ESP32 on and connect to the Wifi. Use the configured [secrets](#secrets) or the [Wifi QR-code](#wifi-connection-qr-code).

Once you are connected you can do the following requests:

- Curl the root endpoint with `curl -X GET http://192.168.4.1/`
- Toggle the LED using the following requests
    - Turn the LED green with `curl -X GET http://192.168.4.1/led/green`
    - Turn the LED off with `curl -X GET http://192.168.4.1/led/off`
- Request static files from the webserver using the `curl -X GET http://192.168.4.1/static/index.html` or opening the URL [http://192.168.4.1/static/index.html](http://192.168.4.1/static/index.html) in your browser


## Sources

- [PlatformIO]
- [ESP32-S3-DevKitC-1]

[PlatformIO]: https://platformio.org/
[ESP32-S3-DevKitC-1]: https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide_v1.1.html#hardware-reference
