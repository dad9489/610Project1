///
///  Matrix.h
///
///  Created by David Dunlap on 2020/10/17.
///  Copyright 2020 Rochester Institute of Technology. All rights reserved.
///

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

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
    
    void populateMatrix(int v00, int v01, int v02, int v10, int v11, int v12, int v20, int v21, int v22);

    
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
    Matrix(int v00, int v01, int v02, int v10, int v11, int v12, int v20, int v21, int v22);

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
    
    ///
    /// multiplyVec - Function to represent the multiplication of this matrix
    ///             with a vector. The vector will be nx1. This function
    ///             returns a clean matrix as the result. Does not
    ///             modify this object.
    ///
    /// @param vec - The vector with which to multiply
    ///
    /// @return a new Matrix that is the multiplication of this matrix and the provided vector
    ///
    Matrix* multiplyVec( tuple<float, float, float> vec );

};

#endif
