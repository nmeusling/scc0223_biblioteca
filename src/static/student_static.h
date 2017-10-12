#define MAX_NAME_SIZE 100
#define MAX_NUSP_SIZE 15
#define MAX_PHONE_SIZE 15
#define MAX_EMAIL_SIZE 100
#define MAX_MESSAGE_SIZE 500

#define MAX_EMAILS_PER_STUDENT 10
#define MAX_STUDENTS 100

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** @struct email
 *  @brief Email node to store the email message for a student
 *  @var char[]::message
 *  Member 'message' message of the email
 */
typedef struct {
    char message[MAX_MESSAGE_SIZE] ;
}email;


/** @struct email_stack
 *  @brief Stack to store all emails for a student
 *  @var int::top
 *  @var email::emails
 *  Member 'top' index of the first email in the stack
 *  Member 'emails' array to store the email stack
 */
typedef struct{
    int top;
    email emails [MAX_EMAILS_PER_STUDENT];
}email_stack;

/** @struct student
 *  @brief Stores all of the information related to a student
 *  @var char[]::name
 *  @var int[]::nusp
 *  @var int[]::phone
 *  @var char[]::email
 *  @var int::next
 *  @var email_stack::emails
 *  @var int::waitlist_beg
 *  @var int::waitlist_end
 *  Member 'name' string that stores name of student
 *  Member 'nusp' stores the numero USP of student
 *  Member 'phone' stores the student's phone number
 *  Member 'email' string that stores student's email
 *  Member 'next' index of the next student in the student list
 *  Member 'emails' stack of all of the students' emails
 *  Member 'waitlist_first' index of the first student on waitlist
 *  Member 'waitlist_last' index of the last student on waitlist
 */
typedef struct _student {
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
    int next;
    email_stack emails;

} student;


/** @struct student_list
 *  @brief List to store student nodes
 *  @var int::first_empty
 *  @var int::beg
 *  @var int::end
 *  Member 'first_empty' index of the first empty space in student memory bank
 *  Member 'first' index of the first student of list
 *  Member 'last' index of the last student of list
 */
typedef struct {
    int first_empty, first, last;
    student elements[MAX_STUDENTS];
} student_list;


/** @brief Creates a new student list for library
 *
 * Initializes the student_list of passed library so that the other functions
 * for the student list can be used successfully.
 *
 * @param library* lib pointer to the library
 */
void create_stud_list(student_list *students);


/** @brief Get next space in student list
 *
 * Find the next available space in the memory bank for the student. Return -1
 * if there is no more available space.
 *
 * @param student_list *studs student list where memory will be searched
 */
int get_node_studentlist(student_list *students);


/** @brief Free the specified index of student memory bank
 *
 * Free the specified index in the student memory bank.
 *
 * @param student_list *studs student list where memory will be freed
 * @param int index index that will be freed
 */
void free_node_studentlist(student_list *students, int index);

int create_student(student_list *students, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]);


void insert_student_to_list(student_list *students, int index);

/** @brief Searches for student with name in the student list
 *
 * Searches for a student in the student list of the passed library whose name
 * is the same as the name passed to the function. Previous student in the list
 * is saved to passed parameter prev_stud.
 *
 * @param library* lib pointer to the library
 * @param char[] name name of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on library's student list, 1 otherwise
 */
int search_student_name(student_list *students, char name[MAX_NAME_SIZE],
                        int *prev_stud);


/** @brief Searches for student with nusp in the student list
 *
 * Searches for a student in the student list of the passed library whose nusp
 * is the same as the nusp passed to the function. Previous student in the list
 * is saved to passed parameter prev_stud.
 *
 * @param library* lib pointer to the library where student will be searched
 * @param int[] nusp nusp of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on list, 1 otherwise
 */
int search_student_nusp(student_list *students, int nusp[MAX_NUSP_SIZE],
                        int *prev_stud);

void remove_student_studentlist(student_list *students, int prev_stud);

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
 * @param email stack* emls pointer to the email stack where message will be
 * removed
 * @param char[] email message message that was removed from stack
 * @return 1 if it was not possible to remove email, 0 if email removed
 */
int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);


/** @brief Clears the email stack
 *
 * Clears the email stack and returns it to it's initial position, with top
 * pointing to NULL. Frees the memory of all nodes that were part of the
 * email stack.
 *
 * @param wait_list* wl wait list to be removed
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