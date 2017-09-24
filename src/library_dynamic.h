/** @file library_dynamic.h
 *  @brief Header file for library_dynamic.c
 *
 *  This file contains the declaration for the library structs, including the
 *  student list, book list, and wait list. It also contains the prototypes for
 *  the operations that manipulate these lists.
 *
 *  @author Natalie Menato (10295051)
 */


#ifndef SCC0223_BIBLIOTECA_LIBRARY_DYNAMIC_H
#define SCC0223_BIBLIOTECA_LIBRARY_DYNAMIC_H

#include <stdlib.h>
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
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char editor[MAX_EDITOR_SIZE];
    char isbn[MAX_ISBN_SIZE];
    int year;
    int edition;
    int count; //number of available copies, 0 if all checked out, 1, if one copy and available, 2 if two copies and both available
    //wait list
} book;

/** @struct student
 *  @brief Stores all of the information related to a student
 *  @var student::name
 *  @var student::nusp
 *  @var student::phone
 *  @var student::email
 *  @var student::next
 *  Member 'name' string that stores name of student
 *  Member 'nusp' stores the numero USP of student
 *  Member 'phone' stores the student's phone number
 *  Member 'email' string that stores student's email
 *  Member 'next' pointer to the next student in the student list
 */
typedef struct _student{
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
    struct _student *next;
} student;

/** @struct student_list
 *  @brief List to store student nodes
 *  @var student_list::first
 *  @var student_list::last
 *  Member 'first' pointer to the first student node of list
 *  Member 'last' pointer to the last student node of list
 */
typedef struct{
    student *first, *last;
} student_list;

/** @brief Creates a new student list
 *
 * Initializes a student_list so that the other functions for the list can be
 * used.
 *
 * @param student_list* studs pointer to student list to be initialized
 */
void create_stud_list(student_list *studs);

/** @brief Creates a new student and adds it to student list
 *
 * Allocates memory for a new student. Saves the passed name, nusp, phone, and
 * email to the new student. Adds the new student to the end of existing
 * student list.
 *
 * @param student_list* studs student list where student will be added
 * @param char[] name name of student to be added
 * @param int[] nusp Numero USP of student to be added
 * @param int[] phone Phone number of student to be added
 * @param char[] email Email of student to be added
 * @return 1 if an error occurred, 0 if student inserted successfully
 */
int insert_student(student_list *studs, char name[MAX_NAME_SIZE], int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE], char email[MAX_EMAIL_SIZE]);

/** @brief Searches for student with name in the list
 *
 * Searches for a student in the student list whose name is the same as the
 * name passed to the function. Previous student in the list is saved to passed
 * parameter prev_stud.
 *
 * @param student_list* studs student list where student will be searched
 * @param char[] name name of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on list, 1 otherwise
 */
int search_student_name(student_list *studs, char name[MAX_NAME_SIZE],
                        student **prev_stud);

/** @brief Searches for student with nusp in the list
 *
 * Searches for a student in the student list whose nusp is the same as the
 * nusp passed to the function. Previous student in the list is saved to passed
 * parameter prev_stud.
 *
 * @param student_list* studs student list where student will be searched
 * @param int[] nusp nusp of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on list, 1 otherwise
 */
int search_student_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE],
                        student **prev_stud);

/** @brief Removes student with name from the list
 *
 * Uses search function to find previous student in list and then remove the
 * desired student.
 *
 * @param student_list* studs student list where student will be removed
 * @param char[] name name of student to be removed
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student removed successfully, 1 otherwise
 */
int remove_student_name(student_list *studs, char name[MAX_NAME_SIZE]);

/** @brief Removes student with nusp from the list
 *
 * Uses search function to find previous student in list and then remove the
 * desired student.
 *
 * @param student_list* studs student list where student will be removed
 * @param int[] nusp nusp of student to be removed
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student removed successfully, 1 otherwise
 */
int remove_student_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE]);

/** @brief Copies elements of an int array to a second int array
 *
 * Copies elements from array2 to array 1. Both arrays must have size
 * elements.
 *
 * @param int* array1 destination array (copied to)
 * @param int* array2 origin array (copied from)
 * @param int size number of elements to be copied
 */
void copy_int_array(int *array1, int *array2, int size);

/** @brief Compares two int arrays to see if they are the same
 *
 * Compares the elements of array 1 with array 2 to see if the arrays contain
 * the same elements in the same order.
 *
 * @param int* array1 first array to be compared
 * @param int* array2 second array to be compated
 * @param int size number of elements to be compared
 * @return 0 if the arrays are the same, 1 if they are different
 */
int compare_int_array(int *array1, int *array2, int size);
#endif //SCC0223_BIBLIOTECA_LIBRARY_DYNAMIC_H
