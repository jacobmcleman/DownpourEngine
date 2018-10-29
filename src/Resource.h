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
      virtual bool LoadInternal(std::vector<byte>&& aBytes) = 0;
      virtual bool UnloadInternal() = 0;

      const Identifier& GetIdentifier() const
      {
        return identifier_;
      }

      const bool& GetIsLoaded() const
      {
        static bool toRet = hasLoaded_;
        return toRet;
      }

    public:
      Resource(const Identifier& aID) :
        IsLoaded(this),
        ID(this),
        identifier_(aID)
      {
        hasLoaded_ = false;
      }

      void Load(std::vector<byte>&& aBytes)
      {
        hasLoaded_ = this->LoadInternal(std::move(aBytes));
      }

      void Unload()
      {
        hasLoaded_ = !(this->UnloadInternal());
      }

      ReadOnlyProperty<bool, Resource, &Resource::GetIsLoaded> IsLoaded;
      ReadOnlyProperty<Identifier, Resource, &Resource::GetIdentifier> ID; 

    private:
      std::atomic_bool hasLoaded_;
      const Identifier identifier_;
  };
}
#endif