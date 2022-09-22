#include "Server.h"

ST_accountsDB_t Accounts_Database[Number_of_Max_Bank_Customers];
ST_transaction_t Transactions_Database[Number_of_Max_Transactions];

uint32_t Last_Account_Array_Number = 0;
uint32_t Current_Account_Array_Number = 0;
uint32_t Current_Transaction_Sequence_Num = 0;

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if(isValidAccount(&transData->cardHolderData))
    {
        return DECLINED_STOLEN_CARD;
    }
    else if(isAmountAvailable(&transData->terminalData))
    {
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if(saveTransaction(transData))
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
    
    for(uint16_t C=0 ; (C<Number_of_Max_Bank_Customers) && (Accounts_Database[C].primaryAccountNumber[0] != '\0') ; C++)
    {
        if(!strcmp((const char*) &cardData->primaryAccountNumber , (char*)&Accounts_Database[C].primaryAccountNumber) )
        {
            Current_Account_Array_Number = C;
            return OKkk;
        }
    }
    
    return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if(termData->transAmount <= Accounts_Database[Current_Account_Array_Number].balance)
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
    Accounts_Database[Current_Account_Array_Number].balance = Accounts_Database[Current_Account_Array_Number].balance - termData->transAmount;
    
    return OKkk;
}




EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    transData = &Transactions_Database[Current_Transaction_Sequence_Num];
    return OKkk;
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
    
    if(transactionSequenceNumber <= Current_Transaction_Sequence_Num)
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
        printf("Transaction Amount : %.2f\n",transData.terminalData.transAmount);
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
        printf("Transaction Not Found in DataBase ! \n");
    }
    
    getchar();
    
    printf("\n\n----------------------------------------\n");
    printf("Go to Main Menu ? (Press Enter)");
    
    getchar();
}

void Server_Module(ST_transaction_t *transData)
{
    transData->transState = recieveTransactionData(transData);
    
    Current_Transaction_Sequence_Num++;
    strcpy((char*) &Transactions_Database[Current_Transaction_Sequence_Num].cardHolderData.cardHolderName , (const char*)&transData->cardHolderData.cardHolderName);
    strcpy((char*) &Transactions_Database[Current_Transaction_Sequence_Num].cardHolderData.primaryAccountNumber , (const char*)&transData->cardHolderData.primaryAccountNumber );
    strcpy((char*) &Transactions_Database[Current_Transaction_Sequence_Num].cardHolderData.cardExpirationDate , (const char*)&transData->cardHolderData.cardExpirationDate);
    strcpy((char*) &Transactions_Database[Current_Transaction_Sequence_Num].terminalData.transactionDate , (const char*)&transData->terminalData.transactionDate);
    Transactions_Database[Current_Transaction_Sequence_Num].terminalData.transAmount = transData->terminalData.transAmount;
    Transactions_Database[Current_Transaction_Sequence_Num].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    Transactions_Database[Current_Transaction_Sequence_Num].transState = transData->transState;
    Transactions_Database[Current_Transaction_Sequence_Num].transactionSequenceNumber = Current_Transaction_Sequence_Num;
    
    if(transData->transState == APPROVED)
    {
        Update_Account_Balance(&transData->terminalData);
        printf("Transaction Approved ! \n");
    }
    else
    {
        printf("Transaction Rejected ! \n");
    }
    printf("Transaction Saved ! \n\n");
}

void Add_New_Account(void)
{
    ST_cardData_t New_ACC;
    
    getchar();
    
    do
    {
        while(getCardPAN(&New_ACC));
        
    }while(isValidCardPAN(&New_ACC));
    
    if(!(isValidAccount(&New_ACC)))
    {
        system("clear");
        printf("Already Saved in Bank Database! (%d)\n",Current_Account_Array_Number);
        Add_New_Account();
    }
    
    strcpy((char*) &Accounts_Database[Last_Account_Array_Number].primaryAccountNumber, (const char*) &New_ACC.primaryAccountNumber);
    
    printf("Enter Account Balance : ");
    scanf("%f",&Accounts_Database[Last_Account_Array_Number].balance);
}
