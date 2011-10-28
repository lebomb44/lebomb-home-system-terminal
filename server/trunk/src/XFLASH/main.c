/****************************************************************************
*  This file is part of the CRXFLASH windows application.
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
*  Name:    main.c
*
*  History:
*
*  21.10.04  mifi   First Version
****************************************************************************/
#define __MAIN_C__

/*==========================================================*/
/*  DEFINE: All Structures and Common Constants             */
/*==========================================================*/
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

/*==========================================================*/
/*  DEFINE: All Structures and Common Constants             */
/*==========================================================*/
//#define _MAX_PATH       256
#define MAX_FILES       1024
#define MAX_PAGE_SIZE   264
#define XFLASH_NAME     "xflash.bin"

#pragma pack(1)

typedef struct _xflash_header {
  char  Magic1;
  char  Magic2;
  WORD wVersion;
  WORD wMaxPages; 
} XFLASH_HEADER;

/*==========================================================*/
/*  DEFINE: Prototypes                                      */
/*==========================================================*/

/*==========================================================*/
/*  DEFINE: Definition of all local Data                    */
/*==========================================================*/
static XFLASH_HEADER  XHeader = { 'X', 'F', 0x0001, 0 };
static char          *Filelist[MAX_FILES];
static int           nFilelistCounter = 0;

/*==========================================================*/
/*  DEFINE: Definition of all local Procedures              */
/*==========================================================*/
/************************************************************/
/*  Usage                                                   */
/************************************************************/
static void Usage(void)
{
  printf("Usage: crxflash DIRECTORY\n");
}

/************************************************************/
/*  CreateXflash                                            */
/************************************************************/
static void CreateXflash (char *pRootDir)
{
  int     i;
  FILE  *hOutFile;
  int    nInFile;

  DWORD dwPos;
  DWORD dwDirSize;
  DWORD dwPageCounter;
  DWORD dwDataPageCounter;
  DWORD dwDirPageCounter;
  DWORD dwRestDirSize;

  char  szDirFilename[_MAX_PATH];
  char  *pDirFilename;
  char  *pChar;
  int    nRootDirLen = strlen(pRootDir);
  WORD   wFilenameLen;
  WORD   wPage  = 0;
  BYTE   bEmptyPage[MAX_PAGE_SIZE];

  memset(bEmptyPage, 0x00, MAX_PAGE_SIZE); 
  
  hOutFile = fopen(XFLASH_NAME, "wb+");
  if (hOutFile == NULL) {
    printf("Error, create file %s\n", XFLASH_NAME);
    exit(2);
  }

  /*
   * Calc DirSize and DataSize
   */
  dwDirSize         = sizeof(XFLASH_HEADER); 
  dwDataPageCounter = 0;

  for(i=0; i<nFilelistCounter; i++) {
    nInFile = _open(Filelist[i], _O_BINARY | _O_RDONLY);
    if (nInFile != -1) {
      dwPos = (DWORD)_lseek(nInFile, 0L, SEEK_END);   
      _close(nInFile);

      sprintf(szDirFilename, "%s", Filelist[i]);
      pDirFilename = &szDirFilename[nRootDirLen+1];
      wFilenameLen = strlen(pDirFilename);

      dwDirSize += sizeof(WORD);
      dwDirSize += wFilenameLen;
      dwDirSize += sizeof(DWORD);
      dwDirSize += sizeof(WORD);

      dwPageCounter      = (dwPos + (MAX_PAGE_SIZE - 1)) / MAX_PAGE_SIZE;
      dwDataPageCounter += dwPageCounter;
    }   
  }
  dwDirSize += sizeof(WORD); /* end marker */


  dwDirPageCounter = (dwDirSize + (MAX_PAGE_SIZE - 1)) / MAX_PAGE_SIZE;

  XHeader.wMaxPages = (WORD)(dwDirPageCounter + dwDataPageCounter);

  /*
   * Write header
   */
  fwrite(&XHeader, sizeof(XFLASH_HEADER), 1, hOutFile);

  /*
   * Create "Directory"
   */
  wPage = (WORD)dwDirPageCounter;
  for(i=0; i<nFilelistCounter; i++) {
    nInFile = _open(Filelist[i], _O_BINARY | _O_RDONLY);
    if (nInFile != -1) {
      dwPos = (DWORD)_lseek(nInFile, 0L, SEEK_END);   
      _close(nInFile);

      sprintf(szDirFilename, "%s", Filelist[i]);
      pDirFilename = &szDirFilename[nRootDirLen+1];
      wFilenameLen = strlen(pDirFilename);

      /*
       * Replace '\' by '/'
       */
      pChar = pDirFilename;
      while(*pChar != 0) {
        if (*pChar == '\\') {
          *pChar = '/';
        }
        pChar++;
      }

      fwrite(&wFilenameLen, sizeof(WORD), 1, hOutFile);
      fwrite(pDirFilename, wFilenameLen, 1, hOutFile);
      fwrite(&dwPos, sizeof(DWORD), 1, hOutFile);
      fwrite(&wPage, sizeof(WORD), 1, hOutFile);


      wPage += (WORD)((dwPos + (MAX_PAGE_SIZE - 1)) / MAX_PAGE_SIZE); 
    }
  }

  fwrite(bEmptyPage, sizeof(WORD), 1, hOutFile); /* end marker */


  dwRestDirSize = (dwDirPageCounter * MAX_PAGE_SIZE) - dwDirSize;
  fwrite(bEmptyPage, dwRestDirSize, 1, hOutFile);


  /*
   * Write the file
   */
  for(i=0; i<nFilelistCounter; i++) {
    nInFile = _open(Filelist[i], _O_BINARY | _O_RDONLY);
    if (nInFile != -1) {

      dwPos = (DWORD)_lseek(nInFile, 0L, SEEK_END);   
      _lseek(nInFile, 0L, SEEK_SET);   
      while (dwPos >= MAX_PAGE_SIZE) {
        _read(nInFile, bEmptyPage,  MAX_PAGE_SIZE);
        fwrite(bEmptyPage, MAX_PAGE_SIZE, 1, hOutFile);

        dwPos -= MAX_PAGE_SIZE;
      }

      /*
       * Read the rest
       */
      if (dwPos != 0) {
        memset(bEmptyPage, 0x00, MAX_PAGE_SIZE);
        _read(nInFile, bEmptyPage, dwPos);
        fwrite(bEmptyPage, MAX_PAGE_SIZE, 1, hOutFile);
      }

      _close(nInFile);
    }
  }


  fclose(hOutFile);
}

/************************************************************/
/*  Add2Filelist                                            */
/************************************************************/
static void Add2Filelist (char *pFilename)
{
  int nLen;

  if ((pFilename != NULL) && (nFilelistCounter < MAX_FILES)) {
    nLen = strlen(pFilename);
    Filelist[nFilelistCounter] = (char*)malloc(nLen+1);
    memset(Filelist[nFilelistCounter], 0x00, nLen+1);
    memcpy(Filelist[nFilelistCounter], pFilename, nLen);
    nFilelistCounter++;
  } else {
    if (nFilelistCounter >= MAX_FILES) {
      printf("Error, to many files\n");
      exit(1);
    }
  }
}

/************************************************************/
/*  FindAllFiles                                            */
/************************************************************/
static void FindAllFiles(char *pStartPath)
{
  HANDLE           hFile;
  WIN32_FIND_DATA   FindData;
  char            szSearchPath[_MAX_PATH];
  char            szFilename[_MAX_PATH];

  memset(&FindData, 0, sizeof(FindData));
  sprintf(szSearchPath, "%s\\*.*", pStartPath);

  hFile = FindFirstFile(szSearchPath, &FindData);
  if (hFile == INVALID_HANDLE_VALUE)
    return;
  do {
    if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      if (FindData.cFileName[0] != '.') {
        sprintf(szSearchPath, "%s\\%s", pStartPath, FindData.cFileName);
        FindAllFiles(szSearchPath);
      }
    } else {
      sprintf(szFilename, "%s\\%s", pStartPath, FindData.cFileName); 
      Add2Filelist(szFilename);
    }
  }
  while (FindNextFile(hFile, &FindData) != 0);

  FindClose(hFile);
}

/*==========================================================*/
/*  DEFINE: All code exported                               */
/*==========================================================*/
/************************************************************/
/*                       M A I N                            */
/************************************************************/
int main(int argc, char **argv)
{
  if (argc != 2) {    
    Usage();
  } else {
    FindAllFiles(argv[1]);
    if (nFilelistCounter != 0) {
      CreateXflash(argv[1]);
    }
  }
}
