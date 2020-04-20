# hc32L196_nbiot_tmote_app_spot
> ##### Copyright (C) 2020 Movebroad Version:20.100 Design by Movebroad
> ##### movebroad Kangkang ps: 版本号以下为此版本修改、增加、去除等内容记录！
> ##### Device: HC32L196 / BL24CXX / P25QXX / SI4438 / NBIoT BC28
> ##### Boot map: 0x0000_0000 ~ 0x0000_7800
> ##### APP map: 0x0000_7800 ~ 0x0004_0000
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
0x0000_0003 ~ 0x0000_0006 | (4Byte) | SNBackUp
0x0000_0007 ~ 0x0000_000A | (4Byte) | VenderBackUp
0x0000_000B ~ 0x0000_000B | (1Byte) | SoftwareMajorBackUp
0x0000_000C ~ 0x0000_000C | (1Byte) | SoftwareMinorBackUp
0x0000_000D ~ 0x0000_000D | (1Byte) | RadioChannel
0x0000_000E ~ 0x0000_000E | (1Byte) | RadioHeartval
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
	* APP开始移植。