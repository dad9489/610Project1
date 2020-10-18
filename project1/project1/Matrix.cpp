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

Matrix::Matrix(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
    populateMatrix(v00, v01, v02, v10, v11, v12, v20, v21, v22);
}

void Matrix::populateMatrix(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
    vector<float> col1 {v00, v01, v02};
    vector<float> col2 {v10, v11, v12};
    vector<float> col3 {v20, v21, v22};

    mat.push_back(col1);
    mat.push_back(col2);
    mat.push_back(col3);
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
vector<float> Matrix::multiplyVec( vector<float> vec ) {
    
    vector<float> res(3, 0);
    
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            float val = (this->mat[j][i]*vec[j]);
            res[i]+=val;
        }
    }
    
    return res;
}
