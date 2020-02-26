#!/bin/sh

# CFLAGS=-std=c99
CFLAGS=-D\ LIB
TARGET=hello

gcc $CFLAGS main.c lib.c -o $TARGET
