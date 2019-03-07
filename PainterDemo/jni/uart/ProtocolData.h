/*
 * ProtocolData.h
 *
 *  Created on: Sep 7, 2017
 *      Author: guoxs
 */

#ifndef _UART_PROTOCOL_DATA_H_
#define _UART_PROTOCOL_DATA_H_

#include <string>
#include "CommDef.h"

#define DATA_LEN 256	// 数据块的最大长度，不要超过2K

// 数据块定义(用户有效数据)
#pragma pack(push,1)
typedef struct {
	// 用户自定义数据
	uint8_t    angle;		// 仪表指针角度
} SProtocolData;
#pragma pack(pop)

#endif /* _UART_PROTOCOL_DATA_H_ */
