# Finance-Tracker.c
 💰 Simple C Finance Tracker

## 📝 Overview

This project is a compact, terminal-based finance tracking application built in C. It is designed to help users track daily expenses across different categories, monitor monthly and yearly spending, and calculate personal savings based on a fixed monthly salary.

It uses a 3D array data structure to store and manage expense data across months, days, and categories, providing quick access to aggregated financial statistics.

## ✨ Key Features

* *Daily Expense Logging:* Record specific expense amounts for any day (1-31) of any month.
* *6 Expense Categories:* Track spending across predefined categories:
    * Travel
    * Logistics
    * Entertainment
    * Grocery
    * Education
    * Other
* *Budget Warning:* Set an optional daily average spending limit for any month and receive a real-time warning if your current average spending exceeds this limit.
* *Monthly Totals & Averages:* Calculate total expenses for any specific month and the average daily spending (calculated over 31 days).
* *Yearly Statistics:* View a breakdown of total spending per month and calculate the overall yearly expense total and daily average.
* *Savings Report:* Automatically calculate and display annual savings and a savings percentage rating based on the provided monthly salary.
* *Robust Input Handling:* Includes custom functions (getValidFloat, getValidInt) to ensure numeric input validation and proper handling of the input buffer.

## 🚀 Getting Started

### Prerequisites

You need a C compiler (like GCC) installed on your system.

### Compilation and Execution

1.  *Save the Code:* Save the provided C code as a file named finance_tracker.c.
2.  *Compile:* Open your terminal or command prompt and run the following command to compile the executable:

    bash
    gcc finance_tracker.c -o finance_tracker
    

3.  *Run:* Execute the compiled program:

    bash
    ./finance_tracker
    

## ⚙ Project Structure (Technical Details)

The core data management relies on the global 3D array:

$$ \text{dayExp}[12][31][6] $$

Where:
* The *1st dimension (12)* represents the *Month*.
* The *2nd dimension (31)* represents the *Day*.
* The *3rd dimension (6)* represents the *Expense Category*.
