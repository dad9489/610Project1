//
//  Matrix.cpp
//  project1
//
//  Created by David Dunlap on 10/17/20.
//  Copyright © 2020 David Dunlap. All rights reserved.
//

#include "Matrix.h"

Matrix::Matrix()
{
    // populate the 3x3 matrix with the identity
    populateMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

Matrix::Matrix(int v00, int v01, int v02, int v10, int v11, int v12, int v20, int v21, int v22)
{
    populateMatrix(v00, v01, v02, v10, v11, v12, v20, v21, v22);
}

void Matrix::populateMatrix(int v00, int v01, int v02, int v10, int v11, int v12, int v20, int v21, int v22)
{
    vector<float> col1;
    vector<float> col2;
    vector<float> col3;
    
    col1.push_back(v00);
    col1.push_back(v01);
    col1.push_back(v02);
    
    col2.push_back(v10);
    col2.push_back(v11);
    col2.push_back(v12);
    
    col3.push_back(v20);
    col3.push_back(v21);
    col3.push_back(v22);
    
    mat.push_back(col1);
    mat.push_back(col2);
    mat.push_back(col1);
}

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
Matrix* Matrix::multiplyMat( Matrix* multMat )
{
    Matrix* res = new Matrix();
    
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            res->mat[i][j] = 0;
            for (k = 0; k < 3; k++)
                res->mat[i][j] += this->mat[i][k] * multMat->mat[k][j];
        }
    }
    
    return res;
}

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
Matrix* Matrix::multiplyVec( tuple<float, float, float> vec ) {
    // TODO implement
    return new Matrix();
}
