# stm32L151_nbiot_tmote_app_boot
movebroad Knagkang

* 2018-12-5
	* 0.29 修改SPIFLASH为读取deviceid方式，兼容其他SPIFLASH型号。
* 2018-9-8
	* 0.28 精简flash，修复应flash过大导致boot异常。
* 2018-9-5
	* 0.27 qmc加热电阻上电拉低。
	* 蜂鸣器调整最大频率。
	* 增加对GD25Q40B SPI FLASH的支持。
	* 修复因小无线晶振异常导致程序卡死，反复重启。
* 2018-8-11
	* 0.26 channel只有36和4两种
* 2018-8-3
	* 0.25 蜂鸣器改用适配无源蜂鸣器
* 2018-7-11
	* 0.24 修改启动地址只能是0x08003800的bug
* 2018-6-28
	* 0.23 启动地址在0x08003800~0x08020000才会跳转,否则默认跳到0x08003800
* 2018-6-25
	* 0.22 修复重启后boot会默认从0x08003800启动的bug
* 2018-6-22
	* 0.19 app的启动地址偏移量由原先的0x5000改为0x3800.
     同时对app进行限定,bin文件的pData[5] = (((appoffset>>8)+2)&0xFF) 才能正常升级.
	* 0.20 将eeprom的TCFG_MAG_FREQ_OFFSET改为存储boot的版本号.
	* 0.21 会根据固件的不同地址,进行跳转. 同时跳转地址不得小于0x08003800
* 2018-3-17
	* 0.18 重启次数超过7次后,偶数次直接启动,计数次进入升级模式
* 2018-1-16
	* 0.15 启动的时候从配置项里选择频段,频段为4或者36
	* 0.16 解决了升级错误的bug
	* 0.17 启动时打印bootmode和bootcount
* 2018-1-11
	* 0.11 sn读取从小端改为大端
	* 0.12 修复写入时的bug
	* 0.13 启动时关闭雷达模块
	* 0.14 解决反复重启后不会进入升级模式的错误

* 2017-12-21
	* 0.8 重启次数超过7次后,偶数次直接启动,计数次进入升级模式
	* 0.9 启动时不清楚启动原因标志位,让app中去判断启动原因.
* 2017-12-19
	* 0.7 修复bug,将程序最大支持到128-20KB
* 2017-12-17
	* 0.5 增加了对包序号的校验,如果收到的包序号小1,那么可能是重传包,不进行烧写