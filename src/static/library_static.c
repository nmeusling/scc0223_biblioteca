/** @file library_static.c
 *  @brief Static Abstract Data Type for Library Management
 *
 *  Contains the operations to manipulate the library data structure. Includes
 *  operations to register a new student, remove a student, register a new book,
 *  remove a book from the library, check out a book and return a book.
 *
 *  @author Natalie Menato (10295051)
 */


#include "library_static.h"


/*
 * Initializes the library, creating its associated student list and book list
 */
void create_library(library *lib){
    create_stud_list(&lib->students);
    create_book_list(&lib->books);
    create_wait_list(&lib->books.wl);
}



/*
 * Calls the necessary functions to create a new student with the passed
 * information and then add the student to the library's student list.
 */
int insert_student(library *lib, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]){

    int index = create_student(&lib->students, name, nusp, phone, email);
    if(index == -1)
        return 1;
    insert_student_to_list(&lib->students, index);
    return 0;

}

/*
 * Calls the necessary functions to remove the student from the student list.
 * The student is also removed from any wait lists that they are currently on.
 */
int remove_student(library *lib, int prev_stud){
    int index = lib->students.first;
    if(index == -1)
        return 1;
    //student is first in list
    if(prev_stud == -1)
        remove_student_all_waitlists(&lib->books, &lib->students.elements[index]);
    else {
        index = lib->books.elements[prev_stud].next;
        remove_student_all_waitlists(&lib->books, &lib->students.elements[index]);
    }
    remove_student_studentlist(&lib->students, prev_stud);
    return 0;
}

/*
 * Uses search function to find previous student in library's student list and
 * then removes the desired student.
 */
int remove_student_name(library *lib, char name[MAX_NAME_SIZE]){
    int prev_stud = -1;

    //student not found in list, otherwise index of previous student saved to prev_stud
    if (search_student_name(&lib->students, name, &prev_stud) == 1) {
        return 1;
    }
    return remove_student(lib, prev_stud);
}

/*
 * Uses search function to find previous student in library's student list and
 * then removes the desired student.
 */
int remove_student_nusp(library *lib, int nusp[MAX_NUSP_SIZE]) {
    int prev_stud = -1;

    //student not found in list, otherwise previous student saved to prev_stud
    if (search_student_nusp(&lib->students, nusp, &prev_stud) == 1) {
        return 1;
    }
    return remove_student(lib, prev_stud);
}



/*
 * Verifies if a book with the same ISBN number already exists. If so, the book
 * count and total are incremented. Otherwise, calls the functions to create a
 * new book and then adds the book to the end of existing book list of passed
 * library.
 */
int insert_book(library *lib, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition){
    int prev, index;
    //already exists book with same isbn
    if(search_book_isbn(&lib->books, isbn, &prev) == 0){
        if(prev == -1) {
            lib->books.elements[lib->books.first].count++;
            lib->books.elements[lib->books.first].total++;
        }
        else {
            index = lib->books.elements[prev].next;
            lib->books.elements[index].count++;
            lib->books.elements[lib->books.first].total++;
        }
        return 2;
    }
    index = create_book(&lib->books, title, author, editor, isbn, year, edition);
    if( index == -1)
        return 1;
    insert_book_booklist(&lib->books, index);
    return 0;
}



/*
 * Verifies if the total number of copies of the book the is more than 1. If so,
 * total is decremented. Otherwise, calls the function to remove the book from
 * the book list and then deletes the book.
 */
int remove_book_title(library *lib, char title[MAX_TITLE_SIZE]){
    int bk = -1;
    int prev_book = -1;

    //book not found in list
    if (search_book_title(&lib->books, title, &prev_book) == 1) {
        return 1;
    }
    if(prev_book == -1){
        bk = lib->books.first;
    }
    else {
        bk = lib->books.elements[prev_book].next;
    }
    if(lib->books.elements[bk].total > 1){
        lib->books.elements[bk].count --;
        lib->books.elements[bk].total --;
        return 2;
    }
    return remove_book_booklist(&lib->books, prev_book);
}

/*
 * Verifies if the total number of copies of the book the is more than 1. If so,
 * total is decremented. Otherwise, calls the function to remove the book from
 * the book list and then deletes the book.
 */
int remove_book_isbn(library *lib, int isbn[MAX_ISBN_SIZE]){
    int bk = -1;
    int prev_book = -1;

    //book not found in list
    if (search_book_isbn(&lib->books, isbn, &prev_book) == 1) {
        return 1;
    }
    if(prev_book == -1){
        bk = lib->books.first;
    }
    else {
        bk = lib->books.elements[prev_book].next;
    }
    if(lib->books.elements[bk].total > 1){
        lib->books.elements[bk].count --;
        lib->books.elements[bk].total --;
        return 2;
    }
    return remove_book_booklist(&lib->books, prev_book);
}



/*
 * If book is available, decrements the number of available copies. If book is
 * not available, student is added to the wait list. If student is already on
 * waitlist, they will not be added again.
 */
int checkout_book(library *lib, student *stud, book *bk){
    if(book_available(bk)) {
        bk->count--;
        return 0;
    }
    if(is_on_waitlist(bk, &lib->books, stud)){
        return 2;
    }
    if(add_to_waitlist(stud, bk, &lib->books) == 0)
        return 1;
    //not possible to add student to waitlist
    return 3;
}


/*
 * If book does not have a waitlist, increments the number of available copies.
 * If book has a waitlist, sends an email to the next student and removes them
 * from wait list. Returns 1 if no student on waitlist, 0 if next student was
 * notified.
 */
int return_book(library *lib, book *bk){
    student *next;
    char message[MAX_MESSAGE_SIZE] = "Um livro esta pronto para voce retirar!\nTitulo:";
    if(bk->waitlist_first == -1){
        bk->count ++;
        return 1;
    }
    else{
        strcat(message, bk->title);
        next = lib->books.wl.items[bk->waitlist_first].stud;
        push_email(&next->emails, message);
        remove_from_waitlist(bk, &lib->books, &next);
        return 0;
    }
}


