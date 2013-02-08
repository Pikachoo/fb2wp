#include "fb2wp.hpp"

class fb2wp::Book fb2wp::Book;
class fb2wp::Settings fb2wp::Settings;
class fb2wp::XML fb2wp::XML;

void fb2wp::Settings::Read(const char *file_name)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_name, pt);

	__settings.blogURL = pt.get<std::string>("fb2wp.BlogURL");
	__settings.blogTitle = pt.get<std::string>("fb2wp.BlogTitle");
	__settings.blogDescription = pt.get<std::string>("fb2wp.BlogDescription");
	__settings.blogLanguage = pt.get<std::string>("fb2wp.BlogLanguage");
	__settings.blogPubDate = pt.get<std::string>("fb2wp.BlogPubDate");

	__settings.authorNickName = pt.get<std::string>("fb2wp.AuthorNickName");
	__settings.authorDisplayName = pt.get<std::string>("fb2wp.AuthorDisplayName");
	__settings.authorEmail = pt.get<std::string>("fb2wp.AuthorEmail");

	__settings.generatorVersion = pt.get<std::string>("fb2wp.GeneratorVersion");

	__settings.postStatus = pt.get<std::string>("fb2wp.PostStatus");
	__settings.postType = pt.get<std::string>("fb2wp.PostType");
	__settings.postVisibility = pt.get<std::string>("fb2wp.PostVisibility");
	__settings.postComments = pt.get<std::string>("fb2wp.PostComments");
	__settings.postCategoryName = pt.get<std::string>("fb2wp.PostCategoryName");
	__settings.postCategoryNiceName = pt.get<std::string>("fb2wp.PostCategoryNiceName");

	__settings.postDate = pt.get<std::string>("fb2wp.PostDate");
	__settings.postDateGMT = pt.get<std::string>("fb2wp.PostDateGMT");
	__settings.postPubDate = pt.get<std::string>("fb2wp.PostPubDate");
}

void fb2wp::Book::Find(const char *search_dir)
{
	__file_list.clear();

	boost::filesystem::path directory(search_dir);

	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory))
	{
		/* ================= *
		 * Get the file list
		 * ================= */

		std::copy(boost::filesystem::directory_iterator(directory), boost::filesystem::directory_iterator(),
				std::back_inserter(__file_list));
	}

	/* =============== *
	 * Sorting results
	 * =============== */

	std::sort(__file_list.begin(), __file_list.end());
}

void fb2wp::Book::Read(const char *file_name)
{
	__text.clear();

	/* ============= *
	 * Read the file
	 * ============= */

	std::string line;
	std::ifstream myfile;

	myfile.open(file_name);

	while (myfile.good())
	{

		std::getline(myfile, line);
		__text.append(line);
	}

	myfile.close();
}

void fb2wp::Book::SearchPrimaryInfo()
{
	/* ================ *
	 * Get primary info
	 * ================ */

	fb2wp::Book.Search("(?<=<genre>)(.*?)(?=</genre>)", __book.genre);
	fb2wp::Book.Search("(?<=<book-title>)(.*?)(?=</book-title>)", __book.title);
	fb2wp::Book.Search("(?<=<book-name>)(.*?)(?=</book-name>)", __book.name);

	fb2wp::Book.Search("(?<=<publisher>)(.*?)(?=</publisher>)", __book.publisher);
	fb2wp::Book.Search("(?<=<city>)(.*?)(?=</city>)", __book.publisherCity);
	fb2wp::Book.Search("(?<=<year>)(.*?)(?=</year>)", __book.publisherYear);
	fb2wp::Book.Search("(?<=<isbn>)(.*?)(?=</isbn>)", __book.publisherISBN);
}

void fb2wp::Book::SearchAuthorsInfo()
{
	/* =========== *
	 * Get authors
	 * =========== */

	fb2wp::Book.Search("(?<=<first-name>)(.*?)(?=</first-name>)", __book.authorFirstName);
	fb2wp::Book.Search("(?<=<last-name>)(.*?)(?=</last-name>)", __book.authorLastName);
}

void fb2wp::Book::SearchContent()
{
	/* ================================== *
	 * Get tales per each <section> in it
	 * ================================== */

	fb2wp::Book.Search("(?<=<section>)(.*?)(?=</section>)", __book.tales);
	fb2wp::Book.SearchInVector("(?<=<title>)(.*?)(?=</title>)", __book.tales, __book.titles);
}

void fb2wp::Book::Search(const char *pattern, std::vector<std::string> &storage)
{
	/* ========================= *
	 * Regular expression search
	 * ========================= */

	boost::regex regex(pattern, boost::regex::perl);

	for (boost::sregex_token_iterator it(__text.begin(), __text.end(), regex, 0), it_end; it != it_end; ++it)
	{
		storage.push_back(*it);
	}

	std::cout << "[" << storage.size() << "]" << std::endl;
}

void fb2wp::Book::SearchInVector(const char *pattern, std::vector<std::string> &text, std::vector<std::string> &storage)
{
	/* ================================================= *
	 * Regular expression search in the vector of string
	 * ================================================= */

	boost::regex regex(pattern, boost::regex::perl);

	for (std::vector<std::string>::iterator it = text.begin(), it_end = text.end(); it != it_end; ++it)
	{
		std::copy(std::tr1::sregex_token_iterator(it->begin(), it->end(), regex), std::tr1::sregex_token_iterator(),
				std::back_inserter(storage));
	}

	std::cout << "[" << storage.size() << "]" << std::endl;
}

fb2wp::Book::file_vector & fb2wp::Book::GetFileList()
{
	return __file_list;
}

fb2wp::book_T & fb2wp::Book::GetBook()
{
	return __book;
}

fb2wp::settings_T & fb2wp::Settings::GetSettings()
{
	return __settings;
}

fb2wp::file_export_T & fb2wp::XML::GetFileExport()
{
	return __file_export;
}

std::string fb2wp::XML::Read(const char *file_name)
{
	/* ============= *
	 * Read the file
	 * ============= */

	std::string text;
	std::string line;
	std::ifstream myfile;

	myfile.open(file_name);

	while (myfile.good())
	{
		std::getline(myfile, line);
		text.append(line);
		text.append("\n");
	}

	myfile.close();

	return text;
}

void fb2wp::XML::PrepareHeader()
{
	__xml_header = fb2wp::XML.Read("wp/header.xml");

	boost::algorithm::replace_all(__xml_header, "[BLOG TITLE]", fb2wp::Settings.GetSettings().blogTitle);
	boost::algorithm::replace_all(__xml_header, "[BLOG URL]", fb2wp::Settings.GetSettings().blogURL);
	boost::algorithm::replace_all(__xml_header, "[BLOG PUB DATE]", fb2wp::Settings.GetSettings().blogPubDate);
	boost::algorithm::replace_all(__xml_header, "[BLOG LANGUAGE]", fb2wp::Settings.GetSettings().blogLanguage);
	boost::algorithm::replace_all(__xml_header, "[BLOG DESCRIPTION]", fb2wp::Settings.GetSettings().blogDescription);
	boost::algorithm::replace_all(__xml_header, "[AUTHOR NICKNAME]", fb2wp::Settings.GetSettings().authorNickName);
	boost::algorithm::replace_all(__xml_header, "[AUTHOR EMAIL]", fb2wp::Settings.GetSettings().authorEmail);
	boost::algorithm::replace_all(__xml_header, "[AUTHOR DISPLAY NAME]", fb2wp::Settings.GetSettings().authorDisplayName);
	boost::algorithm::replace_all(__xml_header, "[GENERATOR VERSION]", fb2wp::Settings.GetSettings().generatorVersion);
}

void fb2wp::XML::PrepareBody()
{
	__xml_body = fb2wp::XML.Read("wp/body.xml");
}

void fb2wp::XML::PrepareFooter()
{
	__xml_footer = fb2wp::XML.Read("wp/footer.xml");
}

void fb2wp::XML::SaveHeader()
{
	std::ofstream myfile;
	myfile.open("output/out.xml");
	myfile << __xml_header;
	myfile.close();
}

void fb2wp::XML::SaveBody()
{
	std::ofstream myfile;
	myfile.open("output/out.xml", std::ios::app);

	for (uint i = 0; i < fb2wp::Book.GetBook().tales.size(); i++)
	{
		std::string tmp = __xml_body;
		std::string post_id = boost::lexical_cast<std::string>(i + 1);
		std::string post_name = fb2wp::XML.CyrToLat(fb2wp::Book.GetBook().titles[i]);
		std::string post_title = fb2wp::XML.StringCleaner(fb2wp::Book.GetBook().titles[i]);

		boost::algorithm::replace_all(tmp, "[POST TITLE]", post_title);
		boost::algorithm::replace_all(tmp, "[BLOG URL]", fb2wp::Settings.GetSettings().blogURL);
		boost::algorithm::replace_all(tmp, "[POST PUB DATE]", fb2wp::Settings.GetSettings().postPubDate);
		boost::algorithm::replace_all(tmp, "[POST AUTHOR]", fb2wp::Settings.GetSettings().authorNickName);
		boost::algorithm::replace_all(tmp, "[POST ID]", post_id);
		boost::algorithm::replace_all(tmp, "[POST CONTENT]", fb2wp::Book.GetBook().tales[i]);
		boost::algorithm::replace_all(tmp, "[POST DATE]", fb2wp::Settings.GetSettings().postDate);
		boost::algorithm::replace_all(tmp, "[POST DATE GMT]", fb2wp::Settings.GetSettings().postDateGMT);
		boost::algorithm::replace_all(tmp, "[POST COMMENTS]", fb2wp::Settings.GetSettings().postComments);
		boost::algorithm::replace_all(tmp, "[POST STATUS]", fb2wp::Settings.GetSettings().postStatus);
		boost::algorithm::replace_all(tmp, "[POST NAME]", post_name);
		boost::algorithm::replace_all(tmp, "[POST VISIBILITY]", fb2wp::Settings.GetSettings().postVisibility);
		boost::algorithm::replace_all(tmp, "[POST TYPE]", fb2wp::Settings.GetSettings().postType);
		boost::algorithm::replace_all(tmp, "[POST CATEGORY NICENAME]", fb2wp::Settings.GetSettings().postCategoryNiceName);
		boost::algorithm::replace_all(tmp, "[POST CATEGORY NAME]", fb2wp::Settings.GetSettings().postCategoryName);

		myfile << tmp;
	}

	myfile.close();
}

void fb2wp::XML::SaveFooter()
{
	std::ofstream myfile;
	myfile.open("output/out.xml", std::ios::app);
	myfile << __xml_footer;
	myfile.close();
}

std::string fb2wp::XML::CyrToLat(std::string &text)
{
	std::string tmp = StringCleaner(text);
	std::string cyr[] = { "А", "а", "Б", "б", "В", "в", "Г", "г", "Д", "д", "Е", "е", "Ё", "ё", "Ж", "ж", "З", "з", "И", "и", "Й",
			"й", "К", "к", "Л", "л", "М", "м", "Н", "н", "О", "о", "П", "п", "Р", "р", "С", "с", "Т", "т", "У", "у", "Ф", "ф",
			"Х", "х", "Ц", "ц", "Ч", "ч", "Ш", "ш", "Щ", "щ", "Ъ", "ъ", "Ы", "ы", "Ь", "ь", "Э", "э", "Ю", "ю", "Я", "я", " "};
	std::string lat[] =
			{ "A", "a", "B", "b", "V", "v", "G", "g", "D", "d", "E", "e", "E", "e", "J", "j", "Z", "z", "I", "i", "I", "i", "K",
					"k", "L", "l", "M", "m", "N", "n", "O", "o", "P", "p", "R", "r", "S", "s", "T", "t", "Y", "y", "F", "f", "H",
					"h", "C", "c", "Ch", "ch", "Sh", "sh", "Sch", "Sch", "J", "j", "i", "i", "", "", "E", "e", "Yu", "yu", "Ya",
					"ya", "-"};

	for (uint i = 0; i < 67; i++)
	{
		boost::algorithm::replace_all(tmp, cyr[i], lat[i]);
	}

	return tmp;
}

std::string fb2wp::XML::StringCleaner(std::string &text)
{
	std::string tmp = text;

	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.end());
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\r'), tmp.end());
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end());

	/* =============== *
	 * Erase HTML tags
	 * =============== */

	bool inflag = false;
	bool done = false;
	size_t i, j;
	while (!done)
	{
		if (inflag)
		{
			i = tmp.find('>');
			if (i != std::string::npos)
			{
				inflag = false;
				tmp.erase(0, i + 1);
			}
			else
			{
				done = true;
				tmp.erase();
			}
		}
		else
		{
			i = tmp.find('<');
			if (i != std::string::npos)
			{
				j = tmp.find('>');
				if (j == std::string::npos)
				{
					inflag = true;
					done = true;
					tmp.erase(i);
				}
				else
				{
					tmp.erase(i, j - i + 1);
				}
			}
			else
			{
				done = true;
			}
		}
	}

	return tmp;
}
