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
   * Identifier for the language (eg. what to put at the "-l=language" argument)
   */
  CString m_strID;
};

/**
 * Array of the available language definitions.
 */
static SLanguageDefinition g_aLanguageDefinitions[] = {
  { "HTML", "html" },
};

UFMT_NS_END;

#endif
