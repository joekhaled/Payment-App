#include "Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime((char*)termData->transactionDate, 11, "%d/%m/%Y", ptm);
    
    return OKK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    uint16_t Card_Exp_Month = atoi((const char*)cardData->cardExpirationDate);
    uint16_t Card_Exp_Year = atoi((const char*)cardData->cardExpirationDate+3);
    
    uint16_t Trans_Exp_Month = atoi((const char*)termData->transactionDate+3);
    uint16_t Trans_Exp_Year = atoi((const char*)termData->transactionDate+8);
    
    if(Card_Exp_Year > Trans_Exp_Year)
    {
        return OKK;
    }
    else if((Card_Exp_Year == Trans_Exp_Year) && (Card_Exp_Month > Trans_Exp_Month))
    {
        return OKK;
    }
    else
    {
        return EXPIRED_CARD;
    }
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    
    uint8_t *Ptr = cardData->primaryAccountNumber;
    uint16_t Sum = 0, Num = *Ptr - 48 , Order = 0;
    
    while(*Ptr != '\0')
    {
        if(Order % 2 == 0)
        {
            if(Num <= 4)
            {
                Num = Num * 2;
            }
            else
            {
                Num = ( ((Num*2)/10) + ((Num*2)%10) );
            }
        }
        
        Sum = Sum + Num;
        
        Ptr ++;
        Order ++;
        
        Num = *Ptr - 48;
    }
    
    if(Sum % 10 ==0)
    {
        return OKK;
    }
    else
    {
        return INVALID_CARD;
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Please Enter the Transaction Amount : ");
    scanf("%f",&termData->transAmount);
    
    if(termData->transAmount > 0)
    {
        return OKK;
    }
    else
    {
        return INVALID_AMOUNT;
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount <= termData->maxTransAmount)
    {
        return OKK;
    }
    else
    {
        return EXCEED_MAX_AMOUNT;
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    printf("Please Enter the Transaction Amount : ");
    scanf("%f",&termData->maxTransAmount);
    
    if(termData->maxTransAmount > 0)
    {
        return OKK;
    }
    else
    {
        return INVALID_MAX_AMOUNT;
    }
}
