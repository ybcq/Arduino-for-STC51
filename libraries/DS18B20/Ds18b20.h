/******************* (c) copyright 2016 ���ƺ��Ϲ����� **********************
 * �ļ���       ��ds18b20.h
 * ����         ������ܽ�
 * ��ע         ����ԭ��
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
