/******************* (c) copyright 2016 ���ƺ��Ϲ����� **********************
 * �ļ���       ��keyscan.h
 * ����         ��void  keyinit(void)         ��ʼ������
                  unsigned char keyscan(unsigned char clock)  ����ɨ��, clock=1ʱ������
 * ���̷ֲ�     ��
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