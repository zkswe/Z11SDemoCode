/*
 * ProtocolSender.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: guoxs
 */

#include "uart/ProtocolSender.h"
#include "uart/UartContext.h"
#include "uart/ProtocolData.h"
#include "utils/Log.h"
#include <stdio.h>


/**
 * 需要根据协议格式进行拼接，以下只是个模板
 */
bool sendProtocol(const BYTE *pData, int len) {
	BYTE dataBuf[DATA_LEN + DATA_PACKAGE_MIN_LEN];
	// 判断数据长度是否超出限制
	if (len > DATA_LEN) {
		LOGE("The data length over the limit!!!");
		return false;
	}

	dataBuf[0] = CMD_HEAD1;
	dataBuf[1] = CMD_HEAD2;			// 同步帧头

	dataBuf[2] = HIBYTE(len);
	dataBuf[3] = LOBYTE(len);
	UINT frameLen = 4;

	// 数据
	for (int i = 0; i < len; ++i) {
		dataBuf[frameLen] = pData[i];
		frameLen++;
	}

	return UARTCONTEXT->send(dataBuf, frameLen);
}
