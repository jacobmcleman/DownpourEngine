#include "Resource.h"

#include <iostream>

using namespace UnnamedEngine;
using namespace UnnamedEngine::Types;

class TestResource : public Resource<std::string>
{
  public:
    TestResource(const std::string& id) : Resource<std::string>(id) {}

  protected:
    void LoadInternal(std::vector<byte>&& aBytes) override
    {
      std::cout << GetIdentifier() << ": ";
      for(byte : aBytes)
      {
        std::cout << static_cast<char>(byte);
      }
      std::cout << std::endl;
      return true;
    }

    void UnloadInternal() override
    {
      std::cout << "Unloaded" << std::endl;
      return true;
    }
}

int main(int argc, char** argv)
{
  TestResource tr("test");

  std::string toReq = "butts lol";

  tr.load(toReq);
}