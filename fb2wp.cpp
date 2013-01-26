#include "fb2wp.hpp"

fb2wp::books fb2wp::books;

void fb2wp::books::find_in(const char *search_dir)
{
	v.clear();

	boost::filesystem::path directory(search_dir);

	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory))
	{

		/* ================= *
		 * Getting file list
		 * ================= */

		for (boost::filesystem::directory_iterator begin(directory), end; begin != end; ++begin)
		{
			v.push_back(*begin);
		}
	}

	/* =============== *
	 * Sorting results
	 * =============== */

	sort(v.begin(), v.end());
}

void fb2wp::books::parse()
{
	text.clear();

	std::ifstream myfile;
	std::vector<boost::filesystem::path>::iterator it;
	std::vector<boost::filesystem::path>::iterator it_end;

	for (it = fb2wp::books.v.begin(), it_end = fb2wp::books.v.end(); it != it_end; ++it)
	{
		/* ============ *
		 * Reading file
		 * ============ */

		myfile.open(it->c_str());

		std::string line;

		while (myfile.good())
		{
			std::getline(myfile, line);
			text.append(line);
		}
		text.push_back('\0');

		myfile.close();
	}
}

void fb2wp::books::regex_search(const char *pattern, std::vector<std::string> &storage)
{
	/* ========================= *
	 * Regular expression search
	 * ========================= */

	boost::smatch m;
	boost::regex reg(pattern);

	if (boost::regex_search(text, m, reg))
	{
		std::cout << "[" << m.size() - 1 << "]: ";

		for (int i = 1; i < m.size(); i++)
		{
			storage.push_back(m[i]);
			std::cout << m[i] << std::endl;
		}
	}
}
