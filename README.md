# esp32-ov7670-mqtt

Use an esp32 and the OV7670 camera without FIFO and send the images via MQTT to a broker. We don't use a hardware display. The BMP image can then be viewed on the MQTT broker.

# What do you need?

Android IDE with ESP32 integration

# Home Assistant

You can connect the OV7670 Camera via MQTT to your home assistant server. Edit the configuration.yaml file and add:

```
camera:
  - platform: mqtt
    name: "<YOUR CAMERA NAME>"
    topic: "<YOUR TOPIC>"
```


# Acknowledgements
The project is based on the "ESP32 I2S Camera" by [bitluni](https://github.com/bitluni/ESP32CameraI2S#esp32-i2s-camera)

# Support the Project

<a href="https://www.buymeacoffee.com/spifitu" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a>

