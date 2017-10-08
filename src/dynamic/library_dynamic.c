/** @file library_dynamic.c
 *  @brief Dynamic Abstract Data Type for Library Management
 *
 *  Contains the operations to manipulate the library data structure. Includes
 *  operations to register a new student, remove a student, register a new book,
 *  remove a book from the library, check out a book and return a book.
 *
 *  @author Natalie Menato (10295051)
 */

#include "library_dynamic.h"

/*
 * Initializes the library, creating its associated student list and book list
 */
void create_library(library *lib){
    create_stud_list(&lib->students);
    create_book_list(&lib->books);
}



int insert_student(library *lib, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]){
    student* s;
    if(create_student(&s, name, nusp, phone, email) == 1)
        return 1;
    insert_student_to_list(&lib->students, s);
    return 0;
}

/*
 * Allocates memory for a new book. Saves the passed title, author, editor,
 * isbn, year, and edition to the new book. Adds the new book to the end of
 * existing library book list. If the ISBN is duplicated, a new record will not
 * be added to the list. Instead the count of books of the original will be
 * incremented.
 */
int insert_book(library *lib, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition) {
    book *bk;
    book *prev;
    //already exists book with same isbn
    if(search_book_isbn(&lib->books, isbn, &prev) == 0){
        if(prev == NULL)
            lib->books.first->count++;
        else
            prev->next->count++;
        return 2;
    }

    if(create_book(&bk, title, author, editor, isbn, year, edition) == 1)
        return 1;
    insert_book_booklist(&lib->books, bk);
    return 0;
}

/*
 * Removes book with title from library's book list. Returns 0 if book is
 * removed successfully. Returns 1 if it is not possible to remove the book, if
 * 1 is returned either list is empty or the book is not on the list.
 */
int remove_book_title(library *lib, char title[MAX_TITLE_SIZE]) {
    book *prev_book = NULL;

    //book not found in list
    if (search_book_title(&lib->books, title, &prev_book) == 1) {
        return 1;
    }

    return remove_book_booklist(&lib->books, prev_book);
}

/*
 * Removes book with ISBN from library's book list. Returns 0 if book is
 * removed successfully. Returns 1 if it is not possible to remove the book
 */
int remove_book_isbn(library *lib, int isbn[MAX_ISBN_SIZE]) {
    book *prev_book = NULL;

    //book not found in list
    if (search_book_isbn(&lib->books, isbn, &prev_book) == 1) {
        return 1;
    }

    return remove_book_booklist(&lib->books, prev_book);
}


int remove_student(library *lib, student *prev_stud){
    if(lib->students.first == NULL)
        return 1;
    if(prev_stud == NULL)
        remove_student_all_waitlists(&lib->books, lib->students.first);
    else
        remove_student_all_waitlists(&lib->books, prev_stud->next);

    remove_student_studentlist(&lib->students, prev_stud);
    return 0;
}



/*
 * Removes student with name from library's student list. Returns 0 if student
 * is removed successfully. Returns 1 if it is not possible to remove the student
 */
int remove_student_name(library *lib, char name[MAX_NAME_SIZE]) {
    student *prev_stud = NULL;

    //student not found in list, otherwise previous student saved to prev_stud
    if (search_student_name(&lib->students, name, &prev_stud) == 1) {
        return 1;
    }
    return remove_student(lib, prev_stud);
}

/*
 * Removes student with nusp from library's student list. Returns 0 if student
 * is removed successfully. Returns 1 if it is not possible to remove the student
 */
int remove_student_nusp(library *lib, int nusp[MAX_NUSP_SIZE]) {
    student *prev_stud = NULL;

    //student not found in list, otherwise previous student saved to prev_stud
    if (search_student_nusp(&lib->students, nusp, &prev_stud) == 1) {
        return 1;
    }
    return remove_student(lib, prev_stud);
}



/*
 * If book is available, decrements the number of available copies. If book is
 * not available, student is added to the wait list.
 */
int checkout_book(student *stud, book *bk){
    if(book_available(bk)) {
        bk->count--;
        return 0;
    }
    add_to_waitlist(stud, &bk->wl);
    return 1;
}

/*
 * If book does not have a waitlist, increments the number of available copies.
 * If book has a waitlist, sends an email to the next student and removes them
 * from wait list.
 */
void return_book(book *bk){
    student *next;
    char message[MAX_MESSAGE_SIZE] = "Um livro esta pronto para voce retirar!\nTitulo:";
    if(bk->wl.first == NULL){
        (bk)->count ++;
    }
    else{
        strcat(message, bk->title);
        next = bk->wl.first->stud;
        push_email(&next->emails, message);
        remove_from_waitlist(next, &bk->wl);
    }
}











