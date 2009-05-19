This is a stripped down version of polarssl (xyssl) 0.10.1. The BSD-license tarball.

I removed the application and the visual studio specific directories. I also removed the contrib directory (some ident shell script).
I had some issues with the *ASM part of the code on linux/gcc 4.1 so I simply changed the default config.h file to not do any ASM code. I also had to patch timing.c function. See report at:

[ timing.c / POLARSSL_HAVE_ASM ]
http://polarssl.org//?page=forum_view_topic&topic_id=14

CMakeLists.txt files replaced the Makefile for the build generator.

--
Mathieu Malaterre
Tue Mar 31 18:17:24 CEST 2009
