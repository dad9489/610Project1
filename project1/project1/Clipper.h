///
//  Clipper.h
//
//  Simple module that performs clipping
//
//  Created by Warren R. Carithers on 02/27/14.
//  Last updated 2019/02/16 by wrc.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  David Dunlap
///

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "Types.h"

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
//
///
int clipPolygon( int num, const Vertex inV[], Vertex outV[],
                 Vertex ll, Vertex ur );
bool inside(Vertex pt, float x, float y, bool lookPositive);
Vertex intersection_point(Vertex start, Vertex end, float x, float y);
int clipBoundary(int num, const Vertex inV[], Vertex outV[], float x, float y, bool lookPositive);


#endif
