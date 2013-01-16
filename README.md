<h1>gauntcraft</h1>

A gauntlet styled minecraft inspired game. Currently it is using SDL but there is a chance it will move to OpenGL. It is programmed in C++.

<h2>Current Status</h2>
<img src="http://roaet.com/images/gauntcraft_001.png"/>

Basic tile engine with 'infinite scrolling' support.
<h2>Next steps</h2>
<ul>
  <li>Network infrastructure</li>
  <li>Further engine improvements</li>
</ul>
<h2>To build</h2>

<h3>Windows</h3>
Building on Windows does not use cmake. cmake is primarily for Linux and variants.

Depends:
<ul>
  <li>Boost</li>
  <li>SDL 1.2.15</li>
  <li>SDL_image</li>
  <li>SDL_gfx</li>
  <li>zlib</li>
</ul>

<ol>
  <li>Open the VS solution</li>
  <li>Build</li>
</ol>

<h3>Linux</h3>

Depends:
<ul>
  <li>Boost</li>
  <li>SDL 1.2.15</li>
  <li>SDL_image</li>
  <li>SDL_image must be compiled with jpeg and png support</li>
  <li>SDL_gfx</li>
  <li>zlib</li>
</ul>

<ol>
  <li>In root git dir create subdir 'build'</li>
  <li>cd build</li>
  <li>cmake ..</li>
  <li>make</li>
  <li>you may need to copy the assets directory where the executable was placed</li>
</ol>

<h2>Resources</h2>
<ul>
  <li>The character sprite was taken from <a href="http://www.gdunlimited.net/forums/gallery/image/879-actor01/">gdunlimited</a></li>
  <li>The dirt tiles were taking from <a href="http://lpc.opengameart.org/static/lpc-style-guide/styleguide.html">open game art</a></li>
</ul>

