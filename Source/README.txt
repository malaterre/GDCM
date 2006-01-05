I will try to organize the source tree as to separate what can be separated. For instance a DICOM Parser can existe without a full DICOM Implementation, eg be able to dump DICOM header without JPEG lib...

So far I have :
- Parser
- Reader
- Writer

Hopefully this is a good choice since reorganizing a cvs tree is just a pain...svn rocks !
