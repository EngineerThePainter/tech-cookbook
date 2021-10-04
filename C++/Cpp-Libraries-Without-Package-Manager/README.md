

### Add library as a git submodule

First start with adding a git submodule that will point to the git repository (if you wish you can just download it as well, but this way you can easily change version if required).

`git submodule add` 'link to library' for example: 'git@github.com:google/googletest.git'

Then just from the directory just go and go to the branch/tag with desired release.

Then you can just add include it to be built as a part of your project - see `CMakeLists.txt` in the root directory.