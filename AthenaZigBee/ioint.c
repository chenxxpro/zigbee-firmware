#include "cc2530.h"
#include "ioint.h"

TTLListener _onTTLChangedListener;

// Set Listener
void setIOINTListener(TTLListener listener) {
	_onTTLChangedListener = listener;
	
}

// Init
void iointInit() {

}

#ifndef _WIN32
#pragma vector = P1INT_VECTOR 
__interrupt void Int1_Sevice() {
	/*��������ű�־λ��������˿ڱ�־λ������᲻�Ͻ����ж�*/
	P1IFG &= ~0x04;		//������P1_2���ŵı�־λ
	P1IF = 0;			//������P1�˿���ı�־λ 
	// onChanged(group, pin, ttl);
}

#endif // !_WIN32
