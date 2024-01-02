#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

class BankAccount {
private:
    std::string accountHolder;
    double balance;
    std::string password;

public:
    BankAccount(const std::string& holder, double initialBalance, const std::string& pwd)
            : accountHolder(holder), balance(initialBalance), password(pwd) {}

    const std::string& getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    bool checkPassword(const std::string& pwd) const {
        return password == pwd;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposit successful. New balance: " << balance << std::endl;
        } else {
            std::cout << "Invalid deposit amount." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawal successful. New balance: " << balance << std::endl;
        } else {
            std::cout << "Invalid withdrawal amount or insufficient funds." << std::endl;
        }
    }
};

class ATM {
private:
    std::vector<BankAccount> accounts;

public:
    void createAccount(const std::string& holder, double initialBalance, const std::string& pwd) {
        accounts.emplace_back(holder, initialBalance, pwd);
        std::cout << "Account created successfully." << std::endl;
    }

    BankAccount* findAccount(const std::string& holder, const std::string& pwd) {
        for (auto& account : accounts) {
            if (account.getAccountHolder() == holder && account.checkPassword(pwd)) {
                return &account;
            }
        }
        return nullptr;
    }

    void displayBalance(BankAccount* account) {
        if (account != nullptr) {
            std::cout << "Account Holder: " << account->getAccountHolder() << std::endl;
            std::cout << "Balance: " << account->getBalance() << std::endl;
        } else {
            std::cout << "Account not found or incorrect password." << std::endl;
        }
    }
};

int main() {
    ATM atm;

    // Create two testing accounts
    atm.createAccount("1234qwerty", 1000.0, "qwerty1234");
    atm.createAccount("4321ytrewq", 500.0, "ytrewq4321");

    while (true) {
        std::cout << "Enter account holder name (or 'exit' to quit): ";
        std::string accountHolder;
        std::cin >> accountHolder;

        if (accountHolder == "exit") {
            break;
        }

        std::cout << "Enter account password: ";
        std::string password;
        std::cin >> password;

        BankAccount* account = atm.findAccount(accountHolder, password);

        if (account != nullptr) {
            std::cout << "1. Display Balance\n2. Deposit\n3. Withdraw\nChoose option (1-3): ";
            int option;
            std::cin >> option;

            switch (option) {
                case 1:
                    atm.displayBalance(account);
                    break;
                case 2:
                    double depositAmount;
                    std::cout << "Enter deposit amount: ";
                    std::cin >> depositAmount;
                    account->deposit(depositAmount);
                    break;
                case 3:
                    double withdrawalAmount;
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> withdrawalAmount;
                    account->withdraw(withdrawalAmount);
                    break;
                default:
                    std::cout << "Invalid option. Please choose again." << std::endl;
            }
        } else {
            std::cout << "Account not found or incorrect password. Please enter valid account holder name and password." << std::endl;
        }
    }

    return 0;
}
