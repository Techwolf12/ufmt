/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
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
  /**
   * The input stream to read from to start processing.
   */
  CFileStream* fmt_pfsInput;

  /**
   * Keep count of the current line in the source file.
   */
  int fmt_iLine;

  /**
   * Keep count of the current column in the source file.
   */
  int fmt_iColumn;

public:
  CFormatter();
  virtual ~CFormatter();

  /**
   * When the formatter starts, this will be the "entry point", a good place to clean
   * class fields and start from an empty state.
   */
  virtual void Start() = 0;

  /**
   * This is called to actually process the input stream and write to the given output
   * stream.
   */
  virtual void Process(CFileStream &fsOutput) = 0;

  /**
   * Get the next char.
   */
  virtual char Next();

  /**
   * Peek the next char.
   */
  virtual char PeekNext();

  /**
   * Get the next string.
   */
  virtual CString NextString(int length);

  /**
   * Peek the next string.
   */
  virtual CString PeekNextString(int length);

  /**
   * Call this when a new line in the source file has been found.
   */
  virtual void Addlines(int n = 1);

  /**
   * Call this to increase the column counter.
   */
  virtual void Addcolumns(int n = 1);
};

UFMT_NS_END;

#endif
