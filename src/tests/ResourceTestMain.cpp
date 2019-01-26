#include "Resource.h"
#include "BaseTypes.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <iostream>

using namespace Downpour;
using namespace Downpour::Types;

class TestResource1 : public Resource<std::string>
{
  public:
    TestResource1(const std::string& id) : Resource<std::string>(id) {}

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

class TestResource2 : public Resource<int>
{
  public:
    TestResource2(int id) : Resource<int>(id) {}

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

TEST(BasicResource, TestResource_StringID)
{
  TestResource1 tr("test1");
  EXPECT_EQ(*tr.ID, "test1");
}

TEST(BasicResource, TestResource_ID)
{
  TestResource2 tr(123);
  EXPECT_EQ(*tr.ID, 123);
}

TEST(BasicResource, TestResource_Aquire)
{
  TestResource1 tr("test1");

  EXPECT_FALSE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");
  
  tr.Aquire();

  EXPECT_TRUE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");
}

TEST(BasicResource, TestResource_AquireRelease)
{
  TestResource1 tr("test1");

  EXPECT_FALSE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");
  
  tr.Aquire();

  EXPECT_TRUE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");

  tr.Release();

  EXPECT_FALSE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");
}

TEST(BasicResource, TestResource_Release)
{
  TestResource1 tr("test1");

  EXPECT_FALSE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");
  
  tr.Release();

  EXPECT_FALSE(*tr.Ready);
  EXPECT_EQ(*tr.ID, "test1");
}

int main(int argc, char**argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}