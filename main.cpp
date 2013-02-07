#include "main.hpp"

int main()
{
	fb2wp::Settings.Read("config.ini");

	fb2wp::Book.Find("books/");
	fb2wp::Book.Read(fb2wp::Book.GetFileList()[0].c_str());

	fb2wp::Book.SearchPrimaryInfo();
	fb2wp::Book.SearchAuthorsInfo();
	fb2wp::Book.SearchContent();



	std::cout << fb2wp::Book.GetBook().genre[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().book_name[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().book_title[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().publisher[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().city[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().year[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().isbn[0] << std::endl;

	std::cout << fb2wp::Settings.GetSettings().blogURL << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogTitle << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogDescription << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogLanguage << std::endl;

	std::cout << fb2wp::Settings.GetSettings().postAuthor << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postStatus << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postType << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postVisibility << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postComments << std::endl;

	std::cout << fb2wp::Settings.GetSettings().postDate << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postDateGMT << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postPubDate << std::endl;


	return 0;
}
