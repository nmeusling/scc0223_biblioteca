/** @file student_static.c
 *  @brief Functions related to student and student list
 *
 *  Static version:
 *  This file contains all of the functions related to the student and student
 *  list, including the functions for manipulating the email stack.
 *
 *  @author Natalie Menato (10295051)
 */

#include "student_static.h"

/*
 * Initializes the library's memory bank to store students.
 */
void create_stud_list(student_list *students){
    int i;
    for(i=0; i<MAX_STUDENTS-1; i++){
        students->elements[i].next = i+1;
    }
    students->elements[MAX_STUDENTS -1].next = -1;
    students->first_empty = 0;
    students->first = -1;
    students->last = -1;
}



/*
 * Find the next available space in the memory bank for the student. Return -1
 * if there is no more available space.
 */
int get_node_studentlist(student_list *studs){
    int index = studs->first_empty;
    if(index == -1 )
        return -1;
    studs->first_empty = studs->elements[index].next;
    studs->elements[index].next = -1;
    return index;

}


/*
 * Frees the space of passed index in the student list memory bank. Adds space
 * back to empty list.
 */
void free_node_studentlist(student_list *studs, int index){
    studs->elements[index].next = studs->first_empty;
    studs->first_empty =  index;
}


/*
 * Allocates memory for the student in the student memory bank and fills in
 * details of student. Returns 1 if error occurred during memory allocation,
 * 0 if created successfully.
 */
int create_student(student_list *students, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]){
    int index = get_node_studentlist(students);
    if (index == -1) {
        return index;
    }

    create_email_stack(&students->elements[index].emails);
    strcpy(students->elements[index].name, name);
    copy_int_array(students->elements[index].nusp, nusp, MAX_NUSP_SIZE);
    copy_int_array(students->elements[index].phone, phone, MAX_PHONE_SIZE);
    strcpy(students->elements[index].email, email);
    return index;

}


/*
 * Adds passed student as the last element of library's student list.
 * Returns 1 if an error occurs,otherwise returns 0.
 */
void insert_student_to_list(student_list *students, int index){
    students->elements[index].next = -1;

    //if list is currently empty
    if (students->first == -1) {
        students->first = index;
    } else { //list has at least one element already
        students->elements[students->last].next = index;
    }
    students->last = index;

}


/*
 * Searches for a student in the passed student list whose name is the same as
 * the name passed to the function. Index of Previous student in the list is
 * saved to passed parameter prev_stud. If it is not possible to find student,
 * prev_stud will be -1 and 1 is returned. Returns 0 if student is found.
 */
int search_student_name(student_list *students, char name[MAX_NAME_SIZE],
                        int *prev_stud){
    int index = students->first;
    int next;
    if(index == -1)
        return 1;
    next = students->elements[index].next;
    //If the student is the first in the list
    if (strcmp(students->elements[index].name, name) == 0) {
        *prev_stud = -1;
        return 0;
    }
    while (next != -1) {
        if (strcmp(students->elements[next].name, name) == 0) {
            *prev_stud = index;
            return 0;
        }
        index = next;
        next = students->elements[next].next;

    }
    return 1;
}

/*
 * Searches for a student in the passed student list whose nusp is the same as
 * the name nusp to the function. Index of Previous student in the list is
 * saved to passed parameter prev_stud. If it is not possible to find student,
 * prev_stud will be -1 and 1 is returned. Returns 0 if student is found.
 */
int search_student_nusp(student_list *students, int nusp[MAX_NUSP_SIZE],
                        int *prev_stud){
    int index = students->first;
    int next;
    if(index == -1)
        return 1;
    next = students->elements[index].next;
    //If the student is the first in the list
    if (compare_int_array(students->elements[index].nusp, nusp, MAX_NUSP_SIZE) == 0) {
        *prev_stud = -1;
        return 0;
    }
    while (next != -1) {
        if (compare_int_array(students->elements[next].nusp, nusp, MAX_NUSP_SIZE) == 0) {
            *prev_stud =index;
            return 0;
        }
        index = next;
        next = students->elements[next].next;

    }
    return 1;
}


/*
 * Removes the student after the passed student from the student list. Frees
 * the index in the student memory bank allocated to the removed student.
 */
void remove_student_studentlist(student_list *students, int prev_stud){
    int index = students->first;
    //student is 1st element
    if (prev_stud == -1) {
        students->first = students->elements[index].next;
        //student was only element, list is now empty
        if (students->first == -1)
            students->last = -1;
        delete_email_stack(&students->elements[index].emails);
        free_node_studentlist(students, index);
        return;
    }
        //student is last but not only element in list
    else if(students->elements[prev_stud].next == students->last)
    {
        students->last = prev_stud;
    }
    index = students->elements[prev_stud].next;
    students->elements[prev_stud].next = students->elements[index].next;
    delete_email_stack(&students->elements[index].emails);
    free_node_studentlist(students, index);
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
    emls->top = -1;
}


/*
 * Adds a new email with message to the email stack. Returns 1 if an error
 * occurred, 0 if it was successful.
 */
int push_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]){
    //if full
    if(emls->top >= MAX_EMAILS_PER_STUDENT - 1)
        return 1;
    emls->top ++;
    strcpy(emls->emails[emls->top].message, message);
    return 0;
}


/*
 * Removes the top message. Saves message of removed email to the passed
 * parameter.
 */
int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]){
    //if empty
    if(emls->top == -1)
        return 1;
    strcpy(message, emls->emails[emls->top].message);
    emls->top --;
    return 0;
}


/*
 * Clears the email stack and returns it to it's initial position, with top
 * pointing to -1.
 */
void delete_email_stack(email_stack *emls){
    emls->top = -1;
}


/*
 * Verifies if the email stack is empty
 */
int isEmailEmpty(email_stack *emls){
    if(emls->top == -1)
        return 1;
    return 0;
}


/*
 * Searches for the student in the library's student list by name and saves the
 * student's index to the passed int parameter if found.
 */
int get_student_by_name(student_list *students, char name[MAX_NAME_SIZE], student **stud){
    int prev, next;
    //student not found
    if(search_student_name(students, name, &prev) == 1)
        return 1;
    if(prev == -1)
        *stud = &students->elements[students->first];
    else {
        next = students->elements[prev].next;
        *stud = &students->elements[next];
    }
    return 0;
}


/*
 * Searches for the student in the library's student list by nusp and saves the
 * student's index to the passed int parameter if found.
 */
int get_student_by_nusp(student_list *students, int nusp[MAX_NUSP_SIZE], student **stud){
    int prev, next;
    //student not found
    if(search_student_nusp(students, nusp, &prev) == 1)
        return 1;
    if(prev == -1)
        *stud = &students->elements[students->first];
    else {
        next = students->elements[prev].next;
        *stud = &students->elements[next];
    }
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