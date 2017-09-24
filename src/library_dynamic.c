/** @file library_dynamic.c
 *  @brief Abstract Data Type for Library Management
 *
 *  Contains the operations to manipulate the library data structure. Includes
 *  operations to register a new student, remove a student, register a new book,
 *  remove a book from the library, check out a book and return a book.
 *
 *  @author Natalie Menato (10295051)
 */

#include "library_dynamic.h"

/*
 * Initializes a new list of students.
 */
void create_stud_list(student_list *studs) {
    studs->first = NULL;
    studs->last = NULL;
}

/*
 * Creates a new student with passed information and then adds student as the
 * last element of student list. Returns 1 if an error occurs, otherwise
 * returns 0.
 */
int insert_student(student_list *studs, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]) {

    student *s = (student *) malloc(sizeof(student));
    if (s == NULL) {
        return 1;
    }

    strcpy(s->name, name);
    copy_int_array(s->nusp, nusp, MAX_NUSP_SIZE);
    copy_int_array(s->phone, phone, MAX_PHONE_SIZE);
    strcpy(s->email, email);

    s->next = NULL;

    //if list is currently empty
    if (studs->first == NULL) {
        studs->first = s;
    } else { //list has at least one element already
        studs->last->next = s;
    }
    studs->last = s;

    return 0;
}

/* Searches for a student in the list with passed name, if found, pointer to
 * the previous student in list is saved in prev_stud and 0 is returned. If it
 * is not possible to find student, prev_stud will be Null and 1 is returned.
 */
int search_student_name(student_list *studs, char name[MAX_NAME_SIZE],
                   student **prev_stud) {
    student *s = studs->first;
    //If the student is the first in the list
    if (strcmp(s->name, name) == 0) {
        *prev_stud = NULL;
        return 0;
    }
    while(s->next != NULL){
        if(strcmp(s->next->name, name) == 0){
            *prev_stud = s;
            return 0;
        }
        s = s->next;

    }
    return 1;
}

/* Removes student with name from student list. Returns 0 if student is removed
 * successfully. Returns 1 if it is not possible to remove the student
 */
int remove_student_name(student_list *studs, char name[MAX_NAME_SIZE]){
    student *prev_stud = NULL;
    student *stud = studs->first;
    //list is empty
    if(stud == NULL){
        return 1;
    }
    //student not found in list
    if(search_student_name(studs, name, &prev_stud) == 1) {
        return 1;
    }
    //student is 1st element
    if(prev_stud == NULL) {
        studs->first = stud->next;
        free(stud);
        //student was only element, list is not empty
        if(studs->first == NULL)
            studs->last = NULL;
        return 0;
    }
    stud = prev_stud->next;
    prev_stud->next = stud->next;
    free(stud);
    return 0;
}

/*
 * Copies elements of array2 into array1. Array1 and Array2 must have size
 * elements.
 */
void copy_int_array(int *array1, int *array2, int size) {
    int i;
    for (i = 0; i < size; i++) {
        array1[i] = array2[i];
    }
}