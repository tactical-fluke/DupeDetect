#ifndef DUPEDETECT_OPTIONS_H
#define DUPEDETECT_OPTIONS_H

#include <string>
#include <vector>
#include <optional>

/**
 * struct describing the form an option can take
 */
struct option
{
	/**
	 * the brief option character. can be in a string prepended by a single '-'
	 */
	std::optional<char> briefOpt;

	/**
	 * the long option string. Must appear solo prepended by a "--"
	 */
	std::optional<std::string> longOpt;

	/**
	 * whether this option has an accompanying value argument
	 */
	bool argument = false;
};

/**
 * struct representing the status an option can have
 */
struct option_status
{
	/**
	 * whether this option was found or not
	 */
	bool found;

	/**
	 * the string value that was supplied for this option on in the program arguments list
	 */
	std::string value;
};

/**
 * Class encapsulating the options that can be supplied to the program
 */
class Options
{
public:

	/**
	 * Parses the arguments that have been supplied
	 * @param argc the number of arguments
	 * @param argv the argument strings that have been supplied
	 */
	static void parseArgs(int argc, char **argv);

	/**
	 * set the possible options for this program
	 * @param optionList the list of all possible options that are valid for this program
	 */
	static void setOptions(const std::vector<option> &optionList);

	/**
	 * whether this option specified by the long option name has been found
	 * @param optionName the long option string for the option
	 * @return true if the option was found in the arguments supplied, false otherwise
	 */
	static bool optionFound(const std::string &optionName);

	/**
	 * retrieves the value for the specified option
	 * @tparam T The type that the option represents
	 * @param optionName the long option name
	 * @return the T value for the option requested
	 * @throw std::logic_error if the option does not exist
	 */
	template<typename T>
	static T getOpt(const std::string &optionName);

	/**
	 * retrieves the value for the specified option
	 * @tparam T The type that the option represents
	 * @param optionChar the brief option character
	 * @return the T value for the option requested
	 * @throw std::logic_error if the option does not exist
	 */
	template<typename T>
	static T getOpt(char optionChar);

private:

	using optionPair = std::pair<option, option_status>;

	/**
	 * parses a string of brief options, those prepended by a '-'. Can contain multiple different brief options
	 * @param optString the string of brief options provided
	 * @param remainingArgs pointer to the current position in the arguments list. May be modified
	 * @param endArgs pointer to the final position in the arguments list. Will never be modified
	 * @throw std::runtime_error if one of the options specified does not exist
	 */
	static void parseBriefOptString(const std::string &optString, char **remainingArgs, char **endArgs);

	/**
	 * parses a long option string, those prepended by a '--'. Can contain only a single long option
	 * @param optString the long option to be parsed
	 * @param remainingArgs pointer to the current position in the arguments list. May be modified
	 * @param endArgs pointer to the final position in the arguments list. Will never be modified
	 * @throw std::runtime_error if the option does not exist
	 */
	static void parseLongOptString(const std::string &optString, char **remainingArgs, char **endArgs);

	/**
	 * finds an option by the brief option character
	 * @param briefOpt the brief option character to search by
	 * @return an iterator to a position in options. Returns options.end() if the option does not exist
	 */
	static inline decltype(std::declval<std::vector<optionPair>>().begin()) findOptionByBriefOpt(char briefOpt);

	/**
	 * finds an option by the long option string
	 * @param briefOpt the long option string to search by
	 * @return an iterator to a position in options. Returns options.end() if the option does not exist
	 */
	static inline decltype(std::declval<std::vector<optionPair>>().begin())
	findOptionByLongOpt(const std::string &longOpt);

	/**
	 * list of all possible options and their status
	 */
	static std::vector<optionPair> options;
};

#endif //DUPEDETECT_OPTIONS_H
