
int main()
{
    return(0);
}
namespace nsa
{
    void Foo(){}

    namespace nsa_a
    {
        void Foo();
    }
}

namespace nsb
{
    void Foo(){}
    void Bar(){}
    void Fishi(){}
}

namespace nsa
{
    void AnotherFunc(){}
}

void A()
{
    nsa::Foo();
    using nsb::Foo;
    Foo();
}

using namespace nsa;
using namespace nsb;
namespace nsaaa=nsa::nsa_a;

void B()
{
    nsaaa::Foo();
    
}