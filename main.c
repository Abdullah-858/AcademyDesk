#include <stdio.h>
#include <string.h>
#define MAX 100

struct Student
{
    int id;
    char name[50];
    int age;
    char phone[20];
    int batchID;
    float monthlyFee;
    int active;
};
struct Batch
{
    int batchID;
    char batchName[50];
    char subject[30];
    char timing[30];
};
struct Attendance
{
    int studentID;
    char date[15];
    char status[10];
};
struct Payment
{
    int studentID;
    float amountPaid;
    char paymentDate[15];
};
struct Result
{
    int studentID;
    char subject[30];
    float obtainedMarks;
    float totalMarks;
};
struct Student students[MAX];
struct Batch batches[MAX];
struct Attendance attendance[MAX];
struct Payment payments[MAX];
struct Result results[MAX];
int studentCount = 0;
int batchCount = 0;
int attendanceCount = 0;
int paymentCount = 0;
int resultCount = 0;
void loadStudents();
void saveStudents();
void loadBatches();
void saveBatches();
void saveAllData();
void studentMenu();
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void archiveStudent();
int findStudent(int id);
void batchMenu();
void addBatch();
void viewBatches();
void assignStudent();
int findBatch(int id);
void loadAttendance();
void saveAttendance();
void loadPayments();
void savePayments();
void loadResults();
void saveResults();
void displayDashboard();


void loadStudents()
{
    FILE *fp;
    fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        return;
    }
    studentCount = fread(students,
                         sizeof(struct Student),
                         MAX, fp);
    fclose(fp);
}

void saveStudents()
{
    FILE *fp;
    fp = fopen("students.dat", "wb");
    if (fp == NULL)
    {
        printf("Error saving student records!\n");
        return;
    }
    fwrite(students,
           sizeof(struct Student),
           studentCount, fp);
    fclose(fp);
}

void loadBatches()
{
    FILE *fp;
    fp = fopen("batches.dat", "rb");
    if (fp == NULL)
    {
        return;
    }
    batchCount = fread(batches,
                       sizeof(struct Batch),
                       MAX, fp);
    fclose(fp);
}

void saveBatches()
{
    FILE *fp;
    fp = fopen("batches.dat", "wb");
    if (fp == NULL)
    {
        printf("Error saving batch records!\n");
        return;
    }
    fwrite(batches,
           sizeof(struct Batch),
           batchCount, fp);
    fclose(fp);
}

void saveAllData()
{
    saveStudents();
    saveBatches();
    saveAttendance();
    savePayments();
    saveResults();
}
int findStudent(int id)
{
    int i;
    for (i = 0; i < studentCount; i++)
    {
        if (students[i].id == id &&
            students[i].active == 1)
        {
            return i;
        }
    }
    return -1;
}

void studentMenu()
{
    int choice;
    do
    {
        printf("\n========== STUDENT MANAGEMENT ==========\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Archive Student\n");
        printf("0. Back to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                archiveStudent();
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}


void addStudent()
{
    int id;
    if (studentCount >= MAX)
    {
        printf("Student storage is full!\n");
        return;
    }
    printf("\nEnter Student ID: ");
    scanf("%d", &id);
    int i;
    for (i = 0; i < studentCount; i++)
    {
        if (students[i].id == id)
        {
            printf("This Student ID already exists!\n");
            return;
        }
    }

    students[studentCount].id = id;
    printf("Enter Student Name: ");
    scanf(" %49[^\n]", students[studentCount].name);
    printf("Enter Age: ");
    scanf("%d", &students[studentCount].age);
    printf("Enter Phone Number: ");
    scanf(" %19s", students[studentCount].phone);
    printf("Enter Monthly Fee: ");
    scanf("%f", &students[studentCount].monthlyFee);
    students[studentCount].batchID = 0;
    students[studentCount].active = 1;
    studentCount++;
    saveStudents();
    printf("\nStudent added successfully!\n");
}



void viewStudents()
{
    int i;
    int found = 0;

    printf("\n========== STUDENT RECORDS ==========\n");

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].active == 1)
        {
            printf("\nStudent ID: %d", students[i].id);
            printf("\nName: %s", students[i].name);
            printf("\nAge: %d", students[i].age);
            printf("\nPhone: %s", students[i].phone);
            printf("\nMonthly Fee: %.2f", students[i].monthlyFee);

            if (students[i].batchID == 0)
            {
                printf("\nBatch: Not Assigned\n");
            }
            else
            {
                printf("\nBatch ID: %d\n", students[i].batchID);
            }

            printf("------------------------------------\n");

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No active students found!\n");
    }
}

void searchStudent()
{
    int id;
    int index;

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    index = findStudent(id);

    if (index == -1)
    {
        printf("Student not found!\n");
    }
    else
    {
        printf("\nStudent Found!\n");

        printf("ID: %d\n", students[index].id);
        printf("Name: %s\n", students[index].name);
        printf("Age: %d\n", students[index].age);
        printf("Phone: %s\n", students[index].phone);
        printf("Monthly Fee: %.2f\n",
               students[index].monthlyFee);
        printf("Batch ID: %d\n",
               students[index].batchID);
    }
}



void updateStudent()
{
    int id;
    int index;

    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);

    index = findStudent(id);

    if (index == -1)
    {
        printf("Student not found!\n");
        return;
    }

    printf("\nEnter New Name: ");
    scanf(" %49[^\n]", students[index].name);

    printf("Enter New Age: ");
    scanf("%d", &students[index].age);

    printf("Enter New Phone: ");
    scanf(" %19s", students[index].phone);

    printf("Enter New Monthly Fee: ");
    scanf("%f", &students[index].monthlyFee);

    saveStudents();

    printf("\nStudent updated successfully!\n");
}


void archiveStudent()
{
    int id;
    int index;

    printf("\nEnter Student ID to archive: ");
    scanf("%d", &id);

    index = findStudent(id);

    if (index == -1)
    {
        printf("Student not found!\n");
        return;
    }

    students[index].active = 0;

    saveStudents();

    printf("\nStudent archived successfully!\n");
}


int findBatch(int id)
{
    int i;

    for (i = 0; i < batchCount; i++)
    {
        if (batches[i].batchID == id)
        {
            return i;
        }
    }

    return -1;
}



void batchMenu()
{
    int choice;

    do
    {
        printf("\n========== BATCH MANAGEMENT ==========\n");

        printf("1. Create Batch\n");
        printf("2. View Batches\n");
        printf("3. Assign Student to Batch\n");
        printf("0. Back to Main Menu\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBatch();
                break;

            case 2:
                viewBatches();
                break;

            case 3:
                assignStudent();
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);
}


void addBatch()
{
    int id;

    if (batchCount >= MAX)
    {
        printf("Batch storage is full!\n");
        return;
    }

    printf("\nEnter Batch ID: ");
    scanf("%d", &id);

    if (findBatch(id) != -1)
    {
        printf("Batch ID already exists!\n");
        return;
    }

    batches[batchCount].batchID = id;

    printf("Enter Batch Name: ");
    scanf(" %49[^\n]", batches[batchCount].batchName);

    printf("Enter Subject: ");
    scanf(" %29[^\n]", batches[batchCount].subject);

    printf("Enter Class Timing: ");
    scanf(" %29[^\n]", batches[batchCount].timing);

    batchCount++;

    saveBatches();

    printf("\nBatch created successfully!\n");
}


void viewBatches()
{
    int i;

    printf("\n========== AVAILABLE BATCHES ==========\n");

    if (batchCount == 0)
    {
        printf("No batches available!\n");
        return;
    }

    for (i = 0; i < batchCount; i++)
    {
        printf("\nBatch ID: %d", batches[i].batchID);

        printf("\nBatch Name: %s", batches[i].batchName);

        printf("\nSubject: %s", batches[i].subject);

        printf("\nTiming: %s\n", batches[i].timing);

        printf("------------------------------------\n");
    }
}


void assignStudent()
{
    int studentID;
    int batchID;
    int studentIndex;
    int batchIndex;
    printf("\nEnter Student ID: ");
    scanf("%d", &studentID);
    studentIndex = findStudent(studentID);
    if (studentIndex == -1)
    {
        printf("Student not found!\n");
        return;
    }
    printf("Enter Batch ID: ");
    scanf("%d", &batchID);
    batchIndex = findBatch(batchID);
    if (batchIndex == -1)
    {
        printf("Batch not found!\n");
        return;
    }
    students[studentIndex].batchID = batchID;
    saveStudents();
    printf("\nStudent assigned to batch successfully!\n");
}

void saveAttendance()
{
    FILE *fp = fopen("attendance.dat", "wb");
    if (fp == NULL)
    {
        printf("Error saving attendance!\n");
        return;
    }
    fwrite(attendance, sizeof(struct Attendance),
           attendanceCount, fp);
    fclose(fp);
}

void loadAttendance()
{
    FILE *fp = fopen("attendance.dat", "rb");

    if (fp == NULL)
        return;

    attendanceCount = fread(attendance,
                            sizeof(struct Attendance),
                            MAX, fp);

    fclose(fp);
}

void markAttendance()
{
    int id, i;
    char date[15];
    char status[10];
    if (attendanceCount >= MAX)
    {
        printf("Attendance limit reached!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%d", &id);
    if (findStudent(id) == -1)
    {
        printf("Student not found!\n");
        return;
    }
    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%14s", date);
    for (i = 0; i < attendanceCount; i++)
    {
        if (attendance[i].studentID == id &&
            strcmp(attendance[i].date, date) == 0)
        {
            printf("Attendance already marked!\n");
            return;
        }
    }
    printf("Enter Status (Present/Absent): ");
    scanf("%9s", status);
    if (strcmp(status, "Present") != 0 &&
        strcmp(status, "Absent") != 0)
    {
        printf("Invalid status!\n");
        return;
    }
    attendance[attendanceCount].studentID = id;
    strcpy(attendance[attendanceCount].date, date);
    strcpy(attendance[attendanceCount].status, status);
    attendanceCount++;
    saveAttendance();
    printf("Attendance marked successfully!\n");
}

void viewAttendance()
{
    int i;
    if (attendanceCount == 0)
    {
        printf("No attendance records found!\n");
        return;
    }
    printf("\n========== ATTENDANCE RECORDS ==========\n");
    for (i = 0; i < attendanceCount; i++)
    {
        printf("\nStudent ID: %d", attendance[i].studentID);
        printf("\nDate: %s", attendance[i].date);
        printf("\nStatus: %s\n", attendance[i].status);
        printf("----------------------------------------\n");
    }
}

void attendanceMenu()
{
    int choice;
    do
    {
        printf("\n========== ATTENDANCE MANAGEMENT ==========\n");
        printf("1. Mark Attendance\n");
        printf("2. View Attendance\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                markAttendance();
                break;
            case 2:
                viewAttendance();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

void savePayments()
{
    FILE *fp = fopen("payments.dat", "wb");
    if (fp == NULL)
    {
        printf("Error saving payments!\n");
        return;
    }
    fwrite(payments, sizeof(struct Payment),
           paymentCount, fp);
    fclose(fp);
}

void loadPayments()
{
    FILE *fp = fopen("payments.dat", "rb");
    if (fp == NULL)
        return;
    paymentCount = fread(payments,
                         sizeof(struct Payment),
                         MAX, fp);
    fclose(fp);
}

void recordPayment()
{
    int id;
    if (paymentCount >= MAX)
    {
        printf("Payment limit reached!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%d", &id);
    if (findStudent(id) == -1)
    {
        printf("Student not found!\n");
        return;
    }
    printf("Enter Amount Paid: ");
    scanf("%f", &payments[paymentCount].amountPaid);
    if (payments[paymentCount].amountPaid <= 0)
    {
        printf("Invalid payment amount!\n");
        return;
    }
    printf("Enter Payment Date (DD-MM-YYYY): ");
    scanf("%14s", payments[paymentCount].paymentDate);
    payments[paymentCount].studentID = id;
    paymentCount++;
    savePayments();
    printf("Payment recorded successfully!\n");
}

void viewPayments()
{
    int i;
    if (paymentCount == 0)
    {
        printf("No payment records found!\n");
        return;
    }
    printf("\n========== FEE PAYMENT RECORDS ==========\n");
    for (i = 0; i < paymentCount; i++)
    {
        printf("\nStudent ID: %d", payments[i].studentID);
        printf("\nAmount Paid: %.2f", payments[i].amountPaid);
        printf("\nPayment Date: %s\n", payments[i].paymentDate);
        printf("-----------------------------------------\n");
    }
}

void feeMenu()
{
    int choice;
    do
    {
        printf("\n========== FEE MANAGEMENT ==========\n");
        printf("1. Record Payment\n");
        printf("2. View Payments\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                recordPayment();
                break;
            case 2:
                viewPayments();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

void saveResults()
{
    FILE *fp = fopen("results.dat", "wb");
    if (fp == NULL)
    {
        printf("Error saving results!\n");
        return;
    }
    fwrite(results, sizeof(struct Result),
           resultCount, fp);
    fclose(fp);
}

void loadResults()
{
    FILE *fp = fopen("results.dat", "rb");
    if (fp == NULL)
        return;
    resultCount = fread(results,
                        sizeof(struct Result),
                        MAX, fp);
    fclose(fp);
}

void addResult()
{
    int id;
    if (resultCount >= MAX)
    {
        printf("Result limit reached!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%d", &id);
    if (findStudent(id) == -1)
    {
        printf("Student not found!\n");
        return;
    }
    results[resultCount].studentID = id;
    printf("Enter Subject: ");
    scanf(" %29[^\n]", results[resultCount].subject);
    printf("Enter Total Marks: ");
    scanf("%f", &results[resultCount].totalMarks);
    if (results[resultCount].totalMarks <= 0)
    {
        printf("Invalid total marks!\n");
        return;
    }
    printf("Enter Obtained Marks: ");
    scanf("%f", &results[resultCount].obtainedMarks);
    if (results[resultCount].obtainedMarks < 0 ||
        results[resultCount].obtainedMarks >
        results[resultCount].totalMarks)
    {
        printf("Invalid obtained marks!\n");
        return;
    }
    resultCount++;
    saveResults();
    printf("Academic result added successfully!\n");
}

void viewResults()
{
    int i;
    float percentage;
    if (resultCount == 0)
    {
        printf("No academic results found!\n");
        return;
    }
    printf("\n========== ACADEMIC RESULTS ==========\n");
    for (i = 0; i < resultCount; i++)
    {
        percentage = (results[i].obtainedMarks /
                      results[i].totalMarks) * 100;
        printf("\nStudent ID: %d", results[i].studentID);
        printf("\nSubject: %s", results[i].subject);
        printf("\nObtained Marks: %.2f",
               results[i].obtainedMarks);
        printf("\nTotal Marks: %.2f",
               results[i].totalMarks);
        printf("\nPercentage: %.2f%%\n", percentage);
        printf("--------------------------------------\n");
    }
}

void resultMenu()
{
    int choice;
    do
    {
        printf("\n========== ACADEMIC RESULTS ==========\n");
        printf("1. Add Result\n");
        printf("2. View Results\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                addResult();
                break;
            case 2:
                viewResults();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

void displayDashboard()
{
    printf("\n========== ACADEMY DASHBOARD ==========\n");
    int i;
    int totalActive = 0;
    for (i = 0; i < studentCount; i++)
    {
        if (students[i].active == 1)
        {
            totalActive++;
        }
    }
    printf("\nTotal Active Students: %d", totalActive);
    printf("\nTotal Batches: %d", batchCount);
    printf("\n=======================================\n");
}



int main()
{
    int choice;
    loadStudents();
    loadBatches();
    loadAttendance();
    loadPayments();
    loadResults();
    printf("\n");
    printf("========================================\n");
    printf("          WELCOME TO ACADEMY DESK       \n");
    printf("       STUDENT MANAGEMENT SYSTEM        \n");
    printf("========================================\n");
    do
    {
        printf("\n============== MAIN MENU ==============\n");
        printf("1. Student Management\n");
        printf("2. Batch Management\n");
        printf("3. Attendance Management\n");
        printf("4. Fee Management\n");
        printf("5. Academic Results\n");
        printf("6. Dashboard and Reports\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                studentMenu();
                break;
            case 2:
                batchMenu();
                break;
            case 3:
                attendanceMenu();
                break;
            case 4:
                feeMenu();
                break;
            case 5:
                resultMenu();
                break;
            case 6:
                displayDashboard();
                break;
            case 0:
                saveAllData();
                printf("\nThank you for using Academy Desk!\n");
                printf("All records saved successfully.\n");
                break;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 0);
    return 0;
}
