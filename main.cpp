#include "main.hpp"

int main()
{
	fb2wp::Books books;
    books.find_in("books/");
	books.parse();


	fb2wp::book_skel book;


	/* ===================== *
	 * Get book primary info
	 * ===================== */

	books.regex_search("<genre>(.*?)</genre>", book.genre);
	books.regex_search("<book-name>(.*?)</book-name>", book.book_name);
	books.regex_search("<book-title>(.*?)</book-title>", book.book_title);
	books.regex_search("<publisher>(.*?)</publisher", book.publisher);
	books.regex_search("<city>(.*?)</city>", book.city);
	books.regex_search("<year>(.*?)</year>", book.year);
	books.regex_search("<isbn>(.*?)</isbn>", book.isbn);


	/* ================ *
	 * Get book authors
	 * ================ */

	books.regex_search("<first-name>(.*?)</first-name>", book.first_name);
	books.regex_search("<last-name>(.*?)</last-name>", book.last_name);


	/* ======================================= *
	 * Get book tales per each <section> in it
	 * ======================================= */

	books.regex_search("<section>(.*?)</section>", book.isbn);

	std::cout << book.genre[0] << std::endl;
	std::cout << book.book_name[0] << std::endl;
	std::cout << book.book_title[0] << std::endl;
	std::cout << book.publisher[0] << std::endl;
	std::cout << book.city[0] << std::endl;
	std::cout << book.year[0] << std::endl;
	std::cout << book.isbn[0] << std::endl;

	return 0;
}
