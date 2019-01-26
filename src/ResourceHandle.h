#ifndef _RESOURCE_HANDLE_H
#define _RESOURCE_HANDLE_H

#include "utils/Defer.h"

namespace Downpour
{
template<typename ResourceType>
class ResourceHandle
{
public:
  explicit ResourceHandle(ResourceType* handleTo) : pointer_(handleTo)
  {
    if(pointer_ != nullptr) AquireHandle();
  }

  ~ResourceHandle()
  {
    if(pointer_ != nullptr) ReleaseHandle();
  }

  ResourceHandle& operator=(ResourceType* rhs) 
  {
    if(pointer_ != nullptr) ReleaseHandle();
    pointer_ = rhs;
    if(pointer_ != nullptr) AquireHandle();

    return *this;
  }

  ResourceHandle& operator=(const ResourceHandle& rhs) 
  {
    return (*this = rhs.pointer_);
  }

  /*
    All the operators needed to let this handle type pretend
    to be a resource pointer
  */
  ResourceType* operator->() const { return pointer_; }
  operator ResourceType*() const { return pointer_; };

private:
  ResourceType* pointer_;

  void AquireHandle() { static_cast<Resource<typename ResourceType::ID_Type>*>(pointer_)->OnHandleAquired(); }
  void ReleaseHandle() { static_cast<Resource<typename ResourceType::ID_Type>*>(pointer_)->OnHandleReleased(); }
};
}

#endif
