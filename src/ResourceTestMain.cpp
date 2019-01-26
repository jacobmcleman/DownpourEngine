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
    bool AquireInternal() override
    {
      std::cout << "Loaded: " << *ID << std::endl;
      return true;
    }

    bool ReleaseInternal() override
    {
      std::cout << "Unloaded: " << *ID << std::endl;
      return true;
    }
};

int main(int argc, char** argv)
{
  TestResource tr1("test1");
  TestResource tr2("test2");

  tr1.Aquire();
  tr1.Release();

  return 0;
}