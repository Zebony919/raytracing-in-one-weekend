# Raytracing-in-one-weekend
A three-book series that takes you through building a fully functioning ray-tracing renderer. While TinyRenderer built images by rasterizing pre-made models placed in world space, 
this ray tracer calculates each pixel by shooting a ray from the camera and checking whether it intersects any objects defined in the scene. When it does, the hit object's material 
determines how the ray behaves: Lambertian materials randomly scatter the ray in a direction weighted toward the surface normal (absorbing some color at each bounce), Metal materials 
reflect it more directly, and Dielectric materials reflect or refract it based on viewing angle (via Schlick's approximation), bending refracted rays according to Snell's law.

I've currently completed the first book, which builds the core renderer: sphere intersection, the three materials above, multi-sample anti-aliasing, and an adjustable, 
positionable camera with defocus blur (depth of field). Many of the underlying techniques (vector math, coordinate transforms) build directly on what I learned in TinyRenderer. 
I plan to continue with the remaining two books, which cover more advanced techniques like acceleration structures, textures, and Monte Carlo integration theory.

# Some renderings from my Ray tracer
<img width="803" height="451" alt="Screenshot 2026-09-18 154549" src="https://github.com/user-attachments/assets/86fb1828-08c8-4613-bb28-ead0ffe62da3" />
<img width="803" height="452" alt="Screenshot 2026-09-18 153351" src="https://github.com/user-attachments/assets/13d53feb-106c-4584-8ee2-6087ca85f60f" />
<img width="798" height="450" alt="Screenshot 2026-09-18 154928" src="https://github.com/user-attachments/assets/4d3c6a68-55bb-4ad7-9e8f-29f65d508d63" />
