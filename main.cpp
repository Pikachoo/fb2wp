#include "main.hpp"

int main()
{
	fb2wp::books.find_in("books/");
	fb2wp::books.load_in_memory(fb2wp::books.get_file_list()[0].c_str());

	fb2wp::books.get_primary_info();
	fb2wp::books.get_authors_info();
	fb2wp::books.get_the_content();




	std::cout << fb2wp::books.get_skel().genre[0] << std::endl;
	std::cout << fb2wp::books.get_skel().book_name[0] << std::endl;
	std::cout << fb2wp::books.get_skel().book_title[0] << std::endl;
	std::cout << fb2wp::books.get_skel().publisher[0] << std::endl;
	std::cout << fb2wp::books.get_skel().city[0] << std::endl;
	std::cout << fb2wp::books.get_skel().year[0] << std::endl;
	std::cout << fb2wp::books.get_skel().isbn[0] << std::endl;

	return 0;
}
