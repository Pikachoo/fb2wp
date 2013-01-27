#include "main.hpp"

int main()
{
	fb2wp::books.find_in("books/");
	fb2wp::books.parse();

	fb2wp::book_skel mybook;


	/* ===================== *
	 * Get book primary info
	 * ===================== */

	fb2wp::books.regex_search("(?<=<genre>)(.*)(?=</genre>)", mybook.genre);
	fb2wp::books.regex_search("(?<=<book-name>)(.*)(?=</book-name>)", mybook.book_name);
	fb2wp::books.regex_search("(?<=<book-title>)(.*)(?=</book-title>)", mybook.book_title);
	fb2wp::books.regex_search("(?<=<publisher>)(.*)(?=</publisher>)", mybook.publisher);
	fb2wp::books.regex_search("(?<=<city>)(.*)(?=</city>)", mybook.city);
	fb2wp::books.regex_search("(?<=<year>)(.*)(?=</year>)", mybook.year);
	fb2wp::books.regex_search("(?<=<isbn>)(.*)(?=</isbn>)", mybook.isbn);

	/* ================ *
	 * Get book authors
	 * ================ */

	fb2wp::books.regex_search("(?<=<first-name>)(.*)(?=</first-name>)", mybook.first_name);
	fb2wp::books.regex_search("(?<=<last-name>)(.*)(?=</last-name>)", mybook.last_name);

	/* ======================================= *
	 * Get book tales per each <section> in it
	 * ======================================= */

	fb2wp::books.regex_search("(?<=<section>)(.*)(?=</section>)", mybook.tales);

	std::cout << mybook.genre[0] << std::endl;
	std::cout << mybook.book_name[0] << std::endl;
	std::cout << mybook.book_title[0] << std::endl;
	std::cout << mybook.publisher[0] << std::endl;
	std::cout << mybook.city[0] << std::endl;
	std::cout << mybook.year[0] << std::endl;
	std::cout << mybook.isbn[0] << std::endl;

	return 0;
}
