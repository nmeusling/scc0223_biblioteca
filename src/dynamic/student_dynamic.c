/** @file student_dynamic.c
 *  @brief Functions related to student and student list
 *
 *  Dynamic version:
 *  This file contains all of the functions related to the student and student
 *  list, including the functions for manipulating the email stack.
 *
 *  @author Natalie Menato (10295051)
 */
#include "student_dynamic.h"

/*
 * Initializes the library's list of students.
 */
void create_stud_list(student_list *students) {
    students->first = NULL;
    students->last = NULL;
}


/*
 * Allocates memory for the student and fills in details of student. Returns 1
 * if error occurred during memory allocation, 0 if created successfully.
 */
int create_student(student **stud, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]){
    student *s = (student *) malloc(sizeof(student));
    if (s == NULL) {
        return 1;
    }
    create_email_stack(&s->emails);
    strcpy(s->name, name);
    copy_int_array(s->nusp, nusp, MAX_NUSP_SIZE);
    copy_int_array(s->phone, phone, MAX_PHONE_SIZE);
    strcpy(s->email, email);
    *stud = s;
    return 0;
}

/*
 * Adds passed student as the last element of library's student list.
 * Returns 1 if an error occurs,otherwise returns 0.
 */
void insert_student_to_list(student_list *students, student * s) {

    s->next = NULL;

    //if list is currently empty
    if (students->first == NULL) {
        students->first = s;
    } else { //list has at least one element already
        students->last->next = s;
    }
    students->last = s;

}

/*
 * Searches for a student in the passed student list with passed name, if
 * found, pointer to the previous student in list is saved in prev_stud and 0
 * is returned. If it is not possible to find student, prev_stud will be Null
 * and 1 is returned.
 */
int search_student_name(student_list *students, char name[MAX_NAME_SIZE],
                        student **prev_stud) {
    student *s = students->first;
    if(s == NULL)
        return 1;
    //If the student is the first in the list
    if (strcmp(s->name, name) == 0) {
        *prev_stud = NULL;
        return 0;
    }
    while (s->next != NULL) {
        if (strcmp(s->next->name, name) == 0) {
            *prev_stud = s;
            return 0;
        }
        s = s->next;

    }
    return 1;
}


/*
 * Searches for a student in the passed student list with passed nusp, if
 * found, pointer to the previous student in list is saved in prev_stud and 0
 * is returned. If it is not possible to find student, prev_stud will be Null
 * and 1 is returned.
 */
int search_student_nusp(student_list *students, int nusp[MAX_NUSP_SIZE],
                        student **prev_stud) {
    student *s = students->first;
    if(s == NULL)
        return 1;

    //If the student is the first in the list
    if (compare_int_array(nusp, s->nusp, MAX_NUSP_SIZE) == 0) {
        *prev_stud = NULL;
        return 0;
    }
    while (s->next != NULL) {
        if (compare_int_array(s->next->nusp, nusp, MAX_NUSP_SIZE) == 0) {
            *prev_stud = s;
            return 0;
        }
        s = s->next;

    }
    return 1;
}


/*
 * Removes the student after the passed student from the student list. Frees
 * the memory allocated to the removed student.
 */
void remove_student_studentlist(student_list *students, student *prev_stud){

    student *stud = students->first;
    //student is 1st element
    if (prev_stud == NULL) {
        students->first = stud->next;
        //student was only element, list is not empty
        if (students->first == NULL)
            students->last = NULL;
        delete_email_stack(&stud->emails);

        free(stud);
        return;
    }
        //student is last but not only element
    else if(prev_stud->next == students->last)
    {
        students->last = prev_stud;
    }
    stud = prev_stud->next;
    prev_stud->next = stud->next;
    delete_email_stack(&stud->emails);
    free(stud);
}


/*
 * Gets the name of the passed student and returns it as a string.
 */
char* get_stud_name(student *stud){
    return stud->name;
}


/*
 * Creates stack to store the email messages for a student.
 */
void create_email_stack(email_stack *emls){
    emls->top = NULL;
}


/*
 * Adds a new email with message to the email stack. Returns 1 if an error
 * occurred, 0 if it was successful.
 */
int push_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]){
    email * eml = (email *) malloc(sizeof(email));
    if(eml == NULL)
        return 1;
    strcpy(eml->message, message);
    eml->next = emls->top;
    emls->top = eml;

    return 0;
}


/*
 * Removes the top message. Saves message of removed email to the passed
 * parameter.
 */
int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]){
    if(emls->top == NULL)
        return 1;
    strcpy(message, emls->top->message);
    email * temp = emls->top;
    emls->top = emls->top->next;
    free(temp);
    return 0;
}


/*
 * Clears the email stack and returns it to it's initial position, with top
 * pointing to NULL. Frees the memory of all nodes that were part of the
 * email stack.
 */
void delete_email_stack(email_stack *emls){
    char *message = NULL;
    while(pop_email(emls, message) == 0);
}


/*
 * Verifies if the email stack is empty
 */
int isEmailEmpty(email_stack *emls){
    if(emls->top == NULL)
        return 1;
    return 0;
}

/*
 * Searches for the student in the library's student list by name and saves the
 * student to the passed student parameter if found.
 */
int get_student_by_name(student_list *students, char name[MAX_NAME_SIZE], student **stud){
    student *prev ;
    if(search_student_name(students, name, &prev) == 1)
        return 1;
    if(prev == NULL)
        *stud = (students->first);
    else
        *stud = (prev)->next;
    return 0;
}


/*
 * Searches for the student by nusp in the library's student list and saves the
 * student to the passed student parameter if found.
 */
int get_student_by_nusp(student_list *students, int nusp[MAX_NUSP_SIZE], student **stud){
    student *prev ;
    if(search_student_nusp(students, nusp, &prev) == 1)
        return 1;
    if(prev == NULL)
        *stud = students->first;
    else
        *stud = (prev)->next;
    return 0;
}


/* Copies elements of array2 into array1. Array1 and Array2 must have size
 * elements.
 */
void copy_int_array(int *array1, int *array2, int size) {
    int i;
    for (i = 0; i < size; i++) {
        array1[i] = array2[i];
    }
}


/* Compares the elements of array 1 with array 2. Returns 0 if they are the same,
 * 1 if they are different.
 */
int compare_int_array(int *array1, int *array2, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (array1[i] != array2[i])
            return 1;
    }
    return 0;
}