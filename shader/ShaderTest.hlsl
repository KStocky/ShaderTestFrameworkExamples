#include "/MyTests/ShaderHeader.hlsli"

#include "/Test/STF/ShaderTestFramework.hlsli"

[numthreads(1, 1, 1)]
void ThisTestShouldPass()
{
    ASSERT(AreEqual, Identity(42), 42);
}
                        
[numthreads(1, 1, 1)]
void ThisTestShouldFail()
{
    ASSERT(Fail);
}
