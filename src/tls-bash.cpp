/**
 * @file   tls-bash.cpp
 * @brief  Monster Bash tileset handler
 *
 * This file format is fully documented on the ModdingWiki:
 *   http://www.shikadi.net/moddingwiki/DAT_Format_(Monster_Bash)
 *
 * Copyright (C) 2010-2011 Adam Nielsen <malvineous@shikadi.net>
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

#include <boost/shared_array.hpp>
#include <boost/bind.hpp>

#include <camoto/debug.hpp>
#include <camoto/iostream_helpers.hpp>
#include <camoto/byteorder.hpp>
#include <camoto/substream.hpp>
#include "img-ega-planar.hpp"
#include "tls-bash.hpp"

namespace camoto {
namespace gamegraphics {

namespace io = boost::iostreams;

/// Number of planes in each image
#define MB_NUMPLANES_SPRITE  5
#define MB_NUMPLANES_TILE    4

/// Maximum number of tilesets to load from a tileset collection.
#define MB_SAFETY_MAX_TILESETCOUNT  1024

/// Offset of first tileset in a tileset collection.
#define MB_FIRST_TILESET_OFFSET 0

/// Offset of the first tile within a single tileset.
#define MB_FIRST_TILE_OFFSET    3

/// Width of each image in pixels
#define MB_TILE_WIDTH 16

/// Height of each image in pixels
#define MB_TILE_HEIGHT 16

/// Number of tiles per BG file
#define MB_NUM_TILES_BG 511

/// Number of tiles per FG file
#define MB_NUM_TILES_FG 128

/// Length of each tile in the background file, in bytes
#define MB_TILE_LEN_BG  32 * MB_NUMPLANES_TILE

/// Length of each tile in the foreground file, in bytes
#define MB_TILE_LEN_FG  32 * MB_NUMPLANES_SPRITE

//
// MonsterBashBackgroundTilesetType
//

MonsterBashBackgroundTilesetType::MonsterBashBackgroundTilesetType()
	throw ()
{
}

MonsterBashBackgroundTilesetType::~MonsterBashBackgroundTilesetType()
	throw ()
{
}

std::string MonsterBashBackgroundTilesetType::getCode() const
	throw ()
{
	return "tls-bash-bg";
}

std::string MonsterBashBackgroundTilesetType::getFriendlyName() const
	throw ()
{
	return "Monster Bash Background Tileset";
}

// Get a list of the known file extensions for this format.
std::vector<std::string> MonsterBashBackgroundTilesetType::getFileExtensions() const
	throw ()
{
	std::vector<std::string> vcExtensions;
	return vcExtensions;
}

std::vector<std::string> MonsterBashBackgroundTilesetType::getGameList() const
	throw ()
{
	std::vector<std::string> vcGames;
	vcGames.push_back("Monster Bash");
	return vcGames;
}

MonsterBashBackgroundTilesetType::Certainty MonsterBashBackgroundTilesetType::isInstance(iostream_sptr psGraphics) const
	throw (std::ios::failure)
{
	psGraphics->seekg(0, std::ios::end);
	io::stream_offset len = psGraphics->tellg();
	if (len == MB_NUM_TILES_BG * MB_TILE_LEN_BG) return PossiblyYes;
	// Some tiles are one byte larger for some reason
	if (len == MB_NUM_TILES_BG * MB_TILE_LEN_BG + 1) return PossiblyYes;
	return DefinitelyNo;
}

TilesetPtr MonsterBashBackgroundTilesetType::create(iostream_sptr psGraphics,
	FN_TRUNCATE fnTruncate, SuppData& suppData) const
	throw (std::ios::failure)
{
	char empty[MB_TILE_LEN_BG];
	memset(empty, 0x00, sizeof(empty));
	for (int i = 0; i < MB_NUM_TILES_BG; i++) {
		psGraphics->write(empty, MB_TILE_LEN_BG);
	}
	return TilesetPtr(new MonsterBashTileset(psGraphics, fnTruncate, MB_NUMPLANES_TILE));
}

TilesetPtr MonsterBashBackgroundTilesetType::open(iostream_sptr psGraphics,
	FN_TRUNCATE fnTruncate, SuppData& suppData) const
	throw (std::ios::failure)
{
	return TilesetPtr(new MonsterBashTileset(psGraphics, fnTruncate, MB_NUMPLANES_TILE));
}

SuppFilenames MonsterBashBackgroundTilesetType::getRequiredSupps(const std::string& filenameGraphics) const
	throw ()
{
	// No supplemental types/empty list
	return SuppFilenames();
}


//
// MonsterBashForegroundTilesetType
//

MonsterBashForegroundTilesetType::MonsterBashForegroundTilesetType()
	throw ()
{
}

MonsterBashForegroundTilesetType::~MonsterBashForegroundTilesetType()
	throw ()
{
}

std::string MonsterBashForegroundTilesetType::getCode() const
	throw ()
{
	return "tls-bash-fg";
}

std::string MonsterBashForegroundTilesetType::getFriendlyName() const
	throw ()
{
	return "Monster Bash Foreground Tileset";
}

// Get a list of the known file extensions for this format.
std::vector<std::string> MonsterBashForegroundTilesetType::getFileExtensions() const
	throw ()
{
	std::vector<std::string> vcExtensions;
	return vcExtensions;
}

std::vector<std::string> MonsterBashForegroundTilesetType::getGameList() const
	throw ()
{
	std::vector<std::string> vcGames;
	vcGames.push_back("Monster Bash");
	return vcGames;
}

MonsterBashForegroundTilesetType::Certainty MonsterBashForegroundTilesetType::isInstance(iostream_sptr psGraphics) const
	throw (std::ios::failure)
{
	psGraphics->seekg(0, std::ios::end);
	io::stream_offset len = psGraphics->tellg();
	if (len == MB_NUM_TILES_FG * MB_TILE_LEN_FG) return PossiblyYes;
	// Some tiles are one byte larger for some reason
	if (len == MB_NUM_TILES_FG * MB_TILE_LEN_FG + 1) return PossiblyYes;
	return DefinitelyNo;
}

TilesetPtr MonsterBashForegroundTilesetType::create(iostream_sptr psGraphics,
	FN_TRUNCATE fnTruncate, SuppData& suppData) const
	throw (std::ios::failure)
{
	char empty[MB_TILE_LEN_FG];
	memset(empty, 0x00, sizeof(empty));
	for (int i = 0; i < MB_NUM_TILES_FG; i++) {
		psGraphics->write(empty, MB_TILE_LEN_FG);
	}
	return TilesetPtr(new MonsterBashTileset(psGraphics, fnTruncate, MB_NUMPLANES_SPRITE));
}

TilesetPtr MonsterBashForegroundTilesetType::open(iostream_sptr psGraphics,
	FN_TRUNCATE fnTruncate, SuppData& suppData) const
	throw (std::ios::failure)
{
	return TilesetPtr(new MonsterBashTileset(psGraphics, fnTruncate, MB_NUMPLANES_SPRITE));
}

SuppFilenames MonsterBashForegroundTilesetType::getRequiredSupps(const std::string& filenameGraphics) const
	throw ()
{
	// No supplemental types/empty list
	return SuppFilenames();
}


//
// MonsterBashTileset
//

MonsterBashTileset::MonsterBashTileset(iostream_sptr data, FN_TRUNCATE fnTruncate,
	uint8_t numPlanes)
	throw (std::ios::failure) :
		FATTileset(data, fnTruncate, MB_FIRST_TILE_OFFSET),
		numPlanes(numPlanes)
{
	assert(this->data->good());

	this->data->seekg(0, std::ios::end);
	io::stream_offset len = this->data->tellg();

	this->lenTile = (MB_TILE_WIDTH * MB_TILE_HEIGHT / 8) * numPlanes;
	int numImages = len / this->lenTile;

	this->items.reserve(numImages);
	for (int i = 0; i < numImages; i++) {
		FATEntry *fat = new FATEntry();
		EntryPtr ep(fat);
		fat->isValid = true;
		fat->attr = None;
		fat->index = i;
		fat->offset = i * this->lenTile;
		fat->size = this->lenTile;
		fat->lenHeader = 0;
		this->items.push_back(ep);
	}

}

MonsterBashTileset::~MonsterBashTileset()
	throw ()
{
}

int MonsterBashTileset::getCaps()
	throw ()
{
	return 0;
}

void MonsterBashTileset::resize(EntryPtr& id, size_t newSize)
	throw (std::ios::failure)
{
	if (newSize != this->lenTile) {
		throw std::ios::failure("tiles in this tileset are a fixed size");
	}
	return;
}

void MonsterBashTileset::getTilesetDimensions(unsigned int *width, unsigned int *height)
	throw ()
{
	*width = MB_TILE_WIDTH;
	*height = MB_TILE_HEIGHT;
	return;
}


unsigned int MonsterBashTileset::getLayoutWidth()
	throw ()
{
	return 20;
}

ImagePtr MonsterBashTileset::createImageInstance(const EntryPtr& id,
	iostream_sptr content, FN_TRUNCATE fnTruncate)
	throw (std::ios::failure)
{
	PLANE_LAYOUT planes;
	int offset = (this->numPlanes == MB_NUMPLANES_SPRITE) ? 1 : 0;
	planes[PLANE_BLUE] = 4 + offset;
	planes[PLANE_GREEN] = 3 + offset;
	planes[PLANE_RED] = 2 + offset;
	planes[PLANE_INTENSITY] = 1 + offset;
	planes[PLANE_HITMAP] = 0;
	planes[PLANE_OPACITY] = 0 + offset;

	EGAPlanarImage *ega = new EGAPlanarImage();
	ImagePtr conv(ega);
	ega->setParams(
		content, fnTruncate, 0, MB_TILE_WIDTH, MB_TILE_HEIGHT, planes
	);

	return conv;
}

MonsterBashTileset::FATEntry *MonsterBashTileset::preInsertFile(
	const MonsterBashTileset::FATEntry *idBeforeThis, MonsterBashTileset::FATEntry *pNewEntry)
	throw (std::ios::failure)
{
	// All tiles are a fixed size in this format.
	pNewEntry->size = this->lenTile;

	return pNewEntry;
}

} // namespace gamegraphics
} // namespace camoto