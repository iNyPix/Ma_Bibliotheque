#include "book.h"

Book::Book()
{
    id = 0;
    title = "";
    authors = "";
    editors = "";
    gender = "";
    collection = "";
    numbers = 1;
    year = 0;
    tome = 0;
    tomeEnd = 0;
    isbn = 0;
}

const int &Book::getId() const {
    return id;
}

void Book::setId(int id) {
    Book::id = id;
}

const string &Book::getTitle() const {
    return title;
}

void Book::setTitle(const string &title) {
    Book::title = title;
}

const string &Book::getAuthors() const {
    return authors;
}

void Book::setAuthors(const string &authors) {
    Book::authors = authors;
}

const string &Book::getEditors() const {
    return editors;
}

void Book::setEditors(const string &editors) {
    Book::editors = editors;
}

const string &Book::getGender() const {
    return gender;
}

void Book::setGender(const string &gender) {
    Book::gender = gender;
}

const string &Book::getCollection() const {
    return collection;
}

void Book::setCollection(const string &collection) {
    Book::collection = collection;
}

int Book::getNumbers() const {
    return numbers;
}

void Book::setNumbers(int numbers) {
    Book::numbers = numbers;
}

int Book::getYear() const {
    return year;
}

void Book::setYear(int year) {
    Book::year = year;
}

int Book::getTome() const {
    return tome;
}

void Book::setTome(int tome) {
    Book::tome = tome;
}

int Book::getTomeEnd() const {
    return tomeEnd;
}

void Book::setTomeEnd(int tomeEnd) {
    Book::tomeEnd = tomeEnd;
}

int Book::getIsbn() const {
    return isbn;
}

void Book::setIsbn(int isbn) {
    Book::isbn = isbn;
}

const string &Book::getSummary() const {
    return summary;
}

void Book::setSummary(const string &summary) {
    Book::summary = summary;
}

const string &Book::getImg() const {
    return img;
}

void Book::setImg(const string &img) {
    Book::img = img;
}
