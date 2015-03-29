/**
 * Ultimate-Formatter is licensed under the GNU GPL v2.
 * Please see the LICENSE file for more information.
 *
 * (c) Christiaan de Die <contact@techwolf12.nl>
 * (c) Angelo Geels <spansjh@gmail.com>
 */

#include "StdH.h"

#include "UFMT.h"

int main(int argc, char* argv[])
{
  {
    UFMT::CUltimateFormatter ufmt;
    ufmt.Main(argc, argv);
  }

#if _MSC_VER && DEBUG
  getchar();
#endif

  return 0;
}
