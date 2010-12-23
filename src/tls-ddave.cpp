/**
 * @file   tls-ddave.cpp
 * @brief  Dangerous Dave tileset handler.
 *
 * This file format is fully documented on the ModdingWiki:
 *   http://www.shikadi.net/moddingwiki/Zone_66_Tileset_Format
 *
 * Copyright (C) 2010 Adam Nielsen <malvineous@shikadi.net>
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

#include <boost/bind.hpp>
#include <camoto/iostream_helpers.hpp>

#include "img-ega-rowplanar.hpp"
#include "tls-ddave.hpp"
#include "img-ddave.hpp"
#include "pal-vga-raw.hpp"

/// Offset of the number of tilesets
#define DD_TILECOUNT_OFFSET    0

/// Offset where the FAT starts
#define DD_FAT_OFFSET          4

/// Length of each entry in the FAT (a uint32 offset)
#define DD_FAT_ENTRY_LEN       4

/// Offset of first tile in an empty tileset
#define DD_FIRST_TILE_OFFSET   4

/// Maximum tiles to load in case of a corrupted file
#define DD_SAFETY_MAX_TILES    4096

/// First tile with width and height fields
#define DD_FIRST_TILE_WITH_DIMS  53

namespace camoto {
namespace gamegraphics {

namespace io = boost::iostreams;

DDaveTilesetType::DDaveTilesetType()
	throw ()
{
}

DDaveTilesetType::~DDaveTilesetType()
	throw ()
{
}

std::vector<std::string> DDaveTilesetType::getFileExtensions() const
	throw ()
{
	std::vector<std::string> vcExtensions;
	vcExtensions.push_back("dav");
	return vcExtensions;
}

std::vector<std::string> DDaveTilesetType::getGameList() const
	throw ()
{
	std::vector<std::string> vcGames;
	vcGames.push_back("Dangerous Dave");
	return vcGames;
}

DDaveTilesetType::Certainty DDaveTilesetType::isInstance(
	iostream_sptr psTileset) const
	throw (std::ios::failure)
{
	psTileset->seekg(0, std::ios::end);
	io::stream_offset len = psTileset->tellg();
	// TESTED BY: TODO
	if (len < DD_FIRST_TILE_OFFSET) return DefinitelyNo; // too short

	psTileset->seekg(0, std::ios::beg);
	uint32_t numFiles;
	psTileset >> u32le(numFiles);

	if ((numFiles == 0) && (len > DD_FIRST_TILE_OFFSET)) return DefinitelyNo; // invalid empty file

	uint32_t offset, lastOffset = 0;
	uint32_t firstOffset, secondOffset;
	for (int i = 0; i < numFiles; i++) {
		psTileset >> u32le(offset);
		if (i == 0) firstOffset = offset;
		else if (i == 1) secondOffset = offset;

		// Make sure the offsets are increasing, otherwise we'd get a negative
		// file size (or the file has been tweaked to make opening difficult, but
		// then there's the -f option to gamegfx for that.)
		// TESTED BY: TODO
		if (offset < lastOffset) return DefinitelyNo;

		// Make sure the tile is contained within the file
		// TESTED BY: TODO
		if (offset > len) return DefinitelyNo;

		lastOffset = offset;
	}

	// Check the size of the first tile to see what format it's in.
	if (numFiles > 0) {
		if (numFiles == 1) {
			// have to use EOF as second file's offset
			secondOffset = len;
		}
		// Call function in DDave[CEV]GATilesetType
		if (!this->isInstance(secondOffset - firstOffset)) return DefinitelyNo;
	}

	// TESTED BY: tls_ddave_isinstance_c00
	return DefinitelyYes;
}

MP_SUPPLIST DDaveTilesetType::getRequiredSupps(
	const std::string& filenameTileset) const
	throw ()
{
	MP_SUPPLIST supps;
	return supps;
}


std::string DDaveCGATilesetType::getCode() const
	throw ()
{
	return "tls-ddave-cga";
}

std::string DDaveCGATilesetType::getFriendlyName() const
	throw ()
{
	return "Dangerous Dave CGA tileset";
}

TilesetPtr DDaveCGATilesetType::create(iostream_sptr psTileset,
	FN_TRUNCATE fnTruncate, MP_SUPPDATA& suppData) const
	throw (std::ios::failure)
{
	fnTruncate(4);
	psTileset->seekp(0, std::ios::beg);
	psTileset << u32le(0);

	PaletteTablePtr pal = CGAImage::generatePalette(CGAImage::CyanMagentaBright);
	return TilesetPtr(new DDaveTileset(psTileset, fnTruncate, DDaveTileset::CGA, pal));
}

TilesetPtr DDaveCGATilesetType::open(iostream_sptr psTileset,
	FN_TRUNCATE fnTruncate, MP_SUPPDATA& suppData) const
	throw (std::ios::failure)
{
	PaletteTablePtr pal = CGAImage::generatePalette(CGAImage::CyanMagentaBright);
	return TilesetPtr(new DDaveTileset(psTileset, fnTruncate, DDaveTileset::CGA, pal));
}

bool DDaveCGATilesetType::isInstance(int firstTileSize) const
	throw ()
{
	return (firstTileSize == 64);
}


std::string DDaveEGATilesetType::getCode() const
	throw ()
{
	return "tls-ddave-ega";
}

std::string DDaveEGATilesetType::getFriendlyName() const
	throw ()
{
	return "Dangerous Dave EGA tileset";
}

TilesetPtr DDaveEGATilesetType::create(iostream_sptr psTileset,
	FN_TRUNCATE fnTruncate, MP_SUPPDATA& suppData) const
	throw (std::ios::failure)
{
	fnTruncate(4);
	psTileset->seekp(0, std::ios::beg);
	psTileset << u32le(0);

	return TilesetPtr(new DDaveTileset(psTileset, fnTruncate, DDaveTileset::EGA, PaletteTablePtr()));
}

TilesetPtr DDaveEGATilesetType::open(iostream_sptr psTileset,
	FN_TRUNCATE fnTruncate, MP_SUPPDATA& suppData) const
	throw (std::ios::failure)
{
	return TilesetPtr(new DDaveTileset(psTileset, fnTruncate, DDaveTileset::EGA, PaletteTablePtr()));
}

bool DDaveEGATilesetType::isInstance(int firstTileSize) const
	throw ()
{
	return (firstTileSize == 128);
}


std::string DDaveVGATilesetType::getCode() const
	throw ()
{
	return "tls-ddave-vga";
}

std::string DDaveVGATilesetType::getFriendlyName() const
	throw ()
{
	return "Dangerous Dave VGA tileset";
}

TilesetPtr DDaveVGATilesetType::create(iostream_sptr psTileset,
	FN_TRUNCATE fnTruncate, MP_SUPPDATA& suppData) const
	throw (std::ios::failure)
{
	fnTruncate(4);
	psTileset->seekp(0, std::ios::beg);
	psTileset << u32le(0);

	ImagePtr palFile(new VGAPalette(
		suppData[SuppItem::Palette].stream,
		suppData[SuppItem::Palette].fnTruncate
	));
	PaletteTablePtr pal = palFile->getPalette();

	return TilesetPtr(new DDaveTileset(psTileset, fnTruncate, DDaveTileset::VGA, pal));
}

TilesetPtr DDaveVGATilesetType::open(iostream_sptr psTileset,
	FN_TRUNCATE fnTruncate, MP_SUPPDATA& suppData) const
	throw (std::ios::failure)
{
	ImagePtr palFile(new VGAPalette(
		suppData[SuppItem::Palette].stream,
		suppData[SuppItem::Palette].fnTruncate
	));
	PaletteTablePtr pal = palFile->getPalette();

	return TilesetPtr(new DDaveTileset(psTileset, fnTruncate, DDaveTileset::VGA, pal));
}

MP_SUPPLIST DDaveVGATilesetType::getRequiredSupps(
	const std::string& filenameTileset) const
	throw ()
{
	MP_SUPPLIST supps;
	supps[SuppItem::Palette] = "vga.pal";
	return supps;
}

bool DDaveVGATilesetType::isInstance(int firstTileSize) const
	throw ()
{
	return (firstTileSize == 256);
}


DDaveTileset::DDaveTileset(iostream_sptr data,
	FN_TRUNCATE fnTruncate, ImageType imgType, PaletteTablePtr pal)
	throw (std::ios::failure) :
		FATTileset(data, fnTruncate, DD_FIRST_TILE_OFFSET),
		imgType(imgType),
		pal(pal)
{
	this->data->seekg(0, std::ios::end);
	io::stream_offset len = this->data->tellg();

	// We still have to perform sanity checks in case the user forced an
	// open even though it failed the signature check.
	if (len < DD_FIRST_TILE_OFFSET) throw std::ios::failure("file too short");

	this->data->seekg(0, std::ios::beg);
	uint32_t numTiles;
	this->data >> u32le(numTiles);
	this->items.reserve(numTiles);
	if (numTiles > DD_SAFETY_MAX_TILES) throw std::ios::failure("too many tiles");

	if (numTiles > 0) {
		uint32_t nextOffset;
		this->data >> u32le(nextOffset);
		for (int i = 0; i < numTiles; i++) {
			FATEntry *fat = new FATEntry();
			EntryPtr ep(fat);
			fat->isValid = true;
			fat->attr = None;
			fat->index = i;
			fat->offset = nextOffset;
			fat->lenHeader = 0;
			if (i + 1 == numTiles) {
				// Last entry ends at EOF
				nextOffset = len;
			} else {
				this->data >> u32le(nextOffset);
			}
			fat->size = nextOffset - fat->offset;
			this->items.push_back(ep);
		}
	}
}

DDaveTileset::~DDaveTileset()
	throw ()
{
}

int DDaveTileset::getCaps()
	throw ()
{
	return 0 | (this->pal ? Tileset::HasPalette : 0);
}

ImagePtr DDaveTileset::createImageInstance(const EntryPtr& id,
	iostream_sptr content, FN_TRUNCATE fnTruncate)
	throw (std::ios::failure)
{
	FATEntry *fat = dynamic_cast<FATEntry *>(id.get());
	assert(fat);

	ImagePtr conv;
	bool fixedSize = fat->index < DD_FIRST_TILE_WITH_DIMS;
	switch (this->imgType) {
		case CGA:
			conv.reset(new DDaveCGAImage(content, fnTruncate, fixedSize));
			break;
		case EGA:
			conv.reset(new DDaveEGAImage(content, fnTruncate, fixedSize));
			break;
		case VGA: {
			//VGAPalette vgaPal;
			conv.reset(new DDaveVGAImage(content, fnTruncate, fixedSize, this->pal));
			break;
		}
	}
	return conv;
}

PaletteTablePtr DDaveTileset::getPalette()
	throw ()
{
	return this->pal;
}

void DDaveTileset::updateFileOffset(const FATEntry *pid,
	std::streamsize offDelta)
	throw (std::ios::failure)
{
	uint32_t fatSize = DD_FAT_OFFSET + this->items.size() * DD_FAT_ENTRY_LEN;

	// Because offsets are stored from the end of the FAT (i.e. the first entry
	// will always say offset 0) we need to adjust the value we will be writing.
	uint32_t fatOffset = pid->offset - fatSize;

	this->data->seekg(DD_FAT_OFFSET + pid->index * DD_FAT_ENTRY_LEN, std::ios::beg);
	this->data << u32le(fatOffset);
	return;
}

DDaveTileset::FATEntry *DDaveTileset::preInsertFile(
	const DDaveTileset::FATEntry *idBeforeThis, DDaveTileset::FATEntry *pNewEntry)
	throw (std::ios::failure)
{
	uint32_t fatSize = DD_FAT_OFFSET + this->items.size() * DD_FAT_ENTRY_LEN;

	// Because offsets are stored from the end of the FAT (i.e. the first entry
	// will always say offset 0) we need to adjust the value we will be writing.
	//uint32_t fatOffset = pNewEntry->offset - fatSize;

	this->data->seekp(DD_FAT_OFFSET + pNewEntry->index * DD_FAT_ENTRY_LEN);
	this->data->insert(DD_FAT_ENTRY_LEN);
	//this->data << u32le(fatOffset);
	// No need to write the offset now as it will be wrong, and will be updated
	// in postInsertFile() anyway.

	// Update the offsets now there's a new FAT entry taking up space.  Although
	// no offsets will change (because they're counting from the end of the FAT -
	// the first entry will always have an offset of 0), we still need to update
	// the in-memory offsets, which *will* change as they count from the start of
	// the file.
	this->shiftFiles(
		NULL,
		fatSize,
		DD_FAT_ENTRY_LEN,
		0
	);
	// Because the new entry isn't in the vector yet we need to shift it manually
	pNewEntry->offset += DD_FAT_ENTRY_LEN;

	return pNewEntry;
}

void DDaveTileset::postInsertFile(FATEntry *pNewEntry)
	throw (std::ios::failure)
{
	// Now the FAT vector has been updated, recalculate the file offsets so they
	// are correct (i.e. entry 0 is still at offset 0).
	this->shiftFiles(NULL, 0, 0, 0);
	this->updateFileCount(this->items.size());
	return;
}

void DDaveTileset::postRemoveFile(const FATEntry *pid)
	throw (std::ios::failure)
{
	// Update the offsets now there's one less FAT entry taking up space.  This
	// must be called before the FAT is altered, because it will write a new
	// offset into the FAT entry we're about to erase (and if we erase it first
	// it'll overwrite something else.)
	this->shiftFiles(
		NULL,
		DD_FAT_OFFSET + this->items.size() * DD_FAT_ENTRY_LEN,
		-DD_FAT_ENTRY_LEN,
		0
	);

	// Remove the last FAT entry now it is no longer in use
	//this->data->seekp(DD_FAT_OFFSET + pid->index * DD_FAT_ENTRY_LEN);
	this->data->seekp(DD_FAT_OFFSET + this->items.size() * DD_FAT_ENTRY_LEN);
	this->data->remove(DD_FAT_ENTRY_LEN);

	this->updateFileCount(this->items.size());
	return;
}

void DDaveTileset::updateFileCount(uint32_t newCount)
	throw (std::ios_base::failure)
{
	this->data->seekp(DD_TILECOUNT_OFFSET);
	this->data << u32le(newCount);
	return;
}


} // namespace gamegraphics
} // namespace camoto
