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
	/*先清除引脚标志位，再清除端口标志位，否则会不断进入中断*/
	P1IFG &= ~0x04;		//软件清除P1_2引脚的标志位
	P1IF = 0;			//软件清除P1端口组的标志位 
	// onChanged(group, pin, ttl);
}

#endif // !_WIN32
