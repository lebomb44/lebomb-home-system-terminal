/****************************************************************************
*  This file is part of the XFLASH device driver application.
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
*  Name:    xflash.c
*
*  Remarks: This file system is for an AT45DB041B.
*
*  History:
*
*  23.10.04  mifi   First Version
****************************************************************************/
#define __XFLASH_C__


#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>

#include <sys/heap.h>
#include <sys/event.h>
#include <sys/thread.h>
#include <sys/atom.h>
#include <sys/device.h>

#include "xflash.h"

/*=========================================================================*/
/*  DEFINE: All Structures and Common Constants                            */
/*=========================================================================*/
#define XFLASH_OK       0
#define XFLASH_ERROR    -1

#define WRITE_FILENAME  "xflash.bin"

/* 
 * SPI memory chip layout, see data sheet. 
 */
#define MAX_PAGE_SIZE       264
#define MAX_PAGE_COUNT      2048

/* 
 * SPI memory chip select, see schematics. 
 */
#define SPIMEM_CS_PORT      PORTB
#define SPIMEM_CS_DDR       DDRB
#define SPIMEM_CS           0x10


#define SPI_CS_LOW()        PORTB |= SPIMEM_CS
#define SPI_CS_HIGH()       PORTB &= ~SPIMEM_CS

typedef char          CHAR;     /* 8-bit signed data    */
typedef unsigned char BYTE;     /* 8-bit unsigned data  */
typedef unsigned short WORD;    /* 16-bit unsigned data */
typedef long           LONG;    /* 32-bit signed data   */
typedef unsigned long ULONG;    /* 32-bit unsigned data */
typedef unsigned long DWORD;    /* 32-bit unsigned data */

typedef char          RESULT;

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

typedef struct _xflash_header {
  BYTE bMagic1;
  BYTE bMagic2;
  WORD wVersion;
  WORD wMaxPages;   
} XFLASH_HEADER;

typedef struct _fhandle {
  DWORD  dFileSize;
  DWORD  dFilePointer;  
  WORD   wStartPage;
} FHANDLE;

typedef struct _size_page {
  DWORD dFileSize;
  WORD  wPage;
} SIZE_PAGE;

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Data                                   */
/*=========================================================================*/
static HANDLE hXFLASHSemaphore;

/*=========================================================================*/
/*  DEFINE: Definition of all local Procedures                             */
/*=========================================================================*/
/***************************************************************************/
/*  XFLASHLock                                                             */
/***************************************************************************/
static void XFLASHLock (void)
{
  NutEventWait(&hXFLASHSemaphore, 0);
} /* XFLASHLock */

/***************************************************************************/
/*  XFLASHFree                                                             */
/***************************************************************************/
static void XFLASHFree (void)
{
  NutEventPost(&hXFLASHSemaphore);
} /* XFLASHFree */

/***************************************************************************/
/*  FATSemaInit                                                            */
/***************************************************************************/
static void XFLASHSemaInit (void)
{
  NutEventPost(&hXFLASHSemaphore);
} /* XFLASHSemaInit */

/***************************************************************************/
/*  SpiByte                                                                */
/*                                                                         */
/*  Send a data byte over the SPI bus,                                     */
/*  at the same time a byte is read back                                   */
/***************************************************************************/ 
static BYTE SpiByte (BYTE bData)
{
  /*
   * Put the byte in the transmit register
   */ 
  SPDR = bData;                 
  
  /*
   * Wait for serial transfer is complete
   */
  while ((inb(SPSR) & 0x80) == 0);

  
  /*
   * Read the byte from the receive register
   */
  return (SPDR);               
} /* SpiByte */ 

/***************************************************************************/
/*  ReadStatus                                                             */
/*                                                                         */
/*  Read the status from the flash memory.                                 */
/***************************************************************************/
BYTE SpiMemStatus(void)
{
  BYTE bData;

  SPI_CS_LOW();
  
  SpiByte(0xD7);
  bData = SpiByte(0);
  
  SPI_CS_HIGH();
  
  return (bData);
} /* SpiMemStatus */

/***************************************************************************/
/*  WriteBlock                                                             */
/*                                                                         */
/*  Write a block with the size wSize to the spi bus                       */
/***************************************************************************/
static void WriteBlock (BYTE *pBuffer, WORD wSize)
{
  while(wSize--) {
    outb(SPDR, *pBuffer);
    pBuffer++;
    while ((inb(SPSR) & 0x80) == 0);
  }
} /* WriteBlock */

/***************************************************************************/
/*  ReadBlock                                                              */
/*                                                                         */
/*  Read a block with the size wSize from the spi bus.                     */
/***************************************************************************/
static void ReadBlock (BYTE *pBuffer, WORD wSize)
{
  while(wSize--) {
    outb(SPDR, 0x00);
    while ((inb(SPSR) & 0x80) == 0);
    *pBuffer = inb(SPDR);
    pBuffer++;
  }
} /* ReadBlock */

/***************************************************************************/
/*  PageWrite                                                              */
/*                                                                         */
/*  Write a block of data with the size of wSize to the page wPage.        */
/***************************************************************************/
static int PageWrite (WORD wPage, BYTE *pBuffer, WORD wSize, WORD wOffset)
{
  BYTE bByte1;
  BYTE bByte2;
  BYTE bByte3;
  
  bByte1 = LOBYTE(wPage >> 7);
  
  bByte2 = LOBYTE(wPage << 1);  
  if (wOffset & 0x100) {
    bByte2 |= 0x01;
  }
  
  bByte3 = LOBYTE(wOffset);
  
  SPI_CS_LOW();

  /* Select mode */
  SpiByte(0x82);
  SpiByte(bByte1);
  SpiByte(bByte2);
  SpiByte(bByte3);
  
  /* Write data */
  WriteBlock(pBuffer, wSize);

  SPI_CS_HIGH();  

  while((SpiMemStatus() & 0x80) == 0);

  return (XFLASH_OK);
} /* PageWrite */

/***************************************************************************/
/*  PageRead                                                               */
/*                                                                         */
/*  Read a block of data with the size of wSize from the page wPage.       */
/***************************************************************************/
static int PageRead (WORD wPage, BYTE *pBuffer, WORD wSize, WORD wOffset)
{
  BYTE bByte1;
  BYTE bByte2;
  BYTE bByte3;    
  
  bByte1 = LOBYTE(wPage >> 7);
  
  bByte2 = LOBYTE(wPage << 1);  
  if (wOffset & 0x100) {
    bByte2 |= 0x01;
  }
  
  bByte3 = LOBYTE(wOffset);

  while((SpiMemStatus() & 0x80) == 0);

  SPI_CS_LOW();  

  SpiByte(0xE8);
  SpiByte(bByte1);
  SpiByte(bByte2);
  SpiByte(bByte3);
  SpiByte(0x00);
  SpiByte(0x00);
  SpiByte(0x00);
  SpiByte(0x00);
  ReadBlock(pBuffer, wSize);

  SPI_CS_HIGH();  

  return (XFLASH_OK);
} /* PageRead */

/***************************************************************************/
/*  FindFile                                                               */
/***************************************************************************/
static NUTFILE *FindFile(NUTDEVICE *pDevice, char *pSearchFile)
{  
  int         i;
  NUTFILE   *hNUTFile = (NUTFILE *)XFLASH_ERROR;
  FHANDLE   *hFile;
  SIZE_PAGE  SizePage;
  BYTE      *pBuffer;
  DWORD      dReadPointer = 0;
  WORD       wPage;
  WORD       wPageOffset;
  WORD       wSearchLen = strlen(pSearchFile);
  WORD       wDirLen;
  WORD       wJumpRead;
  BYTE       bFound;

  /*
   * Create the directory buffer
   */
  pBuffer = (BYTE*)NutHeapAlloc(MAX_PAGE_SIZE);
  if (pBuffer != NULL) {
  
    /*
     * Jump over the XFLASH header
     */
    dReadPointer = sizeof(XFLASH_HEADER); 
    
    while (1) {
      /*
       * Read the len of the filename
       */
      wPage        = (WORD)(dReadPointer / MAX_PAGE_SIZE);
      wPageOffset  = (WORD)(dReadPointer % MAX_PAGE_SIZE);            
      PageRead(wPage, (char*)&wDirLen, sizeof(WORD), wPageOffset);
      dReadPointer += sizeof(WORD);
      
      if (wDirLen == 0) {
        /* end of directory */
        NutHeapFree(pBuffer);
        break;
      }
      
      if (wDirLen == wSearchLen) {
        /*
         * Read the filename and SIZE_PAGE
         */
        wPage        = (WORD)(dReadPointer / MAX_PAGE_SIZE);
        wPageOffset  = (WORD)(dReadPointer % MAX_PAGE_SIZE);            
        PageRead(wPage, pBuffer, wDirLen, wPageOffset);
        dReadPointer += wDirLen;
         
        wPage        = (WORD)(dReadPointer / MAX_PAGE_SIZE);
        wPageOffset  = (WORD)(dReadPointer % MAX_PAGE_SIZE);            
        PageRead(wPage, (char*)&SizePage, sizeof(SIZE_PAGE), wPageOffset);
        dReadPointer += sizeof(SIZE_PAGE);        
        
        bFound = TRUE;
        for(i=0; i<wDirLen; i++) {
          if (pBuffer[i] != pSearchFile[i]) {
            bFound = FALSE;
            break;
          }          
        }
        if (bFound == TRUE) {
          /*
           * Now we can release the dir buffer
           */
          NutHeapFree(pBuffer); 
           
          hNUTFile = NutHeapAlloc(sizeof(NUTFILE));       
          hFile    = (FHANDLE *)NutHeapAlloc(sizeof(FHANDLE));
          if ((hNUTFile != NULL) && (hFile != NULL)) {      
            hNUTFile->nf_next = 0;
            hNUTFile->nf_dev  = pDevice;
            hNUTFile->nf_fcb  = hFile;
            
            memset(hFile, 0x00, sizeof(FHANDLE));      
            hFile->wStartPage      = SizePage.wPage;
            hFile->dFileSize       = SizePage.dFileSize;
            hFile->dFilePointer    = 0;
          } else {
            if (hNUTFile != NULL) {
              NutHeapFree(hNUTFile);
            }
            if (hFile != NULL) {
              NutHeapFree(hFile);
            }
            hNUTFile = (NUTFILE *)XFLASH_ERROR;
          }
          
          /* break out of the while loop */
          break; 
        }                 
      } else {
        /*
         * This could not be our file,
         * jump to the next entry.
         */
        wJumpRead = wDirLen + sizeof(SIZE_PAGE); 
        
        wPage        = (WORD)(dReadPointer / MAX_PAGE_SIZE);
        wPageOffset  = (WORD)(dReadPointer % MAX_PAGE_SIZE);            
        PageRead(wPage, pBuffer, wJumpRead, wPageOffset);
        dReadPointer += wJumpRead;
      }
    }
  } 
      
  return (hNUTFile);
} /* FindFile */

/***************************************************************************/
/*  XflashInit                                                             */
/***************************************************************************/
static int XflashInit (NUTDEVICE *pDevice)
{
  int           nError = XFLASH_ERROR;
  volatile BYTE bValue;
  
  UNUSED_VAR(pDevice);
    
  XFLASHSemaInit();

  /*
   * Init SPI memory chip select
   */     
  SPIMEM_CS_PORT &= ~SPIMEM_CS;
  SPIMEM_CS_DDR  |=  SPIMEM_CS;
     
  /* 
   * Init SS pin. When configured as input, we will lose master
   * mode, if this pin goes low. Thus we switch on the pull-up.
   */
  if(bit_is_clear(DDRB, 0)) {
    sbi(PORTB, 0);
  }

  /* Set SCK output. */
  sbi(DDRB, 1);
  /* Set MOSI output. */
  sbi(DDRB, 2);
  /* Enable MISO pullup. */
  sbi(PORTB, 3);

  /* Set double speed. */
  SPCR = (1 << SPI2X);

  SPCR = (1 << SPE) | (1 << MSTR);  /* enable SPI as master, set clk divider */
                                    /* set to max speed */
  
  /* Clean-up the status. */
  outb(SPSR, inb(SPSR));
  bValue = inb(SPDR);
    
  /* Read the status register for a rudimentary check. */
  /* Check if this is a AT45DB041B                     */
  bValue = SpiMemStatus();
  if ((bValue & 0x80) == 0x80) {
    bValue = (bValue >> 2) & 0x0F;
    if(bValue == 7) {
      nError = XFLASH_OK;
    }
  }

  return (nError); 
} /* XflashInit */

/***************************************************************************/
/*  XflashRead                                                             */
/*                                                                         */
/*  Read data from a file.                                                 */
/*                                                                         */
/*  Parameters: pFile Identifies the file to read from. This pointer must  */
/*              have been created by calling XflashOpen().                 */   
/*                                                                         */    
/*              pData Points to the buffer that receives the data.         */
/*                                                                         */
/*              nSize Specifies the number of bytes to read from the file. */
/*                                                                         */
/*  Returns:    The number of bytes read from the file or                  */
/*              -1 if an error occured.                                    */
/***************************************************************************/
static int XflashRead (NUTFILE *hNUTFile, void *pData, int nSize)
{
  int       nBytesRead = XFLASH_ERROR;     
  FHANDLE  *hFile      = NULL;
  WORD      wPage;
  WORD      wPageOffset;
  
  XFLASHLock();
  
  if((hNUTFile != NULL) && (hNUTFile->nf_fcb)){
    hFile = (FHANDLE *)hNUTFile->nf_fcb;  
   
    /*
     * Check for EOF
     */ 
    if (hFile->dFilePointer < hFile->dFileSize) {

      /*
       * Check if nSize is greater than the rest of the file
       */ 
      if ((hFile->dFilePointer + nSize) > hFile->dFileSize) {
        nSize = (int)(hFile->dFileSize - hFile->dFilePointer);
      }
      
      /*
       * Calc start of the file
       */      
      wPage        = (WORD)(hFile->dFilePointer / MAX_PAGE_SIZE);
      wPageOffset  = (WORD)(hFile->dFilePointer % MAX_PAGE_SIZE);
      /*
       * Add the offset in the flash
       */                                                
      wPage += hFile->wStartPage;
      
      PageRead(wPage, (char*)pData, (WORD)nSize, wPageOffset);
      
      hFile->dFilePointer += (DWORD)nSize;        
      
      nBytesRead = nSize;
    } else {
      nBytesRead = 0;
    }
  }
  
  XFLASHFree();     
  
  return (nBytesRead);
} /* XflashRead */

/***************************************************************************/
/*  XflashWrite                                                            */
/*                                                                         */
/*  Write data to a file.                                                  */
/*                                                                         */
/*  Parameters: pFile Identifies the file to write to. This pointer must   */
/*              have been created by calling XflashOpen().                 */ 
/*                                                                         */
/*              pData Points to the buffer that holds the data.            */
/*                                                                         */
/*              nSize Specifies the number of bytes to write to the file.  */                      
/*                                                                         */
/*  Returns:    The number of bytes written to the file or                 */
/*               -1 if an error occured.                                   */
/***************************************************************************/
static int XflashWrite (NUTFILE *hNUTFile, CONST void *pData, int nSize)
{
  int      nBytesWrite  = XFLASH_ERROR;
  BYTE    *pBuffer      = (char*)pData;
  WORD     wDataToWrite = (WORD)nSize;  
  FHANDLE *hFile;
  WORD      wPage;
  WORD      wPageOffset;  
  WORD      wRestInPage;
  WORD      wWriteDataSize;  
  
  XFLASHLock();
  
  if((hNUTFile != NULL) && (hNUTFile->nf_fcb)){
    hFile = (FHANDLE *)hNUTFile->nf_fcb;
    
    while (wDataToWrite) {
      wPage        = (WORD)(hFile->dFilePointer / MAX_PAGE_SIZE);
      wPageOffset  = (WORD)(hFile->dFilePointer % MAX_PAGE_SIZE);
      wRestInPage  = MAX_PAGE_SIZE - wPageOffset;
      
      if (wDataToWrite > wRestInPage) {
        wWriteDataSize = wRestInPage;
      } else {
        wWriteDataSize = wDataToWrite;      
      }
      
      PageWrite(wPage, pBuffer, wRestInPage, wPageOffset);
      
      pBuffer               += wWriteDataSize;
      hFile->dFilePointer   += wWriteDataSize;              
      wDataToWrite          -= wWriteDataSize;
    }  
    
    nBytesWrite = nSize;
  }
  
  XFLASHFree();   
  
  return (nBytesWrite);
} /* XflashWrite */ 

#ifdef __HARVARD_ARCH__
static int XflashWrite_P(NUTFILE *hNUTFile, PGM_P pData, int nSize)
{
  UNUSED_VAR(hNUTFile);
  UNUSED_VAR(pData);
  UNUSED_VAR(nSize);
  return (XFLASH_ERROR);
}
#endif

/***************************************************************************/
/*  XflashOpen                                                             */
/*                                                                         */
/*  Opens an existing file for reading.                                    */
/*                                                                         */
/*  Parameters: pName points to a string that specifies the name of the    */
/*              file to open. The name must exactly match the full         */
/*              pathname of the file.                                      */
/*                                                                         */
/*  Returns:    A pointer to a FILE structure that can be used to read the */
/*              file and retrieve information about the file.              */
/*                                                                         */
/*              A return value of -1 indicates an error.                   */
/***************************************************************************/
static NUTFILE *XflashOpen (NUTDEVICE *pDevice, CONST char *pName, int nMode,
                            int nAccess)
{
  NUTFILE  *hNUTFile = (NUTFILE *)XFLASH_ERROR;
  FHANDLE  *hFile;
  
  UNUSED_VAR(nAccess);
  
  /*
   * Sorry for the return here,
   * but we must check it.
   */
  if (pName == NULL) {
    return (hNUTFile);
  }
  
  XFLASHLock();  
  
  if (nMode & _O_BINARY) {
    if (nMode & _O_WRONLY) {
      if (strcmp(pName, (char*)WRITE_FILENAME) == 0) {      
        /*
         * Create a new file handle.
         */    
        hNUTFile = NutHeapAlloc(sizeof(NUTFILE));       
        hFile    = (FHANDLE *)NutHeapAlloc(sizeof(FHANDLE));
      
        if ((hNUTFile != NULL) && (hFile != NULL)) {      
          hNUTFile->nf_next = 0;
          hNUTFile->nf_dev  = pDevice;
          hNUTFile->nf_fcb  = hFile;
            
          memset(hFile, 0x00, sizeof(FHANDLE));      
          hFile->wStartPage      = 0;
          hFile->dFileSize       = 0;
          hFile->dFilePointer    = 0;
        } else {
          if (hNUTFile != NULL) {
            NutHeapFree(hNUTFile);
          }
          if (hFile != NULL) {
            NutHeapFree(hFile);
          }
          hNUTFile = (NUTFILE *)XFLASH_ERROR;
        } 
      }
    } else {
      hNUTFile = FindFile(pDevice, (char*)pName);    
    } 
  }
  
  XFLASHFree();   
  
  return (hNUTFile);
} /* XflashOpen */

/***************************************************************************/
/*  XflashClose                                                            */
/*                                                                         */
/*  Close a previously opened file.                                        */
/*                                                                         */
/*  Parameters: hNUTFile Identifies the file to close. This pointer must   */
/*              have been created by calling XflashOpen().                 */                                   
/*                                                                         */
/*  Returns:    0 if the function is successfully closed,                  */
/*              -1 otherwise.                                              */
/***************************************************************************/
static int XflashClose (NUTFILE * hNUTFile)
{
  int      nError = XFLASH_ERROR;
  FHANDLE *hFile;

  XFLASHLock();  

  if (hNUTFile != NULL) {
    hFile = (FHANDLE *) hNUTFile->nf_fcb;
    if (hFile != NULL) {
      /*
       * Clear the File-Handle
       */
      NutHeapFree(hFile);
    }
    /*
     * Clear the NUT-Handle
     */
    NutHeapFree(hNUTFile);

    nError = XFLASH_OK;
  }

  XFLASHFree();

  return (nError);
} /* XflashClose */

/***************************************************************************/
/*  XflashSize                                                             */
/*                                                                         */
/*  Retrieve the size of a file.                                           */
/*                                                                         */
/*  Parameters: pFile Identifies the file to query. This pointer must have */
/*              been created by calling XflashOpen().                      */                    
/*                                                                         */
/*  Returns:    The number of bytes in this file or                        */
/*              -1 if an error occured                                     */
/***************************************************************************/
long XflashSize (NUTFILE *hNUTFile)
{
  FHANDLE *hFile;
  LONG     lFileSize = XFLASH_ERROR;

  XFLASHLock();  

  if (hNUTFile != NULL) {
    hFile = (FHANDLE *) hNUTFile->nf_fcb;
    if (hFile != NULL) {
      lFileSize = (LONG)hFile->dFileSize;
    }
  }

  XFLASHFree();
  
  return (lFileSize);

} /* XflashSize */

/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/
/*
 * XFLASH device information structure.
 */
NUTDEVICE devXflash = {
  0,                      /*!< Pointer to next device. */
  {'X', 'F', 'L', 'A', 'S', 'H', 0, 0, 0},        /*!< Unique device name. */
  IFTYP_STREAM,           /*!< Type of device. Obsolete. */
  0,                      /*!< Base address. Unused. */
  0,                      /*!< First interrupt number. Unused. */
  0,                      /*!< Interface control block. Unused. */
  0,                      /*!< Driver control block. Unused. */
  XflashInit,             /*!< Driver initialization routine. Not supported. */
  0,                      /*!< Driver specific control function. Not supported. */
  XflashRead,             /*!< Read data from a file. */
  XflashWrite,            /*!< Write data to a file. */
#ifdef __HARVARD_ARCH__
  XflashWrite_P,          /*!< Write data from program space to a file. */
#endif
  XflashOpen,             /*!< Open a file. */
  XflashClose,            /*!< Close a file. */
  XflashSize              /*!< Return file size. */
};
