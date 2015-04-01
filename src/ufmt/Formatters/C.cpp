/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "../StdH.h"

#include "C.h"

UFMT_NS_BEGIN;

CCFormatter::CCFormatter()
{
}

CCFormatter::~CCFormatter()
{
}

void CCFormatter::Start()
{
}

void CCFormatter::Process(CFileStream &fsOutput)
{
  bool bInComment = false;

  while(!fmt_pfsInput->AtEOF()) {
    char c = fmt_pfsInput->ReadChar();

    if(bInComment) {
      if(c == '\n') {
        bInComment = false;
        Addlines();
      }
      continue;
    }

    if(c == '/') {

    }
  }
}

UFMT_NS_END;
