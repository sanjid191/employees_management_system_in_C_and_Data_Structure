#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sn=1;
// structure for an employee record
struct emp
{
  char name[30];
  int age;
  float salary;
  struct emp *prev;
  struct emp *next;
};

struct emp *head = NULL;
struct emp *tail = NULL;


// function to insert a new node at the end of the linked list
void insert_at_end(char name[], int age, float salary){

      struct emp *new_node;
      struct emp *temp;

      new_node = (struct emp *)malloc(sizeof(struct emp));
      strcpy(new_node->name, name);
      new_node->age = age;
      new_node->salary = salary;
      new_node->prev = NULL;
      new_node->next = NULL;

      if (head == NULL){
        head = new_node;
        tail = new_node;
        return;
      }

      temp = tail;
      temp->next = new_node;
      new_node->prev = temp;
      tail = new_node;
}


// function to sort the employee records in the linked list by name
void sort_employees(){
      struct emp *temp1;
      struct emp *temp2;
      struct emp *temp3;
      struct emp *temp4;
      char temp_name[30];
      int temp_age;
      float temp_salary;

      if (head == NULL){
        printf("Linked list is empty.\n");
        return;
      }

      // sort the linked list using bubble sort
      temp1 = head;
      while (temp1 != NULL){
        temp2 = temp1->next;
        while (temp2 != NULL){
          // compare the names of the two nodes and swap them if necessary
          if (strcmp(temp1->name, temp2->name) > 0){
                     // swap the names
            strcpy(temp_name, temp1->name);
            strcpy(temp1->name, temp2->name);
            strcpy(temp2->name, temp_name);
                      // swap the ages
            temp_age = temp1->age;
            temp1->age = temp2->age;
            temp2->age = temp_age;
                     // swap the salaries
            temp_salary = temp1->salary;
            temp1->salary = temp2->salary;
            temp2->salary = temp_salary;
          }
          temp2 = temp2->next;
        }
        temp1 = temp1->next;
     }

          // update the head and tail pointers if necessary
      temp3 = head;
      while (temp3->prev != NULL){
        temp3 = temp3->prev;
      }
      head = temp3;
      temp4 = tail;
      while (temp4->next != NULL){
        temp4 = temp4->next;
      }
      tail = temp4;

      printf("\n\n \t\t Employees sorted by name.\n");
}


// function to display all the employee records in the linked list
void list_records(){
      struct emp *temp;

      if (head == NULL){
        printf("Linked list is empty.\n");
        return;
      }

      temp = head;
      printf("\n");
      printf("\---------------------------------\n");
      printf("\t--- Employees Records ---\n");
      printf("---------------------------------\n");
      while (temp != NULL){
        printf("\t SN    : 00%d \n",sn++);
        printf("\t Name  : %s \n", temp->name);
        printf("\t Age   : %d \n", temp->age);
        printf("\t Salary: %.2f \n", temp->salary);
        printf("-------------------------------\n");
        printf("-------------------------------\n");
        temp = temp->next;
      }
}


// function to add a new employee record to the linked list
void add_record(){
      char name[30];
      int age;
      float salary;

      printf("\n");
      printf("\n\t\t Enter Employees Details \n");
      printf("\n\t Enter Name  : ");
      scanf("%s", name);
      printf("\t Enter Age   : ");
      scanf("%d", &age);
      printf("\t Enter Salary: ");
      scanf("%f", &salary);

      insert_at_end(name, age, salary); // insert the new node at the end of the linked list
}


// function to load the employee records from a file
void load_from_file(){
      FILE *fp;
      struct emp e;
      long int recsize;

      fp = fopen("employees.txt", "rb");
      if (fp == NULL){
        printf("Error opening file.\n");
        return;
      }

      // read the employee records from the file and insert them into the linked list
      recsize = sizeof(e);
      while (fread(&e, recsize, 1, fp) == 1){
        insert_at_end(e.name, e.age, e.salary);
      }

      fclose(fp);
      printf("Employee records loaded from file.\n");
}


// function to save the employee records to a file
void save_to_file(){
      FILE *fp;
      struct emp *temp;

      fp = fopen("employees.txt", "wb");
      if (fp == NULL){
        printf("Error opening file.\n");
        return;
      }

      // write the employee records from the linked list to the file
      temp = head;
      while (temp != NULL){
        fwrite(temp, sizeof(struct emp), 1, fp);
        temp = temp->next;
      }

      fclose(fp);
      printf("\t Employee records saved to file.\n");
}


void modify_record(){
      char name[30];
      struct emp *temp;

      printf("\n");
      printf("Enter the name of the employee to Modify : ");
      scanf("%s", name);

      temp = head;

      // search for the employee record with the specified name
      while (temp != NULL){
        if (strcmp(temp->name, name) == 0){
          printf("\t Enter new Name: ");
          scanf("%s", temp->name);
          printf("\t Enter new Age: ");
          scanf("%d", &temp->age);
          printf("\t Enter new Salary: ");
          scanf("%f", &temp->salary);
          printf("\t Record modified successfully.\n");
          return;
        }

        temp = temp->next; // move to the next node in the linked list
      }

      printf("Employee record not found.\n");
}


// function to delete the employee records from the file
void delete_record(){
      char name[30];
      struct emp *temp, *prev;

      printf("\n");
      printf("Enter the name of the employee to Delete : ");
      scanf("%s", name);

      temp = head;
      prev = NULL;

      // search for the employee record with the specified name
      while (temp != NULL){
        if (strcmp(temp->name, name) == 0){
          if (prev == NULL){
            head = temp->next;
          }
          else{
            prev->next = temp->next;
          }

          if (temp->next != NULL){
            temp->next->prev = prev;
          }

          free(temp);
          printf("Record deleted successfully.\n");
          return;
        }

        prev = temp;       // update the previous node
        temp = temp->next; // move to the next node in the linked list
      }

      printf("\t Employee record not found.\n");
}


// function to search for an employee by name
void search_employee(){
    char name[30];
    struct emp *temp;

    printf("\n");
    printf("Enter the name of the employee to search for: ");
    scanf("%s", name);

    temp = head;

    while (temp != NULL){
        if (strcmp(temp->name, name) == 0) {
            printf("\n");
            printf("---------------------------------\n");
            printf("\t --Employee found--\n");
            printf("---------------------------------\n");
            printf("\n");
            printf("\t Found Detail is . \n");
            printf("\t Name: %s \n", temp->name);
            printf("\t Age: %d \n", temp->age);
            printf("\t Salary: %.2f \n", temp->salary);
            return;
        }
        temp = temp->next;  // move to the next node in the linked list
    }
    printf("\t Employee not found.\n");
}


//main function started
int main()
{
      int choice;
      char another;

      load_from_file();
      do{

          system("cls");
        printf("\n\n  --- Employee Management System ---\n");
        printf("\n");
        printf("\t 1. Add Record \n");
        printf("\t 2. List Records \n");
        printf("\t 3. Modify Record \n");
        printf("\t 4. Delete Record \n");
        printf("\t 5. Sort Employees \n");
        printf("\t 6. Search Employee \n");
        printf("\t 7. Exit\n");
        printf("\n");
        printf("\t Enter your choice: ");
        scanf("%d", &choice);

        switch (choice){

            case 1:
               system("cls");
               another = 'y';
               while(another == 'y'){
                    add_record();
                    save_to_file();
                    printf("\nAdd another record(y/n) : ");
                    another = getche();
               }
               break;

            case 2:
               system("cls");
               list_records();
               getch();
               break;

            case 3:
               system("cls");
               another = 'y';
               while(another == 'y'){
                    modify_record();
                    printf("\nModify another record(y/n) : ");
                    another = getche();
               }
               break;

            case 4:
               system("cls");
               another = 'y';
               while(another == 'y'){
                    delete_record();
                    printf("\nDelete another record(y/n) : ");
                    another = getche();
               }
               break;

            case 5:
               system("cls");
               sort_employees();
               getch();
               break;

            case 6:
               system("cls");
               search_employee();
               getch();
               break;

            case 7:
                printf("\n");
                printf("\t EXIT FROM THE PROGRAM\n");
                printf("\t THANK YOU --\n");
                printf("\t-------------------------");
               return 0;
         }
      }
      while (choice != 7);

  return 0;
}

