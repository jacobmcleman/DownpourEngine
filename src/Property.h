
namespace UnnamedEngine
{
  template<typename T, class OwnerClass, const T&(OwnerClass::* AccessorFunc)(), void (OwnerClass::* MutatorFunc)(const T&)>
  class Property
  {
    public:
      Property(OwnerClass& aOwner) : owner_(aOwner) {}

      operator T() const { return owner.AccessorFunc(); }
      Property& operator=(const T& value) { owner.MutatorFunc(value); return *this; }

    private:
      OwnerClass& owner_;
  };

  template<typename T, class OwnerClass, const T&(OwnerClass::* AccessorFunc)()>
  class Property
  {
    public:
      Property(OwnerClass& aOwner) : owner_(aOwner) {}

      operator T() const { return owner.AccessorFunc(); }

    private:
      OwnerClass& owner_;
  };
}