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

void CUltimateFormatter::HandleArgument(const CString &strKey, const CString &strValue)
{
  if(strKey == "--lang") {
    m_strLanguage = strValue;
  }

  if(strKey == "--stdout") {
    m_bStdout = TRUE;
  }
}

void CUltimateFormatter::ProcessFile(const CString &strFilename)
{
  if(m_iFileCount > 1) {
    printf("--- %s\n", strFilename);
  }


}

void CUltimateFormatter::ShowHelp()
{
  printf("Ultimate-Formatter\n");
  printf("  Usage examples:\n");
  printf("    ufmt <filename>\n");
  printf("    ufmt <filename> [--lang=language] [--stdout]\n");

  printf("\n");
  printf("  Available languages are:\n");

  for(int i=0; i<ARRAY_SIZE(g_aLanguageDefinitions); i++) {
    SLanguageDefinition &def = g_aLanguageDefinitions[i];
    printf("    * %s: -l=%s (*.%s)\n", def.m_strName, def.m_strID, def.m_strExtension);
  }

  printf("\n");
}

void CUltimateFormatter::Main(int argc, char* argv[])
{
  if(argc > 1) {
    CStackArray<CString> aFiles;

    for(int i=1; i<argc; i++) {
      CString strArg = argv[i];

      // Handle command line arguments
      if(strArg.StartsWith("--")) {
        CString strKey, strValue;

        // If it has a value (eg. "--a=b")
        if(strArg.Contains('=')) {
          CStackArray<CString> aParse;
          strArg.Split("=", aParse);

          strKey = aParse[0];
          strValue = aParse[1];

        // If it only has a key (eg. "--a")
        } else {
          strKey = strArg;
        }

        HandleArgument(strKey, strValue);
        continue;
      }

      // If it doesn't start with --, handle this as a filename
      aFiles.Push() = strArg;
    }

    // Remember how many files there are to be processed, this is useful for knowing if it's a single or multiple files (for stdout output, for example)
    m_iFileCount = aFiles.Count();

    // Process each file
    for(int i=0; i<aFiles.Count(); i++) {
      ProcessFile(aFiles[i]);
    }

  } else {
    // No command line parameters given, so show basic help
    ShowHelp();
  }
}

UFMT_NS_END;
