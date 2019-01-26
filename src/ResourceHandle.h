#ifndef _RESOURCE_HANDLE_H
#define _RESOURCE_HANDLE_H

#include "Resource.h"
#include "utils/Defer.h"

namespace Downpour
{
template<typename ResourceType>
class ResourceHandle
{
public:
  explicit ResourceHandle(ResourceType* handleTo) : pointer(handleTo)
  {
    pointer_->OnHandleAquired();
  }

  ~ResourceHandle()
  {
    pointer_->OnHandleReleased();;
  }

private:
  ResourceType* pointer_;
};
}

#endif
