/**
 *  @file colors.h
 *  @author Ivan Dryanovski <ivan.dryanovski@gmail.com>
 * 
 *  @section LICENSE
 * 
 *  Copyright (C) 2013, Ivan Dryanovski
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef RGBD_2_SCHEMATIC_COLORS_H
#define RGBD_2_SCHEMATIC_COLORS_H

const double SAT_MIN = 0.20;
const double VAL_MIN = 0.25;

// Wool color data indices

const int MAT_WHITE       = 0;
const int MAT_ORANGE      = 1;
const int MAT_MAGENTA     = 2;
const int MAT_LIGHT_BLUE  = 3;
const int MAT_YELLOW      = 4;
const int MAT_LIME        = 5;
const int MAT_PINK        = 6;
const int MAT_GRAY        = 7;
const int MAT_LIGHT_GRAY  = 8;
const int MAT_CYAN        = 9;
const int MAT_PURPLE      = 10;
const int MAT_BLUE        = 11;
const int MAT_BROWN       = 12;
const int MAT_GREEN       = 13;
const int MAT_RED         = 14;
const int MAT_BLACK       = 15;

// Wool rgb values

const int WHITE[3]      = {222, 222, 222};
const int ORANGE[3]     = {218, 124, 61};
const int MAGENTA[3]    = {178, 78, 187};
const int LIGHT_BLUE[3] = {108, 138, 201};
const int YELLOW[3]     = {175, 164, 38};
const int LIME[3]       = {65, 173, 56};
const int PINK[3]       = {208, 132, 153};
const int GRAY[3]       = {63, 63, 63};
const int LIGHT_GRAY[3] = {159, 159, 159};
const int CYAN[3]       = {68, 125, 148};
const int PURPLE[3]     = {127, 61, 182};
const int BLUE[3]       = {45, 55, 139};
const int BROWN[3]      = {78, 49, 30};
const int GREEN[3]      = {71, 87, 48};
const int RED[3]        = {151, 51, 48};
const int BLACK[3]      = {21, 21, 21};

// Wool hue values

const int H_PINK       = 344;
const int H_RED        = 2;       // 13
const int H_ORANGE     = 24;
const int H_BROWN      = 25;      // 30
const int H_YELLOW     = 55;      // 70
const int H_GREEN      = 85;      // 100
const int H_LIME       = 115;     // 155
const int H_CYAN       = 198;     // 210
const int H_LIGHT_BLUE = 220;
const int H_BLUE       = 234;     // 255
const int H_PURPLE     = 273;     // 285
const int H_MAGENTA    = 295;     // 320

#endif // RGBD_2_SCHEMATIC_COLORS_H
