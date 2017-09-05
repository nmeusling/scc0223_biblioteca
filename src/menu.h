//
// Created by nmeusling on 9/5/17.
//

#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 20
#define MAX_PHONE_SIZE 13
#define MAX_EMAIL_SIZE 50

typedef struct{
    char name[MAX_NAME_SIZE];
    int nusp;
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
} student;

void print_home();
void print_menu();
int get_selection();

/** @brief Flushes any extra characters input by user
 *
 * If the user inputs more than the expected number of characters, the extra
 * character are disregarded to prevent errors from occurring during program
 * execution.
 */
void flush_std_in(void);

int menu_register_student(student *stud);

void print_student(student *stud);