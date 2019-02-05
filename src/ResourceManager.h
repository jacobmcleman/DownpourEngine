#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include <unordered_map>

#include "Resource.h"
#include "ResourceHandle.h"
#include "utils/Singleton.h"

namespace Downpour
{
  template<typename Identifier_t>
  class ResourceManager : public Singleton<ResourceManager<Identifier_t>>
  {
    public:
      ResourceManager();
      ~ResourceManager();

      template<typename Resource_t>
      ResourceHandle<Resource_t> Request(const Identifier_t& identifier)
      {
        return ResourceHandle<Resource_t>(resources[identifier]);
      }

    private:
      std::unordered_map<Identifier_t, Resource<Identifier_t>*> resources;
  };
}
#endif