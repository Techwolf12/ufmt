/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

UFMT_NS_BEGIN;

/**
 * The actual application.
 */
class CUltimateFormatter
{
public:
  CUltimateFormatter();
  virtual ~CUltimateFormatter();

  /**
   * Start processing a file based on the class fields set.
   */
  virtual void ProcessFile(const CString &strFilename);

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
