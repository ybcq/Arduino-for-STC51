/******************* (c) copyright 2016 枫云海韵工作室 **********************
 * 文件名       ：ds18b20.h
 * 作用         ：定义管脚
 * 备注         ：非原创
 ****************************************************************************/

#ifndef __ds18b20_h
#define __ds18b20_h

void dsPin(int DS);
bit dsReadBit(void);
void dsInit(void);
void dsWait(void);
void dsWriteByte(unsigned char dat);
void dsSendChangeCMD(void);
void dsSendReadCMD(void);
int dsGetTmpValue(void);
unsigned char dsReadByte();


#endif  //__ds18b20_h
