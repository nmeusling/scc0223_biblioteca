//
// Created by nmeusling on 9/5/17.
//

#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 20
#define MAX_NUSP_SIZE 12
#define MAX_PHONE_SIZE 13
#define MAX_EMAIL_SIZE 50
#define MAX_TITLE_SIZE 50
#define MAX_AUTHOR_SIZE 50
#define MAX_EDITOR_SIZE 50
#define MAX_ISBN_SIZE 20

typedef struct{
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
} student;

typedef struct{
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char editor[MAX_EDITOR_SIZE];
    char isbn[MAX_ISBN_SIZE];
    int year;
    int edition;
    int count; //number of available copies, 0 if all checked out, 1, if one copy and available, 2 if two copies and both available
    //wait list
} book;

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

int get_student_info(student *stud);

int get_book_info(book *bk);

void print_student(student *stud);

void print_book(book *bk);

void get_name(char *name);

void get_nusp(int *nusp);

void get_phone(int *phone);

void get_email(char *email);

void get_title(char *title);

void get_author(char *author);

void get_editor(char *editor);

void get_isbn(char *isbn);

void get_year(int *year);

void get_edition(int *edition);