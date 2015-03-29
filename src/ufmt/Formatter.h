/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#ifndef UFMT_FORMATTER_H_INCLUDED
#define UFMT_FORMATTER_H_INCLUDED

#include "StdH.h"

UFMT_NS_BEGIN;

/**
 * Base formatter class. Inherit from this class to define a new language formatter.
 */
class CFormatter
{
public:
  CFormatter();
  virtual ~CFormatter();

  /**
   * When the formatter starts, this will be the "entry point". 
   */
  virtual void Start(CFileStream &fs) = 0;

  /**
   * When the formatter ends, this will be called as a finishing touch for the output.
   */
  virtual void End(CFileStream &fs) = 0;
};

UFMT_NS_END;

#endif
