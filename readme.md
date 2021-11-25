# radar visualization
1. accese can driver to retrieve raw data(can/canfd)
   - only vector driver is supported for now 
     - J2534 is not an option here because of canfd
     - need to support other can devices, but this task has a lower priority because other cheap devices do not support canfd
2. unpack raw data to signals, which needs read & parse dbc file
3. draw the detected area with parsed signals using some simple apis such as opencv
   - for performance reason do not use python/matlab for now
4. access usb camera to record real scenes