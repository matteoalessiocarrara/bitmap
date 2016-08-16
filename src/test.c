/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

# include "bitmap.c"

# define BIT_TEST 8


int main()
{
	uint8_t *bitmap = bitmap_create(17);

	bitmap_enable(bitmap, BIT_TEST);
	printf("bit %u: %u\n", BIT_TEST, bitmap_get(bitmap, BIT_TEST));

	bitmap_disable(bitmap, BIT_TEST);
	printf("bit %u: %u\n", BIT_TEST, bitmap_get(bitmap, BIT_TEST));

	return 0;
}
