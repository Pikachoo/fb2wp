#include "fb2wp.hpp"

class fb2wp::books fb2wp::books;

void fb2wp::books::find_in(const char *search_dir)
{
	file_list.clear();

	boost::filesystem::path directory(search_dir);

	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory))
	{
		/* ================= *
		 * Getting file list
		 * ================= */

		std::copy(boost::filesystem::directory_iterator(directory),
				boost::filesystem::directory_iterator(), std::back_inserter(file_list));
	}

	/* =============== *
	 * Sorting results
	 * =============== */

	sort(file_list.begin(), file_list.end());
}

void fb2wp::books::load_in_memory(const char *file_path)
{
	text.clear();

	/* ============= *
	 * Read the file
	 * ============= */

	std::ifstream myfile;

	myfile.open(file_path);

	while (myfile.good())
	{
		std::string line;
		std::getline(myfile, line);
		text.append(line);
	}

	myfile.close();
}

void fb2wp::books::regex_search(const char *pattern, std::vector<std::string> &storage)
{
	/* ========================= *
	 * Regular expression search
	 * ========================= */

	boost::regex regex(pattern, boost::regex::perl);

	for (boost::sregex_token_iterator it(text.begin(), text.end(), regex, 0), it_end; it != it_end; ++it)
	{
		storage.push_back(*it);
	}
}
