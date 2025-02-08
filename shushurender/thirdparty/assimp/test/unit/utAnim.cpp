/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2022, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/
#include "UnitTestPCH.h"

#include <assimp/anim.h>

using namespace Assimp;

class utAnim : public ::testing::Test {
    // empty
};

TEST_F( utAnim, aiVectorKeyCreationTest ) {
    aiVectorKey defaultConstTest;
    EXPECT_DOUBLE_EQ( 0.0, defaultConstTest.mTime );

    aiVector3D v( 1, 2, 3 );
    aiVectorKey constrWithValuesTest( 1, v );
    EXPECT_DOUBLE_EQ( 1.0, constrWithValuesTest.mTime );
    EXPECT_EQ( v, constrWithValuesTest.mValue );

    EXPECT_NE( defaultConstTest, constrWithValuesTest );
    EXPECT_TRUE( defaultConstTest != constrWithValuesTest );
    defaultConstTest.mTime = 1;
    constrWithValuesTest.mTime = 2;
    EXPECT_TRUE( defaultConstTest < constrWithValuesTest );
}

TEST_F( utAnim, aiQuatKeyTest ) {
    aiQuatKey defaultConstrTest;
    EXPECT_DOUBLE_EQ( 0.0, defaultConstrTest.mTime );

    aiQuaternion q;
    aiQuatKey constrWithValuesTest( 1.0, q );
    EXPECT_DOUBLE_EQ( 1.0, constrWithValuesTest.mTime );
    EXPECT_EQ( q, constrWithValuesTest.mValue );
}

TEST_F( utAnim, aiNodeAnimTest ) {
    bool ok( true );
    try {
        aiNodeAnim myAnim;
        EXPECT_EQ( aiAnimBehaviour_DEFAULT, myAnim.mPreState );
        EXPECT_EQ( aiAnimBehaviour_DEFAULT, myAnim.mPostState );
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( utAnim, aiMeshAnimTest ) {
    bool ok( true );
    try {
        aiMeshAnim myMeshAnim;
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}

TEST_F( utAnim, aiAnimationTest ) {
    bool ok( true );
    try {
        aiAnimation myAnimation;
    } catch ( ... ) {
        ok = false;
    }
    EXPECT_TRUE( ok );
}
