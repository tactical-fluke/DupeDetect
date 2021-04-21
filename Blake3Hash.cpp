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

#include "Blake3Hash.h"
#include "Options.h"

#include <algorithm>
#include <iostream>
#include <fstream>

bool Blake3Hash::operator<(Blake3Hash &&other) const
{
	for (int i = BLAKE3_OUT_LEN - 1; i >= 0; i--)
	{
		if (hash[i] < other.hash[i])
			return true;
		if (hash[i] > other.hash[i])
			return false;
	}
	return false;
}

bool Blake3Hash::operator<(const Blake3Hash &other) const
{
	for (int i = BLAKE3_OUT_LEN - 1; i >= 0; i--)
	{
		if (hash[i] < other.hash[i])
			return true;
		if (hash[i] > other.hash[i])
			return false;
	}
	return false;
}

bool Blake3Hash::operator==(const Blake3Hash &other) const
{
	return std::equal(&hash[0], &hash[0] + BLAKE3_OUT_LEN, &other.hash[0]);
}

bool Blake3Hash::operator!=(const Blake3Hash &other) const
{
	return !(*this == other);
}

Blake3Hash Blake3_hashFile(const std::filesystem::path& file)
{
	if(Options::getOpt<bool>("verbose"))
	{
		std::cout << "parsing file \"" << file.generic_string() << "\"\n";
	}

	// Initialize the hasher.
	blake3_hasher hasher;
	blake3_hasher_init(&hasher);

	unsigned char buf[65536]{};

	std::ifstream fileReader(file);

	if (fileReader.fail())
	{
		throw std::runtime_error("Failed to open fileReader\"" + file.generic_string() + "\".");
	}

	while (!fileReader.eof())
	{
		fileReader.read(reinterpret_cast<char *>(&buf), sizeof(buf));
		blake3_hasher_update(&hasher, buf, fileReader.gcount());
	}

	Blake3Hash hash{};
	blake3_hasher_finalize(&hasher, hash.getBuffer(), BLAKE3_OUT_LEN);

	return hash;
}
