# radar visualization

__online mode__
1. access can driver to retrieve raw data(can/canfd). Following devices are supported:
   - VN1600 Interface Family (tested on VN1630A and VN1640A) 
   - PCAN-USB (tested on PCAN-USB Pro FD)
2. unpack raw data to signals, which needs read & parse dbc file
3. draw the detected area with parsed signals using basic drawing apis from opencv
   - for performance reason do not use python/matlab for now
4. access usb camera and record real scenes
5. support scene scaling and draging with mouse key or wheel
6. record video and blf simultanously

__offline mode__
1. replay recorded blf to generate visualization video offline
   - display mode for immediate visualization with almost the same experience of online mode
   - silent mode supports batch conversion