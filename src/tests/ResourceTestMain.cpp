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
  tr.Aquire();
  EXPECT_TRUE(*tr.Ready);
}

TEST(BasicResource, TestResource_AquireRelease)
{
  TestResource1 tr("test1");

  EXPECT_FALSE(*tr.Ready);
  tr.Aquire();
  EXPECT_TRUE(*tr.Ready);
  tr.Release();
  EXPECT_FALSE(*tr.Ready);
}

TEST(BasicResource, TestResource_Release)
{
  TestResource1 tr("test1");
  EXPECT_FALSE(*tr.Ready);
  tr.Release();
  EXPECT_FALSE(*tr.Ready);
}

TEST(ResourceHandles, Handle_Create)
{
  TestResource2 tr(27);
  ResourceHandle<TestResource2> tr_h(&tr);
  EXPECT_EQ(*(tr_h->ID), 27);
}

TEST(ResourceHandles, Handle_Reassign)
{
  TestResource2 tr1(27);
  TestResource2 tr2(12);

  ResourceHandle<TestResource2> tr_h(&tr1);
  tr_h = &tr2;

  EXPECT_EQ(*(tr_h->ID), 12);
}

TEST(ResourceHandles, Handle_DestroyLastReleases)
{
  TestResource2 tr(27);
  tr.Aquire();

  {
    ResourceHandle<TestResource2> tr_h(&tr);
    EXPECT_TRUE(*tr_h->Ready);
  }

  EXPECT_FALSE(*tr.Ready);
}

TEST(ResourceHandles, Handle_DestroyDoesntRelease)
{
  TestResource2 tr(27);
  tr.Aquire();

  ResourceHandle<TestResource2> tr_h1(&tr);
  EXPECT_TRUE(*tr_h1->Ready);

  {
    ResourceHandle<TestResource2> tr_h2(&tr);
    EXPECT_TRUE(*tr_h2->Ready);
  }

  EXPECT_TRUE(*tr_h1->Ready);
}

int main(int argc, char**argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}