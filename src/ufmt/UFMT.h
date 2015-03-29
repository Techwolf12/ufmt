/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

#include "LanguageDefinition.h"

UFMT_NS_BEGIN;

/**
 * The actual application.
 */
class CUltimateFormatter
{
public:
  /**
   * Whether to output to stdout instead of overwrite the file.
   * Toggled with --stdout.
   */
  BOOL m_bStdout;

  /**
   * Whether to be verbose or not.
   * Toggled with --verbose.
   */
  BOOL m_bVerbose;

  /**
   * Explicit language identifier. If empty, ufmt will guess the language based on file extension.
   * Set with --lang=...
   */
  CString m_strLanguage;

  /**
   * How many files are to be processed.
   */
  int m_iFileCount;

public:
  CUltimateFormatter();
  virtual ~CUltimateFormatter();

  /**
   * Whether or not the printing is verbose.
   * This only returns true if --verbose is given.
   */
  virtual BOOL IsVerbose();

  /**
   * Whether or not printing verbose information is adviced.
   * This always returns true if --verbose is given.
   */
  virtual BOOL ShouldPrint();

  /**
   * Handle a command line argument.
   * For "--a=b", the key is "--a" and the value is "b".
   * For "--a", the key is "--a" and the value is an empty string.
   */
  virtual void HandleArgument(const CString &strKey, const CString &strValue);

  /**
   * Find the language definition from the given ID.
   */
  virtual SLanguageDefinition* GetDefinition(const CString &strID);

  /**
   * Start processing a file based on the class fields set.
   */
  virtual void ProcessFile(const CFilename &fnm);

  /**
   * Show the basic help usage text.
   */
  virtual void ShowHelp();

  /**
   * Application entry point.
   */
  virtual void Main(int argc, char* argv[]);
};

UFMT_NS_END;
