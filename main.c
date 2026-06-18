#include <stdio.h>
#include <string.h>

#define MAX 100
int count = 0;

struct Student
{
    int id;
    char name[50];
    float marks;
};

struct Student students[MAX];
int choice;

int isDuplicate(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

char *getGrade(float marks)
{
    if (marks >= 90)
        return "A+";
    else if (marks >= 80)
        return "A";
    else if (marks >= 70)
        return "B";
    else if (marks >= 60)
        return "C";
    else if (marks >= 50)
        return "D";
    else
        return "F";
}

void printStudent(int idx)
{
    printf("\nID    : %d\n", students[idx].id);
    printf("Name  : %s\n", students[idx].name);
    printf("Marks : %.2f\n", students[idx].marks);
    printf("Grade : %s\n", getGrade(students[idx].marks));
}

void Add_students()
{
    if (count >= MAX)
    {
        printf("Oops storage full! you cannot enter further\n");
        return;
    }

    int id;
    printf("Enter the student id: ");
    scanf("%d", &id);

    if (isDuplicate(id))
    {
        printf("Oops! student with this ID already exists\n");
        return;
    }
    students[count].id = id;

    printf("Enter the student name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter the student marks: ");
    scanf("%f", &students[count].marks);

    count++;
    printf("Student added to the records successfully!\n");
}

void savetofile()
{
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL)
    {
        printf("Oops! error in opening file\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d|%s|%f\n", students[i].id, students[i].name, students[i].marks);
    }
    fclose(fp);
    printf("Data saved successfully!\n");
}

void Loadfromfile()
{
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL)
    {
        return;
    }
    count = 0;
    while (fscanf(fp, "%d|%[^|]|%f\n", &students[count].id, students[count].name, &students[count].marks) != EOF)
    {
        count++;
    }
    fclose(fp);
}

void display()
{
    if (count == 0)
    {
        printf("No records found\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("\nStudent : %d\n", i + 1);
        printStudent(i);
    }
}

void sortByMarks()
{
    if (count == 0)
    {
        printf("No records found\n");
        return;
    }
    struct Student temp;
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (students[j].marks < students[j + 1].marks)
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Sorted by marks (highest to lowest)!\n");
    display();
}

void searchByName()
{
    if (count == 0)
    {
        printf("No records found\n");
        return;
    }
    char name[50];
    printf("Enter the student name: ");
    scanf(" %[^\n]", name);

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            printf("\nStudent found!\n");
            printStudent(i);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Student not found\n");
    }
}

void search()
{
    if (count == 0)
    {
        printf("No records found\n");
        return;
    }

    int flag = 0;
    int id, idx = -1;
    printf("Enter the student id: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (id == students[i].id)
        {
            idx = i;
            flag = 1;
            break;
        }
    }

    if (flag)
    {
        printf("\nStudent found!\n");
        printStudent(idx);

        int choice;
        printf("\nWhat would you like to do?\n");
        printf("1. Update\n");
        printf("2. Delete\n");
        printf("3. Back to menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the new id: ");
            int newid;
            scanf("%d", &newid);
            if (newid != students[idx].id && isDuplicate(newid))
            {
                printf("Oops! this ID already exists\n");
                break;
            }
            students[idx].id = newid;

            printf("Enter the new name: ");
            scanf(" %[^\n]", students[idx].name);

            printf("Enter the new marks: ");
            scanf("%f", &students[idx].marks);
            printf("Updated successfully!\n");
            break;

        case 2:
            for (int i = idx; i < count - 1; i++)
            {
                students[i] = students[i + 1];
            }
            count--;
            printf("Deleted successfully!\n");
            break;

        case 3:
            return;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
    else
    {
        printf("Student not found\n");
    }
}

int main()
{
    Loadfromfile();
    while (1)
    {
        printf("\n<--- Student Management --->\n");
        printf("1. Add student\n");
        printf("2. Display students\n");
        printf("3. Search by ID\n");
        printf("4. Search by Name\n");
        printf("5. Sort by Marks\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Add_students();
            break;
        case 2:
            display();
            break;
        case 3:
            search();
            break;
        case 4:
            searchByName();
            break;
        case 5:
            sortByMarks();
            break;
        case 6:
            savetofile();
            return 0;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}