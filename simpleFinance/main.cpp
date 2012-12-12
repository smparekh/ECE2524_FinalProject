/********************************************************
*
* main.cpp
* Shaishav Parekh, ECE 2524
* Interface for finance class.
* Provides a prompt to add, remove and modify finances.
*
********************************************************/
#include <QCoreApplication>
#include "simpleFinance.h"
#include <QDate>
using namespace std;
int main(int argc, char *argv[])
{
    // Error Check
    if (argc > 1)
    {
        cerr << "Error: Invalid Usage\n Usage: ./simpleFinance\n";
    }
    else
    {
        // variables to hold commands entered by a user
        string arg;
        QString qarg;
        QStringList cmds;

        // show greeting
        cout << "Welcome to Simple Finance!" << endl;
        cout << "Enter a command, type in 'help' for help. ";
        cout << "Remember changes WILL NOT be saved without a owner." << endl;
        cout << "Check the help file included in the directory for examples." << endl;
        cout << "ECE 2524 Intro to UNIX, Shaishav Parekh" << endl;
        cout << QDate::currentDate().toString().toStdString() << endl;

        // create a session
        Finance financeSession;
        // read and execute commands until 'exit' is called
        while (true)
        {
            // command prompt
            cout << "% ";
            // get argument
            getline(cin, arg);
            // Transform into QString
            qarg = QString::fromStdString(arg);
            // Split argument into a QStringList by spaces
            cmds = qarg.split(QRegExp("\\s"), QString::SkipEmptyParts);

            /*************************************************************
             * Command: help
             * Function: displays help
             ************************************************************/
            if (cmds.at(0) == "help")
            {
                financeSession.showHelp();
            }
            /*************************************************************
             * Command: load <filename>
             * Function: Loads <filename> into memory. Also reads the
             * file for owner, amount, expenses, incomes, and goals.
             ************************************************************/
            else if (cmds.at(0) == "load")
            {
                // Error check number of arguments
                if (cmds.size() != 2)
                {
                    cout << "Invalid Usage, command not executed, see help file for more info" << endl;
                }
                else
                {
                    // make sure file is created successfully
                    bool create;
                    QString file = cmds.at(1) + ".txt";
                    create = financeSession.openFinanceFile(file);
                    // if it is read for owner, amount, expenses, incomes and goals
                    if (create)
                    {
                        financeSession.createLists();
                    }
                    // else inform the user that file is empty
                    else
                    {
                        cout << "File is empty. You can add or modify elements." << endl;
                    }
                }
            }
            /*************************************************************
             * Command: create <filename>
             * Function: Creates a file with the specified <filename>.
             ************************************************************/
            else if (cmds.at(0) == "create")
            {
                // Error check number of arguments
                if (cmds.size() != 2)
                {
                    cout << "Invalid Usage, command not executed, see help file for more info" << endl;
                }
                else
                {
                    // create the file, make sure it doesn't already exits in the directory
                    bool newFile;
                    QString filename = cmds.at(1) + ".txt";
                    newFile = financeSession.openFinanceFile(filename);
                    // Check existence
                    if (!newFile)
                    {
                        cout << "File created.\n";
                    }
                    else
                    {
                        cout << "File already exists, cannot create file of same name "
                             << "If you want to use this file load it or create a file "
                             << "with another name.\n";
                    }
                }
            }
            /*************************************************************
             * Command: show <option>
             * Function: Shows information related to <option>.
             * Options are:
             * Owner, Amount in Bank, Expenses, Income and Goals.
             ************************************************************/
            else if (cmds.at(0) == "show")
            {
                // Error check number of arguments
                if (cmds.size() != 2)
                {
                    cout << "Invalid Usage, please see help file." << endl;
                }
                else
                {
                    // Show owner
                    if (QString::compare(cmds.at(1), "Owner", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.showOwner();
                    }
                    // Show amount in bank
                    else if (QString::compare(cmds.at(1), "Amount", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.showAmount();
                    }
                    // Show list of expenses
                    else if (QString::compare(cmds.at(1), "Expenses", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.showExpenses();
                    }
                    // Show list of incomes
                    else if (QString::compare(cmds.at(1), "Income", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.showIncomes();
                    }
                    // Show list of goals
                    else if (QString::compare(cmds.at(1), "Goals", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.showGoals();
                    }
                    // Error
                    else
                    {
                        cout << "Invalid Usage, please see help file." << endl;
                    }
                }
            }
            /*************************************************************
             * Command: add <expense/income> <description> <amount> <date>
             * Function: adds an expense OR an income.
             * <description> one word description
             * <amount> amount spent/earned
             * <date> date of purchase/deposit in format MM/DD/YYYY
             ************************************************************/
            else if (cmds.at(0) == "add")
            {
                // Error check number of arguments
                if (cmds.size() != 5 && !(QString::compare(cmds.at(1), "Goal", Qt::CaseInsensitive) == 0))
                {
                    cout << "Invalid Usage, please see help file." << endl;
                }
                else
                {
                    // add the expense to expense list
                    bool success;
                    if (QString::compare(cmds.at(1), "Expense", Qt::CaseInsensitive) == 0)
                    {
                        success = financeSession.addExpense(cmds.at(2), cmds.at(3).toDouble(), cmds.at(4), true);
                        // if it was added successfully print new balance
                        if (success)
                        {
                            cout << "Expense successfully added." << endl;
                            cout << "New balance: ";
                            financeSession.showAmount();
                        }
                        // else print error
                        else
                        {
                            cout << "Expense could not be added." << endl;
                        }
                    }
                    // add the income to income list
                    else if (QString::compare(cmds.at(1), "Income", Qt::CaseInsensitive) == 0)
                    {
                        success = financeSession.addIncome(cmds.at(2), cmds.at(3).toDouble(), cmds.at(4), true);
                        // if it was added successfully print new balance
                        if (success)
                        {
                            cout << "Income successfully added." << endl;
                            cout << "New balance: ";
                            financeSession.showAmount();
                        }
                        // else print error
                        else
                        {
                            cout << "Income could not be added." << endl;
                        }
                    }
                    /********************************************************************************
                     * Command: add goal <description> <amountCurrentlySaved> <goalAmount> <endDate>
                     * Function: Adds a goal to the goal list with parameters.
                     * <description> One word description of goal.
                     * <goalAmount> Amount needed to reach goal.
                     * <amountCurrentlySaved> Amount currently saved for goal.
                     * <endDate> End Date for goal.
                     *******************************************************************************/
                    else if (QString::compare(cmds.at(1), "Goal", Qt::CaseInsensitive) == 0)
                    {
                        // Error check number of arguments
                        if (cmds.size() != 6)
                        {
                            cout << "Invalid usage for command goal, please see help file and try again" << endl;
                        }
                        else
                        {
                            // Add goal to goal list
                            success = financeSession.addGoal(cmds.at(2), cmds.at(4).toDouble(), cmds.at(3).toDouble(), cmds.at(5));
                            // if goal is successfully added or not, print a message
                            if (success)
                            {
                                cout << "Goal successfully added." << endl;
                            }
                            else
                            {
                                cout << "Goal could not be added." << endl;
                            }
                        }
                    }
                    // Error check
                    else
                    {
                        cout << "Invalid Usage, please see help file." << endl;
                    }
                }
            }
            /*************************************************************
             * Command: remove <expense/income/goal> <description>
             * Function: Removes an expense, income or goal based on the
             * <description>. Better if show <expenses/income/goals> is
             * used to find description.
             ************************************************************/
            else if (cmds.at(0) == "remove")
            {
                // Error check number of arguments
                if (cmds.size() != 3)
                {
                    cout << "Invalid Usage, please see help file." << endl;
                }
                // Remove
                else
                {
                    bool success;
                    // Remove expense
                    if (QString::compare(cmds.at(1), "Expense", Qt::CaseInsensitive) == 0)
                    {
                        success = financeSession.removeExpense(cmds.at(2));
                        // If removal is successful, show new balance
                        if (success)
                        {
                            cout << "Expense successfully removed." << endl;
                            cout << "New balance: ";
                            financeSession.showAmount();
                        }
                        // else dont
                        else
                        {
                            cout << "Expense not found. Is description right?" << endl;
                        }
                    }
                    // Remove income
                    else if (QString::compare(cmds.at(1), "Income", Qt::CaseInsensitive) == 0)
                    {
                        success = financeSession.removeIncome(cmds.at(2));
                        // If removal is successful, show new balance
                        if (success)
                        {
                            cout << "Income successfully removed." << endl;
                            cout << "New balance: ";
                            financeSession.showAmount();
                        }
                        // else dont
                        else
                        {
                            cout << "Income not found. Is description right?" << endl;
                        }
                    }
                    // Remove goal
                    else if (QString::compare(cmds.at(1), "Goal", Qt::CaseInsensitive) == 0)
                    {
                        success = financeSession.removeGoal(cmds.at(2));
                        // if removal is successful print a message
                        if (success)
                        {
                            cout << "Goal successfully removed." << endl;
                        }
                        // else print error message
                        else
                        {
                            cout << "Goal not found. Is description right?" << endl;
                        }
                    }
                }
            }
            /*************************************************************
             * Command: modify <amount/date> <goal> <newValue>
             * Function: modifies the amount or date of <goal> specified
             * by new value.
             * <goal> Description for the goal.
             * <newValue> New date or amount.
             ************************************************************/
            else if (cmds.at(0) == "modify")
            {
                // Error check number of arguments
                if (cmds.size() != 4)
                {
                    cout << "Invalid Usage, please see help file." << endl;
                }
                else
                {
                    bool success;
                    // Modify the amount
                    if (QString::compare(cmds.at(1), "Amount", Qt::CaseInsensitive) == 0)
                    {
                       success = financeSession.modifyGoalAmount(cmds.at(2), cmds.at(3).toDouble());
                       // Print success
                       if (success)
                       {
                           cout << "Goal Amount successfully modified." << endl;
                       }
                       // else failure
                       else
                       {
                           cout << "Goal not found. Is Description right?" << endl;
                       }
                    }
                    // Modify the date
                    else if (QString::compare(cmds.at(1), "Date", Qt::CaseInsensitive) == 0)
                    {
                        success = financeSession.modifyGoalDate(cmds.at(2), cmds.at(3));
                        // print success
                        if (success)
                        {
                            cout << "Goal Date successfully modified." << endl;
                        }
                        // else failure
                        else
                        {
                            cout << "Goal not found. Is description right?" << endl;
                        }
                    }
                    // Error check
                    else
                    {
                        cout << "Invalid usage, please see help file." << endl;
                    }
                }
            }
            /*************************************************************
             * Command: set <owner/amount>
             * Function: Sets the owner of the file or amount in the bank.
             ************************************************************/
            else if (cmds.at(0) == "set")
            {
                // Error check number of arguments
                if (cmds.size() < 3)
                {
                    cout << "Invalid Usage, please see help file." << endl;
                }
                else
                {
                    // Set the owner
                    if (QString::compare(cmds.at(1), "Owner", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.setOwner(QString(cmds.at(2) + " " + cmds.at(3)));
                    }
                    // Set the amount
                    else if (QString::compare(cmds.at(1), "Amount", Qt::CaseInsensitive) == 0)
                    {
                        financeSession.modifyBankAmount(cmds.at(2).toDouble());
                    }
                }
            }
            /*************************************************************
             * Command: exit
             * Function: Saves changes and exits the program.
             ************************************************************/
            else if (cmds.at(0) == "exit")
            {
                cout << "Saving changes if necessary...";
                financeSession.saveToFile();
                cout << "done" << endl;
                cout << "Exiting app..." << endl;
                break;
            }
        }
    }
    return 0;
}
