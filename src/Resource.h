#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <atomic>
#include <vector>

#include "BaseTypes.h"
#include "ResourceHandle.h"
#include "utils/Property.h"

namespace Downpour
{
  using namespace Types;

  template<typename Identifier>
  class Resource : public Aquirable
  {
    protected:
      /*
        Overload these with behavior for your resource type

        Return true if requested operation succeeded, false otherwise
      */
      virtual bool AcquireInternal() = 0;
      virtual bool ReleaseInternal() = 0;

    private:
      /*
        Get the identifier that was used to request this resource
      */
      Identifier GetIdentifier() const
      {
        return identifier_;
      }

      /*
        Get if a successful load operation happened
      */      
      bool GetIsReady() const
      {
        return ready_;
      }

      /*
        Get if the most recent load operation failed
        Will be false until it has actually tried to load for the first time
      */
      bool HasAcquireFailed() const
      {
        return hasAttemptedAcquire_ && !ready_;
      }

      /*
        Get/Set if this resource should be unloaded
        upon the final handle to it being released
      */
     bool GetReleaseUnused() const { return releaseOnUnused_; }
     void SetReleaseUnused(const bool& shouldRelease) { releaseOnUnused_ = shouldRelease; }

    public:
      using ID_Type = Identifier;

      /*
        Base constructor for all resource types
      */
      Resource(const Identifier& aID, bool releaseOnUnused = true) :
        Ready(this), AcquireFailed(this),
        ID(this),
        ReleaseOnUnused(this),
        hasAttemptedAcquire_(false),
        ready_(false),
        releaseOnUnused_(releaseOnUnused),
        identifier_(aID),
        users_(0)
      {
      }

      virtual ~Resource() {}

      void Acquire()
      {
        if(!ready_)
        {
          hasAttemptedAcquire_ = true;
          ready_ = this->AcquireInternal();
        }
      }

      void Release()
      {
        if(ready_)
        {
          ready_ = !(this->ReleaseInternal());
          hasAttemptedAcquire_= ready_.load();
        }
      }

      ReadOnlyProperty<bool, Resource, &Resource::GetIsReady> Ready;
      ReadOnlyProperty<bool, Resource, &Resource::HasAcquireFailed> AcquireFailed;
      ReadOnlyProperty<Identifier, Resource, &Resource::GetIdentifier> ID; 

      Property<bool, Resource, &Resource::GetReleaseUnused, &Resource::SetReleaseUnused> ReleaseOnUnused;

    protected:
      void OnHandleAcquired() { ++users_; }
      void OnHandleReleased() 
      { 
        --users_;

        if(releaseOnUnused_ && users_ == 0)
        {
          Release();
        }
      }

    private:
      std::atomic_bool hasAttemptedAcquire_;
      std::atomic_bool ready_;
      std::atomic_bool releaseOnUnused_;

      const Identifier identifier_;

      std::atomic_uint users_;
  };
}
#endif
