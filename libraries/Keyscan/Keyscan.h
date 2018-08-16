/******************* (c) copyright 2016 枫云海韵工作室 **********************
 * 文件名       ：keyscan.h
 * 函数         ：void  keyinit(void)         初始化键盘
                  unsigned char keyscan(unsigned char clock)  键盘扫描, clock=1时自锁。
 * 键盘分布     ：
                  0  4  8  c
                  1  5  9  d
                  2  6  a  e
                  3  7  b  f
 ****************************************************************************/

#ifndef __keyscan_h
#define __keyscan_h

void keyInit(void);
unsigned char keyScan(unsigned char clock);

#endif  //__keyscan_h