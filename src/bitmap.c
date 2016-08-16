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

# include <stdint.h>
# include <stddef.h>
# include <malloc.h>
# include <math.h>


uint8_t *
bitmap_create(size_t bits)
{
	return malloc(ceil(bits/8.0));
}


uint8_t
bitmap_get(uint8_t *bitmap, size_t bitmap_offset)
{
	return (bitmap[bitmap_offset/8] >> (7 - bitmap_offset % 8)) & 1;
}

void
bitmap_enable(uint8_t *bitmap, size_t bitmap_offset)
{
	bitmap[bitmap_offset/8] |= (1 << (7 - bitmap_offset % 8));
}


void
bitmap_disable(uint8_t *bitmap, size_t bitmap_offset)
{
	bitmap[bitmap_offset/8] &= ~(1 << (7 - bitmap_offset % 8));
}
