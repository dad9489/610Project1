///
//  Clipper
//
//  Simple module that performs clipping
//
//  Created by Warren R. Carithers on 01/15/14.
//  Updates: 2019/02/16, 2019/09/17 by wrc.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  David Dunlap
///

#ifdef __cplusplus
using namespace std;
#else
#include <stdbool.h>
#endif

#include "Types.h"
#include "Clipper.h"

#include <iostream>
#include <cmath>


// Calculates if a point is inside a boundary. A boundary is defined
// with x and y. Since all boundary edges are straight lines, they can
// be defined as either a single x value or a single y value. Therefore
// we can assume that one of either x or y will be -1, indicating that
// the other value is to be used. lookPositive indicates where "inside" is
// in respect to this boundary. If it is true, inside is in the positive
// x or y direction, if it is false it is in the negative direction.
bool inside(Vertex pt, float x, float y, bool lookPositive) {
    if(x != -1) {
        // The boundary is vertical, use the x value
        if(lookPositive) {
            return pt.x > x;
        } else {
            return pt.x < x;
        }
    } else {
        // The boundary is horizontal, use the y value
        if(lookPositive) {
            return pt.y > y;
        } else {
            return pt.y < y;
        }
    }
}


// Given start and end verticies and a boundary, finds the
// intersection point of that edge with that boundary. A boundary is defined
// with x and y, one of which will be -1 indicating that the boundary is
// defined by the other axis.
Vertex intersection_point(Vertex start, Vertex end, float x, float y) {
    Vertex output;
    
    if(start.x == end.x) {
        // we have a vertical line (undefined slope)
        output.x = start.x;
        output.y = y;
    } else {
        float m = (end.y - start.y) / (end.x - start.x);
        float b = (-1 * (start.x * m)) + start.y;
        if(x != -1) {
            // The boundary is horizontal
            float n = x;
            output.y = (-1 * m * (start.x - n)) + start.y;
            output.x = x;
        } else {
            // The boundary is vertical
            float n = y;
            output.x = ((-1 * b) + n) / m;
            output.y = y;
        }
    }
    return output;
}

int clipBoundary(int num, const Vertex inV[], Vertex outV[], float x, float y, bool lookPositive) {
    Vertex pred = inV[num - 1];
    int outLength = 0;
    for (int i = 0; i < num; i++) {
        Vertex succ = inV[i];
        if(inside(succ, x, y, lookPositive)) {  // Cases 1 and 4
            if(inside(pred, x, y, lookPositive)) {  // Case 1
                outV[outLength] = succ;
                outLength += 1;
            } else {  // Case 4
                Vertex intersect = intersection_point(pred, succ, x, y);
                outV[outLength] = intersect;
                outLength += 1;
                outV[outLength] = succ;
                outLength += 1;
            }
        } else {  // Cases 2 and 3
            if(inside(pred, x, y, lookPositive)) {  // Case 2
                Vertex intersect = intersection_point(pred, succ, x, y);
                outV[outLength] = intersect;
                outLength += 1;
            }  // Case 3 does nothing
        }
        
        pred = succ;
    }
    return outLength;
}

///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param num   the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
///
int clipPolygon( int num, const Vertex inV[], Vertex outV[],
                 Vertex ll, Vertex ur ) {
    Vertex cleanOutV1[num];
    Vertex cleanOutV2[num];
    Vertex cleanOutV3[num];
    num = clipBoundary(num, inV, cleanOutV1, ur.x, -1, false);  // clip to right edge
    num = clipBoundary(num, cleanOutV1, cleanOutV2, -1, ur.y, false);  // clip to upper edge
    num = clipBoundary(num, cleanOutV2, cleanOutV3, ll.x, -1, true);  // clip to left edge
    num = clipBoundary(num, cleanOutV3, outV, -1, ll.y, true);  // clip to bottom edge

    return( num );  // remember to return the outgoing vertex count!
}
