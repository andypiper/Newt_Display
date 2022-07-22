Shipped with v0.0.11

Unable to update to 1.0.1 OTA (connection dropped)

- Install Arduino IDE 2.0
- Install Espressif 2.0.4 in boards manager
- Install required libraries in libraries manger
- Set board type to "ESP32S2 Native USB"

--> Builds 1.0.0
- Unable to find WifiManager hotspot on start
- Tried different backlevel builds of WifiManager

Reflash to original firmware (from <https://github.com/Phambili-Tech/Newt_Display_Hardware/blob/main/v0.0.11.zip>)

```shell
esptool.py --chip esp32s2 --port "/dev/cu.usbmodem01" --baud 921600  --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 "/Users/andypiper/Downloads/v0.0.11/Newt_0_0_11.ino.bootloader.bin" 0x8000 "/Users/andypiper/Downloads/v0.0.11/Newt_0_0_11.ino.partitions.bin" 0xe000 "/Users/andypiper/Downloads/v0.0.11/boot_app0.bin" 0x10000 "/Users/andypiper/Downloads/v0.0.11/Newt_0_0_11.ino.esp32s2usb.bin"
```
