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

}

virtual char CFormatter::PeekNext()
{

}

virtual CString CFormatter::NextString(int length)
{
  char* sz = new char[length+1];
  fmt_pfsInput->Read(sz, length);
  sz[length] = '\0';
  CString ret(sz);
  delete[] sz;
  return ret;
}

virtual CString CFormatter::PeekNextString(int length)
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
