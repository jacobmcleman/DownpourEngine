#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <atomic>
#include <vector>

#include "BaseTypes.h"
#include "Property.h"

namespace Downpour
{
  using namespace Types;
  template<typename Identifier>
  class Resource
  {
    protected:
      /*
        Overload these with behavior for your resource type

        Return true if requested operation succeeded, false otherwise
      */
      virtual bool AquireInternal() = 0;
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
      bool HasAquireFailed() const
      {
        return hasAttemptedAquire_ && !ready_;
      }

    public:

      /*
        Base constructor for all resource types
      */
      Resource(const Identifier& aID) :
        Ready(this), AquireFailed(this),
        ID(this),
        identifier_(aID),
        hasAttemptedAquire_(false),
        ready_(false)
      {
      }

      void Aquire()
      {
        hasAttemptedAquire_ = true;
        ready_ = this->AquireInternal();
      }

      void Release()
      {
        ready_ = !(this->ReleaseInternal());
        hasAttemptedAquire_= ready_.load();
      }

      ReadOnlyProperty<bool, Resource, &Resource::GetIsReady> Ready;
      ReadOnlyProperty<bool, Resource, &Resource::HasAquireFailed> AquireFailed;
      ReadOnlyProperty<Identifier, Resource, &Resource::GetIdentifier> ID; 

    private:
      std::atomic_bool hasAttemptedAquire_;
      std::atomic_bool ready_;
      const Identifier identifier_;
  };
}
#endif