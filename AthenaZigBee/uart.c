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
    PERCFG = 0x00;       // λ��1 P0��
    P0SEL = 0x3c;        // P0_2,P0_3,P0_4,P0_5��������,�ڶ�����
    P2DIR &= ~0XC0;      // P0 ������ΪUART0 �����ȼ�

    U0CSR |= 0x80;       // UART ��ʽ
    U0GCR |= 11;         // U0GCR��U0BAUD���
    U0BAUD |= 216;       // ��������Ϊ115200
    UTX0IF = 0;          // UART0 TX �жϱ�־��ʼ��λ1  ���շ�ʱ��
    U0CSR |= 0X40;       // �������
    IEN0 |= 0x84;        // �����жϣ������ж�
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
	// ���жϱ�־
	URX0IF = 0;
	_receivedBuff = U0DBUF;
}

#endif // !_WIN32
