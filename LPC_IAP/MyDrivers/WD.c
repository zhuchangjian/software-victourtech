#include "lib_watchdog_lpc213x.h"
#include "WD.h"
//初始化
void WDInit(uint32 count)
{
	//4分频，15000000为1秒
	WD_SetCount(count);
	WD_ModeSet(MODE_2);
	WD_Feed();
}

/*void ClearUserRom(void)
{
	uint8 WdFlag = 0;
	uint8 WriteFlag = 0;
	WdFlag = WD_GetFlag(0x0F);
	
	if(WdFlag & 0x04)
	{
		eepromRead(0xFF00, &WriteFlag, 1);
		if(WriteFlag != 1)
		{
			eepromErase(SECTOR4, SECTOR8);
		}
		//清除标志位
		WD_ClearFlag();
	}
}*/
