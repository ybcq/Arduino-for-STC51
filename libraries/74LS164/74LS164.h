/******************* (c) copyright 2016 ���ƺ��Ϲ����� **********************
 * �ļ���       ��74ls164.h
 * ����         �����������74hc164��������
 * ����         ��ls164_sendbyte(uchar byte)           ����һ���ֽڵ�i2c
                  ls164_display(uchar number)          74ls164��ʾ
 * ת��         ��http://www.baiheee.com/documents/100816/100816210758.htm
 ****************************************************************************/

#ifndef __74LS164_H_
#define __74LS164_H_ 1

void lssendByte(unsigned char byte);
void lsDisplay(unsigned char number);

#endif
