# Before using this code

Do not forget to turn on monitor mode and choose the right channel on your wireless interface card.

Here is a exmaple on how to do it : 
```
sudo ifconfig wlp5s0 down
sudo iwconfig wlp5s0 mode monitor
sudo ifconfig wlp5s0 up
sudo iwconfig wlp5s0 channel 1 
```

To run the code execute `sudo ./bin/exec WIFI_IF_NAME`.

# Source

This code was originally taken from [thomasfla/Linux-ESPNOW](https://github.com/thomasfla/Linux-ESPNOW).