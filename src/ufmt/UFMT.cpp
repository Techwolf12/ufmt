/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

#include "UFMT.h"
#include "LanguageDefinition.h"

UFMT_NS_BEGIN;

CUltimateFormatter::CUltimateFormatter()
{
}

CUltimateFormatter::~CUltimateFormatter()
{
}

void CUltimateFormatter::ProcessFile(const CString &strFilename)
{

}

void CUltimateFormatter::ShowHelp()
{
  printf("Ultimate-Formatter\n");
  printf("  Usage examples: ufmt <filename>\n");
  printf("                  ufmt <filename> [-l=language]\n");

  printf("\n");
  printf("  Available languages are:\n");

  for(int i=0; i<ARRAY_SIZE(g_aLanguageDefinitions); i++) {
    SLanguageDefinition &def = g_aLanguageDefinitions[i];
    printf("    * %s: -l=%s\n", def.m_strName, def.m_strID);
  }
}

void CUltimateFormatter::Main(int argc, char* argv[])
{
  if(argc > 1) {
    
  } else {
    ShowHelp();
  }
}

UFMT_NS_END;
