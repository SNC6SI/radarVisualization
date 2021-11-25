# 依赖
- visual stuido
   - 默认使用2019
- vector设备驱动
- opencv3
   - 版本：3.4.16
   - 解压到本地地址，默认需为D:\opencv，如不同，才需修改工程配置
      - Configuration Properties -> VC++ Directories -> Include Directories
         - 添加 D:\opecv\build\include
         - 添加 D:\opecv\build\include\opencv
         - 添加 D:\opecv\build\include\opencv2
      - Configuration Properties -> VC++ Directories -> Library Directories
         - 添加 D:\opencv\build\x64\vc15\lib
   - 环境变量，根据opencv放的地址，修改PATH，添加 D:\opencv\build\x64\vc15\bin


# 程序流
- 两个线程
   - main线程：用于更新图像
   - RxCanFdThread线程：用于读取vector设备接收的can报文，更新obj/slot的坐标信息等


# 文件
- rv: main
- rv_common: 公用定义
- rv_param: 参数
- menuhelper: 菜单
- vectorhelper: vector设备
- capturehelper: 摄像头
- signalhelper: 接收、解析报文，更新坐标信息
- canvashelper: 更新坐标图像
- videohelper: 更新图像、录屏


# 状态
- 当前代码仅支持vector can设备
- 当前代码仅支持usb camera * 2