#ifndef _DEFER_H
#define _DEFER_H

#include "CompileTimeCounter.h"

namespace Deference
{
  class Deferrer
  {
  public:
    Deferrer(void (*toDefer)()) : deferred(toDefer) {}
    ~Deferrer() { deferred(); }

  private:
    void (*deferred)();
  };
}

#define DEFER(code) \
  struct Deferrer##COUNTER_READ(Deference::Deferrer) \
  {\
    code \
  }

#endif
