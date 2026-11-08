#ifndef __FIFO_H
#define __FIFO_H

#ifdef __cplusplus
extern "C" {
#endif
  
///////////////////////////////////////////

enum { FALSE, TRUE };

typedef struct {
  unsigned char *Buffer;        // Buffer baþlangýç adresi
  unsigned char *pHead;         // Kuyruk baþý göstericisi
  unsigned char *pTail;         // Kuyruk sonu göstericisi
  int           Size;           // Buffer toplam geniþlik
  
  int           bFull;          // Buffer full flag
  int           nLines;         // Kuyruktaki cümle sayýsý: '\n' sayýsý
} FIFO;
  
///////////////////////////////////////////

void FIFO_Clear(FIFO *pFifo);
void FIFO_Init(FIFO *pFifo, unsigned char *buf, int size);
int FIFO_IsEmpty(FIFO *pFifo);
int FIFO_IsFull(FIFO *pFifo);
int FIFO_SetData(FIFO *pFifo, unsigned char val);
unsigned char FIFO_GetData(FIFO *pFifo);
int FIFO_GetLine(FIFO *pFifo, unsigned char *pLine);     
int FIFO_GetCount(FIFO *pFifo);
int FIFO_GetAvail(FIFO *pFifo);

#ifdef __cplusplus
}
#endif

#endif