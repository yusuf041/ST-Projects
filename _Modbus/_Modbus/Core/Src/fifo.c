#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "fifo.h"

void FIFO_Clear(FIFO *pFifo)
{
  pFifo->pHead = pFifo->pTail = pFifo->Buffer;
  
  pFifo->bFull = FALSE;
  pFifo->nLines = 0;
}

void FIFO_Init(FIFO *pFifo, unsigned char *buf, int size)
{
  pFifo->Buffer = buf;
  pFifo->Size = size;
  
  FIFO_Clear(pFifo);
}

int FIFO_IsEmpty(FIFO *pFifo)
{
  return (pFifo->pHead == pFifo->pTail);
}

int FIFO_IsFull(FIFO *pFifo)
{
	unsigned char *ptr = pFifo->pTail;

		if(++ptr == pFifo->Buffer + pFifo->Size)
			ptr = pFifo->Buffer;


  return (ptr == pFifo->pHead)   ;
}

int FIFO_SetData(FIFO *pFifo, unsigned char val)
{
  unsigned char *ptr = pFifo->pTail;
  
  // Dairesel buffer kural�na uygun ilerletme
  if (++ptr == pFifo->Buffer + pFifo->Size)
    ptr = pFifo->Buffer;
  
  if (ptr == pFifo->pHead) {
    pFifo->bFull = TRUE;
    return FALSE;
  }
  
  *pFifo->pTail = val;
  pFifo->pTail = ptr;
  
  if (val == '\n')
    ++pFifo->nLines;
  
  return TRUE;
}

// FIFO buffer'dan veri �eker ve geri d�ner
// E�er FIFO buffer bo�sa bloke bekler
unsigned char FIFO_GetData(FIFO *pFifo)
{
  unsigned char val;
  
  // FIFO buffer bo� oldu�u m�ddet�e bekle
  while (FIFO_IsEmpty(pFifo)) ;
  
  val = *pFifo->pHead;
  
  // pHead g�stericisi dairesel buffer kural�na 
  // uygun olarak ilerletilir
  if (++pFifo->pHead == pFifo->Buffer + pFifo->Size)
    pFifo->pHead = pFifo->Buffer;
  
  if (val == '\n')
    --pFifo->nLines;
  
  pFifo->bFull = FALSE;

  return val;
}

int FIFO_GetLine(FIFO *pFifo, unsigned char *pLine)
{
  unsigned char val;
  
  if (pFifo->nLines == 0) {
    if (pFifo->bFull) {
      // Blokeyi engelleme stratejisi
      FIFO_Clear(pFifo);        
    }
    
    return FALSE;
  }
  
  do {
    val = FIFO_GetData(pFifo);
    *pLine++ = val;    
  } while (val != '\n');
  
  *pLine = '\0';
  return TRUE;
}

// FIFO buffer'daki eleman say�s�na geri d�ner
int FIFO_GetCount(FIFO *pFifo)
{
  int count;
  
  // Enter critical
  
  if (pFifo->pTail >= pFifo->pHead)
    count = pFifo->pTail - pFifo->pHead;
  else
    count = (pFifo->pTail + pFifo->Size) - pFifo->pHead;
  
  // Exit critical
  return count;
}

// FIFO buffer'daki bo� yer say�s�na geri d�ner
int FIFO_GetAvail(FIFO *pFifo)
{
  int count;
  
  count = FIFO_GetCount(pFifo);
  
  return (pFifo->Size - 1) - count;
}

