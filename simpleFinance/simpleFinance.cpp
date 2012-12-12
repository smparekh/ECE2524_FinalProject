/********************************************************
*
* simpleFinance.cpp
* Shaishav Parekh, ECE 2524
* Implementation file for class Finance. Defines and
* implements functions for the interface
*
********************************************************/
#include "simpleFinance.h"


/*************************************************************
 * Constructor
 ************************************************************/
Finance::Finance()
{
    amountInBank = 0;
}

/*************************************************************
 * Destructor
 ************************************************************/
Finance::~Finance()
{
    if (myFinanceFile.isOpen())
        myFinanceFile.close();
}

/*************************************************************
 * Function: bool openFinanceFile(const QString &Filename)
 *
 * Description: Opens Filename and reads its content. If the
 * contents are empty returns false else returns true.
 *
 * Returns: true or false
 ************************************************************/
bool Finance::openFinanceFile(const QString &Filename)
{
    // open the file for reading
    myFinanceFile.setFileName(Filename);
    myFinanceFile.open(QIODevice::ReadOnly|QIODevice::Text);

    myFile.clear();

    QTextStream in(&myFinanceFile);

    // read its contents
    myFile = in.readAll();
    // close the file
    myFinanceFile.close();
    // if its empty return false
    if (myFile.isEmpty())
        return false;

    // else display that file is loaded and return true
    std::cout << "File Loaded.\n";

    return true;
}

/*************************************************************
 * Function: void setOwner(QString owner)
 *
 * Description: Sets or modifies the owner.
 *
 * Returns: none.
 ************************************************************/
void Finance::setOwner(QString owner)
{
    fileOwner = owner;
}


/*************************************************************
 * Function: void showOwner()
 *
 * Description: Outputs owner to the standard output.
 *
 * Returns: none.
 ************************************************************/
void Finance::showOwner()
{
    std::cout << fileOwner.toStdString() << std::endl;
}

/*************************************************************
 * Function: void createLists()
 *
 * Description: Reads a finance file and inputs all the
 * information: owner, amount, expenses, incomes, goals.
 *
 * Returns: none.
 ************************************************************/
void Finance::createLists()
{
    // Read the file and input amount in bank, expenses,
    // income, goals
    QStringList splitFile;
    splitFile = myFile.split(QRegExp("\\n"), QString::SkipEmptyParts);

    for(int i = 0; i < splitFile.size(); i++)
    {
        // Extract owner
        if (splitFile.at(i).contains("Owner: "))
        {
            QStringList owner = splitFile.at(i).split(QRegExp("\\bOwner: \\b"), QString::SkipEmptyParts);
            // owner
            fileOwner = owner.at(0);

        }
        // Extract amount
        else if (splitFile.at(i).contains("Amount In Bank: "))
        {
            QStringList amount = splitFile.at(i).split(QRegExp("(\\W|^)Amount\\s{0,3}In\\s{0,3}Bank:(\\W|$)"), QString::SkipEmptyParts);
            // amount
            amountInBank = amount.at(0).toDouble();
        }
        // Extract expenses
        else if (splitFile.at(i).contains("Expense: "))
        {
            QStringList expense = splitFile.at(i).split(QRegExp("\\bExpense: \\b"), QString::SkipEmptyParts);

            // variables
            QString newExEntry = expense.at(0);
            QStringList splitEntry;
            // split expense into description, amount, date of expense
            splitEntry = newExEntry.split(", ", QString::SkipEmptyParts);
            // add expense to list
            addExpense(splitEntry.at(0), splitEntry.at(1).toDouble(), splitEntry.at(2), false);
        }
        // Extract incomes
        else if (splitFile.at(i).contains("Income: "))
        {
            QStringList income = splitFile.at(i).split(QRegExp("\\bIncome: \\b"), QString::SkipEmptyParts);

            // variables
            QString newInEntry = income.at(0);
            QStringList splitEntry;
            // split income into description, amount, date of income
            splitEntry = newInEntry.split(", ", QString::SkipEmptyParts);
            // add income to list
            addIncome(splitEntry.at(0), splitEntry.at(1).toDouble(), splitEntry.at(2), false);
        }
        // Extract goals
        else if (splitFile.at(i).contains("Goal: "))
        {
            QStringList goal = splitFile.at(i).split(QRegExp("\\bGoal: \\b"), QString::SkipEmptyParts);

            // variables
            QString newGoEntry = goal.at(0);
            QStringList splitEntry;
            // split goal into description, amount, date of goal, amount saved
            splitEntry = newGoEntry.split(", ", QString::SkipEmptyParts);
            // add goal to list
            addGoal(splitEntry.at(0), splitEntry.at(1).toDouble(), splitEntry.at(2).toDouble(), splitEntry.at(3));
        }
    }
}

/**********************************************************************************
 * Function: bool addExpense(QString desc, double amount, QString date, bool calc)
 *
 * Description: Adds an expense to the expense list. Arguments are the description
 * of the expense, amount, date and the bool calc. The boolean checks if its
 * necessary to update the amount in the bank.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::addExpense(QString desc, double amount, QString date, bool calc)
{
    // create new expense
    cashflow* nExpense = new cashflow;
    if (nExpense == NULL)
        return false;

    // construct expense
    nExpense->amount = amount;
    nExpense->dateEntered = date;
    nExpense->description = desc;

    // append expense
    expenseList.append(nExpense);

    // update amount in bank if necessary
    if (calc)
    {
        double newBank = amountInBank - amount;
        modifyBankAmount(newBank);
    }

    return true;
}

/**********************************************************************************
 * Function: bool removeExpense(QString desc)
 *
 * Description: Removes an expense from the expense list. Updates the amount in
 * the bank.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::removeExpense(QString desc)
{
    // Search for expense
    for (int i = 0; i < expenseList.size(); i++)
    {
        // if found update the amount in bank, remove it and return
        if (expenseList.at(i)->description == desc)
        {
            double newBank = amountInBank + expenseList.at(i)->amount;
            modifyBankAmount(newBank);
            expenseList.removeAt(i);
            return true;
        }
    }
    // if expense is not found return false
    return false;
}

/**********************************************************************************
 * Function: bool addIncome(QString desc, double amount, QString date, bool calc)
 *
 * Description: Adds an income to the income list. Arguments are the description
 * of the expense, amount, date and the bool calc. The boolean checks if its
 * necessary to update the amount in the bank.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::addIncome(QString desc, double amount, QString date, bool calc)
{
    // new income
    cashflow* nIncome = new cashflow;
    if (nIncome == NULL)
        return false;

    // construct income
    nIncome->amount = amount;
    nIncome->description = desc;
    nIncome->dateEntered = date;

    // add to income list
    incomeList.append(nIncome);

    // update the amount in bank if necessary
    if (calc)
    {
        double newBank = amountInBank + amount;
        modifyBankAmount(newBank);
    }
    return true;
}

/**********************************************************************************
 * Function: bool removeIncome(QString desc)
 *
 * Description: Removes an income from the income list. Updates the amount in bank.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::removeIncome(QString desc)
{
    // Search for income
    for (int i = 0; i < incomeList.size(); i++)
    {
        // If found, update amount in bank, remove it and return true
        if (incomeList.at(i)->description == desc)
        {
            double newBank = amountInBank - incomeList.at(i)->amount;
            modifyBankAmount(newBank);
            incomeList.removeAt(i);
            return true;
        }
    }
    // return false if income not found
    return false;
}

/************************************************************************************************
 * Function: bool addGoal(QString desc, double amountToSave, double amountSaved, QString endDate
 *
 * Description: Adds a goal to the goal list. Inputs are a description, amount needed for reaching
 * goal, amount currently saved for goal and end date of goal. This function does not affect
 * amount in bank.
 *
 * Returns: true on success or false
 ***********************************************************************************************/
bool Finance::addGoal(QString desc, double amountToSave, double amountSaved, QString endDate)
{
    // new goal
    goal* nGoal = new goal;
    if (nGoal == NULL)
        return false;

    // construct new goal
    nGoal->description = desc;
    nGoal->amountToGoal = amountToSave;
    nGoal->amountSaved = amountSaved;
    nGoal->endDate = endDate;

    // add new goal to goal list
    goalList.append(nGoal);

    return true;
}

/**********************************************************************************
 * Function: bool removeGoal(QString desc)
 *
 * Description: Removes a goal from the goal list based on the description.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::removeGoal(QString desc)
{
    // Search for goal
    for (int i = 0; i < goalList.size(); i++)
    {
        if(goalList.at(i)->description == desc)
        {
            // if found remove it and return true
            goalList.removeAt(i);
            return true;
        }
    }
    // else return false
    return false;
}

/**********************************************************************************
 * Function: bool modifyGoalAmount(QString desc, double amountCurrentlySaved)
 *
 * Description: Modifies the amount of money currently saved for a goal. Searches
 * the goal list for a goal based on the description. Modifies the goal if found.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::modifyGoalAmount(QString desc, double amountCurrentlySaved)
{
    // Search for goal
    for (int i = 0; i < goalList.size(); i++)
    {
        // if found, update the amount and return true
        if(goalList.at(i)->description == desc)
        {
            goalList.at(i)->amountSaved = amountCurrentlySaved;
            return true;
        }
    }
    // else return false
    return false;
}

/**********************************************************************************
 * Function: bool modifyGoalDate(QString desc, QString newEnd)
 *
 * Description: Modifies the end date of a goal. Searches the goal list for a goal
 * based on the description. Modifies the goal if found.
 *
 * Returns: true on success or false
 **********************************************************************************/
bool Finance::modifyGoalDate(QString desc, QString newEnd)
{
    // Search the goal
    for (int i = 0; i < goalList.size(); i++)
    {
        // if found, update the end date and return true
        if(goalList.at(i)->description == desc)
        {
            goalList.at(i)->endDate = newEnd;
            return true;
        }
    }
    // else return false
    return false;
}

/**********************************************************************************
 * Function: void showGoals()
 *
 * Description: Prints all current goals saved in memory to standard output.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::showGoals()
{
    for (int i = 0; i < goalList.size(); i++)
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Goal " << i << ":" << std::endl;
        std::cout << "Description: " << goalList.at(i)->description.toStdString() << std::endl;
        std::cout << "Amount Currently Saved: $" << goalList.at(i)->amountSaved << std::endl;
        std::cout << "Goal Amount: $" << goalList.at(i)->amountToGoal << std::endl;
        std::cout << "End Date: " << goalList.at(i)->endDate.toStdString() << std::endl;
    }
}

/**********************************************************************************
 * Function: void showExpenses()
 *
 * Description: Prints all current expenses saved in memory to standard output.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::showExpenses()
{
    for (int i = 0; i < expenseList.size(); i++)
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Expense " << i << ":" << std::endl;
        std::cout << "Description: " << expenseList.at(i)->description.toStdString() << std::endl;
        std::cout << "Amount: $" << expenseList.at(i)->amount << std::endl;
        std::cout << "Date of Expense: " << expenseList.at(i)->dateEntered.toStdString() << std::endl;
    }
}

/**********************************************************************************
 * Function: void showIncomes()
 *
 * Description: Prints all current incomes saved in memory to standard output.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::showIncomes()
{
    for (int i = 0; i < incomeList.size(); i++)
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Income " << i << ":" << std::endl;
        std::cout << "Description: " << incomeList.at(i)->description.toStdString() << std::endl;
        std::cout << "Amount: $" << incomeList.at(i)->amount << std::endl;
        std::cout << "Date of Income: " << incomeList.at(i)->dateEntered.toStdString() << std::endl;
    }
}

/**********************************************************************************
 * Function: void saveToFile()
 *
 * Description: Saves changes made during session to file. Fails if no file
 * was opened during session.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::saveToFile()
{
    if (!fileOwner.isEmpty())
    {
        // Open the file for overwriting
        myFinanceFile.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate);

        // redirect file output
        QTextStream out(&myFinanceFile);
        // set precision to better output money
        out.setRealNumberNotation(QTextStream::FixedNotation);
        out.setRealNumberPrecision(2);
        // output owner
        out << "Owner: " << fileOwner << endl;
        // output last modified
        out << "Last Modified: " << QDate::currentDate().toString() << endl;
        // output amount in bank
        out << "Amount In Bank: " << amountInBank << endl;
        // out all expenses
        if (!expenseList.isEmpty())
        {
            for (int i = 0; i < expenseList.size(); i++)
            {
                out << "Expense: " << expenseList.at(i)->description
                       << ", " << expenseList.at(i)->amount
                       << ", " << expenseList.at(i)->dateEntered << endl;
            }
        }
        // out all incomes
        if (!incomeList.isEmpty())
        {
            for (int i = 0; i < incomeList.size(); i++)
            {
                out << "Income: " << incomeList.at(i)->description
                       << ", " << incomeList.at(i)->amount
                       << ", " << incomeList.at(i)->dateEntered << endl;
            }
        }
        // out all goals
        if (!goalList.isEmpty())
        {
            for (int i = 0; i < goalList.size(); i++)
            {
                out << "Goal: " << goalList.at(i)->description
                    << ", " << goalList.at(i)->amountSaved
                    << ", " << goalList.at(i)->amountToGoal
                    << ", " << goalList.at(i)->endDate << endl;
            }
        }
    }
}

/**********************************************************************************
 * Function: void showHelp()
 *
 * Description: Prints information about all commands associated with Finance class
 * to standard output.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::showHelp()
{
    std::cout << "Usage: For a better version see help file in program folder." << std::endl;
    // LOAD function
    std::cout << "load <filename>: loads file specified by <filename> parameter." << std::endl << std::endl;
    std::cout << "create <filename>: creates a finance file specified by <filename>." << std::endl << std::endl;
    // ADD function
    std::cout << "add <expense/income> <description> <amount> <date>: Adds an expense or income." << std::endl;
    std::cout << "\t\t<description> give a one word description to your expense or income." << std::endl;
    std::cout << "\t\t<amount> amount of expense or income." << std::endl;
    std::cout << "\t\t<date> enter the date of the transaction in format MM/DD/YYYY." << std::endl << std::endl;
    std::cout << "add goal <description> <amountSaved> <goalAmount> <endDate>: create a goal." << std::endl;
    std::cout << "\t\t<description> give a one word description to your goal." << std::endl;
    std::cout << "\t\t<amountSaved> amount currently saved" << std::endl;
    std::cout << "\t\t<goalAmount> amount of money needed to complete the goal." << std::endl;
    std::cout << "\t\t<endDate> enter the completion date of goal in format MM/DD/YYYY." << std::endl << std::endl;
    // REMOVE function
    std::cout << "remove <expense/income/goal> <description: Removes an expense, income or goal based on the description." << std::endl;
    std::cout << "\t\t<description> one word description of the expense, income or goal." << std::endl;
    std::cout << "\t\tBest used in conjunction with show to check the description of the item to be removed." << std::endl << std::endl;
    // SET function
    std::cout << "set owner <first> <last>: Sets the owner of the file specified by <first> and <last> name" << std::endl;
    std::cout << "set amount <amount>: Sets the amount of money in the bank specified by <amount>" << std::endl << std::endl;
    // SHOW function
    std::cout << "show owner: Shows the owner of the current file loaded into memory." << std::endl;
    std::cout << "show amount: Shows the amount of money in the bank account for the current owner." << std::endl;
    std::cout << "show expenses: Shows all expenses from the current file." << std::endl;
    std::cout << "show income: Shows all incomes from the current file." << std::endl;
    std::cout << "show goals: Shows all goals from the current file." << std::endl << std::endl;
    // MODIFY function
    std::cout << "modify amount <goal> <amount>: Modifies the amount of money to goal." << std::endl;
    std::cout << "\t\t<goal>: description of the goal to modify." << std::endl;
    std::cout << "\t\t<amount>: new amount of money to the goal." << std::endl;
    std::cout << "modify date <goal> <date>: Modifies the end date of goal." << std::endl;
    std::cout << "\t\t<goal>: description of the goal to modify." << std::endl;
    std::cout << "\t\t<date>: new end date for goal in format MM/DD/YYYY." << std::endl << std::endl;

}

/**********************************************************************************
 * Function: void modifyBankAmount(double newAmount)
 *
 * Description: Changes/updates amount in bank.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::modifyBankAmount(double newAmount)
{
    amountInBank = newAmount;
}

/**********************************************************************************
 * Function: void showAmount()
 *
 * Description: Prints current amount in bank to standard output.
 *
 * Returns: none.
 **********************************************************************************/
void Finance::showAmount()
{
    std::cout << "$" << std::fixed << std::setprecision(2) << amountInBank << std::endl;
}
