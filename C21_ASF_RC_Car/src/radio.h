/*
 * radio.h
 *
 * Created: 5/23/2016 6:39:12 PM
 *  Author: brian.tate
 */ 


#ifndef RADIO_H_
#define RADIO_H_
	#include <asf.h>
// 	#include "phy.h"
// 	#include "nwk.h"
	#include "sysTimer.h"

	#ifdef NWK_ENABLE_SECURITY
	#define APP_BUFFER_SIZE     (NWK_MAX_PAYLOAD_SIZE - NWK_SECURITY_MIC_SIZE)
	#else
	#define APP_BUFFER_SIZE     NWK_MAX_PAYLOAD_SIZE
	#endif

	//prototypes
	void radioDataConf(NWK_DataReq_t *req);
	void radioSendData(uint8_t *data, uint8_t size);
	bool radioDataInd(NWK_DataInd_t *ind);
	void radioTimerHandler(SYS_Timer_t *timer);
	void radioInit(void);

#endif /* RADIO_H_ */