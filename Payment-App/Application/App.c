#include "App.h"

void appStart(void)
{
    ST_accountsDB_t Accounts_Database[Number_of_Max_Bank_Customers];
    Import_Bank_Server_Data(Accounts_Database);

    ST_transaction_t Transactions_Database[Number_of_Max_Transactions];
    Import_Transactions_Data(Transactions_Database);
    
    Export_Transactions_Data(Transactions_Database);
}

void appUpdate(void)
{
    //    ST_cardData_t Card1;
    //    ST_terminalData_t Data1;
    //
    //    int Z = getCardPAN(&Card1);
    //    int Y = isValidCardPAN(&Card1);
}

