#include <stdio.h>
#include <string.h>

struct Expense {
    float amount;
    char category[20];
    char note[50];
};

int main() {
    struct Expense e[100];
    int count = 0;
    FILE *fp;

    
    fp = fopen("expense.txt", "a+");
    if(fp==NULL){
        printf("file open error\n");
        return 1;
    }
    rewind(fp);
    if(fp != NULL) {
        while(count<100 &&
        fscanf(fp, "%f %s %s",
                     &e[count].amount,
                     e[count].category,
                     e[count].note) == 3) {
            count++;
        }
        fclose(fp);
    }

    int choice;

    while(1) {
        printf("\n\n=== EXPENSE TRACKER MENU ===\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Category Total\n");
        printf("4. Delete Expense\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice)!=1){
            printf("invalid input number only");
            while(getchar()!='\n');
            continue;
        }


        if(choice == 1) { // Add Expense
            if(count >= 100) {
                printf("Cannot add more expenses, storage full!\n");
                continue;
            }

            printf("Enter amount: ");
            scanf("%f", &e[count].amount);

            printf("Enter category: ");
            scanf("%s", e[count].category);

            printf("Enter note: ");
            scanf("%s", e[count].note);

            // Save to file
            fp = fopen("expense.txt", "a");
            if(fp != NULL) {
                fprintf(fp, "%.2f %s %s\n",
                        e[count].amount,
                        e[count].category,
                        e[count].note);
                fclose(fp);
            } else {
                printf("Error opening file!\n");
            }

            count++;
            printf("Expense added successfully!\n");
        }

        else if(choice == 2) { // View Expenses
            if(count == 0) {
                printf("No expenses found.\n");
            } else {
                printf("\n--- ALL EXPENSES ---\n");
                for(int i = 0; i < count; i++) {
                    printf("%d) Amount: %.2f  Category: %s  Note: %s\n",
                           i+1,
                           e[i].amount,
                           e[i].category,
                           e[i].note);
                }
            }
        }

        else if(choice == 3) { // Category Total
            if(count == 0) {
                printf("No expenses found.\n");
            } else {
                char cat[20];
                float total = 0;
                printf("Enter category: ");
                scanf("%s", cat);

                for(int i = 0; i < count; i++) {
                    if(strcmp(e[i].category, cat) == 0) {
                        total += e[i].amount;
                    }
                }

                printf("Total amount spent in '%s' = %.2f\n", cat, total);
            }
        }

        else if(choice == 4) { // Delete Expense
            if(count == 0) {
                printf("No expenses to delete.\n");
            } else {
                int del;
                printf("Enter expense number to delete: ");
                scanf("%d", &del);

                if(del < 1 || del > count) {
                    printf("Invalid expense number!\n");
                    continue;
                }

                // Shift array elements to delete
                for(int i = del-1; i < count-1; i++) {
                    e[i] = e[i+1];
                }
                count--;

                // Rewrite file
                fp = fopen("expense.txt", "w");
                if(fp != NULL) {
                    for(int i = 0; i < count; i++) {
                        fprintf(fp, "%.2f %s %s\n",
                                e[i].amount,
                                e[i].category,
                                e[i].note);
                    }
                    fclose(fp);
                } else {
                    printf("Error opening file!\n");
                }

                printf("Expense deleted successfully!\n");
            }
        }

        else if(choice == 5) { // Exit
            printf("Exiting program. Goodbye!\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}