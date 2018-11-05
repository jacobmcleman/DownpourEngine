
namespace Downpour
{
  template<
    typename T, 
    class OwnerClass, 
    const T&(OwnerClass::* AccessorFunc)() const, 
    void (OwnerClass::* MutatorFunc)(const T&)>
  class Property
  {
    public:
      Property(OwnerClass* aOwner) : owner_(*aOwner) {}

      operator T() const { return (owner_.*AccessorFunc)(); }
      Property& operator=(const T& value) { (owner_.*MutatorFunc)(value); return *this; }

    private:
      OwnerClass& owner_;
  };

  template<
    typename T, 
    class OwnerClass, 
    const T&(OwnerClass::* AccessorFunc)() const>
  class ReadOnlyProperty
  {
    public:
      ReadOnlyProperty(OwnerClass* aOwner) : owner_(*aOwner) {}

      operator T() const { return (owner_.*AccessorFunc)(); }

    private:
      OwnerClass& owner_;
  };
}