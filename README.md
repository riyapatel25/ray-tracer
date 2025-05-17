# ray-tracer

Overview
- fixed camera a 0,0,0 
- view port is where we shoot the rays through (basically the screen) 
- for each pixel"
    - compute the 3D position on viewport that center of pixel maps to
    - shoot a ray from the camera(0,0,0) towards that pixel
    - check what it hits (using quadratic equation for sphere)
    - color based on hit or not


Variables
- each ray represnted as A + tB 
- A = origin vector, t scalar, B direction
- C = center of sphere 
- r = radius of sphere

Math
- plug in sphere equation [(P-C)^2 = r^2 ]to ray -> at^2 +bt+c=0
- solve quad format

