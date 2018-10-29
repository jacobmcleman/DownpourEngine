#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#import <atomic>
#import <vector>

#import "BaseTypes.h"
#import "Property.h"

namespace UnnamedEngine
{
  template<typename Identifier>
  class Resource
  {
    protected:
      /*
        Overload these with behavior for your resource type

        Return true if requested operation succeeded, false otherwise
      */
      virtual bool LoadInternal(std::vector<Types::byte>&& aBytes) = 0;
      virtual bool UnloadInternal() = 0;

    public:
      Resource(const Identifier& aID) :
        identifier_(aID),
        hasLoaded_(false)
      {
      }

      void Load(std::vector<Types::byte>&& aBytes)
      {
        hasLoaded_ = this->LoadInternal();
      }

      void Unload()
      {
        hasLoaded_ = !(this->UnloadInternal());
      }

      Property<bool, Resource, GetIsLoaded> IsLoaded;

    protected:
      const Identifier& GetIdentifier() const;
      {
        return identifier_;
      }

      bool GetIsLoaded() const
      {
        return hasLoaded_;
      }

    private:
      std::atomic_bool hasLoaded_;
      const Identifier identifier_;
  }
}
#endif