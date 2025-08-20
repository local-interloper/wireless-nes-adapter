# Wireless NES Adapter

The goal of this project was to design a piece of hardware that you can use to play computer games 
using the original Nintendo Entertainment System controller. It comes with all the code, PCB 
schematics and information required to get a printed circuit board printed and assemble and 
program the hardware.

![PCB Schematic](/img/schematic.png)
![PCB Layout](/img/pcb.png)
![Board Preview Image](/img/preview.png)

## Requirements

- [KiCad](https://www.kicad.org/)
- esp32-s3 devboard (make sure it looks like [this](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/_images/esp32-s3-devkitc-1-v1.1-isometric.png))
- NES Controller socket (easily found on AliExpress)
- Arduino IDE setup with [`arduino-esp32`](https://github.com/espressif/arduino-esp32) and [`ESP32-BLE-Gamepad`](https://github.com/lemmingDev/ESP32-BLE-Gamepad) installed
- A soldering iron and some solder

## How to build

1. Select a PCB printing service of your choice (I went with [Aisler](https://aisler.net/en-US)).
2. If your PCB printing service does not support native KiCad files, open `kicad/wireless-nes-adapter` 
    in KiCad and export the schematics so you can get your PCB printed.
3. Assemble the hardware.
4. With your Arduino IDE set up with the aforementioned libraries, select the ESP32-S3 as the target and flash 
    `/arduino/wireless-nes-adapter.ino` to the board.
5. Plug in your controller and power the board via USB.
6. Add the controller in your computer's bluetooth devices.

## All set!

You should now be all set. I recommend using steam as steam input allows you to use the direct input controller
you've just built as an xinput one via remapping. I recommend testing the controller on 
[Rain World](https://store.steampowered.com/app/312520/Rain_World/) or [Celeste](https://store.steampowered.com/app/504230/Celeste/) 
if you have any of those 2 titles due to their low input count requirement.