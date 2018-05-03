To use jrtplib and jthread in another project, you must then do the
following:
- in the project settings, add the include directory
  c:\local\include to the list of include directories (for debug and
  release builds)
- in the project settings, add c:\local\lib to the list of library
  directories.
- for the release version, add jrtplib.lib, jthread.lib and
  ws2_32.lib to the list of libraries
- for the debug version, add jrtplib_d.lib, jthread_d.lib and
  ws2_32.lib to the list of libraries.

In your program files, include a jrtplib header like this:
#include <jrtplib3/rtpsession.h>
and a jthread header like this:
#include <jthread/jthread.h>