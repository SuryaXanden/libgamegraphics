/**
 * @file  tls-ccomic2.hpp
 * @brief Captain Comic II tileset
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

#ifndef _CAMOTO_TLS_CCOMIC2_HPP_
#define _CAMOTO_TLS_CCOMIC2_HPP_

#include <camoto/gamegraphics/tilesettype.hpp>

namespace camoto {
namespace gamegraphics {

class TilesetType_CComic2: virtual public TilesetType
{
	public:
		TilesetType_CComic2();
		virtual ~TilesetType_CComic2();

		virtual std::string code() const;
		virtual std::string friendlyName() const;
		virtual std::vector<std::string> fileExtensions() const;
		virtual std::vector<std::string> games() const;
		virtual Certainty isInstance(stream::input& content) const;
		virtual std::shared_ptr<Tileset> create(
			std::unique_ptr<stream::inout> content, SuppData& suppData) const;
		virtual std::shared_ptr<Tileset> open(
			std::unique_ptr<stream::inout> content, SuppData& suppData) const;
		virtual SuppFilenames getRequiredSupps(stream::input& content,
			const std::string& filename) const;
};

} // namespace gamegraphics
} // namespace camoto

#endif // _CAMOTO_TLS_CCOMIC2_HPP_
