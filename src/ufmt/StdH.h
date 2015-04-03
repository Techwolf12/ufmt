/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#ifndef UFMT_STDH_H_INCLUDED
#define UFMT_STDH_H_INCLUDED

// Versioning
#define UFMT_VERSION "v0.0.1d"

// Namespacing
#define UFMT_NS_BEGIN namespace UFMT {
#define UFMT_NS_END }

// Standard C libraries
#include <stdio.h>
#include <string.h>

// Scratch core library
#include <Scratch/Scratch.h>
using namespace Scratch;

// Useful macros not shipped with libScratch (yet)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))

#endif
