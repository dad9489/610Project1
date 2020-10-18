///
///  Pipeline.cpp
///
///  Created by Warren R. Carithers on 2016/10/19.
///  Based on a version created by Joe Geigel on 11/30/11.
///  Updates: 2019/02/25, 2019/10/01 by wrc.
///  Copyright 2019 Rochester Institute of Technology. All rights reserved.
///
///  Contributor:  David Dunlap
///

#include <iostream>
#include <math.h>

#include "Pipeline.h"
#include "Clipper.h"
#include "Matrix.h"

///
/// Simple wrapper class for midterm assignment
///
/// Only methods in the implementation file whose bodies
/// contain the comment
///
///    // YOUR IMPLEMENTATION HERE
///
/// are to be modified by students.
///

///
/// Constructor
///
/// @param w width of canvas
/// @param h height of canvas
///
Pipeline::Pipeline( int w, int h ) : Canvas(w,h)
    // YOUR IMPLEMENTATION HERE if you need to add initializers
{
    rasterizer = new Rasterizer( w, *this );
    transformMatrix = new Matrix();
}

///
/// addPoly - Add a polygon to the canvas.  This method does not draw
///           the polygon, but merely stores it for later drawing.
///           Drawing is initiated by the drawPoly() method.
///
///           Returns a unique integer id for the polygon.
///
/// @param n - Number of vertices in polygon
/// @param p - Array containing the vertices of the polygon to be added.
///
/// @return a unique integer identifier for the polygon
///
int Pipeline::addPoly( int n, const Vertex p[] )
{
    polygons.push_back(make_pair(n, p));
    int id = (int)polygons.size()-1;
    return id;
}

///
/// drawPoly - Draw the polygon with the given id.  The polygon should
///            be drawn after applying the current transformation to
///            the vertices of the polygon.
///
/// @param polyID - the ID of the polygon to be drawn.
///
void Pipeline::drawPoly( int polyID )
{
    pair<int, const st_vertex*> polyData = polygons[polyID];
    int n = polyData.first;
    const st_vertex* v = polyData.second;
    
//    Vertex polygons_mod[n];
    Vertex *polygons_mod;
    polygons_mod = (Vertex*)malloc(n*sizeof(*polygons_mod));

    for (int i = 0; i < n; i++) {
//        Vertex p = v[i];
//        vector<float> coords = {p.x, p.y, p.z};
//        vector<float> res = this->transformMatrix->multiplyVec(coords);
//        Vertex res_v;
//        res_v.x = res[0];
//        res_v.y = res[1];
//        res_v.z = res[2];
//        polygons_mod[i] = res_v;
        Vertex p = v[i];
        vector<float> coords = {p.x, p.y, p.z};
        vector<float> res = coords;
        Vertex res_v;
        res_v.x = res[0];
        res_v.y = res[1];
        res_v.z = res[2];
        polygons_mod[i] = res_v;
    }

    Vertex tmp[50];
    Vertex *polygons_clip;
    int new_n = clipPolygon(n, polygons_mod, tmp, clipWindowLL, clipWindowUR );
    
    polygons_clip = (Vertex*)malloc(new_n*sizeof(*polygons_clip));
    for (int i = 0; i < new_n; i++)
        polygons_clip[i] = tmp[i];
    
    cout << "----------------\n";
    for (int i = 0; i < n; i++) {
        Vertex p = polygons_clip[i];
        cout << "x: " << p.x;
        cout << " | y: " << p.y << "\n";
    }

    rasterizer->drawPolygon(new_n, polygons_clip);
}

///
/// clearTransform - Set the current transformation to the identity
///            matrix.
///
void Pipeline::clearTransform( void )
{
    transformMatrix = new Matrix();
}

///
/// translate - Add a translation to the current transformation by
///             premultiplying the appropriate translation matrix to
///             the current transformation matrix.
///
/// @param tx - Amount of translation in x.
/// @param ty - Amount of translation in y.
///
void Pipeline::translate( float tx, float ty )
{
    Matrix* translateMatrix = new Matrix(1, 0, 0, 0, 1, 0, tx, ty, 1);
    this->transformMatrix = transformMatrix->multiplyMat(translateMatrix);
}

///
/// rotate - Add a rotation to the current transformation by premultiplying
///          the appropriate rotation matrix to the current transformation
///          matrix.
///
/// @param degrees - Amount of rotation in degrees.
///
void Pipeline::rotate( float degrees )
{
    float theta = degrees * (M_PI / 180.0);
    Matrix* rotateMatrix = new Matrix(cos(theta), sin(theta), 0, -1*sin(theta), cos(theta), 0, 0, 0, 1);
    this->transformMatrix = transformMatrix->multiplyMat(rotateMatrix);
}

///
/// scale - Add a scale to the current transformation by premultiplying
///         the appropriate scaling matrix to the current transformation
///         matrix.
///
/// @param sx - Amount of scaling in x.
/// @param sy - Amount of scaling in y.
///
void Pipeline::scale( float sx, float sy )
{
    Matrix* scaleMatrix = new Matrix(sx, 0, 0, 0, sy, 0, 0, 0, 1);
    this->transformMatrix = transformMatrix->multiplyMat(scaleMatrix);
}

///
/// setClipWindow - Define the clip window.
///
/// @param bottom - y coord of bottom edge of clip window (in world coords)
/// @param top - y coord of top edge of clip window (in world coords)
/// @param left - x coord of left edge of clip window (in world coords)
/// @param right - x coord of right edge of clip window (in world coords)
///
void Pipeline::setClipWindow( float bottom, float top, float left, float right )
{
    clipWindowLL.x = left;
    clipWindowLL.y = bottom;
    clipWindowUR.x = right;
    clipWindowUR.y = top;
}

///
/// setViewport - Define the viewport.
///
/// @param x - x coord of lower left of view window (in screen coords)
/// @param y - y coord of lower left of view window (in screen coords)
/// @param w - width of view window (in pixels)
/// @param h - width of view window (in pixels)
///
void Pipeline::setViewport( int x, int y, int w, int h )
{
    // YOUR IMPLEMENTATION HERE
}
