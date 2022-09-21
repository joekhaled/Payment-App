#include "Server.h"

ST_accountsDB_t Accounts_Database[Number_of_Max_Bank_Customers];
ST_transaction_t Transactions_Database[Number_of_Max_Transactions];
int Current_Transaction_Sequence_Num = 0;

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if(isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
    {
        return DECLINED_STOLEN_CARD;
    }
    else if(isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
    {
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if(saveTransaction(transData) == SAVING_FAILED)
    {
        return INTERNAL_SERVER_ERROR;
    }
    else
    {
        return APPROVED;
    }
    
}


EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    
    for(uint16_t C=0 ; C<Number_of_Max_Bank_Customers ; C++)
    {
        if(cardData->primaryAccountNumber == Transactions_Database[C].cardHolderData.primaryAccountNumber)
        {
            return OKkk;
        }
    }
    
    return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if(termData->transAmount <= Accounts_Database[1].balance)
    {
        return OKkk;
    }
    else
    {
        return LOW_BALANCE;
    }
}


EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    if(1)//Export_Transactions_Data(Transactions_Database))
    {
        transData = &Transactions_Database[Current_Transaction_Sequence_Num+1];
        return OKkk;
    }
    else
    {
        return SAVING_FAILED;
    }
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    if(transactionSequenceNumber > Current_Transaction_Sequence_Num)
    {
        transData = &Transactions_Database[transactionSequenceNumber-1];
        
        return OKkk;
    }
    
    return TRANSACTION_NOT_FOUND;
}
