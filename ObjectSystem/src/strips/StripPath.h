//
// Created by Ethan Horowitz on 11/13/23.
//

#ifndef SIMLED_STRIPPATH_H
#define SIMLED_STRIPPATH_H

/// @brief A class that forms a path through a strip. It rearranges the number line to follow the specified path.
class StripPath {
private:
    int segments;
    int length;
    int* path;
public:
    /// @brief Creates a new StripPath object
    /// @param segments the number of segments in the path
    /// @param path the path to follow. Consists of groups of two numbers, specifying the start (inclusive) and end (exclusive) of a path segment. Segments can go in positive or negative order. ex: {0, 5, 15, 10} corresponds to [0, 1, 2, 3, 4, 15, 14, 13, 12, 11]
    StripPath(int segments, int* path);

    /// @brief Gets the segments of the strip
    /// @return the segments of the strip
    int getLength() { return length;}

    int numSegments() { return segments; }

    /// @brief Gets the index of the path at the specified index
    /// @param index the index to get the path at
    /// @return the index of the path at the specified index
    int get(int index, bool loop = false);
};


#endif //SIMLED_STRIPPATH_H
