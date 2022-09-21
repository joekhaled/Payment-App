#include "App.h"


void appStart(void)
{
    Import_Bank_Server_Data(Accounts_Database);
    Import_Transactions_Data(Transactions_Database);
    Export_Transactions_Data(Transactions_Database);
}

void appUpdate(void)
{
    system("clear");

     switch(Main_Menu())
     {
         case '1':
             system("clear");
             New_Operation();
             break;
         case '2':
             system("clear");
             Search_Transaction();
             break;
         default:
             appUpdate();
             break;
     }
}

uint8_t Main_Menu()
{
    system("clear");
    printf("Please Choose Option From Below :- \n");
    printf("-----------------------------------\n");
    printf("1)New Operation\n");
    printf("2)Search for Old Transaction\n");
    printf("\n");
    printf("Choice : ");
    
    return getchar();
}

void New_Operation(void)
{
    ST_cardData_t New_Card;
    ST_terminalData_t New_Terminal;
    ST_transaction_t New_Transaction;
    
    Card_Module(&New_Card);

    if(!Terminal_Module(&New_Card,&New_Terminal))
    {
        New_Transaction.cardHolderData = New_Card;
        New_Transaction.terminalData = New_Terminal;
        
        EN_serverError_t Transaction_Error = Server_Module(&New_Transaction);
    }
    
    getchar();
    
    printf("\n\n----------------------------------------\n");
    printf("Go to Main Menu ? (Press Enter)");
    
    if(getchar())
    {
        Main_Menu();
    }
}
