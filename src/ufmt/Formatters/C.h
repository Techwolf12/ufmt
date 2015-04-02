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

struct SCBlock
{
  int m_iStartLine;

  SCBlock();
};

class CCFormatter : public CFormatter
{
public:
  CFileStream* m_pfsOutput;

  CString m_strLine;
  int m_iIndent;
  int m_iIndentNext;

public:
  CCFormatter();
  virtual ~CCFormatter();

  virtual void Start();
  virtual void Process(CFileStream &fsOutput);

  virtual void FlushLine(BOOL bNewLine = TRUE);
};

UFMT_NS_END;

#endif
