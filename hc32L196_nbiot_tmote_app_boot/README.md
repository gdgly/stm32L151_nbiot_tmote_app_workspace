# hc32L196_nbiot_tmote_app_boot
> ##### Copyright (C) 2020 Movebroad Version:0.40 Design by Movebroad
> ##### movebroad Kangkang ps: 版本号以下为此版本修改、增加、去除等内容记录！
> ##### Device: HC32L196 / BL24CXX / P25QXX / SI4438 / NBIoT BC28
> ##### Boot map: 0x0000_0000 ~ 0x0000_7800
> ##### memory: 0x2000_0000 ~ 0x2000_8000

<style>
table th:first-of-type {
	width: 320px;
}
table th:nth-of-type(2) {
	width: 320px;
}
table th:nth-of-type(3) {
	width: 320px;
}
</style>

#### EEPROM: (256Byte)

Address | nByte |  Name
:-: | :-: | :-: 
0x0000_0000 ~ 0x0000_0000 | (1Byte) | BootVersion
0x0000_0001 ~ 0x0000_0001 | (1Byte) | BootMode
0x0000_0002 ~ 0x0000_0002 | (1Byte) | BootCount
0x0000_00F7 ~ 0x0000_00FA | (4Byte) | Vender
0x0000_00FB ~ 0x0000_00FE | (4Byte) | SN
0x0000_00FF ~ 0x0000_00FF | (1Byte) | Check

#### NorFlash: (512KByte)

Address | nByte |  Name
:-: | :-: | :-: 
0x0000_0000 ~ 0x0000_0FFF | (4K)   | APP1 Info
0x0000_1000 ~ 0x0003_FFFF | (252K) | APP1 Data
0x0004_0000 ~ 0x0004_0FFF | (4K)   | APP2 Info
0x0004_1000 ~ 0x0007_FFFF | (252K) | APP2 Data

* 2020-04-15 :
	* 0.40 Boot重启Count不增加，强制写0方便调试，后期APP稳定开始重启增加。
* 2020-04-15 : 
	* 0.40 Boot初步发布。
	* 1.可使用配置器通过SI4438对APP进行升级，APP镜像地址需大于0x7800，大于0x7800可正常跳转。
	* 2.当Boot重启次数大于7次，重启次数为双数进行等待配置器升级，单数进行NorFlash中固件恢复(如APP2中有备份固件)。
	* 3.进入远程升级固件提取模式时，当APP1有通过远程写入的固件时，提取APP1固件，当提取APP1固件时重启次数大于3次，标识APP1固件异常，擦除APP1使用APP2恢复。
	* 4.APP2恢复固件时重启次数大于30次，标识APP2固件异常，擦除APP2，只能通过配置器升级，写入固件。
	* 5.具备硬件自检，EEPROM、NorFlash、ChipFlash、SI4438上电异常，蜂鸣器警报，打印错误信息。


