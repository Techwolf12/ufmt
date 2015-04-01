/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "../StdH.h"

#include "Html.h"

UFMT_NS_BEGIN;

CHtmlFormatter::CHtmlFormatter()
{
}

CHtmlFormatter::~CHtmlFormatter()
{
}

void CHtmlFormatter::Start()
{
}

void CHtmlFormatter::Process(CFileStream &fsOutput)
{
  while(!fmt_pfsInput->AtEOF()) {
    char c = fmt_pfsInput->ReadChar();
    if(c == '<') {
      HandleTag(fsOutput);
    }
  }
}

void CHtmlFormatter::HandleTag(CFileStream &fsOutput)
{
  bool bInTag = true;
  bool bInTagString = false;
  bool bInEndTag = false;

  while(!fmt_pfsInput->AtEOF()) {
    c = fmt_pfsInput->ReadChar();
    if(bInTag) {
      if(bInTagString) {
        if(c == '"') {
          bInTagString = false;
        }
        continue;
      }

      if(c == '"') {
        bInTagString = true;
      }
      continue;
    }

    if(c == '<') {
      bInEndTag = fmt_pfsInput->ReadChar() == '/';
    }
  }
}

UFMT_NS_END;
