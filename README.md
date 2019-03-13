# handcar（手动车代码）v2.0

## 文件层次

* Drivers(HAL库驱动层)
* Middlewares(freertos层)
* MDK-ARM （keil工程文件和编译文件）
* User（用户层）
  + bsp (用户底层配置层)
  + drivers（用户模块设备层）
    - counters(控制器等算法)
    - data_struture(用户自定义数据结构)
    - modules（模块和外设）
  + app（应用控制层）
  + user_task(用户任务层)
* Inc（主函数和中断层头文件）
* Src（主函数和中断层源文件）

## 库说明

STM32CubeF4 Firmware Package V1.21.0 / 23-February-2018

## 系统支持

FreeRTOS

## 开发板支持

RM新板，彬哥第一代板（f427IIHx）
RM旧版遥控数据会失真
## 代码命名规则说明

类型|命名规则|示例
-|-|-
 函数名|大驼峰|MyName
 普通变量|全小写,连接加下划线|my_name
 结构体声明|小驼峰加后缀Struct|myNameStruct
 结构体定义|小驼峰加后缀_t|myName_t
 枚举声明|小驼峰加后缀Enum|myNameEnum
 枚举定义|小驼峰加后缀_e|myName_e
 指针类型|相应类型加前缀p|普通变量指针类型pmy_name，结构体指针类型pmyName_t

## 底层外设支持（bsp）

外设|说明
-|-
串口|串口空闲中断+DMA+消息队列不定长度接收
can|can中断

## 模块设备支持（modules）

模块设备|模块名称
-|-
电机|6623  3508  2006	maxion
遥控|大疆遥控dbus

## 数据结构和算法（data_struture，counters）

数据结构和算法|算法名称
-|-
数据结构|循环队列
滤波器|加权滑动平均滤波
