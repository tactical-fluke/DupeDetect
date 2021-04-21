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

#include "Options.h"
#include "StringUtils.h"

#include <algorithm>

std::vector<std::pair<option, option_status>> Options::options = std::vector<std::pair<option, option_status>>();

void Options::parseArgs(int argc, char **argv)
{
	char **iter = argv;
	char **end = argv + argc;
	for (; iter < end; iter++)
	{
		std::string optString(*iter);

		if (StringUtils::startsWith(optString, "--"))
		{
			parseLongOptString(optString.substr(2), iter, end);
		}
		else if (StringUtils::startsWith(optString, "-"))
		{
			parseBriefOptString(optString.substr(1), iter, end);
		}
	}
}

void Options::setOptions(const std::vector<option> &optionList)
{
	for (const auto &opt : optionList)
	{
		options.emplace_back(opt, option_status{false, ""});
	}
}

void Options::parseBriefOptString(const std::string &optString, char **remainingArgs, char **endArgs)
{
	for (const auto &optChar : optString)
	{
		auto option = findOptionByBriefOpt(optChar);

		if (option == options.end())
		{
			std::string errorString = "No known option: ";
			errorString.append(&optChar, 1);
			throw std::runtime_error(errorString);
		}

		auto&[opt, optStatus] = *option;

		optStatus.found = true;
		if (opt.argument)
		{
			if (remainingArgs + 1 >= endArgs)
			{
				std::string error = "Not enough arguments supplied for given option: ";
				error.append(&optChar, 1);
				throw std::runtime_error(error);
			}
			optStatus.value = *(++remainingArgs);
		}
	}
}

void Options::parseLongOptString(const std::string &optString, char **remainingArgs, char **endArgs)
{
	auto option = findOptionByLongOpt(optString);

	if (option == options.end())
	{
		throw std::runtime_error("No known option: " + optString);
	}

	auto&[opt, optStatus] = *option;

	optStatus.found = true;
	if (opt.argument)
	{
		if (remainingArgs + 1 >= endArgs)
		{
			throw std::runtime_error("Not enough arguments supplied for option: " + optString);
		}
		optStatus.value = *(++remainingArgs);
	}
}

inline auto Options::findOptionByBriefOpt(char briefOpt) -> decltype(std::declval<std::vector<optionPair>>().begin())
{
	return std::find_if(options.begin(), options.end(), [briefOpt](const auto &option)
	{
		return option.first.briefOpt == briefOpt;
	});
}

inline auto
Options::findOptionByLongOpt(const std::string &longOpt) -> decltype(std::declval<std::vector<optionPair>>().begin())
{
	return std::find_if(options.begin(), options.end(), [&longOpt](const auto &option)
	{
		return option.first.longOpt == longOpt;
	});
}

template<>
auto Options::getOpt<bool>(char optionChar) -> bool
{
	auto opt = findOptionByBriefOpt(optionChar);

	if (opt == options.end())
	{
		std::string error = "No such option: ";
		error.append(&optionChar, 1);
		throw std::logic_error(error);
	}

	return opt->second.found;
}

template<>
auto Options::getOpt<bool>(const std::string &optionName) -> bool
{
	auto opt = findOptionByLongOpt(optionName);

	if (opt == options.end())
	{
		throw std::logic_error("no such option: " + optionName);
	}

	return opt->second.found;
}

bool Options::optionFound(const std::string &optionName)
{
	return getOpt<bool>(optionName);
}

template<>
auto Options::getOpt<std::string>(char optionChar) -> std::string
{
	auto opt = findOptionByBriefOpt(optionChar);

	if (opt == options.end())
	{
		std::string error = "No such option: ";
		error.append(&optionChar, 1);
		throw std::logic_error(error);
	}

	return opt->second.value;
}

template<>
auto Options::getOpt<std::string>(const std::string &optionName) -> std::string
{
	auto opt = findOptionByLongOpt(optionName);

	if (opt == options.end())
	{
		throw std::logic_error("No such option: " + optionName);
	}

	return opt->second.value;
}

template<>
auto Options::getOpt<int>(char optionChar) -> int
{
	auto opt = findOptionByBriefOpt(optionChar);

	if (opt == options.end())
	{
		std::string error = "No such option: ";
		error.append(&optionChar, 1);
		throw std::logic_error(error);
	}

	return std::stoi(opt->second.value);
}

template<>
auto Options::getOpt<int>(const std::string &optionName) -> int
{
	auto opt = findOptionByLongOpt(optionName);

	if (opt == options.end())
	{
		throw std::logic_error("No such option: " + optionName);
	}

	return std::stoi(opt->second.value);
}