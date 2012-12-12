Simple Finance
==============
###Shaishav Parekh ECE 2524 Final Project

Command line finance tracker. <br \>
You can create finance files to track expenses, income and goals. <br \>
Needs qt4 to run.

*For a sample finance file see sampleFile.txt*

**Please run qmake and make (in that order) for correct compiling and making.**

**Note: If you dont have QT, a precompiled binary is included in the directory.** <br />
The binary might not work on 32-bit machines. In that case you will need to run qmake and make.

% indicates the prompt

#Commands

**help**  <br \>
Prints help to standard output. 
<pre><code>
	% help
</code></pre>

**load**  <br \>
load \<filename>  <br \>
Loads a file into the current session. Dont include .txt <br \>
<pre><code>
	% load myFinance
</code></pre>

**create**  <br \>
create \<filename>  <br \>
Creates a file with the specified file name and loads it into the current session. Dont include .txt
<pre><code>
	% create newFinanceFile
</code></pre>

**show**  <br \>
show \<option>  <br \>
Prints information about the option.  <br \>
Options: <br \>

- Owner: Prints the owner.
<pre><code>
	% show owner
</code></pre>
- Amount: Prints the bank balance. 
<pre><code>
	% show amount
</code></pre>
- Expenses: Prints the expenses list.
<pre><code>
	% show expenses
</code></pre>
- Income: Prints the income list.
<pre><code>
	% show income
</code></pre>
- Goals: Prints the goal list.
<pre><code>
	% show goals
</code></pre>

**add**  <br \>
add \<expense/income> \<description> \<amount> \<date>  <br \>
Adds an expense or an income to the list.  <br \>
\<description> One-word description of the expense or income  <br \>
\<amount> amount of expense or income  <br \>
\<date> date of expense or income  <br \>
<pre><code>
	% add expense Groceries 53.44 12/9/2012
	% add income Job 120 12/9/2012
</code></pre>

add goal \<description> \<amountCurrentlySaved> \<goalAmount> \<endDate>  <br \>
Adds a goal to the goal list.  <br \>
\<description> One-word description of the goal  <br \>
\<amountCurrentlySaved> Money currently saved for the goal  <br \>
\<goalAmount> Money needed to complete goal  <br \>
\<endDate> End date for the goal  <br \>
<pre><code>
	% add goal Travel 0 2000 1/1/2013
</code></pre>

**remove**  <br \>
remove \<expense/income/goal> \<description>  <br \>
Removes an expense, income or goal from the list  <br \>
\<description> One-word description of expense, income or goal  <br \>
<pre><code>
	% remove expense Groceries
	% remove income Job
	% remove goal Travel
</code></pre>

**modify**  <br \>
modify amount \<goal description> \<newAmount>  <br \>
Modifies the amount currently saved of the goal based on the goal description.  <br \>
\<goal description> One-word description of goal  <br \>
\<newAmount> new currently saved amount  <br \>
<pre><code>
	% modify amount Travel 500
</code></pre>

modify date \<goal description> \<newDate>  <br \>
\<goal description> One-word description of goal  <br \>
\<newDate> new end date of goal  <br \>
<pre><code>
	% modify date Travel 1/15/13
</code></pre>

**set**  <br \>
set owner \<first> \<last>  <br \>
Sets the owner of the file to the \<first> and \<last> name.  <br \>
<pre><code>
	% set owner Shaishav Parekh 
</code></pre>

set amount \<newAmount>  <br \>
Sets the bank balance to the \<newAmount>  <br \>
<pre><code>
	% set amount 500.75
</code></pre>

**exit**  <br \>
Saves the changes made during the finance session to a file and exits the program.  <br \>
<pre><code>
	% exit
</code></pre>