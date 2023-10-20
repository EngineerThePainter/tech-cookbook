/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdint.h>

struct Header {
	int8_t version_ihl_;
	int8_t dscp_ecn_;
	int16_t total_length_;
	int16_t identification_;
	int16_t flags_fragment_offset_;
	int8_t time_to_live_;
	int8_t protocol_;
	int16_t header_checksum_;
	int32_t source_ip_address_;
	int32_t destination_ip_address_;
	int32_t options_[4];
} __attribute__((packed));

#include <assert.h>
#include <stdio.h>

#include "stm32f0xx.h"
#include "stm32f0xx_nucleo.h"

int main(void)
{
	struct Header header;
	printf("%d\n", sizeof(header));
	for (;;) {}
}
