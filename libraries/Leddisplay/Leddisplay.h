/******************* (c) copyright 2016 ���ƺ��Ϲ����� **********************
 * �ļ���       ��led.h
 * ����         ��ledInit(void)                                     ��ʼ����Ļ
                  ledDisplay(unsigned int i, unsigned int j, unsigned char point, unsigned char digit)
                  ��Ļɨ��(ǰ4λ����4λ�����Ҳ���С����λ�ã�λ��)
                  ledDisplayEnglish(unsigned char digit, unsigned char letter)         ��ʾӢ�ľɰ�
                  ledDisplayNew(unsigned char letter[8])                       ��ʾӢ���°�
 ****************************************************************************/

#ifndef __leddisplay_h
#define __leddisplay_h

void ledInit(void);
void ledDisplay(unsigned int i, unsigned int j, unsigned char point, unsigned char digit);
void ledDisplayEnglish(unsigned char digit, unsigned char letter);
void ledDisplayNew(unsigned char letter[8]);

#endif  //__led_h

