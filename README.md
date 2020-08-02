# I want to continue working on solys, but right know I lost track of what works and what not, so this readme might be complete trash, and the source code might be too

# solys
A 2D star system simulation

# How to install
## Linux
### Running it directly
You can try directly running the program in the `bin` folder

### Compiling it
* General
	* Automatically
		* Create a folder for solys, download the `install.sh` file, and put it inside
		* Open a terminal in that folder, and run `bash install.sh`
		* Follow the instructions from the script, and solys will be installed
	* Manually
		* Install all required dependencies using `sudo apt-get install <dependency-name>`
			* g++
			* libsfml-dev
		* Download all files as zip
		* Unpack the `.zip` file
		* Open a terminal in the folder where the `makefile` is in, and run `make`
		* Copy the created executable from `bin` to the directory where `data` is in, but not in `data`

# Changelog
## V1.2fr-alpha Jun 19 2020
* New features
	* Added the *Dear ImGui* lib to handle gui easily
	* Added a main menu using *Dear ImGui*
* Removed features
	* Removed my own gui "lib", solui
## V1.1b-alpha Jun 18 2020
* Bug fixes
	* **framerate-limit** setting now works
* New features
	* Added `install.sh` script to automatically install solys
## V1.0-alpha - Jun 15 2020
* The basics are done!
    * The physiys work
    * You can control the camera
    * You have a "menu"
