/*
 * 	DupeDetect: small terminal application to find duplicate files
 *  Copyright (C) 2021  Aidan Haile
 *
 *	This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

#include "RecursiveDuplicateFinder.h"
#include "DepthLimitedDuplicateFinder.h"
#include "Options.h"
#include "StringUtils.h"

std::vector<option> optionsList{
		{'v',          "verbose", false},
		{std::nullopt, "help",    false},
		{'d',          "depth",   true},
		{'l',          "license", false},
		{'s',          "minsize", true},
		{'S',          "maxsize", true}
};

void printUsage()
{
	std::cout << "usage: DupeDetect [OPTIONS...] [DIRECTORY]\n";
	std::cout << "Compiles a list of duplicate files by recursively searching in a given directory\n";
	std::cout << "OPTIONS -\n";
	std::cout << "\t-v, --verbose\tPrint each filename as it is checked\n";
	std::cout << "\t--help\t\tPrints this message\n";
	std::cout << "\t-d, --depth\tDefines the maximum depth to search to\n";
	std::cout << "\t-l, --license\tPrints out the license information for this program\n";
	std::cout << "\t-s, --minsize\tSets the minimum size for files to be checked. Size information below\n";
	std::cout << "\t-S, --maxsize\tSets the maximum size for files to be checked. Size information below\n";

	std::cout << "\n\n";

	std::cout << "\t\tSIZE INFO\n";
	std::cout << "\tSizes are specified via an amount and a suffix, i.e 1Mb (1 megabyte).\n";
	std::cout << "\tThe supported suffixes are as follows:\n";
	std::cout << "\t\tb - byte\n";
	std::cout << "\t\tkb - kibibyte (1024 bytes)\n";
	std::cout << "\t\tKb - kilobyte (1000 bytes)\n";
	std::cout << "\t\tmb - mebibyte (1024 kibibytes)\n";
	std::cout << "\t\tMb - megabyte (1000 kilobytes)\n";
	std::cout << "\t\tgb - gibibyte (1024 mebibytes)\n";
	std::cout << "\t\tGb - gigabyte (1024 megabytes)\n";
}

void printLicense()
{
	std::cout << "\tDupeDetect  Copyright (C) 2021  Aidan Haile\n"
				 "\tThis program comes with ABSOLUTELY NO WARRANTY\n"
				 "\tThis is free software, and you are welcome to redistribute it under certain conditions\n";
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printUsage();
		return EXIT_FAILURE;
	}

	Options::setOptions(optionsList);

	try
	{
		Options::parseArgs(argc - 1, argv + 1);
	}
	catch (const std::runtime_error &e)
	{
		std::cout << e.what();
		printUsage();
		return EXIT_FAILURE;
	}

	if (Options::getOpt<bool>("help"))
	{
		printUsage();
		return EXIT_SUCCESS;
	}
	else if (Options::optionFound("license"))
	{
		printLicense();
		return EXIT_SUCCESS;
	}

	std::string directory(argv[argc - 1]);
	std::string cwd = std::filesystem::current_path().generic_string();

	if (std::filesystem::exists(cwd + directory))
	{
		directory = cwd + directory;
	}

	if (!std::filesystem::exists(directory))
	{
		std::cout << "The specified directory \"" << directory << "\" does not exist\n\n";
		printUsage();
		return EXIT_FAILURE;
	}

	std::unique_ptr<DupeDetect::DuplicateFinder> duplicateFinder;
	decltype(duplicateFinder->findDuplicates()) duplicates;

	try
	{
		if (Options::optionFound("depth"))
		{
			duplicateFinder = std::make_unique<DupeDetect::DepthLimitedDuplicateFinder>(directory,
																						Options::getOpt<int>("depth"));
		}
		else
		{
			duplicateFinder = std::make_unique<DupeDetect::RecursiveDuplicateFinder>(directory);
		}

		duplicates = duplicateFinder->findDuplicates();
	}
	catch(const std::runtime_error& e)
	{
		std::cout << "error occurred: " << e.what() << "\n";
		return EXIT_FAILURE;
	}

	for (const auto &duplicateList : duplicates)
	{
		for (const auto &duplicate : duplicateList)
		{
			std::cout << duplicate.generic_string() << ", ";
		}
		std::cout << "\n";
	}
	return EXIT_SUCCESS;
}
