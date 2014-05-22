#!/bin/bash
#
# Create new rails application
#
# copyright (C) 2014 Azusa Nakano
#

echo "------------------------------------"
echo "Create new Rails application"
echo "------------------------------------"

printf "enter application name:"
read appname

if [ "$appname" = "" ]; then
  echo "no application name. exit."
  exit
fi

while [ "$ret" = "" ]; do
  printf "aplication name is [$appname]?[y/N]:"
  read ret
done

if [ "$ret" != "y" ]; then
  echo "exit."
  exit
fi

rails new $appname --database=mysql

