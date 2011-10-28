/****************************************************************************
*  This file is part of the HYDRA application.
*
*  Copyright (c) 2004 by Michael Fischer. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*  
*  1. Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the distribution.
*  3. Neither the name of the author nor the names of its contributors may 
*     be used to endorse or promote products derived from this software 
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
*  SUCH DAMAGE.
*
****************************************************************************
*
*  Name:    tftp.c
*
*  Remarks: This is the TFTP server for our XFLASH file system.  
*           The server supports only PUT, and only for ONE file
*           "xflash.bin". For more information about TFTP, take a 
*           look in TFTP-Protokoll RFC 1350.
*
*  History:
*
*  23.10.04  mifi   First Version
****************************************************************************/
#define __TFTP_C__

#include <stdio.h>
#include <string.h>
#include <io.h>
#include <ctype.h>
#include <fcntl.h>

#include <sys/thread.h>
#include <sys/timer.h>
#include <sys/heap.h>
#include <sys/confnet.h>
#include <sys/socket.h>
#include <sys/version.h>
#include <net/if_var.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tftp.h"

/*
 * some types to use Windows like source
*/
typedef char          CHAR;     /* 8-bit signed data    */
typedef unsigned char BYTE;     /* 8-bit unsigned data  */
typedef unsigned short WORD;    /* 16-bit unsigned data */
typedef long           LONG;    /* 32-bit signed data   */
typedef unsigned long ULONG;    /* 32-bit unsigned data */
typedef unsigned long DWORD;    /* 32-bit unsigned data */

typedef char          RESULT;

/*
 * some define for the BSD files
 */
typedef unsigned char  u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned long  u_int32_t;

#define FALSE           0
#define TRUE            1
#define OK              0
#define ERROR           -1

#define UNUSED_VAR(_x)  if (_x) {}

/**************************************************************************
* Some WORD, BYTE macro's
***************************************************************************/
#define HIBYTE(_a) ((((WORD)(_a)) >> 8) & 0x00FF)
#define LOBYTE(_a) (((WORD)(_a)) & 0x00FF)

#define HIWORD(_a) ((((DWORD)(_a)) >> 16) & 0xFFFF)
#define LOWORD(_a) (((DWORD)(_a)) & 0xFFFF)

#define SWAP(_a)	 ((LOBYTE((_a)) << 8) | HIBYTE((_a)))

/*=========================================================================*/
/*  DEFINE: All Structures and Common Constants                            */
/*=========================================================================*/
/*
 * We will support only the filename
 * FLASH_FILE_NAME, in our case it is
 * xflash.bin.
 */
#define FLASH_FILE_NAME       "xflash.bin"
#define OPEN_FILE_NAME        "XFLASH:xflash.bin"
#define FLASH_MODE            "octet"

/*
 * Define some timeouts here
 */
#define UDP_RX_TIMEOUT_MS     2000
#define CON_TIMEOUT_MS        10000
#define MAX_CON_TIMOUT        5 // (20000 / CON_TIMEOUT_MS)        

#define TFTP_UDP_PORT         69
#define TFTP_RX_DATA_SIZE     512 + 32
#define TFTP_TX_DATA_SIZE     128

#define TFTP_MAX_DATA_SIZE    512

#define TFTP_RRQ              1    
#define TFTP_WRQ              2    
#define TFTP_DATA             3    
#define TFTP_ACK              4    
#define TFTP_ERROR            5    

/*************************************************************************/
/*                      Error Codes see RFC1350                          */
/*************************************************************************/
#define TFTP_NO_ERROR                 255
#define TFTP_ERROR_IN_USE             0  /* TFTP-Connection in use.           */
#define TFTP_ERROR_FILE_NOT_FOUND     1  /* File not found.                   */
#define TFTP_ERROR_ACCESS_VIOLATION   2  /* Access violation.                 */
#define TFTP_ERROR_DISK_FULL          3  /* Disk full or allocation exceeded. */
#define TFTP_ERROR_ILLEGAL_OPERATION  4  /* Illegal TFTP operation.           */
#define TFTP_ERROR_UNKNOWN_TRANSFER   5  /* Unknown transfer ID.              */
#define TFTP_ERROR_FILE_EXIST         6  /* File already exists.              */
#define TFTP_ERROR_NO_SUCH_USER       7  /* No such user.                     */
#define TFTP_ERROR_NO_ASCII           8  /* No ASCII transfer mode            */
#define TFTP_ERROR_WRONG_BLOCK        9  /* Wrong block number                */
#define TFTP_ERROR_WRITE_ERROR       10  /* Write Flash-ROM ERROR.            */
#define TFTP_MAX_ERROR               11

static char tftp_err_msg[TFTP_MAX_ERROR][40] =
{
  {"TFTP-Connection in use."},
  {"File not found."},                  
  {"Access violation."},                
  {"Disk full or allocation exceeded."},
  {"Illegal TFTP operation."},          
  {"Unknown transfer ID."},             
  {"File already exists."},             
  {"No such user."},
  {"\"netascii\" mode not supported."},
  {"wrong block number."},
  {"Write Flash-ROM ERROR."}
};

typedef enum {
  TFTP_CLOSE  = 0x0000,
  TFTP_OPEN   = 0x0001
} TFTP_STATUS;

typedef struct _error_packet {
  WORD wOpcode;
  WORD wErrorNumber;
  char ErrorMessage;
} ERROR_PACKET;

typedef struct _ack_packet {
  WORD wOpcode;
  WORD wBlockNumber;
} ACK_PACKET;

typedef struct _data_header {
  WORD wOpcode;
  WORD wBlockNumber;
} DATA_HEADER;

typedef struct _data_packet {
  DATA_HEADER Header;
  char        Data[TFTP_MAX_DATA_SIZE];
} DATA_PACKET;

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Data                                   */
/*=========================================================================*/

/*
 * We will use here some "file global" data.
 * Therfore we can accept only one connection,
 * but the code is smaller, and ONE is adequate.
 */
static BYTE       *pTFTPRxData    = NULL;
static BYTE       *pTFTPTxData    = NULL;

static TFTP_STATUS  ServerStatus  = TFTP_CLOSE;
static BYTE        bConTimeout    = 0;
static UDPSOCKET   *Socket;
static DWORD       dDestAddress;
static WORD        wDestPort;
static WORD        wNextBlockNumber;
static int         hFile = -1;

/*=========================================================================*/
/*  DEFINE: Definition of all local Procedures                             */
/*=========================================================================*/
/***************************************************************************/
/*  OpenServer                                                             */
/*                                                                         */
/*  In    : none                                                           */
/*  Out   : none                                                           */
/*  Return: none                                                           */
/***************************************************************************/
static void OpenServer (void)
{
  ServerStatus = TFTP_OPEN;  

  hFile = _open((char*)OPEN_FILE_NAME, _O_BINARY | _O_WRONLY);
} /* OpenServer */

/***************************************************************************/
/*  CloseServer                                                            */
/*                                                                         */
/*  In    : error cause                                                    */
/*  Out   : none                                                           */
/*  Return: none                                                           */
/***************************************************************************/
static void CloseServer (BYTE bError)
{
  UNUSED_VAR(bError);
   
  ServerStatus = TFTP_CLOSE;
   
  if (hFile != -1) {
    _close(hFile);
  }
} /* CloseServer */

/***************************************************************************/
/*  SendError                                                              */
/*                                                                         */
/*  Send an ERROR to the client.                                           */
/*                                                                         */
/*  In    : error cause, dest address and port                             */
/*  Out   : none                                                           */
/*  Return: none                                                           */
/***************************************************************************/
static void SendError (BYTE bCause, DWORD dDestAddress, WORD wDestPort)
{
  ERROR_PACKET *pError  = (ERROR_PACKET *)pTFTPTxData;
  char         *pErrorMessage;  
  int           nStrlen = strlen(tftp_err_msg[bCause]);
  int           nPacketSize;
  
  pError->wOpcode      = htons(TFTP_ERROR);
  pError->wErrorNumber = htons(TFTP_ERROR_ILLEGAL_OPERATION);
  
  pErrorMessage = &(pError->ErrorMessage);
  memcpy(pErrorMessage, tftp_err_msg[bCause], nStrlen+1);
  
  nPacketSize = sizeof(ERROR_PACKET) + nStrlen;
  
  NutUdpSendTo(Socket, dDestAddress, wDestPort, pError, nPacketSize);
} /* SendError */

/***************************************************************************/
/*  SendACK                                                                */
/*                                                                         */
/*  Send an ACK back to the client.                                        */
/*                                                                         */
/*  In    : none                                                           */
/*  Out   : none                                                           */
/*  Return: none                                                           */
/***************************************************************************/
static void SendACK (void)
{
  ACK_PACKET *pACK  = (ACK_PACKET *)pTFTPTxData;
  
  pACK->wOpcode      = htons(TFTP_ACK);
  pACK->wBlockNumber = htons(wNextBlockNumber);
  
  NutUdpSendTo(Socket, dDestAddress, wDestPort, pACK, sizeof(ACK_PACKET));
  
  bConTimeout = 0;
} /* SendACK */

/***************************************************************************/
/*  OpenTFTPServer                                                         */
/*                                                                         */
/*  Open the TFTP server.                                                  */
/*  If the server is already in use, return an error. We support only one  */
/*  connection at the same time. This server is only for the xflash        */
/*  filesystem. Therefore we support only PUT, octet and the filename      */
/*  "xflash.bin".                                                          */
/*                                                                         */
/*  In    : source address and port, udp packet                            */
/*  Out   : none                                                           */
/*  Return: error code                                                     */
/***************************************************************************/
static BYTE OpenTFTPServer (DWORD dAddress, WORD wPort, BYTE *pUDPPacket)
{
  int   i;
  BYTE  bTFTPError = TFTP_NO_ERROR;  
  char *pChar      = (char*)&pUDPPacket[sizeof(WORD)]; /* jump over the opcode */
  BYTE  bLen;
  
  if (ServerStatus == TFTP_OPEN) {
    /* 
     * We support only ONE connection
     */
    bTFTPError = TFTP_ERROR_IN_USE;
  } else {
    /*
     * Check if it is the correct name and mode
     */
    
    /* Check name */ 
    bLen = strlen(pChar);
    for(i=0; i<bLen ; i++) {
      pChar[i] = tolower(pChar[i]); 
    }  
    if (strcmp(pChar, (char*)FLASH_FILE_NAME) != 0) {
      bTFTPError = TFTP_ERROR_FILE_NOT_FOUND;      
    }
    
    /* Check mode */
    pChar += (bLen + 1);
    bLen = strlen(pChar);
    for(i=0; i<bLen ; i++) {
      pChar[i] = tolower(pChar[i]); 
    }  
    if (strcmp(pChar, (char*)FLASH_MODE) != 0) {
      bTFTPError = TFTP_ERROR_NO_ASCII;      
    }
    
    if (bTFTPError == TFTP_NO_ERROR) {
      OpenServer();  
      dDestAddress     = dAddress;
      wDestPort        = wPort;
      wNextBlockNumber = 0;
      bConTimeout      = 0;
      SendACK();    
      wNextBlockNumber++;
    }
  }  
  
  return (bTFTPError);
} /* OpenTFTPServer */

/***************************************************************************/
/*  RxData                                                                 */
/*                                                                         */
/*  Receive the data from the client.                                      */
/*                                                                         */
/*  In    : UDP data packet and packet size                                */
/*  Out   : none                                                           */
/*  Return: error code                                                     */
/***************************************************************************/
static BYTE RxData (BYTE *pUDPPacket, WORD wPacketSize)
{
  BYTE         bTFTPError = TFTP_NO_ERROR;
  DATA_PACKET *pData      = (DATA_PACKET*)pUDPPacket;
  
  wPacketSize = wPacketSize - sizeof(DATA_HEADER);
  
  if (ServerStatus == TFTP_OPEN) {  
    /*
     * Check for duplicated packet
     */
    if (ntohs(pData->Header.wBlockNumber) < wNextBlockNumber) {
      SendACK();        
    } else {
      /*
       * If this packet is the next?
       */
      if (ntohs(pData->Header.wBlockNumber) == wNextBlockNumber) {
        /*
         * Now we can use these data
         */          
        if (hFile != -1) {
          _write(hFile, pData->Data, wPacketSize); 
        }  
          
        SendACK();
        wNextBlockNumber++;
                  
        if (wPacketSize < TFTP_MAX_DATA_SIZE) {
          CloseServer(bTFTPError);
        }      
      } else {
        bTFTPError   = TFTP_ERROR_WRONG_BLOCK;  
        CloseServer(bTFTPError);
      }
    }         
  } else {
    bTFTPError = TFTP_ERROR_IN_USE;
  }  
  
  return (bTFTPError);
} /* RxData */

/***************************************************************************/
/*  NutTFTP                                                                */
/*                                                                         */
/*  This is our thread.                                                    */
/*  Handle the incoming packet here.                                       */
/*                                                                         */
/*  In    : thread data                                                    */
/*  Out   : none                                                           */
/*  Return: none                                                           */
/***************************************************************************/
THREAD(NutTFTP, arg)
{
  BYTE       bTFTPError = TFTP_NO_ERROR;
  int        nPacketLen;
  WORD       wFromPort;
  DWORD      dFromAddress;
  WORD       *pOpcode;

  UNUSED_VAR(arg);
  
  /*
   * Create a socket.
   */
  while ((Socket = NutUdpCreateSocket(TFTP_UDP_PORT)) == 0)
    NutSleep(5000);
    
  pOpcode = (WORD*)pTFTPRxData;    
        
  for(;;) {
    nPacketLen = NutUdpReceiveFrom(Socket, &dFromAddress, &wFromPort, pTFTPRxData, TFTP_RX_DATA_SIZE, UDP_RX_TIMEOUT_MS);
    if (nPacketLen > 0) {
      switch (ntohs(*pOpcode)) {
      
        case TFTP_WRQ: {
          bTFTPError = OpenTFTPServer(dFromAddress, wFromPort, pTFTPRxData);
          break;
        }
        case TFTP_DATA: {
          bTFTPError = RxData(pTFTPRxData, (WORD)nPacketLen);
          break;
        }
        
        case TFTP_RRQ: {
          /*
           * We accept only PUT
           */
          bTFTPError = TFTP_ERROR_ILLEGAL_OPERATION;          
          break;
        }
        
        case TFTP_ACK: {
          /*
           * We get no ACK, because we accept only PUT
           */
          bTFTPError = TFTP_ERROR_ILLEGAL_OPERATION;          
          break;
        }
        case TFTP_ERROR: {
          /*
           * We get no ERROR, because we accept only PUT
           */
          bTFTPError = TFTP_ERROR_ILLEGAL_OPERATION;                            
          break;
        }
        
        default: {
          bTFTPError = TFTP_ERROR_ILLEGAL_OPERATION;
          break;
        }
      } /* end switch */
      
      /*
       * Check if we must send an error
       */
      if (bTFTPError != TFTP_NO_ERROR) {
        SendError(bTFTPError, dFromAddress, wFromPort);              
      }
      
    } else {
      /* timeout */
      bConTimeout++;
    } /* (nPacketLen > 0) */  
    
    if( (ServerStatus == TFTP_OPEN) && (bConTimeout >= MAX_CON_TIMOUT) ){
      bTFTPError = TFTP_ERROR_ILLEGAL_OPERATION;
      CloseServer(bTFTPError);
    }
    
  } /* end for */  
} /* NutTFTP */

/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/
/***************************************************************************/
/*  NutTFTPStart                                                           */
/*                                                                         */
/*  If we got some memory, we will start the TFTP server.                  */
/*                                                                         */
/*  In    : none                                                           */
/*  Out   : none                                                           */
/*  Return: none                                                           */
/***************************************************************************/
void NutTFTPStart (void)
{
  RESULT Error = OK;
  
  /*
   * Alloc the data for the TFTP server
   */
  pTFTPRxData = NutHeapAlloc(TFTP_RX_DATA_SIZE); 
  if (pTFTPRxData == NULL) {
    Error = ERROR;
  } else {
    pTFTPTxData = NutHeapAlloc(TFTP_TX_DATA_SIZE);
    if (pTFTPTxData == NULL) {
      Error = ERROR;
    }
  }  
  
  /*
   * Check if we got the memory
   */
  if (Error != OK) {
    if (pTFTPRxData != NULL) {
      NutHeapFree(pTFTPRxData);
    }
    if (pTFTPTxData != NULL) {
      NutHeapFree(pTFTPTxData);
    }
  } else {
    /*
     * Start out thread...
     */
    NutThreadCreate("TFTP", NutTFTP, 0, 640);  
  }  
} /* NutTFTPStart */

/*** EOF ***/
