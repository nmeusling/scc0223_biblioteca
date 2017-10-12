/** @file student_dynamic.h
 *  @brief Header file for student_dynamic.c
 *
 *  Dynamic version:
 *  This file contains the declaration for the student struct and email struct.
 *  It also contains the declaration of the student lists and email stack data
 *  structures. It contains the prototypes for the operations that manipulate
 *  structures.
 *
 *  @author Natalie Menato (10295051)
 */

#define MAX_NAME_SIZE 100
#define MAX_NUSP_SIZE 15
#define MAX_PHONE_SIZE 15
#define MAX_EMAIL_SIZE 100
#define MAX_MESSAGE_SIZE 500

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** @struct email
 *  @brief Email node to store the email message for a student
 *  @var char[]::message
 *  @var email*::next
 *  Member 'message' message of the email
 *  Member 'last' pointer to the next email in the stack
 */
typedef struct _email{
    char message[MAX_MESSAGE_SIZE] ;
    struct _email *next;
}email;


/** @struct email_stack
 *  @brief Stack to store all emails for a student
 *  @var email*::top
 *  Member 'top' pointer to the first email in the stack
 */
typedef struct{
    email *top;
}email_stack;


/** @struct student
 *  @brief Stores all of the information related to a student
 *  @var char[]::name
 *  @var int[]::nusp
 *  @var int[]::phone
 *  @var char[]::email
 *  @var student*::next
 *  @var email_stack::emails
 *  Member 'name' string that stores name of student
 *  Member 'nusp' stores the numero USP of student
 *  Member 'phone' stores the student's phone number
 *  Member 'email' string that stores student's email
 *  Member 'next' pointer to the next student in the student list
 *  Member 'emails' email stack for the student
 */
typedef struct _student {
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
    struct _student *next;
    email_stack emails;


}student;


/** @struct student_list
 *  @brief List to store student nodes
 *  @var student*::first
 *  @var student*::last
 *  Member 'first' pointer to the first student node of list
 *  Member 'last' pointer to the last student node of list
 */
typedef struct {
    student *first, *last;
} student_list;

/** @brief Creates a new student list for library
 *
 * Initializes the passed student_list so that the other functions for the
 * student list can be used successfully.
 *
 * @param student_list* students pointer to the student list
 */
void create_stud_list(student_list *students);


/** @brief Allocates memory for student and adds details.
 *
 * Allocates memory for a new student and saves all of the passed fields to
 * the student's details.
 *
 * @param student** Used to return address of memory location
 * @param char[]::name string that stores name of student
 * @param int[]::nusp stores the numero USP of student
 * @param int[]::phone stores the student's phone number
 * @param char[]::email string that stores student's email
 * @return 1 if error occurred, 0 if student created successfully
 */
int create_student(student **stud, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]);


/** @brief Inserts student into the student list
 *
 * Passed student is added to the end of the passed student list.
 *
 * @param student_list* student list where student will be added
 * @param student::s student that will be added
 */
void insert_student_to_list(student_list *students, student * s);


/** @brief Searches for student with name in the student list
 *
 * Searches for a student in the passed student list whose name is the same as
 * the name passed to the function. Previous student in the list is saved to
 * passed parameter prev_stud.
 *
 * @param student_list* students pointer to the student list
 * @param char[] name name of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on library's student list, 1 otherwise
 */
int search_student_name(student_list *students, char name[MAX_NAME_SIZE],
                        student **prev_stud);


/** @brief Searches for student with nusp in the student list
 *
 * Searches for a student in the passed student list whose nusp is the same as
 * the nusp passed to the function. Previous student in the list is saved to
 * passed parameter prev_stud.
 *
 * @param student_list* students pointer to the student list
 * @param int[] nusp nusp of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on library's student list, 1 otherwise
 */
int search_student_nusp(student_list *students, int nusp[MAX_NUSP_SIZE],
                        student **prev_stud);


/** @brief Removes student from the student list
 *
 * Removes the student after the passed student from the student list. Frees
 * the memory allocated to the removed student.
 *
 * @param student_list* students pointer to the student list
 * @param student* prev_stud previous student of student who will be removed,
 * NULL if student to be removed is first in list
 */
void remove_student_studentlist(student_list *students, student *prev_stud);


/** @brief Returns the name of passed student
 *
 * Gets the name of the passed student and returns it as a string.
 *
 * @param stud *stud student to get name
 * @return string of student's name
 */
char* get_stud_name(student *stud);


/** @brief Creates an email stack setting it to the correct initial position
 *
 * Initializes the email stack to it's initial position, with top pointing to
 * NULL.
 *
 * @param email_stack* emls email stack to be created
 */
void create_email_stack(email_stack *emls);


/** @brief Adds email to email stack
 *
 * Creates a new node in the email stack and saves the passed message to the
 * new node.
 *
 * @param email stack* emls pointer to the email stack where message will be
 * added
 * @param char[] email message message to be added in the stack
 * @return 1 if it was not possible to add email, 0 if email added
 */
int push_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);


/** @brief Removes top email from stack
 *
 * Removes the top message. Saves message of removed email to the passed
 * parameter.
 *
 * @param email_stack* emls pointer to the email stack where message will be
 * removed
 * @param char[] message email message message that was removed from stack
 * @return 1 if it was not possible to remove email, 0 if email removed
 */
int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);


/** @brief Clears the email stack
 *
 * Clears the email stack and returns it to it's initial position, with top
 * pointing to NULL. Frees the memory of all nodes that were part of the
 * email stack.
 *
 * @param email_stack* emls email stack to be removed
 */
void delete_email_stack(email_stack *emls);


/** @brief Checks if email stack is empty
 *
 * Verifies if the email stick is empty
 *
 * @param email_stack *emls email stack to be checked
 * @return 1 if empty, 0 if not empty
 */
int isEmailEmpty(email_stack *emls);


/** @brief Searches for student and saves student to passed parameter if found
 *
 * Searches for the student in the library's student list  by name and saves
 * the student to the passed student parameter if found.
 *
 * @param student_list *studs list of all registered students
 * @param char[] name name of student to search for
 * @param student **stud pointer to where the pointer to the found student will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_student_by_name(student_list *students, char name[MAX_NAME_SIZE], student **stud);


/** @brief Searches for student and saves student to passed parameter if found
 *
 * Searches for the student by nusp in the library's student list and saves
 * the student to the passed student parameter if found.
 *
 * @param library* lib pointer to the library
 * @param int[] nusp nusp of student to search for
 * @param student **stud pointer to where the pointer to the found student will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_student_by_nusp(student_list *students, int nusp[MAX_NUSP_SIZE], student **stud);


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