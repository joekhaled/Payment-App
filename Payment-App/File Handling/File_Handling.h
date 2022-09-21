#ifndef File_Handling_h
#define File_Handling_h

#include "../Server/Server.h"


//Enumerations
typedef enum EN_FIle_Handling_t
{
    Done , Failed
}EN_FIle_Handling_t ;

//Function Prototypes
EN_FIle_Handling_t Import_Bank_Server_Data(ST_accountsDB_t *Accounts_Database);
EN_FIle_Handling_t Import_Transactions_Data(ST_transaction_t *Transactions_Database);
EN_FIle_Handling_t Export_Transactions_Data(ST_transaction_t *Transactions_Database);

extern int Current_Transaction_Sequence_Num;

#endif
