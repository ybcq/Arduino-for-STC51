/******************* (c) copyright 2016 枫云海韵工作室 **********************
 * 文件名       ：led.h
 * 函数         ：ledInit(void)                                     初始化屏幕
                  ledDisplay(unsigned int i, unsigned int j, unsigned char point, unsigned char digit)
                  屏幕扫描(前4位，后4位，从右侧数小数点位置，位数)
                  ledDisplayEnglish(unsigned char digit, unsigned char letter)         显示英文旧版
                  ledDisplayNew(unsigned char letter[8])                       显示英文新版
 ****************************************************************************/

#ifndef __leddisplay_h
#define __leddisplay_h

void ledInit(void);
void ledDisplay(unsigned int i, unsigned int j, unsigned char point, unsigned char digit);
void ledDisplayEnglish(unsigned char digit, unsigned char letter);
void ledDisplayNew(unsigned char letter[8]);

#endif  //__led_h

