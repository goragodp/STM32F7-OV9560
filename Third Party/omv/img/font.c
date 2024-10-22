/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Font data.
 *
 * Size: 8 Style: Normal
 * Included characters:
 *  !"#$%&'()*+,-./0123456789:;<=>?\x0040ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
 * Antialiasing: yes
 * Type: monospaced
 * Encoding: ASMO-708
 * Unicode bom: no
 *
 * Preset name: Monochrome
 * Data block size: 8 bit(s), uint8_t
 * RLE compression enabled: no
 * Conversion type: Monochrome, Diffuse Dither 128
 * Bits per pixel: 1
 *
 * Preprocess:
 *  main scan direction: top_to_bottom
 *  line scan direction: forward
 *  inverse: yes
 */
#include "font.h"
const glyph_t font[95] = {
  // character: ' '
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: '!'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x10,
  0x10,
  0x10,
  0x00,
  0x10,
  0x00,
  0x00}},
  // character: '"'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x18,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: '#'
  {8, 10, {0x00,
  0x00,
  0x24,
  0x7c,
  0x24,
  0x48,
  0x7c,
  0x48,
  0x00,
  0x00}},
  // character: '$'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x1c,
  0x20,
  0x18,
  0x04,
  0x38,
  0x08,
  0x00}},
  // character: '%'
  {8, 10, {0x00,
  0x00,
  0x24,
  0x58,
  0x28,
  0x14,
  0x1a,
  0x24,
  0x00,
  0x00}},
  // character: '&'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x28,
  0x30,
  0x34,
  0x2c,
  0x1c,
  0x00,
  0x00}},
  // character: '''
  {8, 10, {0x00,
  0x00,
  0x10,
  0x10,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: '('
  {8, 10, {0x00,
  0x00,
  0x08,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x08,
  0x00}},
  // character: ')'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x20,
  0x00}},
  // character: '*'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x38,
  0x28,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: '+'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x10,
  0x10,
  0x7c,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: ','
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x20,
  0x00}},
  // character: '-'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: '.'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x00,
  0x00}},
  // character: '/'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x08,
  0x10,
  0x10,
  0x10,
  0x20,
  0x20,
  0x00}},
  // character: '0'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x24,
  0x24,
  0x24,
  0x24,
  0x18,
  0x00,
  0x00}},
  // character: '1'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x18,
  0x08,
  0x08,
  0x08,
  0x08,
  0x00,
  0x00}},
  // character: '2'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x24,
  0x04,
  0x08,
  0x10,
  0x3c,
  0x00,
  0x00}},
  // character: '3'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x04,
  0x18,
  0x04,
  0x04,
  0x38,
  0x00,
  0x00}},
  // character: '4'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x18,
  0x28,
  0x3c,
  0x08,
  0x08,
  0x00,
  0x00}},
  // character: '5'
  {8, 10, {0x00,
  0x00,
  0x1c,
  0x10,
  0x18,
  0x04,
  0x04,
  0x18,
  0x00,
  0x00}},
  // character: '6'
  {8, 10, {0x00,
  0x00,
  0x0c,
  0x10,
  0x38,
  0x24,
  0x24,
  0x18,
  0x00,
  0x00}},
  // character: '7'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x08,
  0x08,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: '8'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x24,
  0x18,
  0x24,
  0x24,
  0x18,
  0x00,
  0x00}},
  // character: '9'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x24,
  0x24,
  0x3c,
  0x08,
  0x30,
  0x00,
  0x00}},
  // character: ':'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x00,
  0x00,
  0x10,
  0x00,
  0x00}},
  // character: ';'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x00,
  0x00,
  0x10,
  0x20,
  0x00}},
  // character: '<'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x38,
  0x40,
  0x38,
  0x00,
  0x00,
  0x00}},
  // character: '='
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x3c,
  0x00,
  0x3c,
  0x00,
  0x00,
  0x00}},
  // character: '>'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x30,
  0x08,
  0x30,
  0x00,
  0x00,
  0x00}},
  // character: '?'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x08,
  0x08,
  0x10,
  0x00,
  0x10,
  0x00,
  0x00}},
  // character: '\x0040'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x44,
  0x9a,
  0xaa,
  0xaa,
  0xb4,
  0x40,
  0x38}},
  // character: 'A'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x28,
  0x28,
  0x28,
  0x7c,
  0x44,
  0x00,
  0x00}},
  // character: 'B'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x24,
  0x38,
  0x24,
  0x24,
  0x38,
  0x00,
  0x00}},
  // character: 'C'
  {8, 10, {0x00,
  0x00,
  0x1c,
  0x20,
  0x20,
  0x20,
  0x20,
  0x1c,
  0x00,
  0x00}},
  // character: 'D'
  {8, 10, {0x00,
  0x00,
  0x78,
  0x44,
  0x44,
  0x44,
  0x44,
  0x78,
  0x00,
  0x00}},
  // character: 'E'
  {8, 10, {0x00,
  0x00,
  0x3c,
  0x20,
  0x38,
  0x20,
  0x20,
  0x3c,
  0x00,
  0x00}},
  // character: 'F'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x20,
  0x30,
  0x20,
  0x20,
  0x20,
  0x00,
  0x00}},
  // character: 'G'
  {8, 10, {0x00,
  0x00,
  0x1c,
  0x20,
  0x20,
  0x24,
  0x24,
  0x1c,
  0x00,
  0x00}},
  // character: 'H'
  {8, 10, {0x00,
  0x00,
  0x44,
  0x44,
  0x7c,
  0x44,
  0x44,
  0x44,
  0x00,
  0x00}},
  // character: 'I'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 'J'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x08,
  0x08,
  0x08,
  0x08,
  0x30,
  0x00,
  0x00}},
  // character: 'K'
  {8, 10, {0x00,
  0x00,
  0x24,
  0x28,
  0x30,
  0x30,
  0x28,
  0x24,
  0x00,
  0x00}},
  // character: 'L'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x20,
  0x20,
  0x20,
  0x20,
  0x38,
  0x00,
  0x00}},
  // character: 'M'
  {8, 10, {0x00,
  0x00,
  0x44,
  0x6c,
  0x6c,
  0x54,
  0x54,
  0x44,
  0x00,
  0x00}},
  // character: 'N'
  {8, 10, {0x00,
  0x00,
  0x42,
  0x62,
  0x52,
  0x4a,
  0x46,
  0x42,
  0x00,
  0x00}},
  // character: 'O'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x44,
  0x44,
  0x44,
  0x44,
  0x38,
  0x00,
  0x00}},
  // character: 'P'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x24,
  0x24,
  0x38,
  0x20,
  0x20,
  0x00,
  0x00}},
  // character: 'Q'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x44,
  0x44,
  0x44,
  0x44,
  0x38,
  0x10,
  0x08}},
  // character: 'R'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x24,
  0x24,
  0x38,
  0x28,
  0x24,
  0x00,
  0x00}},
  // character: 'S'
  {8, 10, {0x00,
  0x00,
  0x18,
  0x20,
  0x20,
  0x18,
  0x08,
  0x30,
  0x00,
  0x00}},
  // character: 'T'
  {8, 10, {0x00,
  0x00,
  0x38,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 'U'
  {8, 10, {0x00,
  0x00,
  0x44,
  0x44,
  0x44,
  0x44,
  0x44,
  0x38,
  0x00,
  0x00}},
  // character: 'V'
  {8, 10, {0x00,
  0x00,
  0x44,
  0x44,
  0x28,
  0x28,
  0x28,
  0x10,
  0x00,
  0x00}},
  // character: 'W'
  {8, 10, {0x00,
  0x00,
  0x82,
  0x92,
  0xaa,
  0xaa,
  0xaa,
  0x44,
  0x00,
  0x00}},
  // character: 'X'
  {8, 10, {0x00,
  0x00,
  0x44,
  0x28,
  0x10,
  0x10,
  0x28,
  0x44,
  0x00,
  0x00}},
  // character: 'Y'
  {8, 10, {0x00,
  0x00,
  0x44,
  0x28,
  0x28,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 'Z'
  {8, 10, {0x00,
  0x00,
  0x3c,
  0x04,
  0x08,
  0x10,
  0x20,
  0x3c,
  0x00,
  0x00}},
  // character: '['
  {8, 10, {0x00,
  0x00,
  0x18,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x18,
  0x00}},
  // character: '\'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x20,
  0x10,
  0x10,
  0x10,
  0x08,
  0x08,
  0x00}},
  // character: ']'
  {8, 10, {0x00,
  0x00,
  0x30,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x30,
  0x00}},
  // character: '^'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x28,
  0x28,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: '_'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x78,
  0x00}},
  // character: '`'
  {8, 10, {0x00,
  0x10,
  0x08,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00}},
  // character: 'a'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x30,
  0x08,
  0x18,
  0x38,
  0x00,
  0x00}},
  // character: 'b'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x20,
  0x38,
  0x24,
  0x24,
  0x38,
  0x00,
  0x00}},
  // character: 'c'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x20,
  0x20,
  0x18,
  0x00,
  0x00}},
  // character: 'd'
  {8, 10, {0x00,
  0x00,
  0x04,
  0x04,
  0x1c,
  0x24,
  0x24,
  0x1c,
  0x00,
  0x00}},
  // character: 'e'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x38,
  0x38,
  0x20,
  0x18,
  0x00,
  0x00}},
  // character: 'f'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x10,
  0x18,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 'g'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x1c,
  0x24,
  0x1c,
  0x04,
  0x38,
  0x00}},
  // character: 'h'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x20,
  0x38,
  0x24,
  0x24,
  0x24,
  0x00,
  0x00}},
  // character: 'i'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x00,
  0x10,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 'j'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x00,
  0x10,
  0x10,
  0x10,
  0x10,
  0x20,
  0x00}},
  // character: 'k'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x20,
  0x28,
  0x30,
  0x30,
  0x28,
  0x00,
  0x00}},
  // character: 'l'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x08,
  0x00,
  0x00}},
  // character: 'm'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0xec,
  0x92,
  0x92,
  0x92,
  0x00,
  0x00}},
  // character: 'n'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x38,
  0x24,
  0x24,
  0x24,
  0x00,
  0x00}},
  // character: 'o'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x24,
  0x24,
  0x18,
  0x00,
  0x00}},
  // character: 'p'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x38,
  0x24,
  0x24,
  0x38,
  0x20,
  0x00}},
  // character: 'q'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x1c,
  0x24,
  0x24,
  0x1c,
  0x04,
  0x00}},
  // character: 'r'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x10,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 's'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x20,
  0x18,
  0x30,
  0x00,
  0x00}},
  // character: 't'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x10,
  0x18,
  0x10,
  0x10,
  0x08,
  0x00,
  0x00}},
  // character: 'u'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x24,
  0x24,
  0x24,
  0x1c,
  0x00,
  0x00}},
  // character: 'v'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x28,
  0x28,
  0x10,
  0x10,
  0x00,
  0x00}},
  // character: 'w'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x54,
  0x54,
  0x54,
  0x28,
  0x00,
  0x00}},
  // character: 'x'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x28,
  0x10,
  0x10,
  0x28,
  0x00,
  0x00}},
  // character: 'y'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x28,
  0x28,
  0x10,
  0x10,
  0x20,
  0x00}},
  // character: 'z'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x18,
  0x08,
  0x10,
  0x18,
  0x00,
  0x00}},
  // character: '{'
  {8, 10, {0x00,
  0x00,
  0x08,
  0x10,
  0x10,
  0x20,
  0x10,
  0x10,
  0x08,
  0x00}},
  // character: '|'
  {8, 10, {0x00,
  0x00,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x00}},
  // character: '}'
  {8, 10, {0x00,
  0x00,
  0x20,
  0x10,
  0x10,
  0x08,
  0x10,
  0x10,
  0x20,
  0x00}},
  // character: '~'
  {8, 10, {0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x28,
  0x50,
  0x00,
  0x00,
  0x00}}
};
