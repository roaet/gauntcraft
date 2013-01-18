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
  <li><a href="http://code.google.com/p/google-glog/">google-glog</a>
  (<a href="http://google-glog.googlecode.com/svn/trunk/doc/glog.html">HOWTO</a>) 
  (<a href="http://code.google.com/p/google-glog/issues/detail?id=117">BUILD ISSUE</a>)
  (<a href="http://code.google.com/p/google-glog/issues/detail?id=94">WARNING ISSUE</a>)
  </li>
</ul>

<ol>
  <li>Open the VS solution</li>
  <li>Build</li>
</ol>

<h3>Linux</h3>

Depends (all of these are assumed to be installed to the system /usr/local):
<ul>
  <li>On ubuntu: sudo apt-get install cmake libjpeg-dev libpng12-dev libpng++-dev libboost1.50-all-dev freeglut3-dev zlib1g-dev </li>
  <li>SDL 1.2.15 <a href="http://www.libsdl.org/release/SDL-1.2.15.tar.gz">tar</a></li>
  <li>SDL_image <a href="http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12.tar.gz">tar</a></li>
  <li>SDL_image must be compiled with jpeg and png support (the apt above will get it)</li>
  <li>SDL_gfx <a href="http://www.ferzkopp.net/Software/SDL_gfx-2.0/SDL_gfx-2.0.24.tar.gz">tar</a></li>
  <li><a href="http://code.google.com/p/google-glog/">google-glog</a></li>
</ul>

<ol>
  <li>if the build directory exists, delete it</li>
  <li>In root git dir create subdir 'build'</li>
  <li>cd build</li>
  <li>cmake ..</li>
  <li>make</li>
</ol>

<h2>Resources</h2>
<ul>
  <li>The character sprite was taken from <a href="http://www.gdunlimited.net/forums/gallery/image/879-actor01/">gdunlimited</a></li>
  <li>The dirt tiles were taken from <a href="http://lpc.opengameart.org/static/lpc-style-guide/styleguide.html">open game art</a></li>
</ul>

<h2>Notes</h2>
<ul>
  <li>Was planning to use log4cxx but it was too annoying to build</li>
</ul>

