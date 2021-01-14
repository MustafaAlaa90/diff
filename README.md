# diff
diff is a simple Application to detect the difference between two text file
it Generates a report of the difference in line numbers , file size and mismatch line numbers
for example
file1.txt is as follows

line1
line2
line3
line4

file2.txt is as follows

line1
line2 modified
line3 modified
line4
line5 added

diff will generate the following report
-------------------------------------------------------------------------------------------------------
File Path            | input1.txt                               | input2.txt                          |
-------------------------------------------------------------------------------------------------------
Number of lines      | 4                                        | 5                                    |
--------------------------------------------------------------------------------------------------------
File Size (Bytes)    | 24                                       | 54                                   |
--------------------------------------------------------------------------------------------------------
mismach found at lines : 2 3 5 
--- input1.txt 15-01-21 00:23:38
+++ input2.txt 15-01-21 00:23:38
line1
-line2
+line2 modified
-line3
+line3 modified
line4
-line5 added

### how to build
diff is built by autotools, please make sure that you have
auotoconf and libtool installed on your linux machine
sudo apt-get install autoconf
sudo apt-get install libtool

cd diff/
. ./conf_script --dev  // this will build the application for development and provided by default
make
cd src
diff_app is the application name in diff/build/src

you need to provide two exist input files
for example
./diff_app ./inputfile1.txt ./inputfile2.txt
you may need the results in an output file type the following
./diff_app ./inputfile1.txt ./inputfile2.txt ./outfile.txt

Note : the code is compiled by any compiler installed on a linux machine

### Tests
there is a simple test writtent inside the application source code
you need to run the following
. ./conf_script --utest
this will build the application for test
cd src
./diff_app
it should write the results on the console and a print message with Test[Ok]

### Notes
diff app doesn't check the file formats for example if you provided text and binary executable it will check them and result a report but it may produce un accurate or not user-friendly result