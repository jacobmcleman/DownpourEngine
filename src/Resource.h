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
      bool GetIsLoaded() const
      {
        return hasLoaded_;
      }

      /*
        Get if the most recent load operation failed
        Will be false until it has actually tried to load for the first time
      */
      bool HasLoadFailed() const
      {
        return loadFailed_;
      }

    public:
      Resource(const Identifier& aID) :
        IsLoaded(this), LoadFailed(this),
        ID(this),
        identifier_(aID)
      {
        hasLoaded_ = false;
        loadFailed_ = false;
      }

      void Load(std::vector<byte>&& aBytes)
      {
        hasLoaded_ = this->LoadInternal(std::move(aBytes));
        loadFailed_ = !hasLoaded_;
      }

      void Unload()
      {
        hasLoaded_ = !(this->UnloadInternal());
      }

      ReadOnlyProperty<bool, Resource, &Resource::GetIsLoaded> IsLoaded;
      ReadOnlyProperty<bool, Resource, &Resource::HasLoadFailed> LoadFailed;
      ReadOnlyProperty<Identifier, Resource, &Resource::GetIdentifier> ID; 

    private:
      std::atomic_bool hasLoaded_;
      std::atomic_bool loadFailed_;
      const Identifier identifier_;
  };
}
#endif