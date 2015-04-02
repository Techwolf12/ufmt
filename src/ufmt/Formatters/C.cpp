/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "../StdH.h"

#include "C.h"

#include "../UFMT.h"

UFMT_NS_BEGIN;

SCBlock::SCBlock()
{
  m_iStartLine = 1;
}

CCFormatter::CCFormatter()
{
}

CCFormatter::~CCFormatter()
{
}

void CCFormatter::Start()
{
  m_pfsOutput = NULL;

  m_strLine = "";
  m_iIndent = 0;
  m_iIndentNext = 0;
}

void CCFormatter::Process(CFileStream &fsOutput)
{
  m_pfsOutput = &fsOutput;

  bool bInComment = false;
  bool bInCommentBlock = false;
  //bool bInString = false;

  CStackArray<SCBlock> aBlockStack;

  while(!fmt_pfsInput->AtEOF()) {
    char c = Next();

    // break if at EOF
    if(fmt_pfsInput->AtEOF()) {
      break;
    }

    if(c == '\n') {
      FlushLine();
    } else {
      m_strLine += c;
    }

    if(bInComment) {
      if(c == '\n') {
        bInComment = false;
      }
      continue;
    }

    if(bInCommentBlock) {
      if(c == '*' && PeekNext() == '/') {
        Next();
        bInCommentBlock = false;
      }
      continue;
    }

    if(c == '/') {
      if(PeekNext() == '/') {
        Next();
        bInComment = true;
      } else if(PeekNext() == '*') {
        Next();
        bInCommentBlock = true;
      }
      continue;
    }

    if(c == '{') {
      m_iIndentNext++;
      SCBlock &block = aBlockStack.Push();
      block.m_iStartLine = fmt_iLine;
      continue;
    }

    if(c == '}') {
      SCBlock &block = *aBlockStack.Pop();
      if(block.m_iStartLine != fmt_iLine) {
        m_iIndent--;
      }
      m_iIndentNext--;
      delete &block;
      continue;
    }
  }

  if(strlen(m_strLine) > 0) {
    FlushLine(fmt_pProgram->m_bEmptyLastLine);
  }
}

void CCFormatter::FlushLine(BOOL bNewLine)
{
  if(bNewLine) {
    m_pfsOutput->WriteLine(Indent(m_strLine, m_iIndent));
  } else {
    m_pfsOutput->WriteText(Indent(m_strLine, m_iIndent));
  }
  m_strLine = "";
  m_iIndent = m_iIndentNext;
}

UFMT_NS_END;
