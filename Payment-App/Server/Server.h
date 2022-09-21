#ifndef Server_h
#define Server_h

#include "../Standard Types.h"
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"

#define Number_of_Max_Bank_Customers 20
#define Number_of_Max_Transactions 20

//Enumerations
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
    OKkk , SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t ;


//Structures
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

//Global Database Arrays Prototypes
extern ST_accountsDB_t Accounts_Database[];
extern ST_transaction_t Transactions_Database[];


extern int Current_Transaction_Sequence_Num;

//Function Prototypes
EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t Update_Account_Balance(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
EN_serverError_t Server_Module(ST_transaction_t *transData);
void Search_Transaction(void);

#endif
