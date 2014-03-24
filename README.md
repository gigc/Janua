![Logo](https://raw.github.com/gigc/Janua/master/site/img/LogoJanua.png)    
# JANUA 
Accelerate your 3D scene using Janua!

Janua is an automatic portal and cell generator used to perform occlusion culling in 3D scenes.
Janua calculates the Potentially Visible Set (PVS) of the scene and saves it into a file that is queried at runtime.

## FEATURES
* Free and Open Source.
* Extremely low memory footprint.
* Supports up to 1 million occluders in the scene.
* Runtime component is in ANSI C, thus portable to virtually every platform.
* Preview the visibility data using the Janua Viewer.


## COMPONENTS

### Janua Preprocessor
Janua performs all the heavy visibility calculations offline. The programmer gives Janua all the scene polygons and models that exist in the 3D scene. This module divides the scene into regions and calculates which objects are visible from there.
 When finished, the visibility data is stored in very small file so it can be queried at runtime.

### Janua Runtime
The runtime is the tiny module that is executed in the 3D application in real-time. The engine provides a query interface, that returns which objects are potentially visible from a given region in the scene. It uses the visibility data pre calculated in the preprocessing stage.

## Frequently Asked Questions
Check out our [FAQ](https://github.com/gigc/Janua/wiki/FAQ)

## How to use it
Follow our [Tutorial](https://github.com/gigc/Janua/wiki/Tutorial)  and start using Janua now!




**Scene without Occlussion Culling**
All the models rendered from the red box region, however not all of them are visible from that perspective. Many models are Occluded and therefore not visible.
![screenshot1](https://raw.github.com/gigc/Janua/master/site/img/JanuaImg1.jpg).

**Scene with Janua Occlussion Culling**
Only the objects that are highly likely to be visible are considered for rendering. This speeds up the rendering process significantly.
![screenshot2](https://raw.github.com/gigc/Janua/master/site/img/JanuaImg2.jpg).


## LICENSE

The MIT License (MIT)
Copyright (c) 2013 Leandro Roberto Barbagallo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

