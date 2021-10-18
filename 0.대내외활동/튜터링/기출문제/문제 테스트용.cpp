#include <iostream>
#include <string>
using namespace std;


//// 1번
//class Student {
//	int num;
//	string name;
//	string major;
//
//public:
//	// 생성자
//	Student(int n, string a, string m) : num(n), name(a), major(m) { }
//	Student(const Student& obj) : num(obj.num), name(obj.name), major(obj.major) { }
//};


//// 2번
//class Book {
//private:
//    string title;
//    int page;
//public:
//    Book() { }
//    Book(const string& t, int p) {
//        title = t;
//        page = p;
//    }
//    Book(const Book& b) {
//        title = b.title;
//        page = b.page;
//    }
//};
//
//int main() {
//    Book book1;
//    Book book2 = Book();
//    Book* book3 = new Book;
//}



// 3번
class Book {
private:
    string title;
    int page;
public:
    Book() {
        cout << "c1" << endl;
    }
    Book(const string& t, int p) {
        title = t;
        page = p;
        cout << "c2" << endl;
    }
    Book(const Book& b) {
        title = b.title;
        page = b.page;
        cout << "c3" << endl;
    }

    string getTitle() { return title; }
    int getPage() { return page; }

    Book publishBook(string t, int p) {
        Book newBook(t, p);
        return newBook;
        // 복사생성자의 묵시적 호출
    }

    void printInfo(Book b) {
        cout << "title : " << b.getTitle() << endl;
        cout << "page : " << b.getPage() << endl;
    }
};

int main() {
    Book book1("aa", 150);
    Book book2(book1);
    Book book3 = book2.publishBook("bb", 100);
    book1.printInfo(book1);
    book1.printInfo(book2);
    book1.printInfo(book3);
}