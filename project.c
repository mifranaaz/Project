#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100

struct Medicine
{
    int id;
    char name[50];
    char category[30];
    char batch[30];
    int quantity;
    char mfgDate[15];
    char expDate[15];
};

struct Medicine med[MAX];
int count = 0;

/* Add Medicine */
void addMedicine()
{
    printf("\nEnter Medicine ID: ");
    scanf("%d", &med[count].id);

    printf("Enter Medicine Name: ");
    scanf(" %[^\n]", med[count].name);

    printf("Enter Category: ");
    scanf(" %[^\n]", med[count].category);

    printf("Enter Batch Number: ");
    scanf(" %[^\n]", med[count].batch);

    printf("Enter Quantity: ");
    scanf("%d", &med[count].quantity);

    printf("Enter Manufacturing Date (DD-MM-YYYY): ");
    scanf("%s", med[count].mfgDate);

    printf("Enter Expiry Date (DD-MM-YYYY): ");
    scanf("%s", med[count].expDate);

    count++;

    printf("\nMedicine added successfully!\n");
}

/* View all medicines */
void viewMedicines()
{
    int i;

    if (count == 0)
    {
        printf("\nNo medicines available.\n");
        return;
    }

    printf("\n========== ALL MEDICINES ==========\n");

    for (i = 0; i < count; i++)
    {
        printf("\nMedicine ID       : %d", med[i].id);
        printf("\nMedicine Name     : %s", med[i].name);
        printf("\nCategory          : %s", med[i].category);
        printf("\nBatch Number      : %s", med[i].batch);
        printf("\nQuantity          : %d", med[i].quantity);
        printf("\nManufacturing Date: %s", med[i].mfgDate);
        printf("\nExpiry Date       : %s\n", med[i].expDate);
    }
}

/* Search medicine */
void searchMedicine()
{
    int id, i, found = 0;

    printf("\nEnter Medicine ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (med[i].id == id)
        {
            printf("\nMedicine Found!\n");
            printf("Name     : %s\n", med[i].name);
            printf("Category : %s\n", med[i].category);
            printf("Batch    : %s\n", med[i].batch);
            printf("Quantity : %d\n", med[i].quantity);
            printf("Expiry   : %s\n", med[i].expDate);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nMedicine not found.\n");
}

/* Convert date to time */
time_t convertDate(char date[])
{
    int day, month, year;
    struct tm t = {0};

    sscanf(date, "%d-%d-%d", &day, &month, &year);

    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;

    return mktime(&t);
}

/* Check expired medicines */
void checkExpired()
{
    int i;
    time_t today = time(NULL);

    printf("\n========== EXPIRED MEDICINES ==========\n");

    for (i = 0; i < count; i++)
    {
        time_t expiry = convertDate(med[i].expDate);

        if (expiry < today)
        {
            printf("\nID: %d | Name: %s | Expiry: %s",
                   med[i].id, med[i].name, med[i].expDate);
        }
    }

    printf("\n");
}

/* Check medicines expiring soon */
void checkExpiringSoon()
{
    int i;
    time_t today = time(NULL);
    time_t thirtyDays = today + (30 * 24 * 60 * 60);

    printf("\n========== EXPIRING SOON ==========\n");

    for (i = 0; i < count; i++)
    {
        time_t expiry = convertDate(med[i].expDate);

        if (expiry >= today && expiry <= thirtyDays)
        {
            printf("\nID: %d | Name: %s | Expiry: %s",
                   med[i].id, med[i].name, med[i].expDate);
        }
    }

    printf("\n");
}

/* Update stock */
void updateStock()
{
    int id, newQuantity, i, found = 0;

    printf("\nEnter Medicine ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (med[i].id == id)
        {
            printf("Current Quantity: %d\n", med[i].quantity);

            printf("Enter New Quantity: ");
            scanf("%d", &newQuantity);

            med[i].quantity = newQuantity;

            printf("\nStock updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nMedicine not found.\n");
}

/* Delete medicine */
void deleteMedicine()
{
    int id, i, j, found = 0;

    printf("\nEnter Medicine ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (med[i].id == id)
        {
            for (j = i; j < count - 1; j++)
            {
                med[j] = med[j + 1];
            }

            count--;

            printf("\nMedicine deleted successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nMedicine not found.\n");
}

/* Generate report */
void generateReport()
{
    int i, totalStock = 0;

    printf("\n========== MEDICINE REPORT ==========\n");

    printf("Total types of medicines: %d\n", count);

    for (i = 0; i < count; i++)
    {
        totalStock += med[i].quantity;
    }

    printf("Total stock available: %d\n", totalStock);

    printf("\nMedicine List:\n");

    for (i = 0; i < count; i++)
    {
        printf("%d. %s - Quantity: %d\n",
               i + 1, med[i].name, med[i].quantity);
    }
}

/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n\n====================================");
        printf("\n       MEDICINE EXPIRY TRACKER");
        printf("\n====================================");

        printf("\n1. Add Medicine");
        printf("\n2. View All Medicines");
        printf("\n3. Search Medicine");
        printf("\n4. Check Expired Medicines");
        printf("\n5. Check Expiring Soon");
        printf("\n6. Update Medicine Stock");
        printf("\n7. Delete Medicine");
        printf("\n8. Generate Report");
        printf("\n9. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addMedicine();
                break;

            case 2:
                viewMedicines();
                break;

            case 3:
                searchMedicine();
                break;

            case 4:
                checkExpired();
                break;

            case 5:
                checkExpiringSoon();
                break;

            case 6:
                updateStock();
                break;

            case 7:
                deleteMedicine();
                break;

            case 8:
                generateReport();
                break;

            case 9:
                printf("\nThank you! Program ended.\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 9);

    return 0;
}