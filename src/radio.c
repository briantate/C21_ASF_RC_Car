/*
 * radio.c
 *
 * Created: 5/23/2016 6:38:42 PM
 *  Author: brian.tate
 */ 
 #include "radio.h"
 #include "trx_access.h"

 //structures
 static SYS_Timer_t radioTimer;
 static NWK_DataReq_t radioDataReq;
 static bool radioDataReqBusy = false;


 //functions
void radioDataConf(NWK_DataReq_t *req)
{
	radioDataReqBusy = false;
	(void)req;
}

void radioSendData(uint8_t *data, uint8_t size)
{

/*
	if (appDataReqBusy || 0 == appChannelBufferPtr) {
		return;
	}
*/
	if (radioDataReqBusy) {
//		puts("radio busy");
		return;
	}

	//memcpy(appDataReqBuffer, appUartBuffer, appUartBufferPtr);

	radioDataReq.dstAddr = 1 - APP_ADDR;
	radioDataReq.dstEndpoint = APP_ENDPOINT;
	radioDataReq.srcEndpoint = APP_ENDPOINT;
	radioDataReq.options = NWK_OPT_ENABLE_SECURITY;
	radioDataReq.data = data; //appDataReqBuffer; //
	radioDataReq.size = size;//sizeof(data); //appUartBufferPtr; //
	radioDataReq.confirm = radioDataConf;
	NWK_DataReq(&radioDataReq);
	
	printf("sending \n\r channel 0 value = %u\n\r channel 1 value = %u\n\r", data[0],data[1]);

	//appUartBufferPtr = 0;
	radioDataReqBusy = true;
	// port_pin_toggle_output_level(LED_0_PIN);
}

bool radioDataInd(NWK_DataInd_t *ind)
{
	/*for (uint8_t i = 0; i < ind->size; i++) {
		sio2host_putchar(ind->data[i]);
	}
	*/
	uint8_t ch0value = ind->data[0];
	uint8_t ch1value = ind->data[1];
	printf("received \n\r Channel 0 value = %u\n\r Channel 1 value = %u\n\r", ch0value, ch1value);
	// port_pin_toggle_output_level(LED_0_PIN);
	return true;
}

void radioTimerHandler(SYS_Timer_t *timer)
{
	//appSendData();
	(void)timer;
}

void radioInit(void)
{
	NWK_SetAddr(APP_ADDR);
	NWK_SetPanId(APP_PANID);
	PHY_SetChannel(APP_CHANNEL);
	#ifdef PHY_AT86RF212
	PHY_SetBand(APP_BAND);
	PHY_SetModulation(APP_MODULATION);
	#endif
	PHY_SetRxState(true);

	NWK_OpenEndpoint(APP_ENDPOINT, radioDataInd);

	radioTimer.interval = APP_FLUSH_TIMER_INTERVAL;
	radioTimer.mode = SYS_TIMER_INTERVAL_MODE;
	radioTimer.handler = radioTimerHandler;

//	uint8_t value = trx_reg_read(0x1d);//VERSION_NUM_REG (0x1D) = 0x03  -- PART_NUM_REG(0x1C) = 0x07
//	printf("VERSION_NUM_REG = %u", value);
}

