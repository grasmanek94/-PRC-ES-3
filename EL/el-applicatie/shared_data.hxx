#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <mqueue.h>     																	
#include <errno.h>      																	
#include <fcntl.h>      																	
#include <sys/types.h>
#include <sys/stat.h>

struct InputReport
{
	unsigned char messageType : 8;
	unsigned char packetSize : 8;
	bool DPAD_UP : 1;
	bool DPAD_DOWN : 1;
	bool DPAD_LEFT : 1;
	bool DPAD_RIGHT : 1;
	bool BTN_START : 1;
	bool BTN_BACK : 1;
	bool BTN_STICK_LEFT : 1;
	bool BTN_STICK_RIGHT : 1;
	bool BTN_LB : 1;
	bool BTN_RB : 1;
	bool BTN_LOGO : 1;
	bool UNUSED_00 : 1;
	bool BTN_A : 1;
	bool BTN_B : 1;
	bool BTN_X : 1;
	bool BTN_Y : 1;
	unsigned char TRIGGER_LEFT : 8;
	unsigned char TRIGGER_RIGHT : 8;
	short STICK_LEFT_X : 16;
	short STICK_LEFT_Y : 16;
	short STICK_RIGHT_X : 16;
	short STICK_RIGHT_Y : 16;
	int UNUSED_01 : 32;
	short UNUSED_02 : 16;
} __attribute__((packed));

enum LED_ACTION
{
	LED_OFF,
	LED_ALL_BLINKING,
	LED_FLASH_1,
	LED_FLASH_2,
	LED_FLASH_3,
	LED_FLASH_4,
	LED_ON_1,
	LED_ON_2,
	LED_ON_3,
	LED_ON_4,
	LED_ROTATING,
	LED_BLINKING,
	LED_SLOW_BLINKING,
	LED_ALTERNATING,
	MAX_LED_ACTIONS
};

enum Actions
{
	ACTION_LED,
	ACTION_RUMBLE
};

const size_t message_size = 3;
const size_t message_amount = 16;

InputReport* cgi_shm_create(int& shm_fd);
mqd_t cgi_mq_create(int mq_flags, int mq_maxmsg, int mq_msgsize);
mqd_t cgi_mq_open(mq_attr* obuf);
InputReport* cgi_shm_open(int& shm_fd);
#endif
