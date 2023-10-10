#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SURNAME_AND_NAME_SIZE 30
#define NUMBER_OF_MARKS 3.0
#define BAD_MARK 3
#define DAYS_IN_YEAR 365
#define YEAR 2023
#define MONTH 3
#define AVG_DAYS_IN_MONTH 30.5
#define BUFFER_LENGTH 256

#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_YEAR 1900
#define MAX_YEAR 2023
#define MIN_MARK 1
#define MAX_MARK 5

#ifndef functions_h
#define functions_h

//Структура, що представляє дані про студента
typedef struct SStudent{
  char m_cSurname[SURNAME_AND_NAME_SIZE];
  char m_cName[SURNAME_AND_NAME_SIZE];
  int m_iDay;
  int m_iMonth;
  int m_iYear;
  int m_iMark1;
  int m_iMark2;
  int m_iMark3;
  int m_iAge;
  double m_dAvgmark;
}SStudent;

//Структура, що представляє дані про елемент списку
typedef struct SNode{
  SStudent m_Student;
  struct SNode* m_pNext;
}SNode;

void PrintList(SNode *pHead);
void PrintToFile(SNode *pHead, char *pcFilename);
double FindAvgMark(int iMark1, int iMark2, int iMark3);
double FindAge(SNode *pCurr);
void AddNewItem(SNode **pHead, SNode *pNewItem);
void AddNewItemFromUser(SNode **pHead);
void AddNewItemFromFile(char *pcFilename, SNode **ppHead);
void RemoveBadMarks(SNode **ppHead);
void PrintWithout5(SNode *pHead);
SNode* FindOldest(SNode *pHead);
SNode* FindYoungest(SNode *pHead);
void Free(SNode **ppHead);
void PrintMenu();

#endif