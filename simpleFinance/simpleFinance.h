/********************************************************
*
* simpleFinance.h
* Shaishav Parekh, ECE 2524
* Application header for class Finance. Provides
* methods and structures.
*
********************************************************/
#ifndef SIMPLEFINANCE_H
#define SIMPLEFINANCE_H

#include <QFile>
#include <QDate>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QList>
#include <iostream>
#include <iomanip>

// holds a goal
struct goal
{
    QString description;
    double amountToGoal;
    double amountSaved;
    QString endDate;
};

// holds expenses/incomes
struct cashflow
{
    QString description;
    double amount;
    QString dateEntered;
};

class Finance
{
public:
    Finance();
    ~Finance();

    // Open a file
    bool openFinanceFile(const QString &Filename);

    // Sets the owner
    void setOwner(QString owner);

    // Shows the owner
    void showOwner();

    // Adds an expense
    bool addExpense(QString desc, double amount, QString date, bool calc);

    // Removes an expense
    bool removeExpense(QString desc);

    // Adds an income
    bool addIncome(QString desc, double amount, QString date, bool calc);

    // Removes an income
    bool removeIncome(QString desc);

    // Adds a goal
    bool addGoal(QString desc, double amountToSave, double amountSaved, QString endDate);

    // Removes a goal
    bool removeGoal(QString desc);

    // Modifies currently saved amount for a goal
    bool modifyGoalAmount(QString desc, double amountCurrentlySaved);

    // Modifies end date for a goal
    bool modifyGoalDate(QString desc, QString newEnd);

    // Modifies bank amount
    void modifyBankAmount(double newAmount);

    // saves changes to file
    void saveToFile();

    // populates expense, income and goal lists
    void createLists();

    // prints goals
    void showGoals();

    // prints expenses
    void showExpenses();

    // prints incomes
    void showIncomes();

    // prints amount
    void showAmount();

    // prints help
    void showHelp();

private:
    // holds account balance
    double amountInBank;
    // holds file
    QFile myFinanceFile;
    // holds filename
    QString myFile;
    // holds fileowner
    QString fileOwner;
    // holds all goals
    QList<goal*> goalList;
    // holds all incomes
    QList<cashflow*> incomeList;
    // holds all expenses
    QList<cashflow*> expenseList;
};

#endif // SIMPLEFINANCE_H
