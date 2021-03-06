/**
 * @file  test-tls-ddave.cpp
 * @brief Test code for Dangerous Dave tilesets.
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

#include "test-tileset.hpp"

class test_tls_ddave_cga: public test_tileset
{
	public:
		test_tls_ddave_cga()
		{
			this->type = "tls-ddave-cga";
			this->lenMaxFilename = -1;
			this->lenFilesizeFixed = 64;
			this->cga = true;

			this->content[0] = this->tile1();
			this->content[1] = this->tile2();
			this->content[2] = this->tile3();
			this->content[3] = this->tile4();

			this->firstTileDims = {16, 16};
		}

		void addTests()
		{
			this->test_tileset::addTests();

			// c00: Initial state
			this->isInstance(ArchiveType::Certainty::DefinitelyYes, this->initialstate());

			// c01: File too short
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\x00\x00"
			));

			// c01: Header cut off
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\xFF\xFF\x01\x00"
				"\x0C\x00\x00\x00"
				"\x4C\x00\x00\x00"
				) +
				this->tile1() +
				this->tile2()
			);
		}

		virtual std::string tile1() const
		{
			return STRING_WITH_NULLS(
				"\xCF\xFF\xFF\xFF"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x6A\xAA\xAA\xA1"
			);
		}

		virtual std::string tile2() const
		{
			return STRING_WITH_NULLS(
				"\xDF\xFF\xFF\xFF"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x6A\xAA\xAA\xA5"
			);
		}

		virtual std::string tile3() const
		{
			return STRING_WITH_NULLS(
				"\xEF\xFF\xFF\xFF"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x6A\xAA\xAA\xA9"
			);
		}

		virtual std::string tile4() const
		{
			return STRING_WITH_NULLS(
				"\xFF\xFF\xFF\xFF"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x40\x00\x00\x02"
				"\x6A\xAA\xAA\xAD"
			);
		}

		virtual std::string initialstate()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x4C\x00\x00\x00"
				) +
				this->tile1() +
				this->tile2()
			;
		}

		virtual std::string rename()
		{
			throw stream::error("This tileset does not have any tilenames.");
		}

		virtual std::string insert_end()
		{
			return
				STRING_WITH_NULLS(
					"\x03\x00\x00\x00"
					"\x10\x00\x00\x00"
					"\x50\x00\x00\x00"
					"\x90\x00\x00\x00"
				) +
				this->tile1() +
				this->tile2() +
				this->tile3()
			;
		}

		virtual std::string insert_mid()
		{
			return
				STRING_WITH_NULLS(
					"\x03\x00\x00\x00"
					"\x10\x00\x00\x00"
					"\x50\x00\x00\x00"
					"\x90\x00\x00\x00"
				) +
				this->tile1() +
				this->tile3() +
				this->tile2()
			;
		}

		virtual std::string insert2()
		{
			return
				STRING_WITH_NULLS(
					"\x04\x00\x00\x00"
					"\x14\x00\x00\x00"
					"\x54\x00\x00\x00"
					"\x94\x00\x00\x00"
					"\xD4\x00\x00\x00"
				) +
				this->tile1() +
				this->tile3() +
				this->tile4() +
				this->tile2()
			;
		}

		virtual std::string remove()
		{
			return
				STRING_WITH_NULLS(
					"\x01\x00\x00\x00"
					"\x08\x00\x00\x00"
				) +
				this->tile2()
			;
		}

		virtual std::string remove2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00"
			);
		}

		virtual std::string insert_remove()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x4C\x00\x00\x00"
				) +
				this->tile3() +
				this->tile2()
			;
		}

		virtual std::string move()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x4C\x00\x00\x00"
				) +
				this->tile2() +
				this->tile1()
			;
		}

		virtual std::string resize_larger()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}

		virtual std::string resize_smaller()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}

		virtual std::string resize_write()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}
};

class test_tls_ddave_ega: public test_tileset
{
	public:
		test_tls_ddave_ega()
		{
			this->type = "tls-ddave-ega";
			this->lenMaxFilename = -1;
			this->lenFilesizeFixed = 128;

			this->content[0] = this->tile1();
			this->content[1] = this->tile2();
			this->content[2] = this->tile3();
			this->content[3] = this->tile4();

			this->firstTileDims = {16, 16};
		}

		void addTests()
		{
			this->test_tileset::addTests();

			// c00: Initial state
			this->isInstance(ArchiveType::Certainty::DefinitelyYes, this->initialstate());

			// c01: File too short
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\x00\x00"
			));

			// c01: Header cut off
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\xFF\xFF\x01\x00"
				"\x0C\x00\x00\x00"
				"\x8C\x00\x00\x00"
				) +
				this->tile1() +
				this->tile2()
			);
		}

		virtual std::string tile1() const
		{
			return STRING_WITH_NULLS(
				"\xBF\xFF\xBF\xFF\xBF\xFF\xBF\xFF"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\xFF\xFD\x80\x01\x00\x01\x7F\xFC"
			);
		}

		virtual std::string tile2() const
		{
			return STRING_WITH_NULLS(
				"\xBF\xFF\xBF\xFF\xBF\xFF\xFF\xFF"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\xFF\xFD\x80\x01\x00\x01\x7F\xFE"
			);
		}

		virtual std::string tile3() const
		{
			return STRING_WITH_NULLS(
				"\xBF\xFF\xBF\xFF\xFF\xFF\xBF\xFF"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\xFF\xFD\x80\x01\x00\x03\x7F\xFC"
			);
		}

		virtual std::string tile4() const
		{
			return STRING_WITH_NULLS(
				"\xBF\xFF\xBF\xFF\xFF\xFF\xFF\xFF"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\x80\x01\x80\x00\x00\x01\x00\x00"
				"\xFF\xFD\x80\x01\x00\x03\x7F\xFE"
			);
		}

		virtual std::string initialstate()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x8C\x00\x00\x00"
				) +
				this->tile1() +
				this->tile2()
			;
		}

		virtual std::string rename()
		{
			throw stream::error("This tileset does not have any tilenames.");
		}

		virtual std::string insert_end()
		{
			return
				STRING_WITH_NULLS(
					"\x03\x00\x00\x00"
					"\x10\x00\x00\x00"
					"\x90\x00\x00\x00"
					"\x10\x01\x00\x00"
				) +
				this->tile1() +
				this->tile2() +
				this->tile3()
			;
		}

		virtual std::string insert_mid()
		{
			return
				STRING_WITH_NULLS(
					"\x03\x00\x00\x00"
					"\x10\x00\x00\x00"
					"\x90\x00\x00\x00"
					"\x10\x01\x00\x00"
				) +
				this->tile1() +
				this->tile3() +
				this->tile2()
			;
		}

		virtual std::string insert2()
		{
			return
				STRING_WITH_NULLS(
					"\x04\x00\x00\x00"
					"\x14\x00\x00\x00"
					"\x94\x00\x00\x00"
					"\x14\x01\x00\x00"
					"\x94\x01\x00\x00"
				) +
				this->tile1() +
				this->tile3() +
				this->tile4() +
				this->tile2()
			;
		}

		virtual std::string remove()
		{
			return
				STRING_WITH_NULLS(
					"\x01\x00\x00\x00"
					"\x08\x00\x00\x00"
				) +
				this->tile2()
			;
		}

		virtual std::string remove2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00"
			);
		}

		virtual std::string insert_remove()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x8C\x00\x00\x00"
				) +
				this->tile3() +
				this->tile2()
			;
		}

		virtual std::string move()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x8C\x00\x00\x00"
				) +
				this->tile2() +
				this->tile1()
			;
		}

		virtual std::string resize_larger()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}

		virtual std::string resize_smaller()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}

		virtual std::string resize_write()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}
};

class test_tls_ddave_vga: public test_tileset
{
	public:
		test_tls_ddave_vga()
		{
			this->type = "tls-ddave-vga";
			this->lenMaxFilename = -1;
			this->lenFilesizeFixed = 256;

			this->content[0] = this->tile1();
			this->content[1] = this->tile2();
			this->content[2] = this->tile3();
			this->content[3] = this->tile4();

			this->firstTileDims = {16, 16};
		}

		void addTests()
		{
			this->test_tileset::addTests();

			// c00: Initial state
			this->isInstance(ArchiveType::Certainty::DefinitelyYes, this->initialstate());

			// c01: File too short
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\x00\x00"
			));

			// c01: Header cut off
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\xFF\xFF\x01\x00"
				"\x0C\x00\x00\x00"
				"\x0C\x01\x00\x00"
				) +
				this->tile1() +
				this->tile2()
			);
		}

		virtual std::string tile1() const
		{
			return STRING_WITH_NULLS(
				"\x0F\x00\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x00\x0E"
			);
		}

		virtual std::string tile2() const
		{
			return STRING_WITH_NULLS(
				"\x0F\x01\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x01\x0E"
			);
		}

		virtual std::string tile3() const
		{
			return STRING_WITH_NULLS(
				"\x0F\x02\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x02\x0E"
			);
		}

		virtual std::string tile4() const
		{
			return STRING_WITH_NULLS(
				"\x0F\x03\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F\x0F"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0A"
				"\x0C\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x03\x0E"
			);
		}

		virtual std::string initialstate()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x0C\x01\x00\x00"
				) +
				this->tile1() +
				this->tile2()
			;
		}

		virtual std::string rename()
		{
			throw stream::error("This tileset does not have any tilenames.");
		}

		virtual std::string insert_end()
		{
			return
				STRING_WITH_NULLS(
					"\x03\x00\x00\x00"
					"\x10\x00\x00\x00"
					"\x10\x01\x00\x00"
					"\x10\x02\x00\x00"
				) +
				this->tile1() +
				this->tile2() +
				this->tile3()
			;
		}

		virtual std::string insert_mid()
		{
			return
				STRING_WITH_NULLS(
					"\x03\x00\x00\x00"
					"\x10\x00\x00\x00"
					"\x10\x01\x00\x00"
					"\x10\x02\x00\x00"
				) +
				this->tile1() +
				this->tile3() +
				this->tile2()
			;
		}

		virtual std::string insert2()
		{
			return
				STRING_WITH_NULLS(
					"\x04\x00\x00\x00"
					"\x14\x00\x00\x00"
					"\x14\x01\x00\x00"
					"\x14\x02\x00\x00"
					"\x14\x03\x00\x00"
				) +
				this->tile1() +
				this->tile3() +
				this->tile4() +
				this->tile2()
			;
		}

		virtual std::string remove()
		{
			return
				STRING_WITH_NULLS(
					"\x01\x00\x00\x00"
					"\x08\x00\x00\x00"
				) +
				this->tile2()
			;
		}

		virtual std::string remove2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00"
			);
		}

		virtual std::string insert_remove()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x0C\x01\x00\x00"
				) +
				this->tile3() +
				this->tile2()
			;
		}

		virtual std::string move()
		{
			return
				STRING_WITH_NULLS(
					"\x02\x00\x00\x00"
					"\x0C\x00\x00\x00"
					"\x0C\x01\x00\x00"
				) +
				this->tile2() +
				this->tile1()
			;
		}

		virtual std::string resize_larger()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}

		virtual std::string resize_smaller()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}

		virtual std::string resize_write()
		{
			throw stream::error("Tiles in this format are a fixed size.");
		}
};

IMPLEMENT_TESTS(tls_ddave_cga);
IMPLEMENT_TESTS(tls_ddave_ega);
IMPLEMENT_TESTS(tls_ddave_vga);
