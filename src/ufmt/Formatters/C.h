/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#ifndef UFMT_FORMATTERS_C_INCLUDED
#define UFMT_FORMATTERS_C_INCLUDED

#include "../StdH.h"

#include "../Formatter.h"

UFMT_NS_BEGIN;

class CCFormatter : public CFormatter
{
public:
  CCFormatter();
  virtual ~CCFormatter();

  virtual void Start();
  virtual void Process(CFileStream &fsOutput);
};

UFMT_NS_END;

#endif
