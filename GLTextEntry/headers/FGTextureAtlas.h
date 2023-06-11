#ifndef FG_TEXTURE_ATLAS_H
#define FG_TEXTURE_ATLAS_H

#include <vector>
#include "vec234.h"
#include <assert.h>


struct texture_atlas_t
{
    std::vector<ivec3> nodes;

    unsigned short m_width;
    unsigned short m_height;
    unsigned short m_depth;
    unsigned short m_used;

    unsigned int m_id;
    unsigned char *m_data;
    unsigned char m_modified;

    void * m_special;

    texture_atlas_t(const unsigned short width, const unsigned short height, const unsigned short depth)
    {
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        ivec3 node = {1,1,width-2};
        assert( (depth == 1) || (depth == 3) || (depth == 4) );

        m_used = 0;
        m_width = width;
        m_height = height;
        m_depth = depth;
        m_id = 0;
        m_modified = 1;

        nodes.push_back(node);
        m_data = (unsigned char *)calloc( width*height*depth, sizeof(unsigned char) );
        
        assert(m_data != nullptr);

        special();
    }

    ivec4 get_region(const unsigned short width, const unsigned short height)
    {
        int y, best_index;
        size_t best_height, best_width;
        ivec3 *node, *prev;
        ivec4 region = {0,0,width,height};
        size_t i;

        best_height = UINT_MAX;
        best_index  = -1;
        best_width = UINT_MAX;

        for(i=0; i < nodes.size(); ++i)
        {
            y = fit(i, width, height);
            if(y >= 0)
            {
                node = &nodes[i];
                if( ( (y + height) < best_height ) ||
                ( ((y + height) == best_height) && (node->z > 0 && (size_t)node->z < best_width)) ) 
                {
                    best_height = y + height;
                    best_index = i;
                    best_width = node->z;
                    region.x = node->x;
                    region.y = y;
                }
            }
        }

        if( best_index == -1 )
        {
            region.x = -1;
            region.y = -1;
            region.z = 0;
            region.w = 0;
            return region;
        }

        ivec3 newnode;
        newnode.x = region.x;
        newnode.y = region.y + height;
        newnode.z = width;
        nodes.insert(nodes.begin()+best_index, newnode);

        for( i = best_index+1; i < nodes.size(); ++i )
        {
            node = &nodes[i];
            prev = &nodes[i-1];

            if (node->x < (prev->x + prev->z) )
            {
                    int shrink = prev->x + prev->z - node->x;
                    node->x += shrink;
                    node->z -= shrink;
                    if (node->z <= 0) {
                        nodes.erase(nodes.begin() + i);
                        --i;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
        }

        merge();
        m_used += width * height;
        m_modified = 1;    
        return region;


    }

    void special()
    {
        ivec4 region = get_region( 5, 5 );
        texture_glyph_t* glyph = texture_glyph_new( );
        static unsigned char data[4*4*3] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                                            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                                            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                                            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        if(region.x < 0)
        {
            return;
        }
        
        set_region( self, region.x, region.y, 4, 4, data, 0 );
        glyph->codepoint = -1;
        glyph->s0 = (region.x+2)/(float)self->width;
        glyph->t0 = (region.y+2)/(float)self->height;
        glyph->s1 = (region.x+3)/(float)self->width;
        glyph->t1 = (region.y+3)/(float)self->height;

        self->special = (void*)glyph;
    }

    void merge()
    {
        ivec3 *node, *next;
        size_t i;

        for( i=0; i< nodes.size()-1; ++i )
        {
            node = &nodes[i];
            next = &nodes[i+1];

            if( node->y == next->y )
            {
                node->z += next->z;
                nodes.erase(nodes.begin()+i+1);
                --i;
            }
        }
    }

    int fit(const size_t index, const size_t width, const size_t height)
    {
        ivec3 *node;
        int x, y, width_left;
        size_t i;

        node = &nodes[index];
        x = node->x;
        y = node->y;
        width_left = width;
        i = index;

        if ( (x + width) > (width-1) )
        {
            return -1;
        }

        while( width_left > 0 )
        {
            node = &nodes[i];
            if(node->y > y )
            {
                y = node->y;
            }
            if( (y + height) > (m_height-1) )
            {
                return -1;
            }
            width_left -= node->z;
            ++i;
        }
        return y;

    }

    

};



#endif