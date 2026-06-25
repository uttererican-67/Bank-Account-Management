#include <stdio.h>

//max 100 accounts
int accNumber[100];
int accPin[100];
char accName[100][50];
float accBalance[100];

int total = 0;
int nextNum = 1001;//acc number will start from 1001

//find acc pin,num 
int findAccount(int num, int pin) {
    for (int i = 0; i < total; i++) {
        if (accNumber[i] == num && accPin[i] == pin) {
            return i;
        }
    }
    return -1;//if found return i if not then just return -1
}

//tranfer acc
int findByNum(int num) {
    for (int i = 0; i < total; i++) {
        if (accNumber[i] == num) {
            return i;
        }
    }
    return -1;
}

//ask user for acc num and pin and return i if found else -1
int login() {
    int num, pin, i;
    printf("Account No: ");
    scanf("%d", &num);
    printf("PIN: ");
    scanf("%d", &pin);
    i = findAccount(num, pin);
    if (i == -1) {
        printf("Wrong number or PIN!\n");
    }
    return i;
}

int main() {
    int choice, i, j, num;
    float amount;

    do {
        printf("=== BANK SYSTEM ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. View Account\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            //create acc, assign acc number, ask for name, pin, deposit
            accNumber[total] = nextNum++;
            printf("Name: ");
            scanf(" %[^\n]", accName[total]);
            printf("PIN: ");
            scanf("%d", &accPin[total]);
            printf("Deposit: $");
            scanf("%f", &accBalance[total]);
            if (accBalance[total] < 0) { //close when user enter negative number
                printf("Cannot be negative!\n");
                nextNum--;
            } else {
                printf("Account created! Number: %d\n", accNumber[total]);
                total++;
            }

        } else if (choice == 2 || choice == 3) {
            //Deposit (choice 2) or Withdraw (choice 3)
            // Logs in first, then asks for an amount
            i = login();
            if (i == -1) continue;
            printf("Balance: $%.2f\n", accBalance[i]);
            printf("Amount: $");
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Must be more than zero!\n");
            } else if (choice == 3 && amount > accBalance[i]) {
                printf("Not enough money!\n");
            } else {
                if (choice == 2) accBalance[i] += amount;
                if (choice == 3) accBalance[i] -= amount;
                printf("Done! New balance: $%.2f\n", accBalance[i]);
            }

        } else if (choice == 4) {
            //Transfer
            i = login();
            if (i == -1) continue;
            printf("Send to Account No: ");
            scanf("%d", &num);
            j = findByNum(num);
            if (j == -1) {
                printf("Recipient not found!\n");
                continue;
            }
            if (i == j) {
                printf("Cannot send to yourself!\n");
                continue;
            }
            printf("Balance: $%.2f\n", accBalance[i]);
            printf("Amount: $");
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Must be more than zero!\n");
            } else if (amount > accBalance[i]) {
                printf("Not enough money!\n");
            } else {
                accBalance[i] -= amount;
                accBalance[j] += amount;
                printf("Sent $%.2f to %s! Your balance: $%.2f\n", amount, accName[j], accBalance[i]);
            }

        } else if (choice == 5) {
            i = login();
            if (i == -1) continue;
            //view acc 
            printf("Number: %d\n", accNumber[i]);
            printf("Name: %s\n", accName[i]);
            printf("Balance: $%.2f\n", accBalance[i]);

        } else if (choice != 6) {
            printf("Invalid choice!\n");
        }

    } while (choice != 6);

    printf("Thank you!\n");
    return 0;
}