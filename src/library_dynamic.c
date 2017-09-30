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
    create_email_stack(&s->emails);
    create_stud_bklist(&s->bks);
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

/* Searches for a student in the list with passed nusp, if found, pointer to
 * the previous student in list is saved in prev_stud and 0 is returned. If it
 * is not possible to find student, prev_stud will be Null and 1 is returned.
 */
int search_student_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE],
                        student **prev_stud) {
    student *s = studs->first;
    if(s == NULL){
        return 1;
    }
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
//todo remove student from all wait lists
/* Removes student with name from student list. Returns 0 if student is removed
 * successfully. Returns 1 if it is not possible to remove the student
 */
int remove_student_name(student_list *studs, char name[MAX_NAME_SIZE]) {
    student *prev_stud = NULL;
    student *stud = studs->first;
    //list is empty
    if (stud == NULL) {
        return 1;
    }
    //student not found in list
    if (search_student_name(studs, name, &prev_stud) == 1) {
        return 1;
    }
    //student is 1st element
    if (prev_stud == NULL) {
        studs->first = stud->next;
        free(stud);
        //student was only element, list is not empty
        if (studs->first == NULL)
            studs->last = NULL;
        return 0;
    }
    stud = prev_stud->next;
    prev_stud->next = stud->next;
    delete_email_stack(&stud->emails);
    remove_stud_bklist(&stud->bks);
    free(stud);
    return 0;
}
//todo remove student from all wait lists
/* Removes student with nusp from student list. Returns 0 if student is removed
 * successfully. Returns 1 if it is not possible to remove the student
 */
int remove_student_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE]) {
    student *prev_stud = NULL;
    student *stud = studs->first;
    //list is empty
    if (stud == NULL) {
        return 1;
    }
    //student not found in list
    if (search_student_nusp(studs, nusp, &prev_stud) == 1) {
        return 1;
    }
    //student is 1st element
    if (prev_stud == NULL) {
        studs->first = stud->next;
        free(stud);
        //student was only element, list is not empty
        if (studs->first == NULL)
            studs->last = NULL;
        return 0;
    }
    stud = prev_stud->next;
    prev_stud->next = stud->next;
    delete_email_stack(&stud->emails);
    remove_stud_bklist(&stud->bks);
    free(stud);
    return 0;
}


/*
 * Initializes a new list of book.
 */
void create_book_list(book_list *books) {
    books->first = NULL;
    books->last = NULL;
}

//todo deal with potential duplicates
int insert_book(book_list *books, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition) {
    book *b = (book *) malloc(sizeof(book));
    if (b == NULL) {
        return 1;
    }
    create_wait_list(&(b->wl));
    strcpy(b->title, title);
    strcpy(b->author, author);
    strcpy(b->editor, editor);
    copy_int_array(b->isbn, isbn, MAX_ISBN_SIZE);
    b->year = year;
    b->edition = edition;

    b->next = NULL;

    //if list is currently empty
    if (books->first == NULL) {
        books->first = b;
    } else { //list has at least one element already
        books->last->next = b;
    }
    books->last = b;
    b->count = 1;

    return 0;
}

/* Searches for a book in the list with passed title, if found, pointer to
 * the previous book in list is saved in prev_book and 0 is returned. If it
 * is not possible to find book, prev_book will be Null and 1 is returned.
 */
int search_book_title(book_list *bks, char title[MAX_TITLE_SIZE],
                        book **prev_book) {
    book *b = bks->first;
    if(b == NULL)
        return 1;
    //If the student is the first in the list
    if (strcmp(b->title, title) == 0) {
        *prev_book = NULL;
        return 0;
    }
    while (b->next != NULL) {
        if (strcmp(b->next->title, title) == 0) {
            *prev_book = b;
            return 0;
        }
        b = b->next;

    }
    return 1;
}

/* Searches for a book in the list with passed ISBN, if found, pointer to
 * the previous book in list is saved in prev_book and 0 is returned. If it
 * is not possible to find book, prev_book will be Null and 1 is returned.
 */
int search_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE],
                        book **prev_book) {
    book *b = books->first;
    if (b == NULL)
        return 1;
    //If the student is the first in the list
    if (compare_int_array(isbn, b->isbn, MAX_ISBN_SIZE) == 0) {
        *prev_book = NULL;
        return 0;
    }
    while (b->next != NULL) {
        if (compare_int_array(b->next->isbn, isbn, MAX_NUSP_SIZE) == 0) {
            *prev_book = b;
            return 0;
        }
        b = b->next;

    }
    return 1;
}

/* Removes book with title from book list. Returns 0 if book is removed
 * successfully. Returns 1 if it is not possible to remove the book.
 */
int remove_book_title(book_list *books, char title[MAX_TITLE_SIZE]) {
    book *prev_book = NULL;
    book *book = books->first;
    //list is empty
    if (book == NULL) {
        return 1;
    }
    //book not found in list
    if (search_book_title(books, title, &prev_book) == 1) {
        return 1;
    }
    //book is 1st element
    if (prev_book == NULL) {
        books->first = book->next;
        remove_wait_list(&(book->wl));
        free(book);
        //book was only element, list is not empty
        if (books->first == NULL)
            books->last = NULL;
        return 0;
    }
    book = prev_book->next;
    prev_book->next = book->next;
    remove_wait_list(&(book->wl));
    free(book);
    return 0;
}

/* Removes book with ISBN from book list. Returns 0 if book is removed
 * successfully. Returns 1 if it is not possible to remove the book
 */
int remove_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE]) {
    book *prev_book = NULL;
    book *book = books->first;
    //list is empty
    if (book == NULL) {
        return 1;
    }
    //student not found in list
    if (search_book_isbn(books, isbn, &prev_book) == 1) {
        return 1;
    }
    //student is 1st element
    if (prev_book == NULL) {
        books->first = book->next;
        remove_wait_list(&(book->wl));
        free(book);
        //student was only element, list is not empty
        if (books->first == NULL)
            books->last = NULL;
        return 0;
    }
    book = prev_book->next;
    prev_book->next = book->next;
    remove_wait_list(&(book->wl));
    free(book);
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

/*
 * Creates the waitlist with initialized values.
 */
void create_wait_list(wait_list *wl){
    wl->first = NULL;
    wl->last = NULL;

}

/*
 * Removes the wait list, freeing the memory used for the nodes.
 */
void remove_wait_list(wait_list *wl){
    student * temp = NULL;
    while(remove_from_waitlist(temp, wl) == 0);
}

/* Adds the student to the passed wait list. Returns 1 if an error occurred, 0
 * if student was added successfully
 */
int add_to_waitlist(student *stud, wait_list *wl){
    wait_list_entry *new_entry = (wait_list_entry *)malloc(sizeof (wait_list_entry));
    if (new_entry == NULL)
        return 1;
    new_entry->stud = stud;
    new_entry->next = NULL;
    if(wl->first == NULL){
        wl->first = new_entry;
    }
    else {
        wl->last->next = new_entry;
    }
    wl->last = new_entry;
    return 0;
}

/*
 * Removes the first student from the waitlist. Returns 1 if an error occurs, 0
 * if student is removed successfully. Saves student removed to stud.
 */
int remove_from_waitlist(student *stud, wait_list *wl){
    if(wl->first == NULL)
        return 1;

    //possible error on this line
    *stud = *wl->first->stud;
    wait_list_entry *temp = wl->first;
    if(wl->first->next == NULL){
        wl->first = NULL;
        wl->last = NULL;
    }
    else {
        wl->first = wl->first->next;
    }
    free(temp);
    return 0;

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


int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]){
    if(emls->top == NULL)
        return 1;
    strcpy(message, emls->top->message);
    email * temp = emls->top;
    emls->top = emls->top->next;
    free(temp);
    return 0;
}

void delete_email_stack(email_stack *emls){
    char *message = NULL;
    while(pop_email(emls, message) == 0);

}


int send_email(student *stud, char message[MAX_MESSAGE_SIZE]){
    return push_email(&stud->emails, message);
}


int get_student_by_name(student_list *studs, char name[MAX_NAME_SIZE], student **stud){
    student **prev ;
    if(search_student_name(studs, name, prev) == 1)
        return 1;
    if(*prev == NULL)
        *stud = (studs->first);
    else
        *stud = (*prev)->next;
    return 0;
}


int get_student_by_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE], student **stud){
    student **prev ;
    if(search_student_nusp(studs, nusp, prev) == 1)
        return 1;
    if(*prev == NULL)
        *stud = studs->first;
    else
        *stud = (*prev)->next;
    return 0;
}


int get_book_by_title(book_list *bks, char title[MAX_TITLE_SIZE], book **bk){
    book **prev ;
    if(search_book_title(bks, title, prev) == 1)
        return 1;
    if(*prev == NULL)
        *bk = bks->first;
    else
        *bk = (*prev)->next;
    return 0;
}


int get_book_by_isbn(book_list *bks, int isbn[MAX_ISBN_SIZE], book **bk){
    book **prev ;
    if(search_book_isbn(bks, isbn, prev) == 1)
        return 1;
    if(*prev == NULL)
        *bk = bks->first;
    else
        *bk = (*prev)->next;
    return 0;
}


/*
 * Creates student's book list with initialized values.
 */
void create_stud_bklist(stud_bklist *bl){
    bl->first = NULL;
    bl->last = NULL;

}

/*
 * Removes the wait list, freeing the memory used for the nodes.
 */
void remove_stud_bklist(stud_bklist *bl){
    book * temp = NULL;
    while(remove_from_stud_bklist(temp, bl) == 0);
}

/* Adds the student to the passed wait list. Returns 1 if an error occurred, 0
 * if student was added successfully
 */
int add_to_stud_bklist(book *bk, stud_bklist *bl){
    stud_bklist_entry *new_entry = (stud_bklist_entry *)malloc(sizeof (stud_bklist_entry));
    if (new_entry == NULL)
        return 1;
    new_entry->bk = bk;
    new_entry->next = NULL;
    if(bl->first == NULL){
        bl->first = new_entry;
    }
    else {
        bl->last->next = new_entry;
    }
    bl->last = new_entry;
    return 0;
}
//todo needs to search by book name
/*
 * Removes the first student from the waitlist. Returns 1 if an error occurs, 0
 * if student is removed successfully. Saves student removed to stud.
 */
int remove_from_stud_bklist(book *bk, stud_bklist *bl){
    if(bl->first == NULL)
        return 1;

    //possible error on this line
    *bk = *bl->first->bk;
    stud_bklist_entry *temp = bl->first;
    if(bl->first->next == NULL){
        bl->first = NULL;
        bl->last = NULL;
    }
    else {
        bl->first = bl->first->next;
    }
    free(temp);
    return 0;

}