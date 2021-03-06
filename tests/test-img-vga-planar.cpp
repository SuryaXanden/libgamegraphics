/**
 * @file  test-img-vga-planar.cpp
 * @brief Test code for standard VGA full-screen image handler.
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

#include "test-image.hpp"

class test_img_vga_planar: public test_image
{
	public:
		test_img_vga_planar()
		{
			this->type = "img-vga-planar-fullscreen";
			this->hasMask = false;
			this->hasHitmask = false;
		}

		void addTests()
		{
			this->test_image::addTests();

			this->sizedContent({320, 200}, ImageType::PossiblyYes,
				this->initialstate());

			// c00: Initial state
			this->isInstance(ImageType::PossiblyYes, this->initialstate());

			// c01: Too short
			this->isInstance(ImageType::DefinitelyNo, STRING_WITH_NULLS(
				"\x01"
			));
		}

		virtual std::string initialstate() const
		{
			std::string content;

			// Plane 0
			content += std::string(80, '\x0F');
			for (int y = 1; y < 199; y++) {
				content += '\x0C';
				content += std::string(79, '\x00');
			}
			content += '\x0C';
			content += std::string(79, '\x09');

			// Plane 1
			content += std::string(80, '\x0F');
			for (int y = 1; y < 199; y++) {
				content += std::string(80, '\x00');
			}
			content += std::string(80, '\x09');

			// Plane 2
			content += std::string(80, '\x0F');
			for (int y = 1; y < 199; y++) {
				content += std::string(80, '\x00');
			}
			content += std::string(80, '\x09');

			// Plane 3
			content += std::string(80, '\x0F');
			for (int y = 1; y < 199; y++) {
				content += std::string(79, '\x00');
				content += '\x0A';
			}
			content += std::string(79, '\x09');
			content += '\x0E';

			return content;
		}
};

IMPLEMENT_TESTS(img_vga_planar);
