# Simple ballistics hack

This is a very, very simple C implementation of a very low-tech
ballistics calculator.

I first wrote this program in 1994 when I started shooting high-power
rifle competitions, and was sick of having to boot DOS to run the free
ballistics calculator I had.

The method I implemented here is ancient:  the Siacci method.  It uses
tabulated ballistics data that is scaled for the ballistic coefficient
used.  I have tables here for G1 and G7 ballistic coefficients.  The
tables are interpolated to obtain time-of-flight to various distances
and from that bullet drop.

This is NOT a high-tech, modern ballistics calculator and would be
fairly useless for precision shooting solutions.

It is, however, plenty close enough for getting your initial guess at
sight settings for various differences given a good zero and good
measured muzzle velocities.

For best results, get good chronograph readings of your loads and
record the temperature and altitude at which you obtained them.  The
program will take optional arguments for the temperature and altitude
at which you want the charts printed.

## The main program, "simple"
The main program produced by the makefile is called "simple" (I was
very imaginative when I came up with this), and it takes command line
arguments:

 - -a followed by altitude in feet
 - -p followed pressure in inHg
 - -t followed by temperature in Farenheit
 - -v followed by muzzle velocity in feet per second
 - -c followed by ballistic coefficient
 - -r followed by max range in yards
 - -n followed by integer number of distances to compute
 - -h followed by height of the sight over bore (in inches)
 - -w followed by windspeed in MPH
 - -z followed by range in yards at which rifle was zeroed
 - -7 selects the G7 ballistics table instead of the default G1
 - -T followed by a quoted string sets a title for the load

The "loads" file contains example command lines some of my favorite
loads.

## an alternate program, "abt"
This stood for "awkable ballistic table", because back in 1994 I was
doing a lot of work writing simulation programs that had voluminous
output, and used to use formatting of special lines in that output
that could be picked out by the Unix utility "awk" for plotting.

`abt` was originally just a copy of `simple` with all the output
simplified. They have diverged, because I basically never use abt
anymore, and kept working on `simple` a little bit.


## On accuracy
While this is NOT suitable for computing precision shooting solutions,
I have compared its output to many other higher-precision ballistics
calculators that are available for free or for cheap all over the
place nowadays (like, on your phone).  I have found that the solutions
computed by this program for elevation and windage are usually within
a half to a quarter minute of angle of what the higher precision (and
much better) programs get.

So for a quick-and-dirty table to print out before heading out to the
range, `simple` will do the job.  Don't try to win any competitions by
expecting these tables to be perfect --- but they will be good enough
to let you get close so you can make up real dope tables with a
minimum number of shots.

## History
As I said, I wrote this in 1994 when I started trying to get serious
about high-power rifle competition, and only had access to a 200 yard
range on a regular basis.  I needed to be able to compute sight
adjustments for 300 and 600 yard shots before I headed out to
competitions, and this exercise got me there.

This stuff was originally written in K&R C, not ANSI C.  I updated it
in 2013 to what is roughly its current form.  Why?  Because between
1998 and 2013 I had stopped shooting high-power competitions, and in
2013 I started up again.  I wanted this program to work again.

I have occasionally considered rewriting this program to be less
cryptic and more modern, but why bother?  The method it implements
dates back to the 19th century, so why shouldn't the code look
ancient, too?

There is the beginnings of a LaTeX explanation of how this program
works, but I abandoned it almost as soon as I started it.  Don't even
bother building it, it's only a few paragraphs and doesn't explain
anything.  If you really want to understand what it's doing, any book
on exterior ballistics should explain the Siacci method (probably
right before they dismiss it as inadequate for modern needs and
explain more modern methods).  You can start your investigating on
[Wikipedia](https://en.wikipedia.org/wiki/Ballistic_coefficient#Mayevski-Siacci_method)


Oh, and in `drop.c` I make reference to "McShane, Kelly, and Reno".
This is a reference to the book "Exterior Ballistics" which is long
out of print, but may be found in digital,google-digitized form right
[here](https://babel.hathitrust.org/cgi/pt?id=mdp.39015040396205).
