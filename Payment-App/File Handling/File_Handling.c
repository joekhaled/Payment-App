#include "File_Handling.h"

EN_FIle_Handling_t Import_Bank_Server_Data(ST_accountsDB_t *Accounts_Database)
{
    FILE *File_Ptr;
    
    File_Ptr = fopen("/Users/joe/Google Drive/Embedded Systems/Course/Egypt FWD/Embedded Systems Professional Nanodegree Program/Tasks/Payment-App/Payment-App/File Handling/Accounts_DB.txt","r");
    
    for(int C=0 ; C<Number_of_Max_Bank_Customers ; C++)
    {
        fscanf(File_Ptr,"PAN : %s , Balance : %f \n",Accounts_Database[C].primaryAccountNumber,&Accounts_Database[C].balance);
        fscanf(File_Ptr,"---------------------------------------------------------------------------------------\n");
        Last_Account_Array_Number++;
        
        if(feof(File_Ptr))
        {
            break;
        }
    }
    
    return fclose(File_Ptr);
}


EN_FIle_Handling_t Import_Transactions_Data(ST_transaction_t *Transactions_Database)
{
    
    FILE *File_Ptr;
    
    File_Ptr = fopen("/Users/joe/Google Drive/Embedded Systems/Course/Egypt FWD/Embedded Systems Professional Nanodegree Program/Tasks/Payment-App/Payment-App/File Handling/Transactions_DB.txt","r");
    
    for(int C=0 ; C<Number_of_Max_Transactions ; C++)
    {
        fscanf(File_Ptr,"Card Holder Name : %[^\n]\n",Transactions_Database[C].cardHolderData.cardHolderName);
        fscanf(File_Ptr,"Card Holder PAN : %s\n",Transactions_Database[C].cardHolderData.primaryAccountNumber);
        fscanf(File_Ptr,"Card Expiry Date : %s\n",Transactions_Database[C].cardHolderData.cardExpirationDate);
        fscanf(File_Ptr,"------------------------------------\n");
        fscanf(File_Ptr,"Transaction Amount : %f\n",&Transactions_Database[C].terminalData.transAmount);
        fscanf(File_Ptr,"Transaction Date : %s\n",Transactions_Database[C].terminalData.transactionDate);
        fscanf(File_Ptr,"------------------------------------\n");
        fscanf(File_Ptr,"Transaction State : (%d)\n",&Transactions_Database[C].transState);
        fscanf(File_Ptr,"------------------------------------\n");
        fscanf(File_Ptr,"Transaction Sequence Number : %d\n",&Transactions_Database[C].transactionSequenceNumber);
        fscanf(File_Ptr,"\n\n---------------------------------------------------------------------------------------\n\n");
        
        if(feof(File_Ptr))
        {
            Current_Transaction_Sequence_Num = Transactions_Database[C].transactionSequenceNumber;
            break;
        }
        
    }
    
    fclose(File_Ptr);
    
    return fclose(File_Ptr);
}

EN_FIle_Handling_t Export_Transactions_Data(ST_transaction_t *Transactions_Database)
{
    FILE *File_Ptr;
    
    File_Ptr = fopen("/Users/joe/Google Drive/Embedded Systems/Course/Egypt FWD/Embedded Systems Professional Nanodegree Program/Tasks/Payment-App/Payment-App/File Handling/Transactions_DB.txt","w");
    
    for(int C=0 ; C<= Current_Transaction_Sequence_Num ; C++)
    {
        fprintf(File_Ptr,"Card Holder Name : %s\n",Transactions_Database[C].cardHolderData.cardHolderName);
        fprintf(File_Ptr,"Card Holder PAN : %s\n",Transactions_Database[C].cardHolderData.primaryAccountNumber);
        fprintf(File_Ptr,"Card Expiry Date : %s\n",Transactions_Database[C].cardHolderData.cardExpirationDate);
        fprintf(File_Ptr,"------------------------------------\n");
        fprintf(File_Ptr,"Transaction Amount : %.2f\n",Transactions_Database[C].terminalData.transAmount);
        fprintf(File_Ptr,"Transaction Date : %s\n",Transactions_Database[C].terminalData.transactionDate);
        fprintf(File_Ptr,"------------------------------------\n");

        switch (Transactions_Database[Current_Transaction_Sequence_Num-1].transState)
        {
            case APPROVED:
                fprintf(File_Ptr,"Transaction State : (0)  \n");
                break;
            case DECLINED_INSUFFECIENT_FUND:
                fprintf(File_Ptr,"Transaction State : (1)  \n");
                break;
            case DECLINED_STOLEN_CARD:
                fprintf(File_Ptr,"Transaction State : (2)  \n");
                break;
            case INTERNAL_SERVER_ERROR:
                fprintf(File_Ptr,"Transaction State : (3)  \n");
                break;
        }
        
        fprintf(File_Ptr,"------------------------------------\n");
        fprintf(File_Ptr,"Transaction Sequence Number : %d\n",Transactions_Database[C].transactionSequenceNumber);
        fprintf(File_Ptr,"\n\n---------------------------------------------------------------------------------------\n\n");
    }
    
    fclose(File_Ptr);
    
    return fclose(File_Ptr);
}

EN_FIle_Handling_t Export_Bank_Server_Data(ST_accountsDB_t *Accounts_Database)
{
    FILE *File_Ptr;
    
    File_Ptr = fopen("/Users/joe/Google Drive/Embedded Systems/Course/Egypt FWD/Embedded Systems Professional Nanodegree Program/Tasks/Payment-App/Payment-App/File Handling/Accounts_DB.txt","w");
    
    for(int C=0 ; C<Number_of_Max_Bank_Customers ; C++)
    {
        if(Accounts_Database[C].primaryAccountNumber[0] == '\0')
        {
            break;
        }
        fprintf(File_Ptr,"PAN : %s , Balance : %.2f \n",Accounts_Database[C].primaryAccountNumber,Accounts_Database[C].balance);
        fprintf(File_Ptr,"---------------------------------------------------------------------------------------\n");
    }
    
    return fclose(File_Ptr);
}
