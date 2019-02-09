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
      ResourceManager()
      {
      }

      ~ResourceManager()
      {
        for(auto&& respair : resources)
        {
          respair.second->Release();
          delete respair.second;
        }
      }

      template<typename Resource_t>
      ResourceHandle<Resource_t> Request(const Identifier_t& identifier)
      {
        Resource_t* res;
        if(resources.count(identifier) > 0)
        {
          res = static_cast<Resource_t*>(resources[identifier]);
        }
        else
        {
          res = new Resource_t(identifier);
          resources[identifier] = res;
        }

        if(!res->Ready)
        {
          res->Acquire();
        }
        
        return ResourceHandle<Resource_t>(res);
      }

    private:
      std::unordered_map<Identifier_t, Resource<Identifier_t>*> resources;
  };

  template<typename Resource_t, typename Identifier_t>
  ResourceHandle<Resource_t> RequestResource(const Identifier_t& identifier)
  {
    return ResourceManager<Identifier_t>::GetInstance().template Request<Resource_t>(identifier);
  }

  template<typename Resource_t>
  ResourceHandle<Resource_t> RequestResource(const char* identifier)
  {
    return ResourceManager<std::string>::GetInstance().template Request<Resource_t>(identifier);
  }
}
#endif