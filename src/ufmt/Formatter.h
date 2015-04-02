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

class CUltimateFormatter;

/**
 * Base formatter class. Inherit from this class to define a new language formatter.
 */
class CFormatter
{
public:
  /**
   * The main UFMT class object, can be used to access given parameters to the program.
   */
  CUltimateFormatter* fmt_pProgram;

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

  /**
   * Keep count of the current column in the source file, without any indentation.
   */
  int fmt_iColumnContent;

  /**
   * Whether we have hit the content on the current source line or not.
   */
  BOOL fmt_bContentHit;

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
   * Indent the given line with the given amount of indentation.
   */
  virtual CString Indent(const CString &strLine, int iIndent);

  /**
   * Returns whether the given character is whitespace or not.
   */
  virtual BOOL IsWhitespace(char c);

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
  virtual void Addcolumns(int n = 1, int nc = 1);

private:
  /**
   * Handle line and column counters for the next character. This is called internally.
   */
  virtual void HandleCounters(char c);
};

UFMT_NS_END;

#endif
