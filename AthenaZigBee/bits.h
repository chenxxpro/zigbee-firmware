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

// 将指定数值N，和BitMask，设置对应位为 1
#define SETBIT1_OF(N, BM)      N |= BM

// 将指定数值N，和BitMask，设置对应位为 0
#define SETBIT0_OF(N, BM)      N &= ~BM

// 指定数值N，和位序号I，返回其对应位是否为 1
#define IS_BIT1_OF(N, I)       (N & 1 << I)

#endif /* bits_h */
