#include "functions.h"

int main() {
  SNode* pHead = NULL;
  int iInputAnswer;
  char cBuffer[BUFFER_LENGTH];

  printf("Hello! Do you want to add students to a list from the file (press 1) or from the\
 keyboard(press 2)?: ");
  scanf("%d", &iInputAnswer);
  gets(cBuffer);
  while (iInputAnswer != 1 && iInputAnswer != 2) {
    printf("Enter the correct menu number ( 1 or 2 ) : ");
    scanf("%d", &iInputAnswer);
    gets(cBuffer);
  }
  if(iInputAnswer == 1) {
    char cInputFilename[SURNAME_AND_NAME_SIZE];
    printf("Enter the filename: ");
    int iFileError;
    do {
      iFileError = 0;
      gets(cBuffer);
      if (strlen(cBuffer) > 30) {
        printf("The length of file name must be less than 30 symbols. Enter the other: ");
        iFileError = 1;
      }
    } while (iFileError);
    strcpy(cInputFilename, cBuffer);
    AddNewItemFromFile(cInputFilename, &pHead);
  }else if(iInputAnswer == 2) {
    int iAddAnswer;
    printf("Enter the data of the first student:\n");
    AddNewItemFromUser(&pHead);
    printf("If you want to continue, press 1, no - press any other number: ");
    scanf("%d", &iAddAnswer);
    gets(cBuffer);
    while (iAddAnswer == 1) {
      printf("Enter the data of the next student:\n");
      AddNewItemFromUser(&pHead);
      printf("If you want to continue, press 1, no - press any other number: ");
      scanf("%d", &iAddAnswer);
      gets(cBuffer);
    }
  printf("Students were added successfully!\n");
  }
    
  int iMenuAnswer;
  PrintMenu();
  scanf("%d", &iMenuAnswer);
  gets(cBuffer);
  while (iMenuAnswer <= 0 && iMenuAnswer > 7) {
    printf("Enter the correct menu number ( 1 or 2 ) : ");
    scanf("%d", &iMenuAnswer);
    gets(cBuffer);
  }
  while (iMenuAnswer != 7) {
    if(iMenuAnswer == 1) {
      RemoveBadMarks(&pHead);
    }else if(iMenuAnswer == 2) {
      SNode* pOldest = FindOldest(pHead);
      SNode* pYoungest = FindYoungest(pHead);
      if (pOldest == pYoungest && pOldest == pHead) {
        printf("There is one student in the file, unable to get information.\n");
      }else if (pOldest == pYoungest){
        printf("All of the students are on the same age, unable to get information\n");
      }else{
        if (pOldest) {
          printf("The oldest student: %s %s\n", pOldest->m_Student.m_cName, \
          pOldest->m_Student.m_cSurname);
        }
        if (pYoungest) {
          printf("The youngest student: %s %s\n", pYoungest->m_Student.m_cName, \
          pYoungest->m_Student.m_cSurname);
        }
      }
    }else if(iMenuAnswer == 3) {
      if (!pHead) {
        printf("List is empty! Nothing to print!\n");
      }else{
        char cOutputFilename[SURNAME_AND_NAME_SIZE];
        printf("Enter the output file name: ");
        int iFileError;
        do {
          iFileError = 0;
          gets(cBuffer);
          if (strlen(cBuffer) > 30) {
            printf("The length of file name must be less than 30 symbols. Enter the other: ");
            iFileError = 1;
          }
        }while (iFileError);
        strcpy(cOutputFilename, cBuffer);
        PrintToFile(pHead, cOutputFilename);
      }
    }else if(iMenuAnswer == 4) {
      AddNewItemFromUser(&pHead);
    }else if(iMenuAnswer == 5) {
      PrintList(pHead);
    }else if(iMenuAnswer == 6) {
      PrintWithout5(pHead);
    }else {
      printf("Enter correct menu answer\n");
    }
    PrintMenu();
    scanf("%d", &iMenuAnswer);
    gets(cBuffer);
  }

  printf("The program was ended successfully.\n");
  Free(&pHead); 
  return 0;
}