# radar visualization

__online mode__
1. access can driver to retrieve raw data(can/canfd)
   - only vector driver is supported for now 
     - J2534 is not an option here because of canfd
     - need to support other can devices, but this task has a lower priority because other cheap devices do not support canfd
2. unpack raw data to signals, which needs read & parse dbc file
3. draw the detected area with parsed signals using basic drawing apis from opencv
   - for performance reason do not use python/matlab for now
4. access usb camera and record real scenes
5. support scene scaling and draging with mouse key or wheel
6. record video and blf simultanously

__offline mode__
1. replay recorded blf to generate visualization video offline
   - display mode for immediate visualization with almose the same experience of online mode
   - silent mode supports batch conversion