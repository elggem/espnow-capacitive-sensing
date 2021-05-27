/*
Original Author: Etienne Arlaud
Modified by: Ralf Mayet

Licensed under BSD-3
*/

#include <stdint.h>
#include <stdio.h>
#include <string>

#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

#include <thread>

#include "ESPNOW_manager.h"
#include "ESPNOW_types.h"

using namespace std;

typedef struct struct_touch_message {
    int touches[8];
} struct_touch_message;

struct_touch_message inputData;

static uint8_t my_mac[6] = {0xE8, 0x94, 0xF6, 0x27, 0xD1, 0xE6};
static uint8_t broadcast_mac[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

ESPNOW_manager *handler;

void receive_callback(uint8_t src_mac[6], uint8_t *incomingData, int len) {
	// receive package
    memcpy(&inputData, incomingData, sizeof(inputData));
    for (int i=0;i<8;i++) {
    	printf("%i,", inputData.touches[i]);
    }
    printf("%i\n", inputData.touches[9]);
}

int main(int argc, char **argv) {
	assert(argc > 1);

	nice(-20);

	handler = new ESPNOW_manager(argv[1], DATARATE_24Mbps, CHANNEL_freq_1, my_mac, broadcast_mac, false);
	//handler->set_filter(my_mac, broadcast_mac);
	handler->set_recv_callback(&receive_callback);
	handler->start();

	while(1) {
	  usleep(1000*500);
	}

	handler->end();
}


