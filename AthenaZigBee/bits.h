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

// Set bits to 1 with mask
#define SETBIT1_OF(N, BM)	(N |= BM)

// Set bits to 0 with mask
#define SETBIT0_OF(N, BM)	(N &= ~BM)

// Check if bits is 1 of index
#define IS_BIT1_OF(N, I)	(N & 1 << I)

#endif /* bits_h */
