#include "Resource.h"
#include <string>
#include <vector>

namespace Downpour
{
  using AssetIdentifier = std::string;

  class Asset : public Resource<AssetIdentifier>
  {
    public:
    
    protected: 
      virtual bool LoadInternal(const std::vector<byte>& data) = 0;
      virtual bool SaveInternal(const std::vector<byte>& oldData, std::vector<byte>& newData);
      virtual bool UnloadInternal() = 0;

      bool AcquireInternal();
      bool ReleaseInternal();

    private:
      
  };

}