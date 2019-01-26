#ifndef _SINGLETON_H
#define _SINGLETON_H

namespace Downpour
{
  // Forward declared for exception class to use
  template<typename T>
  class Singleton;

  /*
    Exception thrown when an instance of a Singleton 
    class is created
  */
  template<typename T>
  struct SingletonException
  {
    Singleton<T>* existingInstance;
  };

  /*
    Class to simplify and enforce usage
    of the singleton pattern
  */
  template<typename T>
  class Singleton
  {
    public:
      Singleton()
      {
        if(hasCreated)
        {
          SingletonException<T> e;
          e.existingInstance = &instance;
          throw e;
        }
      }

      static T& GetInstance() { return instance; }

    private:
      static Singleton instance;
      static bool hasCreated;
  };
}
#endif