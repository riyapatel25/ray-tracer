# ray-tracer

- fixed camera a 0,0,0 
- view port is where we shoot the rays through (basically the screen) 
- for each pixel"
    - compute the 3D position on viewport that center of pixel maps to
    - shoot a ray from the camera towards that point
    - check what it hits (using quadratic equation for sphere)
    - color based on hit or not