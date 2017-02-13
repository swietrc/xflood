<div style="text-align: center"><img src="http://img15.hostingpics.net/pics/908468Xfloodlogo.png" width=400 height=400 align="middle"></div>

##Project Description

The goal of this project is to reproduce [this game](https://play.google.com/store/apps/details?id=com.wetpalm.colorflood&hl=en)

![color Flood game image](http://www.appscrawler.com/application/ScreenShotImageAction.do?appId=107888&imageId=0)

... and to create a solver for the game that will give the best color suite to play in order to finish the game as fast as possible.

##How to build and execute the program

If it's not already installed, install the common build tools (it includes "make")
```bash
$ sudo apt-get install build-essential
```


You also need to install [the SDL library](https://www.libsdl.org/),
If you are on a debian-like OS, you can install it directly from the repositories :
```bash
$ sudo apt-get install libsdl2-dev
```

Then, just go to the root folder of the project and compile the program with make :
```bash
$ make
```

This will generate the program which can be executed like so :

```bash
$ ./XFlood
```

##How to run unit tests

You first need to install [the CUnit test framework](http://cunit.sourceforge.net/).
If you are on a debian-like OS, you can install it directly from the repositories :
```bash
$ sudo apt-get install libcunit1-dev
```

To run all the tests :

```bash
$ make tests
$ ./tests
```