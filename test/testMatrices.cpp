#include "catch.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/epsilon.hpp"

#include "tracer/geometry/transforms.hpp"
#include "tracer/geometry/primitives.hpp"

#include "tracer/math.hpp"

using namespace tracer;
using namespace geometry;

template<class T>
void logVector(T vect)
{
    for (int j = 0; j < vect.length(); j++)
    {
        std::cout << vect[j] << " ";
    }
    std::cout << std::endl;
}

//NOTE: GLM USES COLUMN MAJOR MATRICES, WHICH IS EASIER FOR ACCESSING COLUMNS IN GRAPHICS MEMORY. HOWEVER THE BOOK USES ROW MAJOR MATRICES
template <class T>
bool matricesEqual(T& matrixA, T& matrixB)
{
    if (matrixA.length() == matrixB.length())
    {
        auto equal = true;
        for (int j = 0; j < matrixA.length(); j++)
        {
            if (!glm::all(glm::equal(matrixA[j], matrixB[j])))
            {
                equal = false;
            }
        }
        return equal;
    }
    else return false;
}

template <class T>
bool vectorsEqual(T& vecA, T& vecB)
{
    return glm::all(glm::epsilonEqual(vecA, vecB, glm::vec4(.000001f)));
}
SCENARIO("Constructing and Inspecting a 4x4 Matrix", "[matrices]")
{
    GIVEN("Creating a 4x4 Matrix with the following values ")
    {

        auto testMatrix = glm::mat4(
            1.0, 2.0, 3.0, 4.0,
            5.5, 6.5, 7.5, 8.5,
            9.0, 10.0, 11.0, 12.0
            , 13.5, 14.5, 15.5, 16.5);
        THEN("Indexing Matrix results in the correct values")
        {
            int column[] = { 0,3,0,2,2,0,2 };
            int row[] = { 0,0,1,1,2,3,3 };
            float testValue[] = { 1,4,5.5,7.5,11,13.5,15.5 };
            for (int j = 0; j < 7; j++)
            {
                REQUIRE(testMatrix[row[j]][column[j]] == testValue[j]);
            }
        }
        AND_THEN("Replacing the second row with all ones causes matrix[1][x]==1")
        {
            testMatrix[1] = glm::vec4(1.0);
            for (int j=0; j < 4; j++)
            {
            
                REQUIRE(testMatrix[1][j] == 1);
            }
        }
    }
}

SCENARIO("Matrix Equality", "[matrices]")
{
    GIVEN("Two Identical Matrices declared from a memory pointer")
    {
        float matrixValues[] = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 }; //values to be stored in array
        // making two new identical arrays
        auto matrixA = glm::make_mat4(matrixValues);
        auto matrixB = glm::make_mat4(matrixValues);
        THEN("Matrices are equal")
        {
       
            REQUIRE(matricesEqual(matrixA,matrixB));
            AND_THEN("Changing a value in Matrix A does not change a value in Matrix B")
            {
                matrixA[1][3] = 0;
                REQUIRE(matrixA[1][3] != matrixB[1][3]);
            }
        }
    }
}

SCENARIO("Matrix Multiplication", "[matrices]")
{
    GIVEN("Two Matrices")
    {
        // making two matrices
        auto matrixA = glm::transpose(glm::mat4(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2));
        auto matrixB = glm::transpose(glm::mat4(
            -2, 1, 2, 3,
            3, 2, 1, -1,
            4, 3, 6, 5,
            1, 2, 7, 8
        ));
        // Make the matrix of the expected result
        auto expectedProductMatrix = glm::transpose(glm::mat4(
            20, 22, 50, 48,
            44, 54, 114, 108,
            40, 58, 110, 102,
            16, 26, 46, 42
        ));
        THEN("Matrices Multiply in expected row-column format")
        {
            auto actualProductMatrix = matrixA * matrixB;
            for (int row = 0; row < 4; row++)
            {
                for (int column = 0; column < 4; column++)
                {
                    REQUIRE(expectedProductMatrix[row][column] == actualProductMatrix[row][column]);
                }
            }

        }
        THEN("Multipliying a Matrix by a vector results in a vector")
        {
            auto tuple = glm::vec4(1, 2, 3, 1);
            REQUIRE(glm::all(glm::equal(matrixA * tuple,glm::vec4(18, 46, 52, 24))));
        }
        THEN("Mutiplying a Matrix by a Scaler scales each element")
        {
            auto expectedMatrix = glm::mat4(
                2, 10, 18, 10, 
                4, 12, 16, 8, 
                6, 14, 14, 6, 
                8, 16, 12, 4);
            auto productMatrix =  matrixA*2.0f;
            REQUIRE(matricesEqual(productMatrix, expectedMatrix));
        }
    }
}

SCENARIO("Translation Matrix","[matrices]")
{
    GIVEN("Two Translation Matrices constructed with overloaded definitions")
    {
        auto testMatA = translationMatrix(3, 3, 3);
        auto testMatB = translationMatrix(3);
        THEN("They should equate to the same matrix")
        {
            REQUIRE(matricesEqual(testMatA, testMatB));
        }
    }
    GIVEN("Point at the origin")
    {
        auto position = point(0, 0, 0);
        THEN("Translating the point by 3 in every direction results in a point at (3,3,3)")
        {
            auto tMat = translationMatrix(3, 3, 3);
            position = translate(position, tMat);
            auto properTranslation = glm::all(glm::equal(position, point(3, 3, 3)));
            REQUIRE(properTranslation);
            AND_THEN("translating by -3 in every direciton resets to the origin")
            {
                auto tMat = translationMatrix(-3, -3, -3);
                position = translate(position, tMat);
                auto properTranslation = glm::all(glm::equal(position, point(0,0,0)));
                REQUIRE(properTranslation);
            }
        }
    }
    GIVEN("A vector pointing towards (1,1,1)")
    {
        auto testVector = vector(1, 1, 1);
        THEN("Translating the vector results in the same vector")
        {
            auto properTranslation = glm::all(glm::equal(testVector, translate(testVector, translationMatrix(3, 5, -1))));
            REQUIRE(properTranslation);
        }
    }
}

SCENARIO("Scaling Matrix", "[matrices]")
{
    GIVEN("Two Scaling Matrices constructed with overloaded definitions")
    {
        auto testMatA = scaleMatrix(3, 3, 3);
        auto testMatB = scaleMatrix(3);
        THEN("They should equate to the same matrix")
        {
            REQUIRE(matricesEqual(testMatA, testMatB));
        }
    }
    GIVEN("A point (1,-1,3) and vector <1,-1,3>")
    {
        auto testPoint = point(1, -1, 3);
        auto testVector = vector(1, -1, 3);
        THEN("Scaling The vector by 2 in each dimension results in new points and vectors")
        {
            auto expectedPoint = point(2, -2, 6);
            auto expectedVector = vector(2, -2, 6);
            auto scaleMat = scaleMatrix(2, 2, 2);
            REQUIRE(vectorsEqual(scale(testPoint, scaleMat), expectedPoint));
            REQUIRE(vectorsEqual(scale(testVector, scaleMat), expectedVector));
            AND_THEN("The vector is not equal to the point")
            {
                REQUIRE(!vectorsEqual(scale(testPoint, scaleMat), scale(testVector, scaleMat)));
            }
        }
    }
}

SCENARIO("Cross Product Matrix" "[matrices]")
{
    GIVEN("A vector <1,2,3>")
    {
        auto testVec = vector(1, 2, 3);
        THEN("The cross product matrix should generate correctly")
        {
            auto expectedMatrix = glm::mat4(
                0,3,-2,0,
                -3,0,1,0,
                2,-1,0,0,
                0,0,0,1
            );
            auto crossMat = crossProductMatrix(testVec);
            REQUIRE(matricesEqual(crossMat, expectedMatrix));
            AND_THEN("The matrix acting on a vector evaluates to a proper cross product")
            {
                auto vecB = vector(1,1,1);
                auto expectedCrossProduct = vector(-1,2,-1);
                REQUIRE(vectorsEqual(crossMat * vecB, expectedCrossProduct));
            }
        }
    }
}

SCENARIO("Rotation Matrix", "[matrices]")
{
    GIVEN("A Rotation matrix about the X axis 180 degree")
    {
        auto rotMat = rotationMatrix(tracer::toRad(180), X_AXIS);
        THEN("The W dimension multiplyer should stay as 1, not negative one")
        {
            REQUIRE(rotMat[3].w == 1.0f);
        }
    }
    GIVEN("A vector <1,0,1>")
    {
        auto testVect = vector(1, 0, 1);
        THEN("General Rotation matrix can perform rotation about the x axis")
        {
            bool rotationTestPassed = true; //tracks if every rotation results in the correct vector
            auto rotMat = rotationMatrix(tracer::toRad(90), X_AXIS);
            glm::vec4 expectedVectors[] = {
                vector(1,-1,0),
                vector(1,0,-1),
                vector(1,1,0),
                vector(1,0,1),
            };

            //rotate the testVector about the x-axis 4 times and confirm it results in the right matrix
            for (int j = 0; j < 4; j++)
            {
                testVect = rotMat * testVect;
                if (!vectorsEqual(testVect, expectedVectors[j]))
                {
                    //if the actual rotation doesn't match the expected rotation, fail the test
                    rotationTestPassed = false;
                }
            }
            //Require that the four rotations 
            REQUIRE(rotationTestPassed);
        }
        THEN("General Rotation matrix can perform rotation about the y axis")
        {
            testVect = vector(1, 0, 1); //reset test vector
            bool rotationTestPassed = true; //tracks if every rotation results in the correct vector
            auto rotMat = rotationMatrix(tracer::toRad(90), Y_AXIS);
            glm::vec4 expectedVectors[] = {
                vector(1,0,-1),
                vector(-1,0,-1),
                vector(-1,0,1),
                vector(1,0,1),
            };

            //rotate the testVector about the x-axis 4 times and confirm it results in the right matrix
            for (int j = 0; j < 4; j++)
            {
                testVect = rotMat * testVect;
                if (!vectorsEqual(testVect, expectedVectors[j]))
                {
                    //if the actual rotation doesn't match the expected rotation, fail the test
                    rotationTestPassed = false;
                }
            }
            //Require that the four rotations 
            REQUIRE(rotationTestPassed);
        }
        THEN("General Rotation matrix can perform rotation about the z axis")
        {
            testVect = vector(1, 0, 1); //reset test vector
            bool rotationTestPassed = true; //tracks if every rotation results in the correct vector
            auto rotMat = rotationMatrix(tracer::toRad(90), Z_AXIS);
            glm::vec4 expectedVectors[] = {
                vector(0,1,1),
                vector(-1,0,1),
                vector(0,-1,1),
                vector(1,0,1),
            };

            //rotate the testVector about the x-axis 4 times and confirm it results in the right matrix
            for (int j = 0; j < 4; j++)
            {
                testVect = rotMat * testVect;
                if (!vectorsEqual(testVect, expectedVectors[j]))
                {
                    //if the actual rotation doesn't match the expected rotation, fail the test
                    rotationTestPassed = false;
                }
            }
            //Require that the four rotations 
            REQUIRE(rotationTestPassed);
        }
        THEN("General Rotation matrix can perform rotation about an arbitrary axis")
        {
            testVect = vector(1, 0, 1); //reset test vector
            bool rotationTestPassed = true; //tracks if every rotation results in the correct vector
            auto rotMat = rotationMatrix(tracer::toRad(90), testVect); //a revolution of a vector about itself should always result in the same vector
            //rotate the testVector about the x-axis 4 times and confirm it results in the right vector
            for (int j = 0; j < 4; j++)
            {
                testVect = rotMat * testVect;
                if (!vectorsEqual(testVect, vector(1,0,1)))
                {
                    //if the actual rotation doesn't match the expected rotation, fail the test
                    rotationTestPassed = false;
                }
            }
            //Require that the four rotations 
            REQUIRE(rotationTestPassed);
        }
    }
}

SCENARIO("Shearing Matrix", "[matrices]")
{
    GIVEN("given point p = (2,3,4)")
    {
        auto p = point(2, 3, 4);
        THEN("shearing (2,3,4) with xy=1 results in (5,3,4)")
        {
            auto transform = shearMatrix(1, 0, 0, 0, 0, 0);
            REQUIRE(vectorsEqual(transform * p, point(5, 3, 4)));
        }
        THEN("shearing (2,3,4) with xz=1 results in (6,3,4)")
        {
            auto transform = shearMatrix(0, 1, 0, 0, 0, 0);
            REQUIRE(vectorsEqual(transform * p, point(6, 3, 4)));
        }
        THEN("shearing (2,3,4) with yx=1 results in (2,5,4)")
        {
            auto transform = shearMatrix(0, 0, 1, 0, 0, 0);
            REQUIRE(vectorsEqual(transform * p, point(2,5,4)));
        }
        THEN("shearing (2,3,4) with yz=1 results in (2,7,4)")
        {
            auto transform = shearMatrix(0, 0, 0, 1, 0, 0);
            REQUIRE(vectorsEqual(transform * p, point(2, 7, 4)));
        }
        THEN("shearing (2,3,4) with zx=1 results in (2,3,6)")
        {
            auto transform = shearMatrix(0, 0, 0, 0, 1, 0);
            REQUIRE(vectorsEqual(transform * p, point(2, 3, 6)));
        }
        THEN("shearing (2,3,4) with zy=1 results in (2,3,7)")
        {
            auto transform = shearMatrix(0, 0, 0, 0, 0, 1);
            REQUIRE(vectorsEqual(transform * p, point(2, 3, 7)));
        }
    }
}

SCENARIO("Combining Transforms", "[matrices]")
{
    GIVEN("A translation matrix and a rotation matrix")
    {
        auto translate = geometry::translationMatrix(0, 1.0f, 1.0f);
        auto rotate = geometry::rotationMatrix(F_PI, X_AXIS);
        THEN("Translating a point at the origin to (0,1,1) and rotation by 180 degrees moves the point to (0,-1,-1)")
        {
            auto transform = rotate * translate;
            auto transformedPoint = transform * geometry::point(0, 0, 0);
            REQUIRE(vectorEqual(transformedPoint, geometry::point(0, -1.0f, -1.0f),0.001f));
        }
        THEN("Rotation a point at the origin by 180 degrees and translating to (0,1,1) moves the point to (0,1,1)")
        {
            auto transform = translate * rotate;
            auto transformedPoint = transform * geometry::point(0, 0, 0);
            REQUIRE(vectorEqual(transformedPoint, geometry::point(0, 1, 1),0.001f));
        }
    }
}