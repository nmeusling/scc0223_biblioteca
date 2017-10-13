/** @file student_dynamic.c
 *  @brief Functions related to student and student list
 *
 *  Dynamic version:
 *  This file contains all of the functions related to the student and student
 *  list, including the functions for manipulating the email stack.
 *
 *  @author Natalie Menato (10295051)
 */

#include "book_dynamic.h"

/*
 * Initializes the book list of library
 */
void create_book_list(book_list *books) {
    books->first = NULL;
    books->last = NULL;
}


/*
 * Allocates memory for a new book and saves the passed fields to the book's
 * details. Saves address of created book to passed bk.
 */
int create_book(book **bk, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition){
    book *b = (book *) malloc(sizeof(book));
    if(b == NULL)
        return 1;
    create_wait_list(&(b->wl));
    strcpy(b->title, title);
    strcpy(b->author, author);
    strcpy(b->editor, editor);
    copy_int_array(b->isbn, isbn, MAX_ISBN_SIZE);
    b->year = year;
    b->edition = edition;
    b->count = 1;
    b->total = 1;
    *bk = b;
    return 0;

}


/*
 * Adds book to the end of the book list.
 */
void insert_book_booklist(book_list *books, book *bk){
    bk->next = NULL;

    //if list is currently empty
    if (books->first == NULL) {
        books->first = bk;
    } else { //list has at least one element already
        books->last->next = bk;
    }
    books->last = bk;
}


/*
 * Searches for a book in the book list whose title is the same as the
 * title passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 */
int search_book_title(book_list *books, char title[MAX_TITLE_SIZE],
                      book **prev_book) {
    book *b = books->first;
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


/*
 * Searches for a book in the book list whose ISBN is the same as the
 * ISBN passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
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


/*
 * The next book after the passed book is removed from the list and the
 * memory that was allocated to the book is freed. Return 0 if book removed, 0
 * otherwise.
 */
int remove_book_booklist(book_list *books, book *prev_book){
    book *bk = books->first;
    //list is empty
    if(bk == NULL)
        return 1;
    //book is 1st element
    if (prev_book == NULL) {
        remove_wait_list(&bk->wl);
        books->first = bk->next;
        //book was only element, list is not empty
        if (books->first == NULL)
            books->last = NULL;

        free(bk);
        return 0;
    }
        //book is last but not only element
    else if(prev_book->next == books->last)
    {
        books->last = prev_book;
    }
    bk = prev_book->next;
    prev_book->next = bk->next;
    remove_wait_list(&bk->wl);
    free(bk);
    return 0;
}


/*
 * Searches for the book in the book list by title and saves the book
 * to the passed book parameter if found. Return 0 if book is found, 1 if not
 * found
 */
int get_book_by_title(book_list *books, char title[MAX_TITLE_SIZE], book **bk){
    book *prev ;
    if(search_book_title(books, title, &prev) == 1)
        return 1;
    if(prev == NULL)
        *bk = books->first;
    else
        *bk = (prev)->next;
    return 0;
}

/*
 * Searches for the book in the library's book list by isbn and saves the book
 * to the passed book parameter if found. Return 0 if book is found, 1 if not
 * found
 */
int get_book_by_isbn(book_list *books, int isbn[MAX_ISBN_SIZE], book **bk){
    book *prev ;
    if(search_book_isbn(books, isbn, &prev) == 1)
        return 1;
    if(prev == NULL)
        *bk = books->first;
    else
        *bk = (prev)->next;
    return 0;
}


/*
 * Gets the title of the passed book and returns it as a string.
 */
char* get_book_title(book *bk){
    return bk->title;
}


/*
 * Checks if passed book is available to be checked out by a student. Return 1
 * if available, 0 if not available
 */
int book_available(book *bk){
    if(bk->count >= 1)
        return 1;
    return 0;
}


/*
 * Creates the waitlist with initialized values.
 */
void create_wait_list(wait_list *wl){
    wl->first = NULL;
    wl->last = NULL;
    wl->total = 0;

}

/*
 * Removes the wait list, freeing the memory used for the nodes.
 */
void remove_wait_list(wait_list *wl){
    student *temp;
    while(remove_from_waitlist(wl, &temp) == 0);
}

/*
 * Adds the student to the passed wait list. Returns 1 if an error occurred, 0
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
    wl->total ++;
    return 0;
}

/*
 * Removes the first student from the waitlist. Returns 1 if an error occurs, 0
 * if student is removed successfully. Saves student removed to stud.
 */
int remove_from_waitlist(wait_list *wl, student **stud){
    if(wl->first == NULL)
        return 1;

    wait_list_entry *temp = wl->first;
    *stud = temp->stud;
    if(wl->first->next == NULL){
        wl->first = NULL;
        wl->last = NULL;
    }
    else {
        wl->first = wl->first->next;
    }
    free(temp);
    wl->total --;
    return 0;

}


/*
 * Checks if student is already on passed waitlist. Returns 1 if student is on
 * wait list, 0 if not
 */
int is_on_waitlist(wait_list *wl, student *stud){
    student *temp;
    int i;
    int result = 0;
    for(i = 0; i<wl->total; i++){
        remove_from_waitlist(wl, &temp);
        if(stud == temp){
            result = 1;
        }
        add_to_waitlist(temp, wl);
    }
    return result;
}


/*
 * Checks the waitlist for each book and removes the student from any wait list
 * they belong to
 */
void remove_student_all_waitlists(book_list *bks, student *stud){
    book *pointer = bks->first;
    student *temp = NULL;
    int i;
    //for all books
    while(pointer != NULL){
        for(i = 0; i<pointer->wl.total;i++){
            remove_from_waitlist(&pointer->wl, &temp);
            if(temp != stud){
                add_to_waitlist(temp, &pointer->wl);
            }
        }
        pointer = pointer->next;
    }
}


