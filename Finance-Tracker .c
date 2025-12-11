#include <stdio.h>
#include <stdlib.h>

// Global constants
#define MAX_DAYS 31 // Simple 31-day month model
#define CAT 6      // Number of expense categories
#define MONTHS 12  // Total months

// Input Validation: Float
float getValidFloat(const char *prompt) {
    float val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &val) == 1) {
            if (val < 0) {
                printf("Negative values not allowed. Try again.\n");
            } else {
                int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
                return val; // Returns valid positive float
            }
        } else {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input. Try again.\n"); // Clear buffer on invalid input
        }
    }
}

// Input Validation: Integer
int getValidInt(const char *prompt, int min, int max) {
    int val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &val) == 1) {
            if (val >= min && val <= max) {
                int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
                return val; // Returns valid int in range
            } else {
                printf("Input out of range (%d-%d). Try again.\n", min, max);
            }
        } else {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input. Try again.\n"); // Clear buffer on invalid input
        }
    }
}

// Global Storage
// 3D array: [Month][Day][Category] for expense storage
float dayExp[MONTHS][MAX_DAYS][CAT] = {0}; 

// Monthly average spending limit
float monthAvgLimit[MONTHS] = {0}; 

// Month names for output
char *monthName[MONTHS] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// Expense Calculation Logic

// Calculate total expenses for a single month
float calcMonthTotal(int monSel) {
    float total = 0;
    for (int d = 0; d < MAX_DAYS; d++)
        for (int c = 0; c < CAT; c++)
            total += dayExp[monSel][d][c];
    return total;
}

// Calculate average daily spending for a month (over 31 days)
float calcMonthAvg(int monSel) {
    return calcMonthTotal(monSel) / MAX_DAYS; 
}

// Calculate total yearly expenses
float calcYearTotal() {
    float total = 0;
    for (int m = 0; m < MONTHS; m++)
        total += calcMonthTotal(m);
    return total;
}

// Calculate average daily spending for the entire year
float calcYearAvg() {
    return calcYearTotal() / (MONTHS * MAX_DAYS);
}

// Main Application Logic
int main() {
    char name[50];
    
    printf("--- Simple C Finance Tracker ---\n");
    printf("Enter your name: ");
    scanf("%49s", name);
    int ch; while ((ch = getchar()) != '\n' && ch != EOF) {} // Clear buffer after name input

    float salary = getValidFloat("Enter your total monthly salary: ");

    printf("\nWELCOME %s!\n", name);

    int mainChoice = 0;
    while (mainChoice != 5) { // Main application loop
        printf("\n===== MAIN MENU =====\n");
        printf("1. Enter Month Data\n");
        printf("2. Show Yearly Total (month-wise)\n");
        printf("3. Show Each Month Average + Yearly Average\n");
        printf("4. Savings\n");
        printf("5. Exit\n");

        mainChoice = getValidInt("Enter choice: ", 1, 5);

        if (mainChoice == 1) { // Option 1: Enter Month Data
            // Get month (1-12) and convert to 0-indexed array position
            int monSel = getValidInt("\nEnter Month Number (1-12): ", 1, 12) - 1;
            int monChoice = 0;

            while (monChoice != 4) { // Month menu loop
                printf("\n---- %s MENU ----\n", monthName[monSel]);
                printf("1. Enter Daily Expenses\n");
                printf("2. Show Monthly Average\n");
                printf("3. Show Monthly Total\n");
                printf("4. Go Back\n");
                
                monChoice = getValidInt("Enter choice: ", 1, 4);

                if (monChoice == 1) {
                    monthAvgLimit[monSel] = getValidFloat("Set your average daily limit (0 to skip/clear): ");
                    
                    int day = getValidInt("Enter day (1-31): ", 1, MAX_DAYS) - 1;
                    
                    int catChoice = getValidInt(
                        "Enter category \n1.Travel\n2.Logistics\n3.Entertainment\n4.Grocery\n5.Education\n6.Other : ", 1, CAT
                    ) - 1;
                    
                    float amt = getValidFloat("Enter amount: ");
                    // Accumulate expense for the day/category
                    dayExp[monSel][day][catChoice] += amt;

                    // Average Check against Limit
                    float totalMon = 0; 
                    int usedDays = 0;
                    
                    // Calculate current month's total and count used days
                    for (int d = 0; d < MAX_DAYS; d++) {
                        float sumDay = 0;
                        for (int c = 0; c < CAT; c++) sumDay += dayExp[monSel][d][c];
                        
                        if (sumDay > 0) usedDays++; // Count days with expenses
                        
                        totalMon += sumDay;
                    }
                    
                    if (usedDays == 0) usedDays = 1; // Ensure non-zero divisor
                    
                    float currentAvg = totalMon / usedDays; // Current average based on days with data
                    
                    if (monthAvgLimit[monSel] > 0 && currentAvg > monthAvgLimit[monSel])
                        printf("\n!!! WARNING: Exceeded daily average limit! Current avg = %.2f, Limit = %.2f\n",
                               currentAvg, monthAvgLimit[monSel]);
                }
                else if (monChoice == 2) {
                    printf("Monthly Average (across 31 days): %.2f\n", calcMonthAvg(monSel));
                }
                else if (monChoice == 3) {
                    printf("Monthly Total: %.2f\n", calcMonthTotal(monSel));
                }
            }
        }

        else if (mainChoice == 2) { // Option 2: Show Yearly Total
            printf("\n==== YEARLY EXPENSE BREAKDOWN ====\n");
            for (int m = 0; m < MONTHS; m++) {
                printf("%-10s: %.2f\n", monthName[m], calcMonthTotal(m));
            }
            printf("Total YEARLY expenses: %.2f\n", calcYearTotal());
        }

        else if (mainChoice == 3) { // Option 3: Show Averages
            printf("\n==== MONTHLY AVERAGES ====\n");
            for (int m = 0; m < MONTHS; m++) {
                printf("%-10s Average = %.2f\n", monthName[m], calcMonthAvg(m));
            }
            printf("Yearly Average (daily across year) = %.2f\n", calcYearAvg());
        }

        else if (mainChoice == 4) { // Option 4: Savings Report
            float yearlySpent = calcYearTotal();
            float yearlySalary = salary * 12; // Annual salary
            float savings = yearlySalary - yearlySpent;
            
            // Calculate percentage saved
            float percentSave = (yearlySalary > 0) ? (savings / yearlySalary) * 100 : 0;

            printf("\n===== SAVINGS REPORT =====\n");
            printf("Yearly Salary: %.2f\n", yearlySalary);
            printf("Yearly Spent: %.2f\n", yearlySpent);
            printf("Savings: %.2f\n", savings);
            printf("Percentage: %.2f%%\n", percentSave);
            
            // Rating based on savings
            if (savings < 0) printf("Rating: WARNING! You are overspending your yearly income.\n");
            else if (percentSave >= 40) printf("Rating: Excellent Savings! Keep up the great work.\n");
            else if (percentSave >= 20) printf("Rating: Good Savings. A healthy reserve.\n");
            else if (percentSave >= 5) printf("Rating: Low Savings. Look for areas to cut back.\n");
            else printf("Rating: Very Low Savings! Immediate action required to reduce expenses.\n");
        }
    }

    printf("\nThank you for using the Finance App, %s! Goodbye.\n", name);
    return 0;
}
