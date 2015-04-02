/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

#include "Formatter.h"

UFMT_NS_BEGIN;

CFormatter::CFormatter()
{
  fmt_pfsInput = NULL;
  fmt_iLine = 1;
  fmt_iColumn = 0;
}

CFormatter::~CFormatter()
{
}

char CFormatter::Next()
{
  char c;
  do {
    c = fmt_pfsInput->ReadChar();
  } while(c == '\r');

  if(c == '\n') {
    Addlines();
  } else {
    Addcolumns();
  }

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
    if(sz[i] == '\n') {
      Addlines();
    } else {
      Addcolumns();
    }
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

void CFormatter::Addcolumns(int n)
{
  fmt_iColumn += n;
}

UFMT_NS_END;
