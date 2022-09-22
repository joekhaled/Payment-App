#include "Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Please Enter the Card Holder Name : ");
    
    uint8_t *ptr , Ch , Length = 0 ;
    
    ptr = cardData->cardHolderName;
    Ch = getchar();
    
    while(Ch != '\n' && Length < (Name_Max+1))
    {
        *ptr = Ch;
        Length ++;
        ptr ++;
        *ptr='\0';
        Ch = getchar();
    }
    
    if(Length >Name_Min && Length <Name_Max)
    {
        return OK;
    }
    else
    {
        return WRONG_NAME;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Please Enter Card Expiry Date (MM/YY) : ");
    
    uint16_t Month ,Year;
    
    scanf("%5s",cardData->cardExpirationDate);
    
    getchar();
    
    Month = atoi((const char*)cardData->cardExpirationDate);
    Year = atoi((const char*)cardData->cardExpirationDate+3);
    
    if((Month>0 && Month<=12) && (*(cardData->cardExpirationDate+2) == '/') && (Year>0 && Year<=99))
    {
        return OK;
    }
    else
    {
        return WRONG_EXP_DATE;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please Enter the Primary Account Number : ");
    
    uint8_t *ptr , Ch;
    uint16_t Length = 0 ;
    
    ptr = cardData->primaryAccountNumber;
    Ch = getchar();
    
    while(Ch != '\n' && Length < 25)
    {
        *ptr = Ch;
        Length ++;
        ptr ++;
        *ptr='\0';
        Ch = getchar();
    }

    if(Length >= PAN_Min && Length < (PAN_Max))
    {
        return OK;
    }
    else
    {
        return WRONG_PAN;
    }
}

void Card_Module(ST_cardData_t *cardData)
{
    printf("Please Enter Card Data :- \n");
    printf("---------------------------------------------------------\n");
    getchar();
    while(getCardHolderName(cardData));
    while(getCardExpiryDate(cardData));
    while(getCardPAN(cardData));
}
