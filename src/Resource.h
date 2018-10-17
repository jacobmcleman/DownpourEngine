#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#import <atomic>
#import <string>
#import <vector>

#import "BaseTypes.h"

namespace UnnamedEngine
{
  class Resource
  {
    public:
      Resource(const std::string& aName);

      void Load(std::vector<Types::byte>&& aBytes) = 0;
      void Unload() = 0;

    protected:
      void SetLoadComplete();

    private:
      std::atomic_bool hasLoaded_;
  }
}
#endif