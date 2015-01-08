#include <string>
#include <iostream>
#include "exception.h"

class Account
{
private:
       double balance;
public:
    Account::Account()
	{
		balance = 0;
	}
	explicit Account::Account(double initialDeposit)
	{
		balance = initialDeposit;
	}
	double getBalance()
	{
		return balance;
	}
	double setBalance(double amount)
	{
		balance += amount;
	}	
};

// returns new balance or -1 if error
double deposit(Account account, double amount)
	{
		double balance = account.getBalance();
		if (amount > 0)
			balance += amount;
		else
			return -1; // code indicating error
		return account.setBalance(balance);
	}

// returns new balance or -1 if invalid amount
double withdraw(Account account, double amount)
	{
		double balance = account.getBalance();
		if((amount > account.getBalance()) || (amount < 0))
			return -1;
		else
			balance -= amount;
		return account.setBalance(balance);
	}