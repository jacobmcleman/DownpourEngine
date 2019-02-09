#include "../Resource.h"
#include "../BaseTypes.h"
#include "../ResourceManager.h"
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
    bool AcquireInternal() override
    {
      //std::cout << "Loaded: " << *ID << std::endl;
      return true;
    }

    bool ReleaseInternal() override
    {
      //std::cout << "Unloaded: " << *ID << std::endl;
      return true;
    }
};

class TestResource2 : public Resource<int>
{
  public:
    TestResource2(int id) : Resource<int>(id) {}

  protected:
    bool AcquireInternal() override
    {
      //std::cout << "Loaded: " << *ID << std::endl;
      return true;
    }

    bool ReleaseInternal() override
    {
      //std::cout << "Unloaded: " << *ID << std::endl;
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

TEST(BasicResource, TestResource_Acquire)
{
  TestResource1 tr("test1");

  EXPECT_FALSE(*tr.Ready);
  tr.Acquire();
  EXPECT_TRUE(*tr.Ready);
}

TEST(BasicResource, TestResource_AcquireRelease)
{
  TestResource1 tr("test1");

  EXPECT_FALSE(*tr.Ready);
  tr.Acquire();
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
  tr.Acquire();

  {
    ResourceHandle<TestResource2> tr_h(&tr);
    EXPECT_TRUE(*tr_h->Ready);
  }

  EXPECT_FALSE(*tr.Ready);
}

TEST(ResourceHandles, Handle_DestroyDoesntRelease)
{
  TestResource2 tr(27);
  tr.Acquire();

  ResourceHandle<TestResource2> tr_h1(&tr);
  EXPECT_TRUE(*tr_h1->Ready);

  {
    ResourceHandle<TestResource2> tr_h2(&tr);
    EXPECT_TRUE(*tr_h2->Ready);
  }

  EXPECT_TRUE(*tr_h1->Ready);
}

TEST(ResourceManager, Manager_RequestResourceHasAcquired)
{
  ResourceHandle<TestResource1> tr1h = RequestResource<TestResource1>("test1");
  EXPECT_TRUE(*tr1h->Ready);
}

TEST(ResourceManager, Manager_RequestResourceSameIDSameResource)
{
  ResourceHandle<TestResource1> tr1h1 = RequestResource<TestResource1>("test1");
  TestResource1* tr1p1 = tr1h1;
  ResourceHandle<TestResource1> tr1h2 = RequestResource<TestResource1>("test1");
  TestResource1* tr1p2 = tr1h2;

  EXPECT_TRUE(tr1p1 == tr1p2);
}

int main(int argc, char**argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}