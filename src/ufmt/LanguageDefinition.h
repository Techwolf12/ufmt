/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#ifndef UFMT_LANGUAGE_H_INCLUDED
#define UFMT_LANGUAGE_H_INCLUDED

#include "StdH.h"

#include "Formatter.h"
#include "Formatters/Html.h"

UFMT_NS_BEGIN;

/**
 * Language definition structure.
 */
struct SLanguageDefinition
{
  /**
   * Display name of the language.
   */
  CString m_strName;

  /**
   * Identifier for the language. (eg. what to put at the "--lang=language" argument)
   */
  CString m_strID;

  /**
   * File extensions for the language for automatic detection, seperated by a semicolon. (;)
   */
  CString m_strExtension;

  /**
   * The formatter object to use for formatting files of this language.
   */
  CFormatter* m_pFormatter;
};

/**
 * Array of the available language definitions.
 */
static SLanguageDefinition g_aLanguageDefinitions[] = {
  { "HTML", "html", "html;htm", new CHtmlFormatter() },
};

UFMT_NS_END;

#endif
