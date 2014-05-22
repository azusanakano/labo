#!/bin/sh
#--------------------------------------------------------------------------
#
#  Alternative Library
#
#
#  Copyright (C) 2007 - 2013 Azusa Nakano All Rights Reserved.
#
#  This program is released under term of the Apache License 2.0.
#  See details for http://www.apache.org/licenses/LICENSE-2.0
#
#---------------------------------------------------------------------------
function clean()
{
  rm -f debug/*.o
  rm -f libalt/debug/*.o
  rm -f test/debug/*.o
  rm -f test_echo_server/debug/*.o
  rm -f debug/*
  rm -f release/*.o
  rm -f libalt/release/*.o
  rm -f test/release/*.o
  rm -f test_echo_server/release/*.o
  rm -f release/*
}

function make_obj_debug()
{
  cat ../Makefile.header.debug > Makefile.debug
  cat Makefile.footer >> Makefile.debug
  make -f Makefile.debug
}

function make_obj_release()
{
  cat ../Makefile.header.release > Makefile.release
  cat Makefile.footer >> Makefile.release
  make -f Makefile.release 
}

function build()
{
  # build library
  cd libalt/altBase
  make_obj_debug;
  make_obj_release;
  cd ..

  cd altMisc
  make_obj_debug;
  make_obj_release;
  cd ..

  cd altNet
  make_obj_debug;
  make_obj_release;
  cd ..

  cd altDB
  make_obj_debug;
  make_obj_release;
  cd ..

  make_obj_debug;
  make_obj_release;
  cd ..

  # build test exe
  cd test/altBase
  make -f Makefile.debug
  make -f Makefile.release
  cd ..

  make -f Makefile.debug
  make -f Makefile.release
  cd ..

  # build echo server
  cd test_echo_server
  make -f Makefile.debug
  make -f Makefile.release
  cd ..

  # build echo client
  cd test_echo_client
  make -f Makefile.debug
  make -f Makefile.release
  cd ..

  # build ssl server
  cd ssl_echo_server
  make -f Makefile.debug
  make -f Makefile.release
  cd ..

  # build ssl client
  cd ssl_echo_client
  make -f Makefile.debug
  make -f Makefile.release
  cd ..
}

function check()
{
  if [ ! -f lib/test.exe ]; then
    build;
  fi
  cd debug
  gdb ./test.exe
}

if [ "$1" = "clean" ]; then
  clean;
elif [ "$1" = "rebuild" ]; then
  clean;
  build;
elif [ "$1" = "check" ]; then
  check;
else
  build;
fi
