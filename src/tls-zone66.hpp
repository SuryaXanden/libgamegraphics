/**
 * @file  tls-zone66.hpp
 * @brief Zone 66 tileset handler.
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

#ifndef _CAMOTO_TLS_ZONE66_HPP_
#define _CAMOTO_TLS_ZONE66_HPP_

#include <camoto/gamegraphics/tilesettype.hpp>

namespace camoto {
namespace gamegraphics {

/// Tileset file handler for Zone 66 tilesets.
class TilesetType_Zone66: virtual public TilesetType
{
	public:
		TilesetType_Zone66();
		virtual ~TilesetType_Zone66();

		virtual std::string code() const;
		virtual std::string friendlyName() const;
		virtual std::vector<std::string> fileExtensions() const;
		virtual std::vector<std::string> games() const;
		virtual Certainty isInstance(stream::input& content) const;
		virtual std::shared_ptr<Tileset> create(
			std::unique_ptr<stream::inout> content, SuppData& suppData) const;
		virtual std::shared_ptr<Tileset> open(
			std::unique_ptr<stream::inout> content, SuppData& suppData) const;
		virtual SuppFilenames getRequiredSupps(const std::string& filenameTileset)
			const;
};

} // namespace gamearchive
} // namespace camoto

#endif // _CAMOTO_TLS_ZONE66_HPP_
