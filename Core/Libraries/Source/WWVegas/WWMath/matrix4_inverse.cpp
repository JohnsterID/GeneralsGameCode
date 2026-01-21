/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Matrix4x4::Inverse() implementation
 *
 * Based on Wine's D3DXMatrixInverse implementation from:
 * https://github.com/wine-mirror/wine/blob/master/dlls/d3dx9_36/math.c
 *
 * Original Wine code:
 * Copyright (C) 2008 David Adam
 * Copyright (C) 2008 Luis Busquets
 * Copyright (C) 2008 Jérôme Gardou
 * Copyright (C) 2008 Philip Nilsson
 * Copyright (C) 2008 Henri Verbeet
 *
 * Wine's math.c is licensed under LGPL 2.1+, which is compatible with GPL v3.
 * Adapted for use with WWMath Matrix4x4 class.
 */

#include "always.h"
#include "matrix4.h"

/**
 * Matrix4x4::Inverse_Wine() - Compute inverse of 4x4 matrix using Wine's algorithm
 *
 * This implementation uses cofactor expansion method, which is numerically
 * stable for general 4x4 matrices. It computes the inverse by:
 * 1. Computing cofactors of the matrix
 * 2. Calculating the determinant
 * 3. Dividing each cofactor by the determinant
 *
 * @param pout Pointer to output matrix (can be same as pm for in-place inversion)
 * @param pdeterminant Optional pointer to receive determinant value
 * @param pm Pointer to input matrix to invert
 * @return Pointer to output matrix, or NULL if matrix is singular (det == 0)
 */
Matrix4x4 Matrix4x4::Inverse_Wine(float* pdeterminant) const
{
    float det, t[3], v[16];
    unsigned i, j;
    
    // Access matrix elements via Row[row][col]
    // Wine uses m[row][col], we use Row[row][col]
    const Matrix4x4& pm = *this;
    Matrix4x4 pout;
    
    // Compute cofactors
    t[0] = pm.Row[2][2] * pm.Row[3][3] - pm.Row[2][3] * pm.Row[3][2];
    t[1] = pm.Row[1][2] * pm.Row[3][3] - pm.Row[1][3] * pm.Row[3][2];
    t[2] = pm.Row[1][2] * pm.Row[2][3] - pm.Row[1][3] * pm.Row[2][2];
    v[0] = pm.Row[1][1] * t[0] - pm.Row[2][1] * t[1] + pm.Row[3][1] * t[2];
    v[4] = -pm.Row[1][0] * t[0] + pm.Row[2][0] * t[1] - pm.Row[3][0] * t[2];

    t[0] = pm.Row[1][0] * pm.Row[2][1] - pm.Row[2][0] * pm.Row[1][1];
    t[1] = pm.Row[1][0] * pm.Row[3][1] - pm.Row[3][0] * pm.Row[1][1];
    t[2] = pm.Row[2][0] * pm.Row[3][1] - pm.Row[3][0] * pm.Row[2][1];
    v[8] = pm.Row[3][3] * t[0] - pm.Row[2][3] * t[1] + pm.Row[1][3] * t[2];
    v[12] = -pm.Row[3][2] * t[0] + pm.Row[2][2] * t[1] - pm.Row[1][2] * t[2];

    // Compute determinant using first row
    det = pm.Row[0][0] * v[0] + pm.Row[0][1] * v[4] +
        pm.Row[0][2] * v[8] + pm.Row[0][3] * v[12];
    
    if (det == 0.0f)
    {
        // Matrix is singular, cannot invert
        if (pdeterminant)
            *pdeterminant = 0.0f;
        return Matrix4x4(true); // Return identity matrix
    }
    
    if (pdeterminant)
        *pdeterminant = det;

    // Continue computing cofactors
    t[0] = pm.Row[2][2] * pm.Row[3][3] - pm.Row[2][3] * pm.Row[3][2];
    t[1] = pm.Row[0][2] * pm.Row[3][3] - pm.Row[0][3] * pm.Row[3][2];
    t[2] = pm.Row[0][2] * pm.Row[2][3] - pm.Row[0][3] * pm.Row[2][2];
    v[1] = -pm.Row[0][1] * t[0] + pm.Row[2][1] * t[1] - pm.Row[3][1] * t[2];
    v[5] = pm.Row[0][0] * t[0] - pm.Row[2][0] * t[1] + pm.Row[3][0] * t[2];

    t[0] = pm.Row[0][0] * pm.Row[2][1] - pm.Row[2][0] * pm.Row[0][1];
    t[1] = pm.Row[3][0] * pm.Row[0][1] - pm.Row[0][0] * pm.Row[3][1];
    t[2] = pm.Row[2][0] * pm.Row[3][1] - pm.Row[3][0] * pm.Row[2][1];
    v[9] = -pm.Row[3][3] * t[0] - pm.Row[2][3] * t[1] - pm.Row[0][3] * t[2];
    v[13] = pm.Row[3][2] * t[0] + pm.Row[2][2] * t[1] + pm.Row[0][2] * t[2];

    t[0] = pm.Row[1][2] * pm.Row[3][3] - pm.Row[1][3] * pm.Row[3][2];
    t[1] = pm.Row[0][2] * pm.Row[3][3] - pm.Row[0][3] * pm.Row[3][2];
    t[2] = pm.Row[0][2] * pm.Row[1][3] - pm.Row[0][3] * pm.Row[1][2];
    v[2] = pm.Row[0][1] * t[0] - pm.Row[1][1] * t[1] + pm.Row[3][1] * t[2];
    v[6] = -pm.Row[0][0] * t[0] + pm.Row[1][0] * t[1] - pm.Row[3][0] * t[2];

    t[0] = pm.Row[0][0] * pm.Row[1][1] - pm.Row[1][0] * pm.Row[0][1];
    t[1] = pm.Row[3][0] * pm.Row[0][1] - pm.Row[0][0] * pm.Row[3][1];
    t[2] = pm.Row[1][0] * pm.Row[3][1] - pm.Row[3][0] * pm.Row[1][1];
    v[10] = pm.Row[3][3] * t[0] + pm.Row[1][3] * t[1] + pm.Row[0][3] * t[2];
    v[14] = -pm.Row[3][2] * t[0] - pm.Row[1][2] * t[1] - pm.Row[0][2] * t[2];

    t[0] = pm.Row[1][2] * pm.Row[2][3] - pm.Row[1][3] * pm.Row[2][2];
    t[1] = pm.Row[0][2] * pm.Row[2][3] - pm.Row[0][3] * pm.Row[2][2];
    t[2] = pm.Row[0][2] * pm.Row[1][3] - pm.Row[0][3] * pm.Row[1][2];
    v[3] = -pm.Row[0][1] * t[0] + pm.Row[1][1] * t[1] - pm.Row[2][1] * t[2];
    v[7] = pm.Row[0][0] * t[0] - pm.Row[1][0] * t[1] + pm.Row[2][0] * t[2];

    v[11] = -pm.Row[0][0] * (pm.Row[1][1] * pm.Row[2][3] - pm.Row[1][3] * pm.Row[2][1]) +
        pm.Row[1][0] * (pm.Row[0][1] * pm.Row[2][3] - pm.Row[0][3] * pm.Row[2][1]) -
        pm.Row[2][0] * (pm.Row[0][1] * pm.Row[1][3] - pm.Row[0][3] * pm.Row[1][1]);

    v[15] = pm.Row[0][0] * (pm.Row[1][1] * pm.Row[2][2] - pm.Row[1][2] * pm.Row[2][1]) -
        pm.Row[1][0] * (pm.Row[0][1] * pm.Row[2][2] - pm.Row[0][2] * pm.Row[2][1]) +
        pm.Row[2][0] * (pm.Row[0][1] * pm.Row[1][2] - pm.Row[0][2] * pm.Row[1][1]);

    // Divide cofactors by determinant to get inverse
    det = 1.0f / det;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            pout.Row[i][j] = v[4 * i + j] * det;

    return pout;
}
