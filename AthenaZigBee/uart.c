#include "cc2530.h"
#include "uart.h"

UartListener _receivedListener;

// Init UART
void uartInit() {
#ifndef _WIN32
	// Wait System Clock Stable
	CLKCONCMD &= ~0x40;
	while (CLKCONSTA & 0x40);
	CLKCONCMD &= ~0x47;

    PERCFG = 0x00;       // λ��1 P0��
    P0SEL = 0x3c;        // P0_2,P0_3,P0_4,P0_5��������,�ڶ�����
    P2DIR &= ~0XC0;      // P0 ������ΪUART0 �����ȼ�

    U0CSR |= 0x80;       // UART ��ʽ
    U0GCR |= 11;         // U0GCR��U0BAUD���
    U0BAUD |= 216;       // ��������Ϊ115200
    UTX0IF = 0;          // UART0 TX �жϱ�־��ʼ��λ1  ���շ�ʱ��
    U0CSR |= 0X40;       // �������
    IEN0 |= 0x84;        // �����жϣ������ж�
#endif // !_WIN32
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

// Listener for received chars
void uartListener(UartListener listener) {
	_receivedListener = listener;
}

#ifndef _WIN32

#pragma vector = URX0_VECTOR
__interrupt void UART0_ISR(void)
{
	// Reset Flag
	URX0IF = 0;
	//_receivedBuff = U0DBUF;
	_receivedListener(U0DBUF);
}

#endif // !_WIN32
