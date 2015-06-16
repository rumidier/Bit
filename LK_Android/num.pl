#!/usr/bin/env perl

use 5.01;
use strict;

my $weight = 9548;
my $w_total = ($weight/14138);
my $slice = ($w_total * 600000);
my $w0_w = ($slice/434573);

printf("$weight | $w_total | $slice | $w0_w \n");
