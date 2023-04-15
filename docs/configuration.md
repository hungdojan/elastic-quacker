# Rubber Ducky basic configurations

The main configuration file is located in `rubber_ducky` directory. `config.h` header file contains list of important macros that defines how the device will behave once it starts running. Macros are listed below:

- `CFG_TUD_HID`
    - TinyUSB macro that enables 'Human Interface Device' class. 
      When enabled the device behaves as a keyboard and is allowed to execute RD script payload.
- `CFG_TUD_MSC`
    - TinyUSB macro that enables 'Mass Storage Class'.
      When enabled the device behaves as a mass storage device and the storage content can be mounted to the machine.
- `KEYPRESS_DELAY_MS`
    - Defines the time delay between (a series of) key presses (in milliseconds).
- `KEY_SEQV_BUFFER_SIZE`
    - How many key sequences (group of key presses) can the device store. For bigger payloads increase the value.
- `WIFI_ENABLED`
    - Enables WiFi module. That will allow the user to dynamically update the RD script payload.
- `WIFI_SSID`
    - If WiFi module is enabled this macro defines WiFi's name. Defaults to "RubberDucky_WiFi".
- `WIFI_PSWD`
    - If WiFi module is enables this macro defines WiFi's password. Defaults to "TheCakeIsALie".
- `_TCP_SERVER_PORT`
    - Defines application port from where the device will listen. This is important as the port value
      is later passed to 'rd_client' script (-H flag). Defaults to 5000. 
- `DEBUG_CAPS_LOCK`
    - When enabled it allows the user to rerun the stored payload when double pressed CAPS LOCK button.
      The device starts executing the payload once CAPS LOCK diode turns off.
- `AUTOSTART_AFTER_PLUGIN`
    - When enabled the device will start executing payload right after it is plugged into the host machine.
    - Autostart is automatically enabled when DEBUG_CAPS_LOCK is disabled.
- `_INITIAL_BOOT_DELAY`
    - This macro delays payload execution after the device is plugged in. Without the delay the device starts
      sending key sequences during the enumeration process.
