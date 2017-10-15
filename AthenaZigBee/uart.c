#include "cc2530.h"
#include "uart.h"

char _receivedBuff = 0;
uint _receivedIndex = 0;

// Check Command is AT
uint _isATCommand() {
	if (_receivedIndex == 0 && 'A' == _receivedBuff) {
		return 1;
	}
	else {
		return 0;
	}

	if (_receivedIndex == 1 && 'T' == _receivedBuff) {
		return 1;
	}
	else {
		return 0;
	}

	if (_receivedIndex == 2 && '+' == _receivedBuff) {
		return 1;
	}
	else {
		return 0;
	}

	return 1;
}

// Reset AT
uint _resetReceived() {
	_receivedBuff = 0;
	_receivedIndex = 0;
	return 0;
}


// Init UART
void uartInit() {
    PERCFG = 0x00;       // 位置1 P0口
    P0SEL = 0x3c;        // P0_2,P0_3,P0_4,P0_5用作串口,第二功能
    P2DIR &= ~0XC0;      // P0 优先作为UART0 ，优先级

    U0CSR |= 0x80;       // UART 方式
    U0GCR |= 11;         // U0GCR与U0BAUD配合
    U0BAUD |= 216;       // 波特率设为115200
    UTX0IF = 0;          // UART0 TX 中断标志初始置位1  （收发时候）
    U0CSR |= 0X40;       // 允许接收
    IEN0 |= 0x84;        // 开总中断，接收中断
}

// Send Data
void uartSend(char* data, const uint dataSize) {
	// Disabled Reciever when sending..
    U0CSR &= ~0x40;
    int i;
    for (i = 0; i < dataSize; i++) {
        char c = *data++;
        U0DBUF = c;
        while (UTX0IF == 0);
        UTX0IF = 0;
    }
    // Enable Receiver
    U0CSR |= 0x40;
}

// Receive data
uint uartReceive(char* buff) {
	// Check: AT+
	if (_isATCommand()) {
		if ('#' != _receivedBuff) {
			buff[_receivedIndex++] = _receivedBuff;
		}
		else {
			const uint len = _receivedIndex;
			_resetReceived();
			return len;
		}
	}
	else {
		return _resetReceived();
	}
}

#ifndef _WIN32

#pragma vector = URX0_VECTOR
__interrupt void UART0_ISR(void)
{
	// 清中断标志
	URX0IF = 0;
	_receivedBuff = U0DBUF;
}

#endif // !_WIN32
