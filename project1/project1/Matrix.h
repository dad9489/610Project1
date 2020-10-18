///
///  Matrix.h
///
///  Created by David Dunlap on 2020/10/17.
///  Copyright 2020 Rochester Institute of Technology. All rights reserved.
///

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <tuple>

using namespace std;

///
/// Simple class used to represent a 3x3 square Matrix. It provides methods for multiplying by another Matrix or multiplying by a vector.
///
class Matrix {
    
private:
   
    /// Tuple representing matrix
    vector<vector<float>> mat;

    
public:

    ///
    /// Constructor
    ///
    ///
    Matrix();
    
    ///
    /// Constructor with values
    ///
    ///
    Matrix(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22);

    ///
    /// multiplyMat - Function to represent the multiplication of matricies.
    ///             Multiplies this matrix with the provided one and
    ///             returns a clean matrix as the result. Does not
    ///             modify this object.
    ///
    /// @param multMat - The matrix with which to multiply
    ///
    /// @return a new Matrix that is the multiplication of this matrix and the provided one
    ///
    Matrix* multiplyMat( Matrix* multMat );

    void populateMatrix(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22);

    ///
    /// multiplyVec - Function to represent the multiplication of this matrix
    ///             with a vector. The vector will be nx1. This function
    ///             returns a clean vector as the result.
    ///
    /// @param vec - The vector with which to multiply
    ///
    /// @return a new vector that is the multiplication of this matrix and the provided vector
    ///
    vector<float> multiplyVec( vector<float> vec );

};

#endif
