#ifndef _DEFER_H
#define _DEFER_H

#define DEFER(statement) \
  struct Deferrer \
  {\
    statement ; \
  }

#endif
