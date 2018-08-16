# Arduino for 51

51Arduino说明文件

(2018年8月15日版)

What’s This？

	51Arduino是一个把51内核单片机进行Arduino语法化（以下简称51Arduino化）的开源项目。其灵感来源于作者的师兄在进行51相关逆向工程时遇到的繁琐的编程，以及知乎上一篇关于《能不能用Arduino语言写51单片机程序？》的问题。
	
	51Arduino化的技术困难集中在：51内核单片机的速度较慢，ROM和RAM都较小，不适合链接很多的库文件，也不适合进行较多的浮点运算；Arduino基于GCC写成，但是51内核是基于PK51编译器的，存在一定的兼容性问题。51移植到Arduino的唯一优势是AT89S5X和AVR是一家公司（笑）。
	对此，我们需要大量的精简化操作，让51可以利用较少的代码实现Arduino的功能。当然，这是在不破坏原有的Arduino语法结构的基础上。
	
	国内有一款炒得比较火的产品叫做51duino，号称中国人自己的Arduino。我下载了其源码，发现其源码很大程度上还是基于51的书写习惯写成。而且，其提出了一套与传统Arduino完全不兼容的硬件系统。换言之，51duino根本不是Arduino。创客以此为基础做简单开发时，依旧会面临较大的编程压力，同时对原Arduino开发人员重新学习51语法造成了较大困难。
	
	所以51duino与本项目除了名字没有任何相似之处！
	
	本项目最终目标是：设计一套基于51内核单片机的Arduino开发板，包括Arduino Nano，Arduino UNO和Arduino 2560，其大小、硬件接口与标准Arduino 完全相同，可以直接使用Arduino的各种扩展模块。软件开发的最终目的是使用Arduino IDE进行51单片机开发和下载，当然这其中包括ISP下载器与IDE链接等一系列纯粹的软件技术问题，难度较大，需要有相关知识的人参与一同开发。在找到合适的合作伙伴之前，暂时使用KEIL或IAR开发。
	
	本项目永久开源！但是也请大家尊重作者的劳动。转载尽可能的注明个出处。任何合适的建议和意见，包括您个人修改完善后的代码都欢迎与作者联系，记得在代码开头的注示中写上你的名字。邮箱地址：Guan_Jeremy@foxmail.com ,十分欢迎各界人士加入此项目。

	希望我们共同打造真正的51Arduino！

作者：枫云海韵

2018年2月26日

目前开发到了哪里？

2018年8月15日工作日志：
1.更新了描述文件
2.更多的使用#define以减小代码压力
3.使用D1, D2……表示数字引脚，代码长度减小
4.引入STC15版本

2018年7月9日工作日志：
1.合并了原有的51lib工程，并且永久不再更新51lib
2.由于sfr不可以被指针寻址，所以重新定义引脚为PORT1，PORT2代替源计划中的00等
3.使用#define伪解决Keil不支持C++的问题

2018年2月26日工程日志：

1.已匹配Arduino大部分基础函数，具体可进入51Arduino.h查看。
2.使用WinRAR自解压文件创建新工程，安全可靠，一键创建工程更方便。
3.突然发现Keil不支持C++，正在考虑其他方法。

适当的使用方法说明？

1.双击“创建新工程.exe”，输入工程名，点击安装可创建一个空的工程。
2.可以使用标准的Arduino语法进行编程。
3.引脚编号可以使用P0^0, P0_0样式的标号，也可以使用D0, D1这样的标号。
4.本工程适用于AT89S52以上Atmel51系列单片机，STC89系列单片机，STC12系列单片机，以及STC15系列单片机。不建议在尾号为51，52的单片机上使用，因为其ROM空间有限。
5.编译结束的HEX输出到OUTPUT文件夹，可以使用STC-ISP, PROGISP下载到单片机中。
6.Serial相关函数请把.改成_因为51单片机通常只有1组串口，不需要写Class。
7.每个头文件里都有较详细的讲解，如果不知道怎么使用请查看代码或者联系作者提出相关建议。
8.如需使用时间函数，请开启初始化串口。
9.Setup文件夹中有你需要用的编程软件Keil等。
10.Tools文件夹中有你需要的下载工具。


51Arduino编写规则，用于协同开发
1.尽可能遵循Arduino的函数命名规则
2.函数多采用首字母小写，第二个单词起大写的命名方式，比如：analogWrite
3.变量多采用全小写字母
4.引脚多采用全大写字母
5.C++中表示类的.全部改为_

51Arduino待解决的问题
1.中断冲突错误
2.滴答定时器的实现
3.利用已有库的示例程序编写
4.更多库的移植
