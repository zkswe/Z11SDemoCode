/*
 * CommDef.h
 *
 *  Created on: 2016-2-15
 *      Author: guoxs
 */

#ifndef _UART_COMMDEF_H_
#define _UART_COMMDEF_H_

#include <stdint.h>

#ifndef BYTE
typedef unsigned char	BYTE;
#endif
#ifndef UINT
typedef unsigned int	UINT;
#endif
#ifndef UINT16
typedef unsigned short  UINT16;
#endif

#ifndef MAKEWORD
#define MAKEWORD(low, high)		(((BYTE)(low)) | (((BYTE)(high)) << 8))
#endif

#ifndef LOBYTE
#define LOBYTE(l)           ((BYTE)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)           ((BYTE)(l >> 8))
#endif

#ifndef TABLESIZE
#define TABLESIZE(table)    (sizeof(table)/sizeof(table[0]))
#endif


// 需要打印协议数据时，打开以下宏
#define DEBUG_PRO_DATA


/* SynchFrame DataLen Data  */
/*     2Byte 	2Byte  N Byte   */
// 无CheckSum情况下最小长度: 2 + 2 = 4


#define DATA_PACKAGE_MIN_LEN		4

// 同步帧头
#define CMD_HEAD1	0xFF
#define CMD_HEAD2	0x55

#endif /* _UART_COMMDEF_H_ */
