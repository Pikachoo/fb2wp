#include "main.hpp"

int main()
{
	fb2wp::Settings.Read("config.ini");

	fb2wp::Book.Find("books/");
	fb2wp::Book.Read(fb2wp::Book.GetFileList()[0].c_str());

	fb2wp::Book.SearchPrimaryInfo();
	fb2wp::Book.SearchAuthorsInfo();
	fb2wp::Book.SearchContent();
	fb2wp::Book.SearchImages();

	fb2wp::XML.PrepareHeader();
	fb2wp::XML.PrepareBody();
	fb2wp::XML.PrepareFooter();
	fb2wp::XML.PrepareImages();

	fb2wp::XML.SaveHeader();
	fb2wp::XML.SaveBody();
	fb2wp::XML.SaveFooter();
	fb2wp::XML.SaveImages();


	std::cout << fb2wp::Book.GetBook().genre[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().title[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().name[0] << std::endl;

	std::cout << fb2wp::Book.GetBook().publisher[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().publisherCity[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().publisherYear[0] << std::endl;
	std::cout << fb2wp::Book.GetBook().publisherISBN[0] << std::endl;

	std::cout << fb2wp::Settings.GetSettings().blogURL << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogTitle << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogDescription << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogLanguage << std::endl;
	std::cout << fb2wp::Settings.GetSettings().blogPubDate << std::endl;

	std::cout << fb2wp::Settings.GetSettings().authorNickName << std::endl;
	std::cout << fb2wp::Settings.GetSettings().authorDisplayName << std::endl;
	std::cout << fb2wp::Settings.GetSettings().authorEmail << std::endl;

	std::cout << fb2wp::Settings.GetSettings().generatorVersion << std::endl;

	std::cout << fb2wp::Settings.GetSettings().postStatus << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postType << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postVisibility << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postComments << std::endl;

	std::cout << fb2wp::Settings.GetSettings().postDate << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postDateGMT << std::endl;
	std::cout << fb2wp::Settings.GetSettings().postPubDate << std::endl;

	return 0;
}
