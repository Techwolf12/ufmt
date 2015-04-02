/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

#include "Formatter.h"

#include "UFMT.h"

UFMT_NS_BEGIN;

CFormatter::CFormatter()
{
  fmt_pProgram = NULL;
  fmt_pfsInput = NULL;
  fmt_iLine = 1;
  fmt_iColumn = 0;
  fmt_iColumnContent = 0;
  fmt_bContentHit = FALSE;
}

CFormatter::~CFormatter()
{
}

CString CFormatter::Indent(const CString &strLine, int iIndent)
{
  if(iIndent == 0) {
    return strLine;
  }

  CString strIndent;
  if(fmt_pProgram->m_bIndentWithTabs) {
    strIndent.Fill('\t', iIndent);
  } else {
    strIndent.Fill(' ', fmt_pProgram->m_iIndentSpaces * iIndent);
  }
  return strIndent + strLine.Trim();
}

BOOL CFormatter::IsWhitespace(char c)
{
  return c == ' ' || c == '\t';
}

char CFormatter::Next()
{
  char c;
  do {
    do {
      c = fmt_pfsInput->ReadChar();
    } while(c == '\r');

    HandleCounters(c);

    if(c == '\n') {
      break;
    }
  } while(!fmt_bContentHit);

  return c;
}

char CFormatter::PeekNext()
{
  char c;
  do {
    c = fmt_pfsInput->ReadChar();
  } while(c == '\r');

  fmt_pfsInput->Seek(-1, 1/*SEEK_CUR*/);

  return c;
}

CString CFormatter::NextString(int length)
{
  char* sz = new char[length+1];
  fmt_pfsInput->Read(sz, length);
  sz[length] = '\0';
  for(int i=0; i<length; i++) {
    HandleCounters(sz[i]);
  }
  CString ret(sz);
  delete[] sz;
  return ret;
}

CString CFormatter::PeekNextString(int length)
{
  char* sz = new char[length+1];
  fmt_pfsInput->Read(sz, length);
  fmt_pfsInput->Seek(-length, 1/*SEEK_CUR*/);
  sz[length] = '\0';
  CString ret(sz);
  delete[] sz;
  return ret;
}

void CFormatter::Addlines(int n)
{
  fmt_iLine += n;
  fmt_iColumn = 0;
}

void CFormatter::Addcolumns(int n, int nc)
{
  fmt_iColumn += n;
  fmt_iColumnContent += nc;
}

void CFormatter::HandleCounters(char c)
{
  if(c == '\n') {
    Addlines();
    fmt_bContentHit = FALSE;
  } else {
    if(!fmt_bContentHit && !IsWhitespace(c)) {
      fmt_bContentHit = TRUE;
    }
    Addcolumns(1, fmt_bContentHit);
  }
}

UFMT_NS_END;
