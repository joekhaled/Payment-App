#include "Server.h"

ST_accountsDB_t Accounts_Database[Number_of_Max_Bank_Customers];
ST_transaction_t Transactions_Database[Number_of_Max_Transactions];

uint8_t Account_Array_Number=0;


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
            Account_Array_Number = C;
            return OKkk;
        }
    }
    
    return ACCOUNT_NOT_FOUND;
    
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if(termData->transAmount <= Accounts_Database[Account_Array_Number].balance)
    {
        return OKkk;
    }
    else
    {
        return LOW_BALANCE;
    }
}

EN_serverError_t Update_Account_Balance(ST_terminalData_t *termData)
{
    Accounts_Database[Account_Array_Number].balance = Accounts_Database[Account_Array_Number].balance - termData->transAmount;
    
    return OKkk;
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
    uint16_t Account_Number = 0;
    
    for(uint16_t C=0 ; C<Number_of_Max_Bank_Customers ; C++)
    {
        if(Transactions_Database[C].transactionSequenceNumber == transactionSequenceNumber)
        {
            Account_Number = C;
        }
    }
    
    if(Transactions_Database[Account_Number].transactionSequenceNumber <= Current_Transaction_Sequence_Num)
    {
        *transData = Transactions_Database[Account_Number];
        
        return OKkk;
    }
    else
    {
        return TRANSACTION_NOT_FOUND;
    }
}

void Search_Transaction(void)
{
    ST_transaction_t transData;
    uint32_t transactionSequenceNumber;
    
    printf("Please Enter Transaction Sequence Number : ");
    scanf("%d",&transactionSequenceNumber);
    
    
    if(!getTransaction(transactionSequenceNumber, &transData))
    {
        printf("\n\n");
        printf("Transaction Details :- \n");
        printf("-----------------------------------------------------------\n");
        printf("Card Holder Name : %s\n",transData.cardHolderData.cardHolderName);
        printf("Card Primary Account Number : %s\n",transData.cardHolderData.primaryAccountNumber);
        printf("Card Expiry Date : %s\n\n",transData.cardHolderData.cardExpirationDate);
        printf("Transaction Amount : %f\n",transData.terminalData.transAmount);
        printf("Transaction Date : %s\n",transData.terminalData.transactionDate);
        printf("Transaction State : ");
        
        switch(transData.transState)
        {
            case APPROVED :
                printf("APPROVED \n");
                break;
            case DECLINED_INSUFFECIENT_FUND:
                printf("DECLINED INSUFFECIENT FUND \n");
                break;
            case DECLINED_STOLEN_CARD:
                printf("DECLINED STOLEN CARD \n");
                break;
            case INTERNAL_SERVER_ERROR:
                printf("INTERNAL SERVER ERROR \n");
                break;
        }
    }
    else
    {
        printf("\n-----------------------------------------------------------\n");
        printf("Transaction Not Found in DataBase! \n");
    }
    
    getchar();
    
    printf("\n\n----------------------------------------\n");
    printf("Go to Main Menu ? (Press Enter)");
    
    getchar();
}

EN_serverError_t Server_Module(ST_transaction_t *transData)
{
    recieveTransactionData(transData);
    
    isValidAccount(&transData->cardHolderData);
    
    isAmountAvailable(&transData->terminalData);
    
    saveTransaction(transData);
    
    return OKkk;
}
