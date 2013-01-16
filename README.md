<h1>gauntcraft</h1>

A gauntlet styled minecraft inspired game. Currently it is using SDL but there is a chance it will move to OpenGL. It is programmed in C++.

<h2>To build</h2>

<h3>Windows</h3>

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
