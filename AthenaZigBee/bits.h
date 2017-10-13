//
//  bits.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/13.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef bits_h
#define bits_h

#define SET_BIT0_TO_1(N)      N |= 0x01
#define SET_BIT1_TO_1(N)      N |= 0x02
#define SET_BIT2_TO_1(N)      N |= 0x04
#define SET_BIT3_TO_1(N)      N |= 0x08
#define SET_BIT4_TO_1(N)      N |= 0x10
#define SET_BIT5_TO_1(N)      N |= 0x20
#define SET_BIT6_TO_1(N)      N |= 0x40
#define SET_BIT7_TO_1(N)      N |= 0x80

#define SET_BIT0_TO_0(N)      N &= ~0x01
#define SET_BIT1_TO_0(N)      N &= ~0x02
#define SET_BIT2_TO_0(N)      N &= ~0x04
#define SET_BIT3_TO_0(N)      N &= ~0x08
#define SET_BIT4_TO_0(N)      N &= ~0x10
#define SET_BIT5_TO_0(N)      N &= ~0x20
#define SET_BIT6_TO_0(N)      N &= ~0x40
#define SET_BIT7_TO_0(N)      N &= ~0x80

#define IS_BIT0_IS_1(N)       (N & 1 << 0)
#define IS_BIT1_IS_1(N)       (N & 1 << 1)
#define IS_BIT2_IS_1(N)       (N & 1 << 2)
#define IS_BIT3_IS_1(N)       (N & 1 << 3)
#define IS_BIT4_IS_1(N)       (N & 1 << 4)
#define IS_BIT5_IS_1(N)       (N & 1 << 5)
#define IS_BIT6_IS_1(N)       (N & 1 << 6)
#define IS_BIT7_IS_1(N)       (N & 1 << 7)

#define IS_BIT_0(N, pos)      0 == N
#define IS_BIT_1(N, pos)      1 == N

#define SET_BIT_0(N, pos)     N = 0
#define SET_BIT_1(N, pos)     N = 1


#endif /* bits_h */
