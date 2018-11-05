#include "Resource.h"
#include "BaseTypes.h"

#include <string>
#include <vector>
#include <iostream>

using namespace Downpour;
using namespace Downpour::Types;

class TestResource : public Resource<std::string>
{
  public:
    TestResource(const std::string& id) : Resource<std::string>(id) {}

  protected:
    bool LoadInternal(std::vector<byte>&& aBytes) override
    {
      if(aBytes.empty()) return false;

      std::cout << GetIdentifier() << ": ";
      for(byte b : aBytes)
      {
        std::cout << static_cast<char>(b);
      }
      std::cout << std::endl;
      return true;
    }

    bool UnloadInternal() override
    {
      std::cout << "Unloaded" << std::endl;
      return true;
    }
};

int main(int argc, char** argv)
{
  TestResource tr1("test1");
  TestResource tr2("test2");

  std::string toReq = "butts lol";
  std::vector<byte> bytes(toReq.begin(), toReq.end());
  tr1.Load(std::move(bytes));
  tr1.Unload();

  tr2.Load(std::vector<byte>());
  tr2.Unload();
}