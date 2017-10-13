//
//  bits.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/13.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef bits_h
#define bits_h

#define BITM_0 0x01
#define BITM_1 0x02
#define BITM_2 0x04
#define BITM_3 0x08
#define BITM_4 0x10
#define BITM_5 0x20
#define BITM_6 0x40
#define BITM_7 0x80

#define MKBIT_1_OF(N, MASK)      N |= MASK

#define BIT1_OF0(N)      N |= BITM_0
#define BIT1_OF1(N)      N |= BITM_1
#define BIT1_OF2(N)      N |= BITM_2
#define BIT1_OF3(N)      N |= BITM_3
#define BIT1_OF4(N)      N |= BITM_4
#define BIT1_OF5(N)      N |= BITM_5
#define BIT1_OF6(N)      N |= BITM_6
#define BIT1_OF7(N)      N |= BITM_7

#define BIT0_OF0(N)      N &= ~BITM_0
#define BIT0_OF1(N)      N &= ~BITM_2
#define BIT0_OF2(N)      N &= ~BITM_3
#define BIT0_OF3(N)      N &= ~BITM_4
#define BIT0_OF4(N)      N &= ~BITM_5
#define BIT0_OF5(N)      N &= ~BITM_6
#define BIT0_OF6(N)      N &= ~BITM_7
#define BIT0_OF7(N)      N &= ~BITM_7

#define IS_BIT1_OF0(N)       (N & 1 << 0)
#define IS_BIT1_OF1(N)       (N & 1 << 1)
#define IS_BIT1_OF2(N)       (N & 1 << 2)
#define IS_BIT1_OF3(N)       (N & 1 << 3)
#define IS_BIT1_OF4(N)       (N & 1 << 4)
#define IS_BIT1_OF5(N)       (N & 1 << 5)
#define IS_BIT1_OF6(N)       (N & 1 << 6)
#define IS_BIT1_OF7(N)       (N & 1 << 7)

#endif /* bits_h */
