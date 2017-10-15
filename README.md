# Athena-ZigBee 指令集

### AT+R 重启模块

命令：

> AT+R

返回：

> +R=OK

1秒后重启

### AT+Z 恢复为出厂设置

命令：

> AT+Z

返回：

> +Z=OK

1秒后重启并恢复出厂设置

### AT+VER 查看固件版本号

**查询：**

> AT+VER

**返回：**

> +VER=2017.10M



### AT+RSSI 查询信号强度

**查询：**

> AT+VER

**返回：**

> +RSSI=9

### AT+MAC 查看硬件MAC地址

**查询：**

> AT+VER

**返回：**

> +MAC=xxx

### AT+UART 查询/设置串口



### AT+CLEAR 清除网络环境

### AT+TYPE 查询/设置设备类型

参数格式：

> =`[TYPE]`

### AT+STAT 查询模块运行状态



### AT+PAN 查询设置PANID

参数格式：

> =[PANID]

### AT+CH 查询/设置信道

参数格式：

> =[CHANNEL]

### AT+GPIO 查询/设置本地GPIO

**参数格式：**

> =`[GROUP:PIN]` , `[TTL]`

- `STATE` 状态，值范围：[TL, TH]，分别是低电平和高电平；

**查询端口的电平状态**：

> AT+GPIO=[GROUP:PIN]

返回：

> +GPIO= [GROUP:PIN] , [TTL]

**设置端口电平状态**：

> AT+GPIO=[GROUP:PIN], [TL, TH]

示例：
> 1: AT+GPIO=0:1,TL // 设置P0_1端口为低电平
> 2: AT+GPIO=1:4,TH // 设置P1_4端口为高电平

返回：

> +GPIO=`OK` // 成功
> +GPIO=`ERR,IODIR` // 状态错误：GPIO端口非输出模式

### AT+RGPIO 查询/设置远程GPIO


### AT+IOPULL 查询/设置本地端口的输入模式

**参数格式：**

> = `[GROUP]`, `[PULL]`

- `PULL` 输入模式，值范围：[PU, PD]：
  1. `PU` PullUp，上拉；
  2. `PD` PullDown，下拉；

查询：

> AT+IOPULL=[GRUOP]
> e.g: AT+IOPULL=0,PU

返回：

> +IOPULL=[GROUP]:[PULL]
> e.g: +IOPULL=0:PU

设置：

> AT+IOPULL=[GRUOP],[PULL]
> e.g: AT+IOPULL=0,PD

返回：

> +IOPULL=OK

### AT+IODIR 查询/设置本地端口输入输出

**参数格式：**

> = `[GROUP:PIN]`, `[DIR]`, `[INMODE]`

- `DIR` IO方向，值范围：[DI, DO]：
  1. `DI` DirInput 输入方向
  2. `DO` DirOutput 输出方向

- `INMODE` 在IO方向不输入时生效，表示端口输入模式，范围: [MP, MN]
  1. `MP` ModePull 上拉下拉模式。需要在 AT+INPULL 指令中配置；
  2. `NM` ModeNone 三态（高阻）模式。

### AT+RIODIR 查询/设置远程端口输入输出

> 通过点对点通讯实现

### AT+INT 查询/设置本地端口中断

**参数格式：**

> =`[PIN] `, `[ENABLE] `, `[TRIGGER]`

- `PIN` 引脚编号；


- `ENABLE` 使能，值范围：[EN, DIS]，分别是禁用和启用；
- `STATE` 触发中断的电平状态，值范围：[PU, PD]，分别是上拉UP和下拉DOWN，默认为上拉模式；

**中断状态消息格式**

> +INT=`[MAC]`, `[PIN]`, `[TRIGGER]`

- `MAC` 触发中断设置MAC地址；
- `PIN` 触发端口；
- `TRIGGER` 触发状态；

> +INT=A1B2C3D4E5F6A7B8, 5, PD

**查询：**

> AT+INT=`[PIN]`

**返回示例：**

> +INT=`3`, `EN`, `PD`
>
> +INT=`3`, `DIS`

**设置：**

> AT+INT=`3`, `EN`, `PU`
>
> AT+INT=`3`, `DIS`

**返回：**

> +INT=`OK`

核心代码实现：

```c
// IENx 设置端口组中断使能；
// PxIEN 设置具体引肢中断使能；
// PICTL 中断触发方式；
// EA 总中断使能；
IEN1 |= 0x10; // 设置P1中断使能；
P1IEN |= 0x04; // 设置P1_2中断使能；
PICTL |= 0x02; // 设置P1_0 - P1_3 下降沿触发；
EA = 1; // 总中断使能

#pragma vector = P1INT_VECTOR
__interrupt void int1Service() {
  // TODO
  // 必须清除中断标记位
  P1IFG &= ~0x04; // 清除P1_2中断标记位；
  P1IF = 0; // 清除P1端口组标记位；
}
```



### AT+RINT 查询/设置远程端口中断

> 通过点对点通讯实现

### AT+PWM 查询/设置本地PWM

**参数格式：**

> =`[PIN] `, `[PWN] `, 

### AT+RPWN 查询/设置远程PWM

> 通过点对点通讯实现

### AT+ADC 查询/设置本地ADC

**参数格式：**

> =`[PIN] `



### AT+RADC 查询/设置远程ADC

> 通过点对点通讯实现



### AT+CNF_PWM 设置PWM波周期

**参数格式：**

> =`[PWM_PERIOD] `, 

