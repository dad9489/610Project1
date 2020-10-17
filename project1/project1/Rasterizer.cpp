///
//  Rasterizer.cpp
//
//  Simple module that provides rasterization algorithms
//
//  Created by Joe Geigel on 11/30/11.
//  Updates: 2019/02/09, 2019/09/14 by wrc.
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  David Dunlap
///

#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include "Types.h"
#include "Rasterizer.h"
#include "Canvas.h"

using namespace std;

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}

typedef struct st_bucket {
   float y_max;
   float x;
   float inv_m;
} Bucket;


vector<vector<Bucket > > add_edge_to_table(vector<vector<Bucket > > edge_table, Vertex p1, Vertex p2) {
    float y_max;
    float y_min;
    float x;
    if(p1.y > p2.y) {
        y_max = p1.y;
        y_min = p2.y;
        x = p2.x;
    } else {
        y_max = p2.y;
        y_min = p1.y;
        x = p1.x;
    }
    if(p1.y != p2.y) {
        float inv_m = (p1.x - p2.x) / (p1.y - p2.y);
        Bucket bucket;
        bucket.y_max = y_max;
        bucket.x = x;
        bucket.inv_m = inv_m;
        edge_table[y_min].push_back(bucket);
    }
    return edge_table;
}

bool compare_buckets(const st_bucket &a, const st_bucket &b)
{
    if(a.x != b.x) {
        return a.x < b.x;
    }
    return a.inv_m < b.inv_m;
}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are supplied in the 'v' array parameter, such
// that the ith vertex is in v[i].
//
// You are to add the implementation here using only calls to the
// addPixel() function.
//
// @param n - number of vertices
// @param v - array of vertices
///
void Rasterizer::drawPolygon( int n, const Vertex v[] )
{
    cout<<"Drawing new polygon...\n";
    vector<vector<Bucket > > edge_table;

    // Populate the edge table with empty lists for all scan lines
    for (int i = 0; i < n_scanlines; i++)
        edge_table.push_back(vector<Bucket>());

    // Create the edge table
    for (int i = 0; i < n-1; i++) {
        Vertex p1 = v[i];
        Vertex p2 = v[i + 1];
        edge_table = add_edge_to_table(edge_table, p1, p2);
    }
    Vertex p1 = v[n-1];
    Vertex p2 = v[0];
    edge_table = add_edge_to_table(edge_table, p1, p2);

    vector<Bucket> active_list;
    for (int y = 0; y < n_scanlines; y++) {
        
        //Discard entries from active list where y = y_max
        active_list.erase(std::remove_if(active_list.begin(), active_list.end(), [y](Bucket bucket){
            return bucket.y_max == y;
        }), active_list.end());
        
        if(edge_table[y].size() > 0) {

            //Move all buckets from ET[y] to AL
            vector<Bucket > et_y = edge_table[y];
            for(int i=0; i < et_y.size(); i++){
                Bucket bucket = et_y[i];
                active_list.push_back(bucket);
            }

            //Sort active list
            std::sort(active_list.begin(), active_list.end(), compare_buckets);
        }

        if(active_list.size() > 0) {
            
            //Fill pixels according to active list
            for (int i = 0; i < active_list.size(); i++) {
                if (i % 2 == 0) {
                    int begin_pxl = ceil(active_list[i].x);
                    int end_pxl = floor(active_list[i + 1].x);

                    Vertex drawn_pxl;
                    for (int x = begin_pxl; x <=end_pxl; x++) {
                        drawn_pxl.x = x;
                        drawn_pxl.y = y;
                        drawn_pxl.z = 0;
                        drawn_pxl.w = 0;
                        C.addPixel(drawn_pxl);
                    }
                }
            }
            
            // For each non-vertical edge in the active list increment x by inverse slope
            for (int i = 0; i < active_list.size(); i++) {
                Bucket bucket = active_list[i];
                bucket.x += bucket.inv_m;
                active_list[i] = bucket;
            }
        }
    }

}
