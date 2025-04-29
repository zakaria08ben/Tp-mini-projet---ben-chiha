#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct Account {
    char name[100];
    int accountNumber;
    char password[20];
    float balance;
};

struct Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;
void saveToFile() {
    FILE *file = fopen("accounts.txt", "w");
    for (int i = 0; i < totalAccounts; i++) {
        fprintf(file, "%s %d %s %.2f\n",
                accounts[i].name,
                accounts[i].accountNumber,
                accounts[i].password,
                accounts[i].balance);
    }
    fclose(file);
}
void loadFromFile() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%s %d %s %f",
                  accounts[totalAccounts].name,
                  &accounts[totalAccounts].accountNumber,
                  accounts[totalAccounts].password,
                  &accounts[totalAccounts].balance) != EOF) {
        totalAccounts++;
    }
    fclose(file);
}
void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("connot create more accounts.\n");
        return;
    }
    printf("Enter the name: ");
    scanf("%s", accounts[totalAccounts].name);
    printf("Enter the account numbers: ");
    scanf("%d", &accounts[totalAccounts].accountNumber);
    printf("Enter the password: ");
    scanf("%s", accounts[totalAccounts].password);
    accounts[totalAccounts].balance = 0.0;
    totalAccounts++;
    saveToFile();
    printf("Account created successfully .\n");
}
int login() {
    int accNo;
    char pass[20];
    printf("Enter the account number: ");
    scanf("%d", &accNo);
    printf("Enter the password: ");
    scanf("%s", pass);

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo &&
            strcmp(accounts[i].password, pass) == 0) {
            printf("successfully logged in .\n");
            return i;
        }
    }
    printf("Incorrect login credentials.\n");
    return -1;
}
void depositMoney(int index) {
    float amount;
    printf("Enter the deposit amount: ");
    scanf("%f", &amount);
    accounts[index].balance += amount;
    saveToFile();
    printf("Deposit successful.\n");
}
void transferMoney(int index) {
    int targetAcc;
    float amount;
    printf("Enter the beneficiary's account number: ");
    scanf("%d", &targetAcc);
    printf(" Enter the amount: ");
    scanf("%f", &amount);

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == targetAcc) {
            if (accounts[index].balance >= amount) {
                accounts[index].balance -= amount;
                accounts[i].balance += amount;
                saveToFile();
                printf("transfer successful.\n");
            } else {
                printf("Insufficient balance.\n");
            }
            return;
        }
    }
    printf("existing account .\n");
}
void checkBalance(int index) {
    printf("current fishing:.2f\n", accounts[index].balance);
}
void deleteAccount(int index) {
    if (accounts[index].balance != 0) {
        printf("account deletion is only possible if the catch is zero.\n");
        return;
    }
    for (int i = index; i < totalAccounts - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    totalAccounts--;
    saveToFile();
    printf("Account deleted.\n");
}
int main() {
    loadFromFile();
    int choice;
    while (1) {
        printf("\n----------- welcome to our bank-----------\n");
        printf("1. create an account\n");
        printf("2. sign in \n");
        printf("3. log out\n");
        printf("your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createAccount();
        } else if (choice == 2) {
            int index = login();
            if (index != -1) {
                int option;
                while (1) {
                    printf("\n1. deposit\n2. transfer\n3. balance\n4. Delete deleteAccount\n5. log out\n");
                    printf("your choice: ");
                    scanf("%d", &option);
                    if (option == 1) depositMoney(index);
                    else if (option == 2) transferMoney(index);
                    else if (option == 3) checkBalance(index);
                    else if (option == 4) deleteAccount(index);
                    else break;
                }
            }
        } else {
            printf("Thanks you for using the system. Goodbye!\n");
            break;
        }
    }
    return 0;
}

    