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

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <malloc.h>
# include <assert.h>
# include <errno.h>
# include <math.h>


// TODO Gestire meglio errori

typedef struct _bitmap
{
	uint8_t *data;
	size_t bits;
} bitmap;


bitmap
bitmap_create(size_t bits)
{
	bitmap ret;

	ret.bits = bits;
	if ((ret.data = calloc(ceil(bits/8.0), 1)) == NULL)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	return ret;
}


void
bitmap_resize(bitmap *b, size_t bits)
{
	uint8_t *tmp = realloc(b->data, ceil(bits/8.0));

	if (tmp == NULL)
	{
		perror("realloc()");
		exit(EXIT_FAILURE);
	}
	else b->data = tmp;

	// Va inizializzata la nuova memoria, realloc non lo fa
	memset(b->data, 0, ceil(bits/8.0) - ceil(b->bits/8.0));

	b->bits = bits;
}


uint8_t
bitmap_get(bitmap *b, size_t bitmap_offset)
{
	assert(bitmap_offset < (b->bits));
	return (b->data[bitmap_offset/8] >> (7 - bitmap_offset % 8)) & 1;
}

void
bitmap_enable(bitmap *b, size_t bitmap_offset)
{
	assert(bitmap_offset < (b->bits));
	b->data[bitmap_offset/8] |= (1 << (7 - bitmap_offset % 8));
}


void
bitmap_disable(bitmap *b, size_t bitmap_offset)
{
	assert(bitmap_offset < (b->bits));
	b->data[bitmap_offset/8] &= ~(1 << (7 - bitmap_offset % 8));
}


size_t
bitmap_find_next_enabled(bitmap *b, size_t start)
{
	// Se la ricerca inizia dentro ad un byte
	if ((start % 8) != 0)
	{
		for(int8_t i = 7 - (start % 8); i >= 0; i--)
			if (b->data[start/8] & (1 << i))
				return (start % 8) == 7? start : start + (7 - (start % 8) - i);

		// Se non ha trovato niente in questo byte, passiamo ai byte successivi
		start += (8 - (start % 8));
	}

	// Se la ricerca inizia dall'inizio di un byte possiamo velocizzare controllando
	// un byte alla volta, piuttosto che i singoli bit
	if ((start % 8) == 0)
	{
		for(size_t i = start/8; i < ceil(b->bits/8.0); i++)
		{
			if (b->data[i])
			{
				start = i * 8;
				for(int8_t i = 7; i >= 0; i--)
					if (b->data[start/8] & (1 << i))
						return start + (7 - i);
			}
		}
	}

	// TODO Err?
	return 0;
}
