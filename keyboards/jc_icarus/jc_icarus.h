/* Copyright 2017 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
#ifndef JC_ICARUS_H
#define JC_ICARUS_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
	k11, k21, k31, k41, k51, k61,							k26, k36, k46, k56, k66, k76, \
	k12, k22, k32, k42, k52, k62,							k27, k37, k47, k57, k67, k77, \
	k13, k23, k33, k43, k53, k63, k71, k72,		  k17, k16, k28, k38, k48, k58, k68, k78, \
	k14, k24, k34, k44, k54, k64, k73, k74,		  k19, k18, k29, k39, k49, k59, k69, k79, \
	k15, k25, k35, k45, 	 k55, k65, k75,		  k1a, k2a,      k3a, k4a, k5a, k6a, k7a, \
) \
{ \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a }, \
    { k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a }, \
    { k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a }, \
    { k61, k62, k63, k64, k65, k66, k67, k68, k69, k6a }, \
    { k71, k72, k73, k74, k75, k76, k77, k78, k79, k7a }, \
}

#endif
