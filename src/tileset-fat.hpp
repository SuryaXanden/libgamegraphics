/**
 * @file  tileset-fat.hpp
 * @brief Generic FAT-based tileset handler.
 *
 * Copyright (C) 2010-2015 Adam Nielsen <malvineous@shikadi.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CAMOTO_TILESET_FAT_HPP_
#define _CAMOTO_TILESET_FAT_HPP_

#include <camoto/config.hpp>
#include <camoto/gamearchive/archive-fat.hpp>
#include <camoto/gamegraphics/tileset.hpp>

namespace camoto {
namespace gamegraphics {

/// Tileset implementation for tilesets with an associated size/offset table.
class CAMOTO_GAMEGRAPHICS_API Tileset_FAT:
	public gamearchive::Archive_FAT,
	public Tileset
{
	public:
		Tileset_FAT(std::unique_ptr<stream::inout> content, stream::pos offFirstTile,
			int lenMaxName);
		virtual ~Tileset_FAT();

		// Archive
		virtual std::shared_ptr<gamearchive::Archive> openFolder(const FileHandle& id);

		// Functions to be filled out by descendent classes
		virtual std::unique_ptr<Image> openImage(const FileHandle& id);
		virtual std::shared_ptr<Tileset> openTileset(const FileHandle& id);

	protected:
		Tileset_FAT(); // for Tileset_FAT_FixedTileSize
};

} // namespace gamegraphics
} // namespace camoto

#endif // _CAMOTO_TILESET_FAT_HPP_
