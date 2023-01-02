all: build
	./.build/AvlTree

build:
	gcc AvlTree.c -o .build/AvlTree