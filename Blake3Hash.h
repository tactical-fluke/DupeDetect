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

#ifndef BLAKE3HASHER_H
#define BLAKE3HASHER_H

#include <string>
#include <filesystem>
#include "BLAKE3/blake3.h"

/**
 * wrapper around a BLAKE3 hash block for easy storage in STL containers
 */
struct Blake3Hash
{
public:
	bool operator<(const Blake3Hash &other) const;

	bool operator<(Blake3Hash &&other) const;

	bool operator==(const Blake3Hash &other) const;

	bool operator!=(const Blake3Hash &other) const;

	uint8_t *getBuffer()
	{
		return &hash[0];
	}

private:
	uint8_t hash[BLAKE3_OUT_LEN];
};

/**
 * provides the BLAKE3 hash of the file with the specified name
 * @param fileName the full filepath of the file to be hashed
 * @return The BLAKE3 hash of the file
 * @throw std::runtime_error if the specified file fails to open
 */
Blake3Hash Blake3_hashFile(const std::filesystem::path& file);

#endif // BLAKE3HASHER_H
