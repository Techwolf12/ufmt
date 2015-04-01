/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die le Clercq <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

#include "UFMT.h"
#include "LanguageDefinition.h"
#include "Formatter.h"

UFMT_NS_BEGIN;

CUltimateFormatter::CUltimateFormatter()
{
}

CUltimateFormatter::~CUltimateFormatter()
{
}

BOOL CUltimateFormatter::IsVerbose()
{
  return m_bVerbose;
}

BOOL CUltimateFormatter::ShouldPrint()
{
  return m_bVerbose || !m_bStdout || m_iFileCount > 1;
}

void CUltimateFormatter::HandleArgument(const CString &strKey, const CString &strValue)
{
  if(strKey == "--lang") {
    if(GetDefinition(strValue) == NULL) {
      printf("ERROR: Language '%s' doesn't exist!\n", (const char*)strValue);
      return;
    }
    m_strLanguage = strValue;
    return;
  }

  if(strKey == "--stdout") {
    m_bStdout = TRUE;
    return;
  }

  if(strKey == "--verbose") {
    m_bVerbose = TRUE;
    return;
  }
}

SLanguageDefinition* CUltimateFormatter::GetDefinition(const CString &strID)
{
  for(int i=0; i<ARRAY_SIZE(g_aLanguageDefinitions); i++) {
    SLanguageDefinition &def = g_aLanguageDefinitions[i];
    if(def.m_strID == strID) {
      return &def;
    }
  }
  return NULL;
}

void CUltimateFormatter::ProcessFile(const CFilename &fnm)
{
  if(!m_bStdout || m_iFileCount > 1) {
    printf("--- %s\n", (const char*)fnm);
  }

  // Find out which formatter to use
  SLanguageDefinition* pLanguage = NULL;

  // If there's no explicit language given, attempt to manually find it by file extension
  if(m_strLanguage == "") {
    CString strExtension = fnm.Extension();

    for(int i=0; i<ARRAY_SIZE(g_aLanguageDefinitions); i++) {
      SLanguageDefinition &def = g_aLanguageDefinitions[i];

      CStackArray<CString> aExtensions;
      def.m_strExtension.Split(";", aExtensions);

      if(aExtensions.Contains(strExtension)) {
        // Language has been found!
        pLanguage = &def;
        break;
      }
    }
  } else {
    pLanguage = GetDefinition(m_strLanguage);
  }

  if(pLanguage == NULL) {
    printf("ERROR: No language found for %s!\n", (const char*)fnm);
    return;
  }

  if(pLanguage->m_pFormatter == NULL) {
    printf("ERROR: Language %s doesn't have a formatter!\n", (const char*)pLanguage->m_strID);
    return;
  }

  CFileStream* pfsInput = new CFileStream();
  if(!pfsInput->Open(fnm, "r")) {
    printf("ERROR: Couldn't open file %s for input!\n", (const char*)fnm);
    return;
  }
  pLanguage->m_pFormatter->fmt_pfsInput = pfsInput;
  pLanguage->m_pFormatter->Start();

  CFileStream fsOutput;
  if(m_bStdout) {
    fsOutput.OpenStdout();
  } else {
    if(!fsOutput.Open(fnm, "w")) {
      printf("ERROR: Couldn't open file %s for output!\n", (const char*)fnm);
      return;
    }
  }
  pLanguage->m_pFormatter->Process(fsOutput);
}

void CUltimateFormatter::ShowHelp()
{
  printf("Ultimate-Formatter " UFMT_VERSION "\n");
  printf("  (c) Christiaan de Die le Clercq <contact@techwolf12.nl>\n");
  printf("  (c) Angelo Geels <spansjh@gmail.com>\n");
  printf("\n");

  // Because people forget to back up their shit
  printf("  \"version control is your own personal backup\" -authors\n");
  printf("\n");

  printf("  Usage examples:\n");
  printf("    ufmt <filename>\n");
  printf("    ufmt <filename> [--recursive] [--lang=language] [--stdout]\n");

  printf("\n");
  printf("  Available languages are:\n");

  for(int i=0; i<ARRAY_SIZE(g_aLanguageDefinitions); i++) {
    SLanguageDefinition &def = g_aLanguageDefinitions[i];

    CStackArray<CString> aExtensions;
    def.m_strExtension.Split(";", aExtensions);

    CString strFormats;
    for(int j=0; j<aExtensions.Count(); j++) {
      if(j == 0) {
        strFormats = "*." + aExtensions[j];
      } else {
        strFormats += ", *." + aExtensions[j];
      }
    }

    printf("    * %s: --lang=%s (%s)\n", (const char*)def.m_strName, (const char*)def.m_strID, (const char*)strFormats);
  }

  printf("\n");
}

void CUltimateFormatter::Main(int argc, char* argv[])
{
  if(argc > 1) {
    CStackArray<CFilename> aFiles;

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
