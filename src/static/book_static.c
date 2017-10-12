//
// Created by nmeusling on 10/8/17.
//

#include "book_static.h"


/*
 * Find the next available space in the memory bank for the book. Return -1
 * if there is no more available space.
 */
int get_node_booklist(book_list *books){
    int index = books->first_empty;
    if(index == -1 )
        return -1;
    books->first_empty = books->elements[index].next;
    books->elements[index].next = -1;
    return index;
}


/*
 * Frees the space of passed index in the book list memory bank. Adds space
 * back to empty list.
 */
void free_node_booklist(book_list *books, int index){
    books->elements[index].next = books->first_empty;
    books->first_empty =  index;
}

/*
 * Find the next available space in the memory bank for the book. Return -1
 * if there is no more available space.
 */
int get_node_waitlist(wait_list *wl){
    int index = wl->first_empty;
    if(index == -1 )
        return -1;
    wl->first_empty = wl->items[index].next;
    wl->items[index].next = -1;
    return index;
}


/*
 * Frees the space of passed index in the book list memory bank. Adds space
 * back to empty list.
 */
void free_node_waitlist(wait_list *wl, int index){
    wl->items[index].next = wl->first_empty;
    wl->first_empty =  index;
}


/*
 * Initializes the memory bank for the book_list in the library so that the
 * other functions for the book list can be used.
 */
void create_book_list(book_list *books){
    int i;
    for(i=0; i<MAX_BOOKS-1; i++){
        books->elements[i].next = i+1;
    }
    books->elements[MAX_STUDENTS -1].next = -1;
    books->first_empty = 0;
    books->first = -1;
    books->last = -1;
}

int create_book(book_list *books, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition){
    int index =  get_node_booklist(books);
    if (index == -1) {
        return index;
    }
    strcpy(books->elements[index].title, title);
    strcpy(books->elements[index].author, author);
    strcpy(books->elements[index].editor, editor);
    copy_int_array(books->elements[index].isbn, isbn, MAX_ISBN_SIZE);
    books->elements[index].year = year;
    books->elements[index].edition = edition;
    books->elements[index].count = 1;
    books->elements[index].waitlist_first = -1;
    books->elements[index].waitlist_last = -1;
    books->elements[index].waitlist_total = 0;
    return index;
}

void insert_book_booklist(book_list *books, int index){
    books->elements[index].next = -1;

    //if list is currently empty
    if (books->first == -1) {
        books->first = index;
    } else { //list has at least one element already
        books->elements[books->last].next = index;
    }
    books->last = index;
}

/*
 * Searches for a book in the library's book list whose title is the same as the
 * title passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 */
int search_book_title(book_list *books, char title[MAX_TITLE_SIZE],
                      int *prev_book){
    int index = books->first;
    int next;
    if(index == -1)
        return 1;
    next = books->elements[index].next;
    //If the student is the first in the list
    if (strcmp(books->elements[index].title, title) == 0) {
        *prev_book = -1;
        return 0;
    }
    while (next!= -1) {

        if (strcmp(books->elements[next].title, title) == 0) {
            *prev_book = index;
            return 0;
        }
        index = next;
        next = books->elements[next].next;

    }
    return 1;
}


/*
 * Searches for a book in the library's book list whose ISBN is the same as the
 * ISBN passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 */
int search_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE],
                     int *prev_book){
    int index = books->first;
    int next;
    if(index == -1)
        return 1;
    next = books->elements[index].next;
    //If the student is the first in the list
    if (compare_int_array(books->elements[index].isbn, isbn, MAX_ISBN_SIZE) == 0) {
        *prev_book = -1;
        return 0;
    }
    while (next != -1) {
        if (compare_int_array(books->elements[next].isbn, isbn, MAX_ISBN_SIZE) == 0) {
            *prev_book = index;
            return 0;
        }
        index = next;
        next = books->elements[next].next;

    }
    return 1;
}

int remove_book_booklist(book_list *books, int prev_book){
    int index = books->first;
    //list is empty
    if(index == -1)
        return 1;
    //book is 1st element
    if (prev_book == -1) {
        remove_wait_list(&books->elements[index], books);
        books->first = books->elements[index].next;
        //book was only element, list is not empty
        if (books->first == -1)
            books->last = -1;

        free_node_booklist(books, index);
        return 0;
    }
        //book is last but not only element
    else if(books->elements[prev_book].next == books->last)
    {
        books->last = prev_book;
    }
    index = books->elements[prev_book].next;
    books->elements[prev_book].next = books->elements[index].next;
    remove_wait_list(&books->elements[index], books);
    free_node_booklist(books, index);
    return 0;
}

int get_book_by_title(book_list *books, char title[MAX_TITLE_SIZE], book **bk){
    int prev, next;
    if(search_book_title(books, title, &prev) == 1)
        return 1;
    if(prev == -1)
        *bk = &books->elements[books->first];
    else {
        next = books->elements[prev].next;
        *bk = &books->elements[next];
    }
    return 0;
}

int get_book_by_isbn(book_list *books, int isbn[MAX_ISBN_SIZE], book **bk){
    int prev, next;
    if(search_book_isbn(books, isbn, &prev) == 1)
        return 1;
    if(prev == -1)
        *bk = &books->elements[books->first];
    else {
        next = books->elements[prev].next;
        *bk = &books->elements[next];
    }
    return 0;
}

char* get_book_title(book *bk){
    return bk->title;
}

int book_available(book *bk){
    if(bk->count >= 1 )
        return 1;
    return 0;
}

/*
 * Creates the waitlist memory bank with initialized values.
 */
void create_wait_list(wait_list *wl){
    int i;
    for(i=0; i<MAX_BOOKS-1; i++){
        wl->items[i].next = i+1;
    }
    wl->items[MAX_BOOKS-1].next = -1;
    wl->first_empty= 0;
}


void remove_wait_list(book *bk, book_list *bks){
    student * temp = NULL;

    while(remove_from_waitlist(bk, bks, &temp) == 0);

}

int add_to_waitlist(student *stud, book *bk, book_list *books){
    int index = get_node_waitlist(&books->wl);
    if (index == -1)
        return 1;
    books->wl.items[index].stud = stud;
    books->wl.items[index].next = -1;
    //list is currently empty
    if(bk->waitlist_first == -1){
        bk->waitlist_first = index;
    }
    else {
        books->wl.items[bk->waitlist_last].next = index;
    }
    bk->waitlist_last = index;
    bk->waitlist_total ++;
    return 0;
}

int remove_from_waitlist(book *bk, book_list *books, student **stud ){
    int first = bk->waitlist_first;
    //waitlist is empty
    if(first == -1)
        return 1;

    //if student is only one on waitlist

    int index = bk->waitlist_first;
    *stud = books->wl.items[index].stud;
    if(books->wl.items[index].next == -1){
        bk->waitlist_first = -1;
        bk->waitlist_last = -1;
    }
    else {
        bk->waitlist_first = books->wl.items[index].next;
    }
    free_node_waitlist(&books->wl, index);
    bk->waitlist_total --;
    return 0;
}

void remove_student_all_waitlists(book_list *bks, student *stud){
    int book_index = bks->first;
    student *temp;
    int i;
    //for all books
    while(book_index != -1){
        for(i = 0; i<bks->elements[book_index].waitlist_total;i++){
            remove_from_waitlist(&(bks->elements[book_index]), bks, &temp);
            if(temp != stud){
                add_to_waitlist(temp, &(bks->elements[book_index]), bks);
            }
        }
        book_index = bks->elements[book_index].next;
    }
}