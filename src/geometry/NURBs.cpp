//will be a class file for nurbs curve and eventually nurbs surface

//what is required: 
// sample along the interval
// when created tell how many control points and degree of curve, this will set the knot vector
// default control points to <0,0,0,1> (point at origin) and knot vector padded appropriately so it is clamped at both ends 
// good addition would creating new control points between original control points but that would require updating the object OR keeping control points in a std::vector
//	which hey, we're not doing matrix math with this, may as well
// once nurbs curves are defined, will need to be able to extend it to a nurbs surface
// Also need to figure out how do to ray-nurbs intersections look at that paper https://www.cs.utah.edu/~shirley/papers/raynurbs.pdf