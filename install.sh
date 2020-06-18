#!/bin/bash

#	MIT LICENSE
# 
# 	Copyright (c) 2020 Kishimi
#		Contact:
# 			Anton Büttner
#			anton@green-pr.org
# 
#	Permission is hereby granted, free of charge, to any person obtaining a copy
#	of this software and associated documentation files (the "Software"), to deal
#	in the Software without restriction, including without limitation the rights
#	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#	copies of the Software, and to permit persons to whom the Software is
#	furnished to do so, subject to the following conditions:
#
#	The above copyright notice and this permission notice shall be included in all
#	copies or substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#	SOFTWARE.

# ASK FOR SUDO
[ "$UID" -eq 0 ] || exec sudo bash "$0" "$@"

echo
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo "%% Installing External Dependencies %%"
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo "-> g++"
echo "-> libsfml-dev"
echo "-> git"
echo "--------------"
read -p "Are you sure you want to continue? (y/n): " confirm
if [ $confirm != 'y' ]; then
	exit
fi

echo
echo "%%%%%%%%%%%%%%%%%%%%"
echo "%% Installing g++ %%"
echo "%%%%%%%%%%%%%%%%%%%%"
yes | sudo apt-get install g++;

echo
echo "%%%%%%%%%%%%%%%%%%%%%%"
echo "%% Installing SFML2 %%"
echo "%%%%%%%%%%%%%%%%%%%%%%"
yes | sudo apt-get install libsfml-dev

echo
echo "%%%%%%%%%%%%%%%%%%%%"
echo "%% Installing git %%"
echo "%%%%%%%%%%%%%%%%%%%%"
yes | sudo apt-get install git

echo
echo "%%%%%%%%%%%%%%"
echo "%% Updating %%"
echo "%%%%%%%%%%%%%%"
sudo apt-get update

echo
echo "%%%%%%%%%%%%%%%%%%%"
echo "%% Getting solys %%"
echo "%%%%%%%%%%%%%%%%%%%"
mkdir repo
cd repo
git clone https://github.com/Kishimi/solys.git

echo
echo "%%%%%%%%%%%%%%%%%%%%%"
echo "%% Compiling solys %%"
echo "%%%%%%%%%%%%%%%%%%%%%"
make

echo
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo "%% Move important files %%"
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%"
cd ../ # move out of the repo folder
# Copy important files out of repo

echo "cp -r repo/solys/data ./"
cp -r repo/solys/data ./

echo "cp repo/solys/bin/solys ./"
cp repo/solys/bin/solys ./

echo
echo "%%%%%%%%%%%%%%%%%%%%%%%%"
echo "%% Change permissions %%"
echo "%%%%%%%%%%%%%%%%%%%%%%%%"

# CHANGE OWNERS AND PERMISSIONS OF THE FILES

echo "chown -R $SUDO_USER:$SUDO_USER ./"
chown -R $SUDO_USER:$SUDO_USER ./

echo "chmod -R 777 ./"
chmod -R 777 ./

echo
echo "%%%%%%%%%%%%%%%%%"
echo "%% Cleaning up %%"
echo "%%%%%%%%%%%%%%%%%"
echo "rm -r repo"
rm -r repo					# delete the repo

echo
echo "DONE!"