#pragma once
#ifndef S21_CAT_H
#define S21_CAT_H
#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int T;
  int t;
  int v;
} flag;

void init_flags(flag *flag);
void check_flags(int argc, char **argv, flag *flag);
void cat_no_arg();
void print(int argc, char *argv[], const flag *flag);

extern int optind, opterr, optopt;

#endif  // S21_CAT_H
