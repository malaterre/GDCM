I will try to organize the source tree as to separate what can be separated. 
For instance a DICOM Parser can existe without a full DICOM Implementation, 
e.g. be able to dump DICOM header without JPEG lib...

So far I have :
- Parser (PS5)
- ModuleAttributes (PS 3)
- Dicts (PS6)
- Reader (hate this name this is stupid)
- Writer (hate this name this is stupid)
Since DICOM is organized as Part 3 (IOD definition), Part 5 (data structures and encoding) and Part 6 (data dictionary)

Hopefully this is a good choice since reorganizing a cvs tree is just a pain...
svn rocks !
