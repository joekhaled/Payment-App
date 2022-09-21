#ifndef Card_h
#define Card_h

#include "../Standard Types.h"
#include <stdio.h>
#include <stdlib.h>

#define Name_Min 20
#define Name_Max 24

#define PAN_Min 16
#define PAN_Max 19

//Enumerations
typedef enum EN_cardError_t
{
    OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

//Structures
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

//Function Prototypes
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
void Card_Module(ST_cardData_t *cardData);

#endif
