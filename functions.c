#include "functions.h"

//------------------------------------------------------------------------------------------
//Функція, що виводить список на екран, починаючи з pHead
void PrintList(SNode *pHead) {
  if(!pHead) {
    printf("List is empty! Nothing to print!\n");
    return;
  }
  printf("List of students:\n");
  SNode *pNew = pHead;
  while(pNew) {
    printf("%-20s %-10s| %02d.%02d.%04d | %d %d %d |\n", pNew->m_Student.m_cSurname,
        pNew->m_Student.m_cName, pNew->m_Student.m_iDay, pNew->m_Student.m_iMonth,
        pNew->m_Student.m_iYear, pNew->m_Student.m_iMark1, pNew->m_Student.m_iMark2,
        pNew->m_Student.m_iMark3);
    pNew = pNew->m_pNext;
  }
}

//------------------------------------------------------------------------------------------
//Функція, що виводить список у текстовий файл pcFilename, починаючи з pHead
void PrintToFile(SNode *pHead, char *pcFilename) {
  int iFileLen = strlen(pcFilename);
  while (pcFilename[iFileLen - 1] != 't' || pcFilename[iFileLen - 2] != 'x' || \
    pcFilename[iFileLen - 3] != 't' || pcFilename[iFileLen - 4] != '.') {
    printf("Incorrect output file name. Enter the .txt file! : ");
    scanf("%s", pcFilename);
    iFileLen = strlen(pcFilename);
  }
  FILE *pOutFilename = fopen(pcFilename, "w");
  SNode *pCurr = pHead;
  while(pCurr) {
    fprintf(pOutFilename, "%s %s %d.%d.%d %d %d %d\n", pCurr->m_Student.m_cSurname,
      pCurr->m_Student.m_cName, pCurr->m_Student.m_iDay, pCurr->m_Student.m_iMonth,
      pCurr->m_Student.m_iYear, pCurr->m_Student.m_iMark1, pCurr->m_Student.m_iMark2,
      pCurr->m_Student.m_iMark3);
    pCurr = pCurr->m_pNext;
  }
  fclose(pOutFilename);
  printf("The list was printed to the file successfully\n");
}

//------------------------------------------------------------------------------------------
//Функція, що знаходить та повертає середню оцінку на основі трьох оцінок iMark1, iMark2, iMark3
double FindAvgMark(int iMark1, int iMark2, int iMark3) {
  return (iMark1 + iMark2 + iMark3) / NUMBER_OF_MARKS;
}

//------------------------------------------------------------------------------------------
//Функція, що знаходить та повертає вік студента pCurr
double FindAge(SNode *pCurr) {
  return DAYS_IN_YEAR * (YEAR - pCurr->m_Student.m_iYear) + AVG_DAYS_IN_MONTH * (MONTH -\
      pCurr->m_Student.m_iMonth) + pCurr->m_Student.m_iDay;
}

//------------------------------------------------------------------------------------------
//Функція, що додає елемент pNewItem у відсортований список починаючи з ppHead на таке місце, 
// щоб не порушити його відсортованість 
void AddNewItem(SNode **ppHead, SNode *pNewItem) {
  if(!(*ppHead)) {
    (*ppHead) = pNewItem;
    (*ppHead)->m_pNext = NULL;
    return;
  }else {
    if(pNewItem->m_Student.m_dAvgmark >= (*ppHead)->m_Student.m_dAvgmark) {
      pNewItem->m_pNext = *ppHead;
      *ppHead = pNewItem;
      return;
    }

    SNode *pCurr = *ppHead;
    while(pCurr->m_pNext) {
      if(pNewItem->m_Student.m_dAvgmark >= pCurr->m_pNext->m_Student.m_dAvgmark){
        pNewItem->m_pNext = pCurr->m_pNext;
        pCurr->m_pNext = pNewItem;
        return;
      }else {
        pCurr = pCurr->m_pNext;
      }
    }
    pCurr->m_pNext = pNewItem;
    pNewItem->m_pNext = NULL;
  }
}

//------------------------------------------------------------------------------------------
//Функція, що зчитує дані про студента з консолі, формує з них елемент списку та додає у 
// відсортований список
void AddNewItemFromUser(SNode **ppHead) {
  char cBuffer[BUFFER_LENGTH] = { 0 };
  SNode* pNewStudent = (SNode*)malloc(sizeof(SNode));
  int iError;
  printf("Enter surname: ");
  do {
    iError = 0;
    gets(cBuffer);
    if (strlen(cBuffer) > 30) {
      printf("Error! Surname is longer than 30 symbols!\n");
      iError = 1;
    }

    if (!isupper(cBuffer[0])) {
      printf("Error! First letter of the surname must be in upper case!\n");
      iError = 1;
    }
    
    int iNumError = 0;
    for (int i = 0; cBuffer[i] != '\0'; i++) {
      if (!isalpha(cBuffer[i])) {
        iError = 1;
        iNumError = 1;
        }
      }
    if (iNumError == 1) {
      printf("Error! Surname contains restricted symbols!\n");
    }
    if (iError == 1) {
      printf("Enter the other surname: ");
    }
  } while (iError);
  strcpy(pNewStudent->m_Student.m_cSurname, cBuffer);
  printf("Enter name: ");
  do {
    iError = 0;
    gets(cBuffer);
    if (strlen(cBuffer) > 30) {
      printf("Error! Name is longer than 30 symbols!\n");
      iError = 1;
    }

    if (!isupper(cBuffer[0])) {
      printf("Error! First letter of the name must be in upper case!\n");
      iError = 1;
    }
    int iNumError = 0;
    for (int i = 0; cBuffer[i] != '\0'; i++) {
      if (!isalpha(cBuffer[i])) {
        iError = 1;
        iNumError = 1;
      }
    }
    if (iNumError == 1) {
      printf("Error! Name contains restricted symbols!\n");
    }
    if (iError == 1) {
      printf("Enter the other name: ");
    }
  } while (iError);
  strcpy(cBuffer, pNewStudent->m_Student.m_cName);
  printf("Enter day of birth: ");
  scanf("%d", &pNewStudent->m_Student.m_iDay);
  gets(cBuffer);
  while (pNewStudent->m_Student.m_iDay < MIN_DAY || pNewStudent->m_Student.m_iDay > MAX_DAY) {
    printf("Incorrect day of birth ( must be between 1 and 31). Enter the correct : ");
    scanf("%d", &pNewStudent->m_Student.m_iDay);
    gets(cBuffer);
  }
  printf("Enter month of birth: ");
  scanf("%d", &pNewStudent->m_Student.m_iMonth);
  gets(cBuffer);
  while (pNewStudent->m_Student.m_iMonth < MIN_MONTH || pNewStudent->m_Student.m_iMonth > \
      MAX_MONTH) {
    printf("Incorrect month of birth ( must be between 1 and 12). Enter the correct : ");
    scanf("%d", &pNewStudent->m_Student.m_iMonth);
    gets(cBuffer);
  }
  printf("Enter year of birth: ");
  scanf("%d", &pNewStudent->m_Student.m_iYear);
  gets(cBuffer);
  while (pNewStudent->m_Student.m_iYear <= MIN_YEAR || pNewStudent->m_Student.m_iYear > \
      MAX_YEAR) {
    printf("Incorrect year of birth ( must be between 1900 and 2023). Enter the correct : ");
    scanf("%d", &pNewStudent->m_Student.m_iYear);
    gets(cBuffer);
  }
  printf("Enter first mark: ");
  scanf("%d", &pNewStudent->m_Student.m_iMark1);
  gets(cBuffer);
  while (pNewStudent->m_Student.m_iMark1 < MIN_MARK || pNewStudent->m_Student.m_iMark1 > \
     MAX_MARK) {
    printf("Incorrect first mark ( must be between 1 and 5). Enter the correct : ");
    scanf("%d", &pNewStudent->m_Student.m_iMark1);
    gets(cBuffer);
  }
  printf("Enter second mark: ");
  scanf("%d", &pNewStudent->m_Student.m_iMark2);
  gets(cBuffer);
  while (pNewStudent->m_Student.m_iMark2 < MIN_MARK || pNewStudent->m_Student.m_iMark2 > \
      MAX_MARK) {
    printf("Incorrect first mark ( must be between 1 and 5). Enter the correct : ");
    scanf("%d", &pNewStudent->m_Student.m_iMark2);
    gets(cBuffer);
  }
  printf("Enter third mark: ");
  scanf("%d", &pNewStudent->m_Student.m_iMark3);
  gets(cBuffer);
  while (pNewStudent->m_Student.m_iMark3 < MIN_MARK || pNewStudent->m_Student.m_iMark3 > \
      MAX_MARK) {
    printf("Incorrect first mark ( must be between 1 and 5). Enter the correct : ");
    scanf("%d", &pNewStudent->m_Student.m_iMark3);
    gets(cBuffer);
  }
  pNewStudent->m_Student.m_iAge = FindAge(pNewStudent);
  pNewStudent->m_Student.m_dAvgmark = FindAvgMark(pNewStudent->m_Student.m_iMark1, \
      pNewStudent->m_Student.m_iMark2, pNewStudent->m_Student.m_iMark3);
  pNewStudent->m_pNext = NULL;

  AddNewItem(ppHead, pNewStudent);
}

//------------------------------------------------------------------------------------------
//Функція, що зчитує дані про студентів з текстового файлу pcFilename та додає їх у вигляді 
// елементів списку до списку, починаючи з ppHead, при цьому елементи сортуються
void AddNewItemFromFile(char *pcFilename, SNode **ppHead) {
  char cSurname[BUFFER_LENGTH] = {0};
  char cName[BUFFER_LENGTH] = {0};
  int iDay;
  int iMonth;
  int iYear;
  int iMark1;
  int iMark2;
  int iMark3;
  double dAvgMark;

  int iFileIdent = 1;
  FILE *pInputFilename = fopen(pcFilename, "r");
  if (!pInputFilename) {
    printf("Incorrect input file name! Enter the correct file name! : ");
    iFileIdent = 0;
    while (!iFileIdent) {
      scanf("%s", pcFilename);
      pInputFilename = fopen(pcFilename, "r");
      while (!pInputFilename) {
        printf("Incorrect input file name! Enter the correct file name! : ");
        scanf("%s", pcFilename);
        pInputFilename = fopen(pcFilename, "r");
        iFileIdent = 0;
      }
      iFileIdent = 1;
    }
  }
  while (fscanf(pInputFilename, "%s %s %d %d %d %d %d %d", cSurname, cName, &iDay, &iMonth, \
  &iYear, &iMark1, &iMark2, &iMark3) == 8) {
    SNode *pNewStudent = (SNode*)malloc(sizeof(SNode));
    if (strlen(cSurname) > 30 || strlen(cName) > 30) {
      Free(ppHead);
      break;
    }
    int iSymb = 0;
    for (int i = 0; i < strlen(cSurname); ++i) {
      if (!isalpha(cSurname[i])) {
        iSymb = 1;
      }
    }
    for (int i = 0; i < strlen(cName); ++i) {
      if (!isalpha(cName[i])) {
        iSymb = 1;
      }
    }
    if (iSymb) {
      Free(ppHead);
      break;
    }
    strcpy(pNewStudent->m_Student.m_cSurname, cSurname);
    strcpy(pNewStudent->m_Student.m_cName, cName);
    if (iDay < MIN_DAY || iDay > MAX_DAY || iMonth < MIN_MONTH || iMonth > MAX_MONTH\
      || iYear < MIN_YEAR || iYear > MAX_YEAR || iMark1 < MIN_MARK || iMark1 > MAX_MARK\
      || iMark2 < MIN_MARK || iMark2 > MAX_MARK || iMark3 < MIN_MARK ||\
      iMark3 > MAX_MARK) {
      Free(ppHead);
      break;
    }
    pNewStudent->m_Student.m_iDay = iDay;
    pNewStudent->m_Student.m_iMonth = iMonth;
    pNewStudent->m_Student.m_iYear = iYear;
    pNewStudent->m_Student.m_iMark1 = iMark1;
    pNewStudent->m_Student.m_iMark2 = iMark2;
    pNewStudent->m_Student.m_iMark3 = iMark3;
    pNewStudent->m_Student.m_dAvgmark = FindAvgMark(iMark1, iMark2, iMark3);
    pNewStudent->m_Student.m_iAge = FindAge(pNewStudent);
    pNewStudent->m_pNext = NULL;

    AddNewItem(ppHead, pNewStudent);
  }
  char cBuffer[BUFFER_LENGTH] = { 0 };
  fgets(cBuffer, BUFFER_LENGTH, pInputFilename);
  if (strlen(cBuffer) != 0) {
    Free(ppHead);
  }
  fclose(pInputFilename);
  if (!*ppHead) {
    printf("An error occured : file is empty or incorrect data in the file. \
Enter the other file name : ");
    scanf("%s", pcFilename);
    AddNewItemFromFile(pcFilename, ppHead);
  }
  else
    printf("Students were added successfully!\n");
}

//------------------------------------------------------------------------------------------
//Функція, що видаляє всіх студентів з першою та третьою оцінками "3" зі списку, 
// починаючи з ppHead
void RemoveBadMarks(SNode **ppHead) {
  if(!*ppHead) {
    printf("Nothing to remove! List is empty!\n");
    return;
  }
  int iTemp = 0;
  SNode *pCurr = *ppHead, *pPrev = NULL;
  while(!pPrev && pCurr) {
    if(pCurr->m_Student.m_iMark1 == BAD_MARK && pCurr->m_Student.m_iMark3 == BAD_MARK) {
      *ppHead = pCurr->m_pNext;
      free(pCurr);
      pCurr = *ppHead;
      iTemp = 1;
      continue;
    }
      pPrev = pCurr;
      pCurr = pCurr->m_pNext;
  }
  while (pCurr) {
    if(pCurr->m_Student.m_iMark1 == BAD_MARK && pCurr->m_Student.m_iMark3 == BAD_MARK){
      pPrev->m_pNext = pCurr->m_pNext;
      free(pCurr);
      pCurr = pPrev->m_pNext;
      iTemp = 1;
      continue;
    }
    pPrev = pCurr;
    pCurr = pCurr->m_pNext;
  }
  if (!iTemp) {
    printf("None of the students have first and third mark '3', nothing to remove.\n");
    return;
  }
  printf("Students with first and third mark '3' were removed successfully\n");
}

//------------------------------------------------------------------------------------------
//Функція, що виводить на екран тих студентів, що не отримали жодної "5" на іспитах, 
//починаючи з pHead
void PrintWithout5(SNode *pHead) {
  if(!pHead) {
    printf("List is empty! Nothing to print!\n");
    return;
  }
  int iTemp = 0;
  SNode* pNew = pHead;
  while (pNew) {
    if(pNew->m_Student.m_iMark1 != 5 && pNew->m_Student.m_iMark2 != 5 &&
        pNew->m_Student.m_iMark3 != 5){
      printf("%-10s %-8s| %02d.%02d.%04d | %d %d %d |\n", pNew->m_Student.m_cSurname,
        pNew->m_Student.m_cName, pNew->m_Student.m_iDay, pNew->m_Student.m_iMonth,
        pNew->m_Student.m_iYear, pNew->m_Student.m_iMark1, pNew->m_Student.m_iMark2,
        pNew->m_Student.m_iMark3);
      iTemp = 1;
    }
    pNew = pNew->m_pNext;
  }
  if (!iTemp) {
    printf("Nothing to print! All students have \"5\"\n");
  }
}

//------------------------------------------------------------------------------------------
//Функція, що знаходить та повертає найстаршого студента, починаючи з pHead
SNode* FindOldest(SNode *pHead) {
  if (!pHead) {
    printf("Unable to find the oldest student, list is empty!\n");
    return NULL;
  }
  SNode *pCurr = pHead, *pOldest = pHead;
  while (pCurr) {
    if(pCurr->m_Student.m_iAge >= pOldest->m_Student.m_iAge) {
      pOldest = pCurr;
    }
      pCurr = pCurr->m_pNext;
  }
  return pOldest;
}

//------------------------------------------------------------------------------------------
//Функція, що знаходить та повертає наймолодшого студента, починаючи з pHead
SNode* FindYoungest(SNode *pHead) {
  if(!pHead){
    printf("Unable to find the youngest student, list is empty!\n");
    return NULL;
  }
  SNode *pCurr = pHead, *pYoungest = pHead;
  while (pCurr) {
    if(pCurr->m_Student.m_iAge <= pYoungest->m_Student.m_iAge) {
      pYoungest = pCurr;
    }
    pCurr = pCurr->m_pNext;
  }
  return pYoungest;
}

//------------------------------------------------------------------------------------------
//Функція, що видаляє список та очищає пам'ять
void Free(SNode **ppHead) {
  if(!(*ppHead)) {
    free(*ppHead);
  }
  if(*ppHead) {
    SNode* pCurr = (*ppHead)->m_pNext;
    while (pCurr) {
      free(*ppHead);
      *ppHead = pCurr;
      pCurr = pCurr->m_pNext;
    }
    *ppHead = NULL;
  }
}

//------------------------------------------------------------------------------------------
//Функція, що виводить на екран головне меню
void PrintMenu(){
  printf("Choose what do you want to do with a list:\n\
    **Press 1 to remove students with first and third mark '3'\n\
    **Press 2 to get info about the oldest and the youngest students\n\
    **Press 3 to put a list in the text file\n\
    **Press 4 to add new student to a list\n\
    **Press 5 to print a list\n\
    **Press 6 to print a list of students without '5'\n\
    **Press 7 to exit: ");
}
