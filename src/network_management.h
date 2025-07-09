/*
 * network_management.h
 *
 * Created: 10/23/2018 11:24:58 AM
 *  Author: Brian Tate
 */ 


#ifndef NETWORK_MANAGEMENT_H_
#define NETWORK_MANAGEMENT_H_

#include "miwi_api.h"
#include <stdbool.h>
//#include <stdint.h>

#define NETWORK_FREEZER_OFF false
#define NETWORK_FREEZER_ON true

#define NETWORK_ROLE true //true = PAN coordinator, false = edge node

//void NetworkInit(bool freezer_enable, bool networkRole);
void NetworkInit(bool freezer_enable, bool networkRole, PacketIndCallback_t ReceivedDataIndication);

void NetworkTasks(void);

#endif /* NETWORK_MANAGEMENT_H_ */