/**
 * @file   test-tileset.cpp
 * @brief  Generic test code for Tileset class descendents.
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

#include <iomanip>
#include <functional>
#include <camoto/util.hpp>
#include <camoto/gamearchive/archive-fat.hpp> // getFileAt()
#include "test-tileset.hpp"
#include "test-image.hpp"

using namespace camoto;
using namespace camoto::gamearchive;

/// Check whether a supp item is present and if so that the content is correct.
#define CHECK_SUPP_ITEM(item, check_func, msg) \
	if (this->suppResult.find(camoto::SuppItem::item) != this->suppResult.end()) { \
		BOOST_CHECK_MESSAGE( \
			this->is_supp_equal(camoto::SuppItem::item, \
				this->suppResult[camoto::SuppItem::item]->check_func()), \
			"[SuppItem::" TOSTRING(item) "] " msg \
		); \
	}

test_tileset::test_tileset()
{
	this->firstTileDims = {9999, 9999};
}

void test_tileset::addTests()
{
	this->test_archive::addTests();
	ADD_TILESET_TEST(false, &test_tileset::test_open_image);
	return;
}

void test_tileset::prepareTest(bool emptyArchive)
{
	auto pTilesetType = TilesetManager::byCode(this->type);
	BOOST_REQUIRE_MESSAGE(pTilesetType, "Could not find tileset type " + this->type);

	// Make this->suppData valid
	this->resetSuppData(emptyArchive);
	this->populateSuppData();

	this->base = std::make_unique<stream::string>();

	if (emptyArchive) {
		BOOST_TEST_CHECKPOINT("About to create new empty instance of "
			+ this->basename);
		// This should really use BOOST_REQUIRE_NO_THROW but the message is more
		// informative without it.
		//BOOST_REQUIRE_NO_THROW(
			this->pArchive = pTilesetType->create(
				stream_wrap(this->base), this->suppData);
		//);
	} else {
		*base << this->initialstate();
		BOOST_TEST_CHECKPOINT("About to open " + this->basename
			+ " initialstate as an archive");
		// This should really use BOOST_REQUIRE_NO_THROW but the message is more
		// informative without it.
		//BOOST_REQUIRE_NO_THROW(
		this->pArchive = pTilesetType->open(
			stream_wrap(this->base), this->suppData);
		//);
	}
	BOOST_REQUIRE_MESSAGE(this->pArchive, "Could not create tileset class");

	if (this->lenMaxFilename < 0) {
		// This format has no filenames, so set them to obviously incorrect values.
		this->filename[0] = "dummy";
		this->filename[1] = "dummy";
		this->filename[2] = "dummy";
		this->filename[3] = "dummy";
	}
	return;
}

void test_tileset::test_isInstance(ArchiveType::Certainty result,
	const std::string& content, unsigned int testNumber)
{
	BOOST_TEST_MESSAGE(createString("isInstance check (" << this->basename
		<< "; " << std::setfill('0') << std::setw(2) << testNumber << ")"));

	auto pTestType = TilesetManager::byCode(this->type);
	BOOST_REQUIRE_MESSAGE(pTestType,
		createString("Could not find tileset type " << this->type));

	stream::string ss;
	ss << content;

	BOOST_CHECK_EQUAL(pTestType->isInstance(ss), result);
	return;
}

void test_tileset::test_isinstance_others()
{
	// Check all file formats except this one to avoid any false positives
	BOOST_TEST_MESSAGE("isInstance check for other formats (not " << this->type
		<< ")");

	stream::string content;
	content << this->initialstate();

	for (const auto& pTestType : TilesetManager::formats()) {
		// Don't check our own type, that's done by the other isinstance_* tests
		std::string otherType = pTestType->code();
		if (otherType.compare(this->type) == 0) continue;

		// Skip any formats known to produce false detections unavoidably
		if (
			std::find(
				this->skipInstDetect.begin(), this->skipInstDetect.end(), otherType
			) != this->skipInstDetect.end()) continue;

		BOOST_TEST_MESSAGE("Checking " << this->type
			<< " content against isInstance() for " << otherType);

		BOOST_CHECK_MESSAGE(pTestType->isInstance(content) < ArchiveType::DefinitelyYes,
			"isInstance() for " << otherType << " incorrectly recognises content for "
			<< this->type);
	}
	return;
}

void test_tileset::test_new_isinstance()
{
	BOOST_TEST_MESSAGE("Checking new tileset is valid instance of itself");

	this->pArchive->flush();

	auto pTestType = TilesetManager::byCode(this->type);
	BOOST_REQUIRE_MESSAGE(pTestType,
		createString("Could not find tileset type " << this->type));

	BOOST_REQUIRE_MESSAGE(pTestType->isInstance(*this->base),
		"Newly created archive was not recognised as a valid instance");

	BOOST_TEST_CHECKPOINT("New tileset reported valid, trying to open");

	// Make this->suppData valid again, reusing previous data
	this->populateSuppData();

	auto base2 = stream_wrap(this->base);

	// This should really use BOOST_REQUIRE_NO_THROW but the message is more
	// informative without it.
	//BOOST_REQUIRE_NO_THROW(
		auto pArchive = pTestType->open(std::move(base2), this->suppData);
	//);

	// Make sure there are now no files in the archive
	auto& files = pArchive->files();
	BOOST_REQUIRE_EQUAL(files.size(), 0);
}

void test_tileset::test_open_image()
{
	BOOST_TEST_MESSAGE("Opening image in tileset");

	auto ep = this->findFile(0);

	auto tileset = std::dynamic_pointer_cast<Tileset>(this->pArchive);
	BOOST_REQUIRE(tileset);

	auto img = tileset->openImage(ep);
	BOOST_REQUIRE(img);

	auto dimsReported = img->dimensions();
	BOOST_CHECK_EQUAL(this->firstTileDims.x, dimsReported.x);
	BOOST_CHECK_EQUAL(this->firstTileDims.y, dimsReported.y);

	auto pixels = img->convert();
	auto pixelsExpected = createPixelData(dimsReported);
	auto strPixels = std::string(pixels.begin(), pixels.end());
	auto strPixelsExpected = std::string(pixelsExpected.begin(), pixelsExpected.end());
	BOOST_REQUIRE_MESSAGE(
		this->is_equal(strPixelsExpected, strPixels),
		"First tile in tileset was not standard test image"
	);
}
