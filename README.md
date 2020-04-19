# How to run programs

# Requirements
## Docker
Install docker [here](https://docs.docker.com/install/)

## Octave (Optional, if you want to view the final image)
Install octave [here](https://www.gnu.org/software/octave/download.html)

## Creating docker image
### Step 1: Build the docker image
NOTE: Make sure you are on the root directory

To build the image, perform the following command 
`docker build . -t asn3`

### Step 2: Run the docker container
To run the container on your system run the following command
`docker run --rm -v ${PWD}:/app -it asn3 /bin/bash`

### Step 3: Head into the directory contiaing 
Once you are in the docker container, to head into the source code perform the following command
`cd app`


## Running Cellular Automata
### Step 1: Jump into the build directory
To run the part 1 algorithm, you would have to go into the directory `build`

### Step 2: Prepare to create an executable using CMAKE
Next you would need to build the project using CMAKE
`cmake ..`

### Step 3: Create an executable for Part 1
Now you would have to create the executable file
`make`

### Step 4: Run program
`./ASN3/ASN3`

## View Results as an image (Optional)
### Step 1: Convert image to .dat format
At the end of the program there will be a file called `ans.txt`,
and this file contains best individual's current state. We have to convert this
to a readable format to be displayed by octave. 
`python3 parser.py`

After this there will be a new file named `test.dat` on the `build` folder

### Step 2: Get out of docker
Open a separate console that is on your local machine and not docker

### Step 2: Open octave
`octave --no-gui`

If you see the following, you can go to the next step
`octave:1> `

### Step3: Display image
`im = dlmread("test.dat"); imshow(im)`