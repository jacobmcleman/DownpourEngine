#ifndef _RESOURCE_HANDLE_H
#define _RESOURCE_HANDLE_H

#include "utils/Defer.h"

namespace Downpour
{

class Aquirable
{
  public:
    template<typename T>
    friend class ResourceHandle;

  protected:
    virtual void OnHandleAcquired() = 0;
    virtual void OnHandleReleased() = 0;
};

template<typename ResourceType>
class ResourceHandle
{
public:
  explicit ResourceHandle(ResourceType* handleTo) : pointer_(handleTo)
  {
    if(pointer_ != nullptr) AcquireHandle();
  }

  ~ResourceHandle()
  {
    if(pointer_ != nullptr) ReleaseHandle();
  }

  ResourceHandle& operator=(ResourceType* rhs) 
  {
    if(pointer_ != nullptr) ReleaseHandle();
    pointer_ = rhs;
    if(pointer_ != nullptr) AcquireHandle();

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

  void AcquireHandle() { static_cast<Aquirable*>(pointer_)->OnHandleAcquired(); }
  void ReleaseHandle() { static_cast<Aquirable*>(pointer_)->OnHandleReleased(); }
};
}

#endif
